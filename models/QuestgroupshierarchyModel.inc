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
     * Model to interact with Questgroupshierarchy-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuestgroupshierarchyModel extends \hhu\z\Model
    {




        /**
         * Construct a new QuestgroupshierarchyModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get a Questgroup hierarchy by its ID.
         *
         * throws   \nre\exceptions\IdNotFoundException
         * @param   int     $questgroupshierarchyId ID of a Questgroup hierarchy
         * @return  array                           Questgroup hierarchy
         */
        public function getHierarchyById($questgroupshierarchyId)
        {
            $data = $this->db->query(
                'SELECT id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url '.
                'FROM questgroupshierarchy '.
                'WHERE questgroupshierarchy.id = ?',
                'i',
                $questgroupshierarchyId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($questgroupshierarchyId);
            }


            return $data[0];
        }


        /**
         * Get a Questgroup hierarchy by its URL.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $seminaryId                 ID of Seminary
         * @param   int     $questgroupshierarchyUrl    URL of a Questgroup hierarchy
         * @return  array                               Questgroup hierarchy
         */
        public function getHierarchyByUrl($seminaryId, $questgroupshierarchyUrl)
        {
            $data = $this->db->query(
                'SELECT id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url '.
                'FROM questgroupshierarchy '.
                'WHERE questgroupshierarchy.seminary_id = ? AND questgroupshierarchy.url = ?',
                'is',
                $seminaryId,
                $questgroupshierarchyUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($questgroupshierarchyUrl);
            }


            return $data[0];
        }


        /**
         * Get the toplevel hierarchy entries of a Seminary.
         *
         * @param   int     $seminaryId ID of the seminary to get hierarchy for
         * @return  array               Toplevel hierarchy
         */
        public function getHierarchyOfSeminary($seminaryId)
        {
            return $this->db->query(
                'SELECT id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url '.
                'FROM questgroupshierarchy '.
                'WHERE '.
                    'questgroupshierarchy.seminary_id = ? AND '.
                    'questgroupshierarchy.parent_questgroupshierarchy_id IS NULL '.
                'ORDER BY questgroupshierarchy.pos ASC',
                'i',
                $seminaryId
            );
        }


        /**
         * Get the Questgroup-Hierarchy for a Questgroup.
         *
         * @param   int     $questgroupId   ID of Questgroup
         * @return  array                   Hierarchy for Questgroup
         */
        public function getHierarchyForQuestgroup($questgroupId)
        {
            $data = $this->db->query(
                'SELECT questgroups_questgroupshierarchy.parent_questgroup_id, questgroups_questgroupshierarchy.pos AS questgroup_pos, questgroupshierarchy.id, questgroupshierarchy.seminary_id, questgroupshierarchy.parent_questgroupshierarchy_id, questgroupshierarchy.pos, questgroupshierarchy.title_singular, questgroupshierarchy.title_plural, questgroupshierarchy.url '.
                'FROM questgroups_questgroupshierarchy '.
                'INNER JOIN questgroupshierarchy ON questgroupshierarchy.id = questgroups_questgroupshierarchy.questgroupshierarchy_id '.
                'WHERE questgroups_questgroupshierarchy.questgroup_id = ?',
                'i',
                $questgroupId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Get the child hierarchy entries of a Questgroup hierarchy.
         *
         * @param   int     $questgroupshierarchyId ID of a Questgroup hierarchy
         * @return  array                           Child Questgroup hierarchy entries
         */
        public function getChildQuestgroupshierarchy($questgroupshierarchyId)
        {
            return $this->db->query(
                'SELECT id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url '.
                'FROM questgroupshierarchy '.
                'WHERE questgroupshierarchy.parent_questgroupshierarchy_id = ? '.
                'ORDER BY questgroupshierarchy.pos ASC',
                'i',
                $questgroupshierarchyId
            );
        }


        /**
         * Check if a title for a Questgroupshierarchy already exists
         * for a Seminary.
         *
         * @param   string  $title                  Title to check
         * @param   int     $seminaryId             ID of Seminary
         * @param   int     $questgroupshierarchyId Do not check this Questgroupshierarchy (for editing)
         * @return                                  Whether title already exists or not
         */
        public function questgroupshierarchyTitleSingularExists($title, $seminaryId, $questgroupshierarchyId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM questgroupshierarchy '.
                'WHERE seminary_id = ? AND (title_singular = ? OR url = ?) ',
                'iss',
                $seminaryId,
                $title,
                \nre\core\Linker::createLinkParam($title)
            );


            return (!empty($data) && (is_null($questgroupshierarchyId) || $questgroupshierarchyId != $data[0]['id']));
        }


        /**
         * Create a new Questgroupshierarchy for a Seminary
         *
         * @param   int     $userId                         ID of creating user
         * @param   int     $seminaryId                     ID of Seminary
         * @param   int     $parentQuestgroupsierarchyId    ID of parent Questgroupshierarchy
         * @param   string  $titleSingular                  Title (singular)
         * @param   string  $titlePlural                    Title (plural)
         */
        public function createQuestgroupshierarchy($userId, $seminaryId, $parentQuestgroupsierarchyId, $titleSingular, $titlePlural)
        {
            // Get last position
            $pos = $this->db->query(
                'SELECT COALESCE(MAX(pos),0) AS pos '.
                'FROM questgroupshierarchy '.
                'WHERE seminary_id = ? AND '.
                'parent_questgroupshierarchy_id '.(!is_null($parentQuestgroupsierarchyId) ? sprintf('= %d', $parentQuestgroupsierarchyId) : 'IS NULL'),
                'i',
                $seminaryId
            );
            $pos = intval($pos[0]['pos']);

            // Create Questgroupshierarchy
            $this->db->query(
                'INSERT INTO questgroupshierarchy '.
                '(created_user_id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url) '.
                'VALUES '.
                '(?, ?, ?, ?, ?, ?, ?)',
                'iiiisss',
                $userId,
                $seminaryId,
                $parentQuestgroupsierarchyId,
                $pos + 1,
                $titleSingular,
                $titlePlural,
                \nre\core\Linker::createLinkParam($titleSingular)
            );


            return $this->db->getInsertId();
        }


        /**
         * Edit a Questgroupshierarchy.
         *
         * @param   int     $questgroupshierarchyId ID of Questgroupshierarchy to edit
         * @param   string  $titleSingular          New title (singular)
         * @param   string  $titlePlural            New title (plural)
         */
        public function editQuestgroupshierarchy($questgroupshierarchyId, $titleSingular, $titlePlural)
        {
            $this->db->query(
                'UPDATE questgroupshierarchy '.
                'SET title_singular = ?, title_plural = ?, url = ? '.
                'WHERE id = ?',
                'sssi',
                $titleSingular,
                $titlePlural,
                \nre\core\Linker::createLinkParam($titleSingular),
                $questgroupshierarchyId
            );
        }


        /**
         * Move a Questgroupshierarchy up (decrement position) or down
         * (increment position).
         *
         * @param   array   $questgroupshierarchy   Questgroupshierarchy to move
         * @param   boolean $up                     True for moving up, false for down
         */
        public function moveQuestgroupshierarchy($questgroupshierarchy, $up)
        {
            $this->db->setAutocommit(false);
            try {
                // Set temporary position
                $this->db->query(
                    'UPDATE questgroupshierarchy '.
                    'SET pos = 0 '.
                    'WHERE id = ?',
                    'i',
                    $questgroupshierarchy['id']
                );
                // Switch entry
                if(is_null($questgroupshierarchy['parent_questgroupshierarchy_id'])) {
                    $this->db->query(
                        'UPDATE questgroupshierarchy '.
                        'SET pos = ? '.
                        'WHERE parent_questgroupshierarchy_id IS NULL AND pos = ?',
                        'ii',
                        $questgroupshierarchy['pos'],
                        $questgroupshierarchy['pos'] + ($up ? -1 : 1)
                    );
                }
                else {
                    $this->db->query(
                        'UPDATE questgroupshierarchy '.
                        'SET pos = ? '.
                        'WHERE parent_questgroupshierarchy_id = ? AND pos = ?',
                        'iii',
                        $questgroupshierarchy['pos'],
                        $questgroupshierarchy['parent_questgroupshierarchy_id'],
                        $questgroupshierarchy['pos'] + ($up ? -1 : 1)
                    );
                }
                // Set new position
                $this->db->query(
                    'UPDATE questgroupshierarchy '.
                    'SET pos = ? '.
                    'WHERE id = ?',
                    'ii',
                    $questgroupshierarchy['pos'] + ($up ? -1 : 1),
                    $questgroupshierarchy['id']
                );

                $this->db->commit();
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }
            $this->db->setAutocommit(true);
        }


        /**
         * Copy complete Questgroupshierarchy of a Seminary.
         *
         * @param   int     $userId             ID of creating user
         * @param   int     $sourceSeminaryId   ID of Seminary to copy hierarchy from
         * @param   int     $targetSeminaryId   ID of Seminary to copy hierarchy to
         * @return  array                       Mapping of hierarchy-IDs from source Seminary to target Seminary
         */
        public function copyQuestgroupshierarchy($userId, $sourceSeminaryId, $targetSeminaryId)
        {
            // Get Hierarchy of Seminary
            $questgroupshierarchy = $this->getHierarchyOfSeminary($sourceSeminaryId);

            // Copy hierarchy
            $hierarchyIds = array();
            foreach($questgroupshierarchy as $hierarchy) {
                $this->copyHierarchy($userId, $sourceSeminaryId, $targetSeminaryId, $hierarchy, $hierarchyIds);
            }


            return $hierarchyIds;
        }


        /**
         * Delete a Questgroupshierarchy.
         *
         * @param   int $questgroupshierarchyId     ID of Questgroups hierarchy to delete
         */
        public function deleteQuestgroupshierarchy($questgroupshierarchyId)
        {
            $this->db->query('DELETE FROM questgroupshierarchy WHERE id = ?', 'i', $questgroupshierarchyId);
        }


        /**
         * Delete complete Questgroupshierarchy of a Seminary.
         * 
         * @param   int $seminaryId ID of Seminary to delete Questgroupshierarchy of
         */
        public function deleteQuestgroupshierarchyOfSeminary($seminaryId)
        {
            $this->db->query('DELETE FROM questgroupshierarchy WHERE seminary_id = ?', 'i', $seminaryId);
        }




        /**
         * Copy a Questgroupshierarchy and its child hierarchy.
         *
         * @param   int     $userId             ID of creating user
         * @param   int     $sourceSeminaryId   ID of Seminary to copy hierarchy from
         * @param   int     $targetSeminaryId   ID of Seminary to copy hierarchy to
         * @param   array   $hierarchy          Hierarchy to copy
         * @param   array   $hierarchyIds       Mapping of hierarchy IDs from source Seminary to target Seminary
         */
        private function copyHierarchy($userId, $sourceSeminaryId, $targetSeminaryId, $hierarchy, &$hierarchyIds)
        {
            // insert for new seminary
            if(is_null($hierarchy['parent_questgroupshierarchy_id']))
            {
                $this->db->query(
                    'INSERT INTO questgroupshierarchy '.
                    '(created_user_id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url) '.
                    'SELECT ?, ?, null, pos, title_singular, title_plural, url '.
                    'FROM questgroupshierarchy '.
                    'WHERE id = ?',
                    'iii',
                    $userId, $targetSeminaryId,
                    $hierarchy['id']
                );
            }
            else
            {
                $this->db->query(
                    'INSERT INTO questgroupshierarchy '.
                    '(created_user_id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url) '.
                    'SELECT ?, ?, ?, pos, title_singular, title_plural, url '.
                    'FROM questgroupshierarchy '.
                    'WHERE id = ?',
                    'iiii',
                    $userId, $targetSeminaryId, $hierarchyIds[$hierarchy['parent_questgroupshierarchy_id']],
                    $hierarchy['id']
                );
            }
            $hierarchyIds[$hierarchy['id']] = $this->db->getInsertId();

            // insert sub hierarchy
            $childHierarchy = $this->getChildQuestgroupshierarchy($hierarchy['id']);
            foreach($childHierarchy as $hierarchy) {
                $this->copyHierarchy($userId, $sourceSeminaryId, $targetSeminaryId, $hierarchy, $hierarchyIds);
            }
        }

    }

?>
