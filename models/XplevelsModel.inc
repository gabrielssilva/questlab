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
     * Model for XP-levels.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class XplevelsModel extends \hhu\z\Model
    {




        /**
         * Construct a new XplevelsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get XP-level by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int $xplevelId  ID of XP-level
         * @return  array           XP-level data
         */
        public function getXPLevelById($xplevelId)
        {
            $data = $this->db->query(
                'SELECT id, seminary_id, xps, level, name '.
                'FROM xplevels '.
                'WHERE id = ?',
                'i',
                $xplevelId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($xplevelId);
            }


            return $data[0];
        }


        /**
         * Get all XP-levels for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int $seminaryId ID of Seminary
         * @return  array           List of XP-level
         */
        public function getXPLevelsForSeminary($seminaryId)
        {
            return $this->db->query(
                'SELECT id, seminary_id, xps, level, name '.
                'FROM xplevels '.
                'WHERE seminary_id = ? '.
                'ORDER BY level ASC',
                'i',
                $seminaryId
            );
        }


        /**
         * Create a new XP-level for a Seminary.
         *
         * @param   int $userId     ID of creating user
         * @param   int $seminaryId ID of Seminary
         * @param   int $xps        XPs of new XP-level
         * @param   string  $name       Name of new XP-level (optional)
         */
        public function createXPLevel($userId, $seminaryId, $xps, $name=null)
        {
            // Get level
            $level = $this->db->query(
                'SELECT COALESCE(MAX(level),0)+1 AS level '.
                'FROM xplevels '.
                'WHERE seminary_id = ?',
                'i',
                $seminaryId
            );
            $level = $level[0]['level'];

            $this->db->setAutocommit(false);
            try {
                // Create XP-level
                $this->db->query(
                    'INSERT INTO xplevels '.
                    '(created_user_id, seminary_id, xps, level, name) '.
                    'VALUES '.
                    '(?, ?, ?, ?, ?)',
                    'iiiis',
                    $userId,
                    $seminaryId,
                    $xps,
                    $level,
                    $name
                );
                $xplevelId = $this->db->getInsertId();

                // Create avatars
                $this->db->query(
                    'INSERT INTO avatars '.
                    '(created_user_id, charactertype_id, xplevel_id) '.
                    'SELECT ?, charactertypes.id, ? '.
                    'FROM charactertypes '.
                    'WHERE seminary_id = ?',
                    'iii',
                    $userId,
                    $xplevelId,
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
        }


        /**
         * Edit a XP-level.
         *
         * @param   int $xplevelId  ID of XP-level to edit
         * @param   int $xps        New XPs of XP-level
         * @param   string  $name       New name of XP-level (optional)
         */
        public function editXPLevel($xplevelId, $xps, $name=null)
        {
            $this->db->query(
                'UPDATE xplevels '.
                'SET xps = ?, name = ? '.
                'WHERE id = ?',
                'isi',
                $xps,
                $name,
                $xplevelId
            );
        }


        /**
         * Copy all XP-levels of a Seminary.
         *
         * @param   int     $userId             ID of copying user
         * @param   int     $sourceSeminaryId   ID of Seminary to copy from
         * @param   int     $targetSeminaryId   ID of Seminary to copy to
         * @param   array                       Mapping of XP-level-IDs from source Seminary to targetSeminary
         */
        public function copyXPLevelsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId)
        {
            $xplevelIds = array();

            // Get XP-levels
            $xplevels = $this->getXPLevelsForSeminary($sourceSeminaryId);

            // Copy each XP-level
            foreach($xplevels as &$level)
            {
                $this->db->query(
                    'INSERT INTO xplevels '.
                    '(created_user_id, seminary_id, xps, level, name) '.
                    'SELECT ?, ?, xps, level, name '.
                    'FROM xplevels '.
                    'WHERE id = ?',
                    'iii',
                    $userId, $targetSeminaryId,
                    $level['id']
                );
                $xplevelIds[$level['id']] = $this->db->getInsertId();
            }


            return $xplevelIds;
        }


        /**
         * Delete a XP-level.
         *
         * @param   int $xplevel    XP-level to delete
         */
        public function deleteXPLevel($xplevel)
        {
            $this->db->setAutocommit(false);
            try {
                // Delete XP-level
                $this->db->query('DELETE FROM xplevels WHERE id = ?', 'i', $xplevel['id']);

                // Adjust levels
                $this->db->query(
                    'UPDATE xplevels '.
                    'SET level = level - 1 '.
                    'WHERE seminary_id = ? AND level > ?',
                    'ii',
                    $xplevel['seminary_id'],
                    $xplevel['level']
                );

                $this->db->commit();
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }

            $this->db->setAutocommit(true);
        }


        /**
         * Delete all XP-levels of a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to delete XP-levels of
         */
        public function deleteXPLevelsOfSeminary($seminaryId)
        {
            $this->db->query('DELETE FROM xplevels WHERE seminary_id = ?', 'i', $seminaryId);
        }

    }

?>
