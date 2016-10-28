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
     * Model to interact with Questtopics-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuesttopicsModel extends \hhu\z\Model
    {




        /**
         * Construct a new QuesttopicsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get a Questtopic by its URL.
         *
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $questtopicUrl  URL-Title of Questtopic
         * @return  array                   Questtopic data
         */
        public function getQuesttopicByUrl($seminaryId, $questtopicUrl)
        {
            $data = $this->db->query(
                'SELECT id, title, url '.
                'FROM questtopics '.
                'WHERE seminary_id = ? AND url = ?',
                'is',
                $seminaryId, $questtopicUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($questtopicUrl);
            }


            return $data[0];
        }


        /**
         * Get a Questtopic by its ID.
         *
         * @param   int     $questtopicId   ID of Questtopic
         * @return  array                   Questtopic data
         */
        public function getQuesttopicById($questtopicId)
        {
            $data = $this->db->query(
                'SELECT id, title, url '.
                'FROM questtopics '.
                'WHERE id = ?',
                'i',
                $questtopicId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($questtopicId);
            }


            return $data[0];
        }


        /**
         * Get all Questtopics for a Seminary.
         *
         * @param   int     $seminaryId ID of Seminary
         * @return  array               List of Questtopics
         */
        public function getQuesttopicsForSeminary($seminaryId)
        {
            return $this->db->query(
                'SELECT id, title, url '.
                'FROM questtopics '.
                'WHERE seminary_id = ? '.
                'ORDER BY title ASC',
                'i',
                $seminaryId
            );
        }


        /**
         * Copy all Questtopics and their subtopics of a Seminary.
         *
         * @param   int     $userId             ID of creating user
         * @param   int     $sourceSeminaryId   ID of Seminary to copy from
         * @param   int     $targetSeminaryId   ID of Seminary to copy to
         * @param   array   $questIds           Mapping of Quest-IDs from source Seminary to target Seminary
         * @return  array                       Mapping of Questsubtopic-IDs from source Seminary to targetSeminary
         */
        public function copyQuesttopicsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId, $questIds)
        {
            $questsubtopicIds = array();

            // Get Questtopics
            $questtopics = $this->getQuesttopicsForSeminary($sourceSeminaryId);
            foreach($questtopics as &$questtopic)
            {
                // Copy Questtopic
                $this->db->query(
                    'INSERT INTO questtopics '.
                    '(created_user_id, seminary_id, title, url) '.
                    'SELECT ?, ?, title, url '.
                    'FROM questtopics '.
                    'WHERE id = ?',
                    'iii',
                    $userId, $targetSeminaryId,
                    $questtopic['id']
                );
                $targetQuesttopicId = $this->db->getInsertId();

                // Get Questsubtopics
                $questsubtopics = $this->getSubtopicsForQuesttopic($questtopic['id']);
                foreach($questsubtopics as &$questsubtopic)
                {
                    // Copy Questsubtopic
                    $this->db->query(
                        'INSERT INTO questsubtopics '.
                        '(created_user_id, questtopic_id, title, url) '.
                        'SELECT ?, ?, title, url '.
                        'FROM questsubtopics '.
                        'WHERE id = ?',
                        'iii',
                        $userId, $targetQuesttopicId,
                        $questsubtopic['id']
                    );
                    $questsubtopicIds[$questsubtopic['id']] = $this->db->getInsertId();

                    // Get Quest links
                    $quests = $this->db->query(
                        'SELECT quest_id '.
                        'FROM quests_questsubtopics '.
                        'WHERE questsubtopic_id = ?',
                        'i',
                       $questsubtopic['id']
                    );
                    foreach($quests as &$quest)
                    {
                        $this->db->query(
                            'INSERT INTO quests_questsubtopics '.
                            '(quest_id, questsubtopic_id) '.
                            'VALUES '.
                            '(?, ?)',
                            'ii',
                            $questIds[$quest['quest_id']],
                            $questsubtopicIds[$questsubtopic['id']]
                        );
                    }
                }
            }


            return $questsubtopicIds;
        }


        /**
         * Get count of Quests that are linked to a Questtopic.
         *
         * @param   int $questtopicId   ID of Questtopic
         * @return  int                 Count of Quests
         */
        public function getQuestCountForQuesttopic($questtopicId)
        {
            $data = $this->db->query(
                'SELECT count(DISTINCT quests_questsubtopics.quest_id) AS c ' .
                'FROM questsubtopics '.
                'LEFT JOIN quests_questsubtopics ON quests_questsubtopics.questsubtopic_id = questsubtopics.id '.
                'WHERE questsubtopics.questtopic_id = ?',
                'i',
                $questtopicId
            );
            if(!empty($data)) {
                return $data[0]['c'];
            }


            return 0;
        }


        /**
         * Get count of Quests that are linked to a Questtopic and are
         * unlocked by a Character.
         *
         * @param   int $questtopicId   ID of Questtopic
         * @param   int $characterId    ID of Character
         * @return  int                 Count of Quests
         */
        public function getCharacterQuestCountForQuesttopic($questtopicId, $characterId)
        {
            $data = $this->db->query(
                'SELECT count(DISTINCT quests_characters.quest_id) AS c '.
                'FROM questsubtopics '.
                'LEFT JOIN quests_questsubtopics ON quests_questsubtopics.questsubtopic_id = questsubtopics.id '.
                'INNER JOIN quests_characters ON quests_characters.quest_id = quests_questsubtopics.quest_id AND quests_characters.character_id = ? AND quests_characters.status = 3 '.
                'WHERE questsubtopics.questtopic_id = ?',
                'ii',
                $characterId,
                $questtopicId
            );
            if(!empty($data)) {
                return $data[0]['c'];
            }


            return 0;
        }


        /**
         * Get alle Questsubtopics for a Questtopic.
         *
         * @param   int     $questtopicId   ID of Questtopic
         * @return  array                   List of Questsubtopics for this Questtopic
         */
        public function getSubtopicsForQuesttopic($questtopicId)
        {
            return $this->db->query(
                'SELECT id, questtopic_id, title, url '.
                'FROM questsubtopics '.
                'WHERE questsubtopics.questtopic_id = ? '.
                'ORDER BY title ASC',
                'i',
                $questtopicId
            );
        }


        /**
         * Get all Questsubtopics for a Quest.
         *
         * @param   int     $questId    ID of Quest
         * @return  array               List of Questsubtopics
         */
        public function getQuestsubtopicsForQuest($questId)
        {
            return $this->db->query(
                'SELECT DISTINCT id, questtopic_id, title, url '.
                'FROM quests_questsubtopics '.
                'INNER JOIN questsubtopics ON questsubtopics.id = quests_questsubtopics.questsubtopic_id '.
                'WHERE quests_questsubtopics.quest_id = ? '.
                'ORDER BY questsubtopics.title ASC',
                'i',
                $questId
            );
        }


        /**
         * Set Questsubtopics for a Quest.
         *
         * @param   int     $questId            ID of Quest to set subtopics for
         * @param   array   $questsubtopicIds   List of IDs of subtopics to set
         */
        public function setQuestsubtopicsForQuest($questId, $questsubtopicIds)
        {
            $this->db->setAutocommit(false);
            try {
                // Remove Questsubtopics
                $this->db->query(
                    'DELETE FROM quests_questsubtopics '.
                    'WHERE quest_id = ?',
                    'i',
                    $questId
                );

                // Add Questsubtopics
                foreach($questsubtopicIds as &$questsubtopicId)
                {
                    $this->db->query(
                        'INSERT INTO quests_questsubtopics '.
                        '(quest_id, questsubtopic_id) '.
                        'VALUES '.
                        '(?, ?)',
                        'ii',
                        $questId, $questsubtopicId
                    );
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }

            $this->db->setAutocommit(true);
        }


        /**
         * Check if a Questtopic title already exists.
         *
         * @param   string  $title          Questtopic title to check
         * @param   int     $questtopicId   Do not check this ID (for editing)
         * @return  boolean                 Whether Questtopic title exists or not
         */
        public function questtopicTitleExists($title, $questtopicId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM questtopics '.
                'WHERE title = ? OR url = ?',
                'ss',
                $title,
                \nre\core\Linker::createLinkParam($title)
            );

            return (!empty($data) && (is_null($questtopicId) || $questtopicId != $data[0]['id']));
        }


        /**
         * Create a new Questtopic for a Seminary.
         *
         * @param   int     $userId     ID of creating user
         * @param   int     $seminaryId ID of Seminary
         * @param   string  $title      Title for new Questtopic
         * @return  int                 ID of newly created Questtopic
         */
        public function createQuesttopic($userId, $seminaryId, $title)
        {
            $this->db->query(
                'INSERT INTO questtopics '.
                '(created_user_id, seminary_id, title, url) '.
                'VALUES '.
                '(?, ?, ?, ?) ',
                'iiss',
                $userId,
                $seminaryId,
                $title,
                \nre\core\Linker::createLinkParam($title)
            );

            return $this->db->getInsertId();
        }


        /**
         * Edit a Questtopic.
         *
         * @param   int     $questtopicId   ID of Questtopic to edit
         * @param   string  $title          New title of Questtopic
         */
        public function editQuesttopic($questtopicId, $title)
        {
            $this->db->query(
                'UPDATE questtopics '.
                'SET title = ?, url = ? '.
                'WHERE id = ?',
                'ssi',
                $title,
                \nre\core\Linker::createLinkParam($title),
                $questtopicId
            );
        }


        /**
         * Delete a Questtopic.
         *
         * @param   int $questtopicId   ID of Questtopic to delete
         */
        public function deleteQuesttopic($questtopicId)
        {
            $this->db->query('DELETE FROM questtopics WHERE id = ?', 'i', $questtopicId);
        }


        /**
         * Check if a Questsubtopic title already exists.
         *
         * @param   int     $questtopicId       ID of Questtopic
         * @param   string  $title              Questsubtopic title to check
         * @param   int     $questsubtopicId    Do not check this ID (for editing)
         * @return  boolean                     Whether Questsubtopic title exists or not
         */
        public function questsubtopicTitleExists($questtopicId, $title, $questsubtopicId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM questsubtopics '.
                'WHERE questtopic_id = ? AND (title = ? OR url = ?)',
                'iss',
                $questtopicId,
                $title,
                \nre\core\Linker::createLinkParam($title)
            );

            return (!empty($data) && (is_null($questsubtopicId) || $questsubtopicId != $data[0]['id']));
        }


        /**
         * Create a new Questsubtopic for a Questtopic.
         *
         * @param   int     $userId         ID of creating user
         * @param   int     $questtopicId   ID of Qusttopic
         * @param   string  $title          Title for new Questtopic
         * @return  int                     ID of newly created Questsubtopic
         */
        public function createQuestsubtopic($userId, $questtopicId, $title)
        {
            $this->db->query(
                'INSERT INTO questsubtopics '.
                '(created_user_id, questtopic_id, title, url) '.
                'VALUES '.
                '(?, ?, ?, ?) ',
                'iiss',
                $userId,
                $questtopicId,
                $title,
                \nre\core\Linker::createLinkParam($title)
            );

            return $this->db->getInsertId();
        }


        /**
         * Edit a Questsubtopic.
         *
         * @param   int     $questsubtopicId    ID of Questsubtopic to edit
         * @param   string  $title              New title of Questsubtopic
         */
        public function editQuestsubtopic($questsubtopicId, $title)
        {
            $this->db->query(
                'UPDATE questsubtopics '.
                'SET title = ?, url = ? '.
                'WHERE id = ?',
                'ssi',
                $title,
                \nre\core\Linker::createLinkParam($title),
                $questsubtopicId
            );
        }


        /**
         * Delete a Questsubtopic.
         *
         * @param   int $questtopicId   ID of Questsubtopic to delete
         */
        public function deleteQuestsubtopic($questtopicId)
        {
            $this->db->query('DELETE FROM questsubtopics WHERE id = ?', 'i', $questtopicId);
        }


        /**
         * Delete all Questtopics of a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to delete Questtopics of
         */
        public function deleteQuesttopicsOfSeminary($seminaryId)
        {
            $this->db->query('DELETE FROM questtopics WHERE seminary_id = ?', 'i', $seminaryId);
        }

    }

?>
