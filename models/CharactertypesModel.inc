<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\models;


    /**
     * Model to interact with Charactertypes-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactertypesModel extends \hhu\z\Model
    {




        /**
         * Construct a new CharactertypesModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get all Character types of a Seminary.
         *
         * @param   int     $seminaryId ID of Seminary to get types of
         * @return  array               Character types
         */
        public function getCharacterTypesForSeminary($seminaryId)
        {
            return $this->db->query(
                'SELECT id, seminary_id, name, url '.
                'FROM charactertypes '.
                'WHERE seminary_id = ? '.
                'ORDER BY name ASC',
                'i',
                $seminaryId
            );
        }


        /**
         * Get Character type by its URL.
         *
         * @param   int     $seminaryId         ID of Seminary
         * @param   string  $charactertypeUrl   URL-title of Character type
         * @return  array                       Character type data
         */
        public function getCharactertypeByUrl($seminaryId, $charactertypeUrl)
        {
            $data = $this->db->query(
                'SELECT id, seminary_id, name, url '.
                'FROM charactertypes '.
                'WHERE seminary_id = ? AND url = ?',
                'is',
                $seminaryId,
                $charactertypeUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($charactertypeUrl);
            }


            return $data[0];
        }


        /**
         * Get Character type by its ID.
         *
         * @param   string  $charactertypeId    ID of Character type
         * @return  array                       Character type data
         */
        public function getCharactertypeById($charactertypeId)
        {
            $data = $this->db->query(
                'SELECT id, seminary_id, name, url '.
                'FROM charactertypes '.
                'WHERE id = ?',
                'i',
                $charactertypeId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($charactertypeId);
            }


            return $data[0];
        }


        /**
         * Check if a Charactertype name already exists.
         *
         * @param   int     $seminaryId         ID of Seminary
         * @param   string  $name               Charactertype name to check
         * @param   int     $charactertypeId    Do not check this ID (for editing)
         * @return  boolean                     Whether Charactertype name exists or not
         */
        public function charactertypeNameExists($seminaryId, $name, $charactertypeId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM charactertypes '.
                'WHERE seminary_id = ? AND (name = ? OR url = ?)',
                'iss',
                $seminaryId,
                $name,
                \nre\core\Linker::createLinkParam($name)
            );

            return (!empty($data) && (is_null($charactertypeId) || $charactertypeId != $data[0]['id']));
        }


        /**
         * Create a new Charactertype for a Seminary.
         *
         * @param   int     $userId     ID of creating user
         * @param   int     $seminaryId ID of Seminary
         * @param   string  $name       Name for new Charactertype
         * @return  int                 ID of newly created Charactertype
         */
        public function createCharactertype($userId, $seminaryId, $name)
        {
            $charactertypeId = null;
            $this->db->setAutocommit(false);
            try {
                // Create Charactertype
                $this->db->query(
                    'INSERT INTO charactertypes '.
                    '(created_user_id, seminary_id, name, url) '.
                    'VALUES '.
                    '(?, ?, ?, ?) ',
                    'iiss',
                    $userId,
                    $seminaryId,
                    $name,
                    \nre\core\Linker::createLinkParam($name)
                );
                $charactertypeId = $this->db->getInsertId();

                // Create avatars
                $this->db->query(
                    'INSERT INTO avatars '.
                    '(created_user_id, charactertype_id, xplevel_id) '.
                    'SELECT ?, ?, xplevels.id '.
                    'FROM xplevels '.
                    'WHERE seminary_id = ?',
                    'iii',
                    $userId,
                    $charactertypeId,
                    $seminaryId
                );

                $this->db->commit();
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }
            $this->db->setAutocommit(true);


            return $charactertypeId;
        }


        /**
         * Edit a Charactertype.
         *
         * @param   int     $charactertypeId    ID of Charactertype to edit
         * @param   string  $name               New name of Charactertype
         */
        public function editCharactertype($charactertypeId, $name)
        {
            $this->db->query(
                'UPDATE charactertypes '.
                'SET name = ?, url = ? '.
                'WHERE id = ?',
                'ssi',
                $name,
                \nre\core\Linker::createLinkParam($name),
                $charactertypeId
            );
        }


        /**
         * Copy all Charactertypes of a Seminary.
         *
         * @param   int     $userId             ID of copying user
         * @param   int     $sourceSeminaryId   ID of Seminary to copy from
         * @param   int     $targetSeminaryId   ID of Seminary to copy to
         * @param   array                       Mapping of Charactertype-IDs from source Seminary to targetSeminary
         */
        public function copyCharactertypesOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId)
        {
            $charactertypeIds = array();

            // Get Charactertypes
            $charactertypes = $this->getCharacterTypesForSeminary($sourceSeminaryId);

            // Copy each Charactertype
            foreach($charactertypes as &$type)
            {
                $this->db->query(
                    'INSERT INTO charactertypes '.
                    '(created_user_id, seminary_id, name, url) '.
                    'SELECT ?, ?, name, url '.
                    'FROM charactertypes '.
                    'WHERE id = ?',
                    'iii',
                    $userId, $targetSeminaryId,
                    $type['id']
                );
                $charactertypeIds[$type['id']] = $this->db->getInsertId();
            }


            return $charactertypeIds;
        }


        /**
         * Delete a Charactertype.
         *
         * @param   int $charactertypeId    ID of Charactertype to delete
         */
        public function deleteCharactertype($charactertypeId)
        {
            $this->db->query('DELETE FROM charactertypes WHERE id = ?', 'i', $charactertypeId);
        }


        /**
         * Delete all Charactertypes of a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to delete Charactertypes of
         */
        public function deleteCharactertypesOfSeminary($seminaryId)
        {
            $this->db->query('DELETE FROM charactertypes WHERE seminary_id = ?', 'i', $seminaryId);
        }

    }

?>
