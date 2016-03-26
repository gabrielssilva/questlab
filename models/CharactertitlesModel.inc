<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\models;


    /**
     * Model to interact with Charactertitles-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactertitlesModel extends \hhu\z\Model
    {




        /**
         * Construct a new CharactertitlesModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get a Character title by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $titleId    ID of title
         * @return  array               Title data
         */
        public function getTitleById($titleId)
        {
            $data = $this->db->query(
                'SELECT id, hash, title_male, title_female '.
                'FROM charactertitles '.
                'WHERE id = ?',
                'i',
                $titleId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($titleId);
            }


            return $data[0];
        }


        /**
         * Get a Character title by its hash.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $titleHash  Hash of title
         * @return  array               Title data
         */
        public function getTitleByHash($titleHash)
        {
            $data = $this->db->query(
                'SELECT id, hash, title_male, title_female '.
                'FROM charactertitles '.
                'WHERE hash = ?',
                's',
                $titleHash
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($titleHash);
            }


            return $data[0];
        }


        /**
         * Get all Character titles of a Seminary.
         *
         * @param   int     $seminaryId ID of Seminary to get titles for
         * @return  array               List of title data
         */
        public function getTitlesForSeminary($seminaryId)
        {
            return $this->db->query(
                'SELECT id, hash, title_male, title_female '.
                'FROM charactertitles '.
                'WHERE seminary_id = ? '.
                'ORDER BY title_male, title_female ',
                'i',
                $seminaryId
            );
        }


        /**
         * Get all titles a Character owns.
         *
         * @param   int     $characterId    ID of Character to get titles for
         * @return  array                   List of title data
         */
        public function getTitlesForCharacter($characterId)
        {
            return $this->db->query(
                'SELECT charactertitles.id, title_male, title_female '.
                'FROM characters_charactertitles '.
                'INNER JOIN charactertitles ON charactertitles.id = characters_charactertitles.charactertitle_id '.
                'WHERE characters_charactertitles.character_id = ? '.
                'ORDER BY title_male, title_female ',
                'i',
                $characterId
            );
        }


        /**
         * Check if a title for a Characters already exists.
         *
         * @param   int     $seminaryId ID of Seminary
         * @param   string  $title      Character title to check
         * @param   int     $titleId    Do not check this ID (for editing)
         * @return  boolean             Whether Character title exists or not
         */
        public function titleExists($seminaryId, $title, $titleId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM charactertitles '.
                'WHERE seminary_id = ? AND (title_male = ? OR title_female = ?)',
                'iss',
                $seminaryId,
                $title,
                $title
            );

            return (!empty($data) && (is_null($titleId) || $titleId != $data[0]['id']));
        }


        /**
         * Create a new Character title.
         *
         * @param   int     $userId         User-ID that creates the new title
         * @param   int     $seminaryId     ID of Questgroup
         * @param   string  $titleMale      Title for male Characters
         * @param   string  $titleFemale    Title for female Characters
         * @return  int                     ID of new Character title
         */
        public function createTitle($userId, $seminaryId, $titleMale, $titleFemale)
        {
            $this->db->query(
                'INSERT INTO charactertitles '.
                '(created_user_id, seminary_id, hash, title_male, title_female) '.
                'VALUES '.
                '(?, ?, ?, ?, ?)',
                'iisss',
                $userId, $seminaryId,
                \hhu\z\Utils::createRandomHash(),
                $titleMale, $titleFemale
                //\nre\core\Linker::createLinkParam($title),
            );


            return $this->db->getInsertId();
        }


        /**
         * Edit a Character title.
         *
         * @param   int     $titleId        ID of Character title to edit
         * @param   string  $titleMale      Title for male Characters
         * @param   string  $titleFemale    Title for female Characters
         */
        public function editTitle($titleId, $titleMale, $titleFemale)
        {
            $this->db->query(
                'UPDATE charactertitles '.
                'SET title_male = ?, title_female = ? '.
                'WHERE id = ?',
                'ssi',
                $titleMale,
                $titleFemale,
                $titleId
            );
        }


        /**
         * Delete a Character title.
         *
         * @param   int $titleId    ID of Character title to delete
         */
        public function deleteTitle($titleId)
        {
            $this->db->query(
                'DELETE FROM charactertitles '.
                'WHERE id = ?',
                'i',
                $titleId
            );
        }

    }

?>
