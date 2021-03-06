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
     * Model to interact with Quests-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuestsModel extends \hhu\z\Model
    {
        /**
         * Quest-status: Entered
         *
         * @var int;
         */
        const QUEST_STATUS_ENTERED = 0;
        /**
         * Quest-status: submitted
         *
         * @var int;
         */
        const QUEST_STATUS_SUBMITTED = 1;
        /**
         * Quest-status: Unsolved
         *
         * @var int;
         */
        const QUEST_STATUS_UNSOLVED = 2;
        /**
         * Quest-status: Solved
         *
         * @var int;
         */
        const QUEST_STATUS_SOLVED = 3;

        /**
         * Required models
         *
         * @var array
         */
        public $models = array('questtypes', 'questtexts', 'media');




        /**
         * Construct a new QuestsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get a Quest and its data by its URL.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $seminaryId     ID of the corresponding Seminary
         * @param   int     $questgroupId   ID of the corresponding Questgroup
         * @param   string  $questUrl       URL-title of a Quest
         * @return  array                   Quest data
         */
        public function getQuestByUrl($seminaryId, $questgroupId, $questUrl)
        {
            $data = $this->db->query(
                'SELECT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.entry_text, quests.task, quests.wrong_text, quests.questsmedia_id '.
                'FROM quests '.
                'LEFT JOIN questgroups ON questgroups.id = quests.questgroup_id '.
                'WHERE questgroups.seminary_id = ? AND questgroups.id = ? AND quests.url = ?',
                'iis',
                $seminaryId, $questgroupId, $questUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($questUrl);
            }


            return $data[0];
        }


        /**
         * Get a Quest and its data by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $questId    ID of a Quest
         * @return  array               Quest data
         */
        public function getQuestById($questId)
        {
            $data = $this->db->query(
                'SELECT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.entry_text, quests.task, quests.wrong_text, quests.questsmedia_id '.
                'FROM quests '.
                'LEFT JOIN questgroups ON questgroups.id = quests.questgroup_id '.
                'WHERE quests.id = ?',
                'i',
                $questId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($questId);
            }


            return $data[0];
        }


        /**
         * Get the first Quest of a Qusetgroup.
         *
         * @param   int     $questgroupId   ID of Questgroup
         * @return  array                   Data of first Quest
         */
        public function getFirstQuestOfQuestgroup($questgroupId)
        {
            $data = $this->db->query(
                'SELECT id, questtype_id, title, url, xps, task '.
                'FROM quests '.
                'LEFT JOIN quests_previousquests ON quests_previousquests.quest_id = quests.id '.
                'WHERE questgroup_id = ? AND quests_previousquests.previous_quest_id IS NULL',
                'i',
                $questgroupId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Get all Quests a Qusetgroup that do not have a following
         * Quest.
         *
         * @param   int     $questgroupId   ID of Questgroup
         * @return  array                   List of last Quests
         */
        public function getLastQuestsOfQuestgroup($questgroupId)
        {
            return $this->db->query(
                'SELECT id, questtype_id, title, url, xps, task '.
                'FROM quests '.
                'WHERE questgroup_id = ? AND NOT EXISTS ('.
                    'SELECT quest_id '.
                    'FROM quests_previousquests '.
                    'WHERE quests_previousquests.previous_quest_id = quests.id'.
                ')',
                'i',
                $questgroupId
            );
        }


        /**
         * Get Quests that follow-up a Quest.
         *
         * @param   int     $questId    ID of Quest to get next Quests of
         * @return  array               Quests data
         */
        public function getNextQuests($questId)
        {
            return $this->db->query(
                'SELECT quests.id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.entry_text, quests.task, questgroups.title AS questgroup_title, questgroups.url AS questgroup_url '.
                'FROM quests_previousquests '.
                'INNER JOIN quests ON quests.id = quests_previousquests.quest_id '.
                'INNER JOIN questgroups ON questgroups.id = quests.questgroup_id '.
                'WHERE quests_previousquests.previous_quest_id = ?',
                'i',
                $questId
            );
        }


        /**
         * Get Quests that the given Quests follows-up to.
         *
         * @param   int     $questId    ID of Quest to get previous Quests of
         * @return  array               Quests data
         */
        public function getPreviousQuests($questId)
        {
            return $this->db->query(
                'SELECT quests.id, quests.title, quests.url, quests.entry_text, questgroups.title AS questgroup_title, questgroups.url AS questgroup_url '.
                'FROM quests_previousquests '.
                'INNER JOIN quests ON quests.id = quests_previousquests.previous_quest_id '.
                'INNER JOIN questgroups ON questgroups.id = quests.questgroup_id '.
                'WHERE quests_previousquests.quest_id = ?',
                'i',
                $questId
            );
        }


        /**
         * Set the previous Quest for a Quest.
         *
         * @param   int $questId            ID of Quest to set previous Quest for
         * @param   int $previousQuestId    Id of previous Quest
         */
        public function setPreviousQuest($questId, $previousQuestId)
        {
            $this->db->query(
                'REPLACE INTO quests_previousquests '.
                '(quest_id, previous_quest_id) '.
                'VALUES '.
                '(?, ?)',
                'ii',
                $questId,
                $previousQuestId
            );
        }


        /**
         * Mark a Quest as entered for a Character.
         *
         * @param   int $questId        ID of Quest to mark as entered
         * @param   int $characterId    ID of Character that entered the Quest
         */
        public function setQuestEntered($questId, $characterId)
        {
            $this->setQuestStatus($questId, $characterId, self::QUEST_STATUS_ENTERED, false);
        }


        /**
         * Mark a Quest as submitted for a Character.
         *
         * @param   int $questId        ID of Quest to mark as unsolved
         * @param   int $characterId    ID of Character that unsolved the Quest
         */
        public function setQuestSubmitted($questId, $characterId)
        {
            $this->setQuestStatus($questId, $characterId, self::QUEST_STATUS_SUBMITTED);
        }


        /**
         * Mark a Quest as unsolved for a Character.
         *
         * @param   int $questId        ID of Quest to mark as unsolved
         * @param   int $characterId    ID of Character that unsolved the Quest
         */
        public function setQuestUnsolved($questId, $characterId)
        {
            $this->setQuestStatus($questId, $characterId, self::QUEST_STATUS_UNSOLVED);
        }


        /**
         * Mark a Quest as solved for a Character.
         *
         * @param   int $questId        ID of Quest to mark as solved
         * @param   int $characterId    ID of Character that solved the Quest
         */
        public function setQuestSolved($questId, $characterId)
        {
            $this->setQuestStatus($questId, $characterId, self::QUEST_STATUS_SOLVED, false);
        }


        /**
         * Determine if the given Character has entered a Quest.
         *
         * @param   int     $questId        ID of Quest to check
         * @param   int     $characterId    ID of Character to check
         * @result  boolean                 Whether Character has entered the Quest or not
         */
        public function hasCharacterEnteredQuest($questId, $characterId)
        {
            $count = $this->db->query(
                'SELECT count(id) AS c '.
                'FROM quests_characters '.
                'WHERE quest_id = ? AND character_id = ? AND status IN (?,?,?)',
                'iiiii',
                $questId,
                $characterId,
                self::QUEST_STATUS_ENTERED, self::QUEST_STATUS_SOLVED, self::QUEST_STATUS_UNSOLVED
            );


            return (!empty($count) && intval($count[0]['c']) > 0);
        }


        /**
         * Determine if the given Character has tried to solve a Quest.
         *
         * @param   int     $questId        ID of Quest to check
         * @param   int     $characterId    ID of Character to check
         * @result  boolean                 Whether Character has tried to solved the Quest or not
         */
        public function hasCharacterTriedQuest($questId, $characterId)
        {
            $count = $this->db->query(
                'SELECT count(id) AS c '.
                'FROM quests_characters '.
                'WHERE quest_id = ? AND character_id = ? AND status IN (?,?)',
                'iiii',
                $questId,
                $characterId,
                self::QUEST_STATUS_SOLVED, self::QUEST_STATUS_UNSOLVED
            );


            return (!empty($count) && intval($count[0]['c']) > 0);
        }


        /**
         * Determine if the given Character has solved the given Quest.
         *
         * @param   int     $questId        ID of Quest to check
         * @param   int     $characterId    ID of Character to check
         * @result  boolean                 Whether Character has solved the Quest or not
         */
        public function hasCharacterSolvedQuest($questId, $characterId)
        {
            $count = $this->db->query(
                'SELECT count(id) AS c '.
                'FROM quests_characters '.
                'WHERE quest_id = ? AND character_id = ? AND status = ?',
                'iii',
                $questId,
                $characterId,
                self::QUEST_STATUS_SOLVED
            );


            return (!empty($count) && intval($count[0]['c']) > 0);
        }


        /**
         * Get the last Quests for a Character.
         *
         * @param   int     $characterId    ID of Character
         * @retrun  array                   Quest data
         */
        public function getLastQuestForCharacter($characterId)
        {
            $data = $this->db->query(
                'SELECT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, quests.wrong_text, quests.questsmedia_id '.
                'FROM quests_characters '.
                'LEFT JOIN quests ON quests.id = quests_characters.quest_id '.
                'WHERE quests_characters.character_id = ? AND quests_characters.status IN (?, ?, ?) '.
                'ORDER BY quests_characters.created desc '.
                'LIMIT 1',
                'iiii',
                $characterId,
                self::QUEST_STATUS_ENTERED, self::QUEST_STATUS_SUBMITTED, self::QUEST_STATUS_SOLVED
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Get all Quests for a Seminary.
         *
         * @param   int     $seminaryId ID of Seminary
         * @return  array               Quests for this Seminary
         */
        public function getQuestsForSeminary($seminaryId)
        {
            return $this->db->query(
                'SELECT DISTINCT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, quests.wrong_text, quests.questsmedia_id, questgroups.title AS questgroup_title, questgroups.url AS questgroup_url '.
                'FROM questgroups '.
                'INNER JOIN quests ON quests.questgroup_id = questgroups.id '.
                'WHERE questgroups.seminary_id = ? '.
                'ORDER BY quests.title ASC',
                'i',
                $seminaryId
            );
        }


        /**
         * Get count of all Quests for a Seminary.
         *
         * @param   int     $seminaryId     ID of Seminary
         * @param   int     $questgroupId   ID of Questgroup (optional)
         * @param   int     $questtypeId    ID of Questtype (optional)
         * @param   string  $title          Part of the title to filter for (optional)
         * @return  int                     Count of Quests for this Seminary
         */
        public function getCountForQuestsForSeminaryByOpenSubmissions($seminaryId, $questgroupId=null, $questtypeId=null, $title=null)
        {
            $data = $this->db->query(
                'SELECT count(DISTINCT quests.id) AS c '.
                'FROM questgroups '.
                'INNER JOIN quests ON quests.questgroup_id = questgroups.id '.
                'WHERE questgroups.seminary_id = ? '.
                (!empty($questgroupId) ? sprintf('AND questgroups.id = %d ', $questgroupId) : null).
                (!empty($questtypeId) ? sprintf('AND quests.questtype_id = %d ', $questtypeId) : null).
                (!empty($title) ? sprintf('AND quests.title LIKE \'%%%s%%\' ', $title) : null),
                'i',
                $seminaryId
            );
            if(!empty($data)) {
                return $data[0]['c'];
            }


            return 0;
        }


        /**
         * Get all Quests for a Seminary order by their count of open
         * submissions.
         *
         * @param   int     $seminaryId     ID of Seminary
         * @param   int     $questgroupId   ID of Questgroup (optional)
         * @param   int     $questtypeId    ID of Questtype (optional)
         * @param   string  $title          Part of title to filter for (optional)
         * @param   int     $limit          Limit amount of Quests (optional)
         * @param   int     $offset         Offset (optional)
         * @return  array                   Quests for this Seminary
         */
        public function getQuestsForSeminaryByOpenSubmissions($seminaryId, $questgroupId=null, $questtypeId=null, $title=null, $limit=null, $offset=0)
        {
            return $this->db->query(
                'SELECT DISTINCT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, quests.wrong_text, quests.questsmedia_id, questgroups.title AS questgroup_title, questgroups.url AS questgroup_url, ('.
                    'SELECT count(DISTINCT quests_characters.character_id) '.
                    'FROM quests_characters '.
                    'WHERE quests_characters.quest_id = quests.id AND quests_characters.status = ? AND NOT EXISTS ('.
                        'SELECT id '.
                        'FROM quests_characters AS qc '.
                        'WHERE qc.quest_id = quests_characters.quest_id AND qc.character_id = quests_characters.character_id AND qc.created > quests_characters.created'.
                    ')'.
                ') AS opensubmissionscount '.
                'FROM questgroups '.
                'INNER JOIN quests ON quests.questgroup_id = questgroups.id '.
                'WHERE questgroups.seminary_id = ? '.
                (!empty($questgroupId) ? sprintf('AND questgroups.id = %d ', $questgroupId) : null).
                (!empty($questtypeId) ? sprintf('AND quests.questtype_id = %d ', $questtypeId) : null).
                (!empty($title) ? sprintf('AND quests.title LIKE \'%%%s%%\' ', $title) : null).
                'ORDER BY opensubmissionscount DESC '.
                (!empty($limit) ? sprintf('LIMIT %d, %d', $offset, $limit) : null),
                'ii',
                self::QUEST_STATUS_SUBMITTED,
                $seminaryId
            );
        }


        /**
         * Get all Quests that are linked to a Questtopic.
         *
         * @param   int     $questtopicId   ID of Questtopic
         * @return  array                   Quests for this Questtopic
         */
        public function getQuestsForQuesttopic($questtopicId)
        {
            return $this->db->query(
                'SELECT DISTINCT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, quests.wrong_text, quests.questsmedia_id, questgroups.url AS questgroup_url '.
                'FROM quests_questsubtopics '.
                'INNER JOIN questsubtopics ON questsubtopics.id = quests_questsubtopics.questsubtopic_id '.
                'INNER JOIN quests ON quests.id = quests_questsubtopics.quest_id '.
                'INNER JOIN questgroups ON questgroups.id = quests.questgroup_id '.
                'WHERE questsubtopics.questtopic_id = ? '.
                'ORDER BY quests.title ASC',
                'i',
                $questtopicId
            );
        }



        /**
         * Mark a Quest for a Character.
         *
         * @param   int     $questId        ID of Quest to mark
         * @param   int     $characterId    ID of Character to mark the Quest for
         * @param   int     $status         Quest status to mark
         * @param   boolean $repeated       Insert although status is already set for this Quest and Character
         */
        private function setQuestStatus($questId, $characterId, $status, $repeated=true)
        {
            // Check if status is already set
            if(!$repeated)
            {
                $count = $this->db->query(
                    'SELECT count(*) AS c '.
                    'FROM quests_characters '.
                    'WHERE quest_id = ? AND character_id = ? AND status = ?',
                    'iii',
                    $questId,
                    $characterId,
                    $status
                );
                if(!empty($count) && intval($count[0]['c']) > 0) {
                    return;
                }
            }

            // Set status
            $this->db->query(
                'INSERT INTO quests_characters '.
                '(quest_id, character_id, status) '.
                'VALUES '.
                '(?, ?, ?) ',
                'iii',
                $questId,
                $characterId,
                $status
            );
        }


        /**
         * Get the last status of a Quest for a Character.
         *
         * @param   int $questId        ID of Quest
         * @param   int $characterId    ID of Character to get status for
         * @return  int                 Last status
         */
        public function getLastQuestStatus($questId, $characterId)
        {
            $data = $this->db->query(
                'SELECT id, created, status '.
                'FROM quests_characters '.
                'WHERE quest_id = ? AND character_id = ? '.
                'ORDER BY created DESC '.
                'LIMIT 1',
                'ii',
                $questId, $characterId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Check if a Quest title already exists.
         *
         * @param   string  $title      Quest title to check
         * @param   int     $seminaryId ID of Seminary
         * @param   int     $questId    Do not check this ID (for editing)
         * @return  boolean             Whether Quest title exists or not
         */
        public function questTitleExists($title, $seminaryId, $questId=null)
        {
            $data = $this->db->query(
                'SELECT quests.id '.
                'FROM quests '.
                'INNER JOIN questgroups ON questgroups.id = quests.questgroup_id '.
                'WHERE questgroups.seminary_id = ? AND (quests.title = ? OR quests.url = ?)',
                'iss',
                $seminaryId,
                $title,
                \nre\core\Linker::createLinkParam($title)
            );

            return (!empty($data) && (is_null($questId) || $questId != $data[0]['id']));
        }


        /**
         * Create a new Quest.
         *
         * @param   int     $userId         User-ID that creates the new character
         * @param   int     $questgroupId   ID of Questgroup
         * @param   int     $questtypeId    ID of Questtype
         * @param   string  $title          Title for new Quest
         * @param   int     $xps            XPs for new Quest
         * @param   string  $task           Task for new Quest
         * @param   string  $entrytext      Entrytext for new Quest
         * @param   string  $wrongtext      Wrongtext for new Quest
         * @return  int                     ID of new Quest
         */
        public function createQuest($userId, $questgroupId, $questtypeId, $title, $xps, $task, $entrytext, $wrongtext)
        {
            $questId = null;
            $this->db->setAutocommit(false);
            try {
                // Get last Quests of Questgroup
                $lastQuests  = $this->getLastQuestsOfQuestgroup($questgroupId);

                // Create Quest
                $this->db->query(
                    'INSERT INTO quests '.
                    '(created_user_id, questgroup_id, questtype_id, title, url, xps, entry_text, wrong_text, task) '.
                    'VALUES '.
                    '(?, ?, ?, ?, ?, ?, ?, ?, ?)',
                    'iiississs',
                    $userId, $questgroupId, $questtypeId,
                    $title, \nre\core\Linker::createLinkParam($title),
                    $xps, $entrytext, $wrongtext, $task
                );
                $questId = $this->db->getInsertId();

                // Set previous Quest
                if(count($lastQuests) > 0) {
                    $this->setPreviousQuest($questId, $lastQuests[0]['id']);
                }

                $this->db->commit();
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }

            $this->db->setAutocommit(true);
            return $questId;
        }


        /**
         * Set the media for a Quest.
         *
         * @param   int $questId        ID of Quest to set media for
         * @param   int $questsmediaId  ID of Questsmedia to set
         */
        public function setQuestmedia($questId, $questsmediaId)
        {
            $this->db->query(
                'UPDATE quests '.
                'SET questsmedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $questsmediaId,
                $questId
            );
        }


        /**
         * Edit a new Quest.
         *
         * @param   int     $questId        ID of Quest to edit
         * @param   int     $questtypeId    ID of Questtype
         * @param   string  $title          New title for Quest
         * @param   int     $xps            XPs for Quest
         * @param   string  $task           New task for Quest
         * @param   string  $entrytext      New entrytext for Quest
         * @param   string  $wrongtext      New wrongtext for Quest
         */
        public function editQuest($questId, $questtypeId, $title, $xps, $task, $entrytext, $wrongtext)
        {
            $this->db->query(
                'UPDATE quests '.
                'SET questtype_id = ?, title = ?, url = ?, xps = ?, entry_text = ?, wrong_text = ?, task = ? '.
                'WHERE id = ?',
                'ississsi',
                $questtypeId,
                $title,
                \nre\core\Linker::createLinkParam($title),
                $xps,
                $entrytext,
                $wrongtext,
                $task,
                $questId
            );
        }


        /**
         * Copy all Quests from a Seminary.
         *
         * @param   int     $userId             ID of creating user
         * @param   int     $sourceSeminaryId   ID of Seminary to copy from
         * @param   array   $questgroupIds      Mapping of Questgroup-IDs from source Seminary to target Seminary
         * @param   array   $seminaryMediaIds   Mapping of Seminary-media-IDs from source Seminary to target Seminary (optional)
         * @return  array                       Mapping of Quest-IDs from source Seminary to target Seminary
         */
        public function copyQuests($userId, $sourceSeminaryId, $questgroupIds, $seminaryMediaIds=null)
        {
            $questIds = array();
            $questtextIds = array();

            // Get Quests
            $quests = $this->getQuestsForSeminary($sourceSeminaryId);

            // Copy each Quest
            foreach($quests as &$quest)
            {
                // Copy Quest
                $this->db->query(
                    'INSERT INTO quests '.
                    '(created_user_id, questgroup_id, questtype_id, title, url, xps, entry_text, wrong_text, task) '.
                    'SELECT ?, ?, questtype_id, title, url, xps, entry_text, wrong_text, task '.
                    'FROM quests '.
                    'WHERE id = ?',
                    'iii',
                    $userId, $questgroupIds[$quest['questgroup_id']],
                    $quest['id']
                );
                $questIds[$quest['id']] = $this->db->getInsertId();

                // Copy media
                if(!is_null($seminaryMediaIds) && !is_null($quest['questsmedia_id']))
                {
                    $this->Media->copyQuestsmedia($userId, $seminaryMediaIds[$quest['questsmedia_id']]);
                    $this->db->query(
                        'UPDATE quests '.
                        'SET questsmedia_id = ? '.
                        'WHERE id = ?',
                        'ii',
                        $seminaryMediaIds[$quest['questsmedia_id']],
                        $questIds[$quest['id']]
                    );
                }

                // Copy texts
                $questtextIds = $questtextIds + $this->Questtexts->copyQuesttexts($userId, $quest['id'], $questIds[$quest['id']], $seminaryMediaIds);

                // Copy content
                $questtype = $this->Questtypes->getQuesttypeById($quest['questtype_id']);
                if(!is_null($questtype['classname']))
                {
                    // Load Questtype Model
                    \hhu\z\models\QuesttypeModel::load($questtype['classname']);

                    // Construct Questtype Model
                    $questtypeModel = \hhu\z\models\QuesttypeModel::factory($questtype['classname']);

                    // Copy content
                    $questtypeModel->copyQuest($userId, $quest['id'], $questIds[$quest['id']], $seminaryMediaIds);
                }
            }

            // Copy flow
            // Do this after copying the Quests themselves to ensure all Quests
            // have their target IDs.
            foreach($quests as &$quest)
            {
                $previousQuests = $this->db->query(
                    'SELECT previous_quest_id '.
                    'FROM quests_previousquests '.
                    'WHERE quest_id = ?',
                    'i',
                    $quest['id']
                );
                foreach($previousQuests as &$previousQuest)
                {
                    $this->db->query(
                        'INSERT INTO quests_previousquests '.
                        '(quest_id, previous_quest_id) '.
                        'VALUES '.
                        '(?, ?)',
                        'ii',
                        $questIds[$quest['id']],
                        $questIds[$previousQuest['previous_quest_id']]
                    );
                }
            }


            return array(
                'quests' => $questIds,
                'questtexts' => $questtextIds
            );
        }


        /**
         * Delete a Quest of a Seminary.
         *
         * @param   int $questId    ID of Quest to delete
         */
        public function deleteQuest($questId)
        {
            $this->db->setAutocommit(false);
            try {
                // Set previous Quests of following Quests
                $previousQuests = $this->getPreviousQuests($questId);
                $nextQuests = $this->getNextQuests($questId);
                foreach($nextQuests as &$nextQuest) {
                    foreach($previousQuests as &$previousQuest) {
                        $this->setPreviousQuest($nextQuest['id'], $previousQuest['id']);
                    }
                }

                // Delete Quest
                $this->db->query('DELETE FROM quests WHERE id = ?', 'i', $questId);

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
         * Delete all Quests of a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to delete all Quests of
         */
        public function deleteQuestsOfSeminary($seminaryId)
        {
            // Get Quests
            $quests = $this->getQuestsForSeminary($seminaryId);

            // Delete each Quest
            foreach($quests as &$quest)
            {
                // Delete content
                $questtype = $this->Questtypes->getQuesttypeById($quest['questtype_id']);
                if(!is_null($questtype['classname']))
                {
                    // Load Questtype Model
                    \hhu\z\models\QuesttypeModel::load($questtype['classname']);

                    // Construct Questtype Model
                    $questtypeModel = \hhu\z\models\QuesttypeModel::factory($questtype['classname']);

                    // Delete content
                    $questtypeModel->deleteQuest($quest['id']);
                }

                // Delete Quests texts
                $this->Questtexts->deleteQuesttexts($quest['id']);

                // Delete quest
                $this->db->query('DELETE FROM quests WHERE id = ?', 'i', $quest['id']);
            }
        }

    }

?>
