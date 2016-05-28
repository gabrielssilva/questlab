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
     * Model to interact with Questtexts-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuesttextsModel extends \hhu\z\Model
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('media');




        /**
         * Construct a new QuesttextsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get the first text of a Quest.
         *
         * @param   int     $questId    ID of a Quest
         * @return  string              First text of this Quest or NULL
         */
        public function getFirstQuestText($questId)
        {
            $prolog = $this->getQuesttextsOfQuest($questId, 'Prolog');
            if(!empty($prolog)) {
                return $prolog[0]['text'];
            }


            return null;
        }


        /**
         * Get all Questtexts for a Quest.
         *
         * @param   int     $questId            ID of the Quest
         * @param   string  $questtexttypeUrl   URL of the Questtexttype
         * @return  array                       All Questtexts for a Quest
         */
        public function getQuesttextsOfQuest($questId, $questtexttypeUrl=null)
        {
            if(is_null($questtexttypeUrl))
            {
                return $this->db->query(
                    'SELECT questtexts.id, questtexts.quest_id, questtexts.text, questtexts.pos, questtexts.out_text, questtexts.abort_text, questtexts.questsmedia_id, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
                    'FROM questtexts '.
                    'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
                    'WHERE questtexts.quest_id = ?',
                    'i',
                    $questId
                );
            }
            else
            {
                return $this->db->query(
                    'SELECT questtexts.id, questtexts.quest_id, questtexts.text, questtexts.pos, questtexts.out_text, questtexts.abort_text, questtexts.questsmedia_id, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
                    'FROM questtexts '.
                    'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
                    'WHERE questtexts.quest_id = ? and questtexttypes.url = ?',
                    'is',
                    $questId,
                    $questtexttypeUrl
                );
            }
        }


        /**
         * Get count of Questtexts for a Quest.
         *
         * @param   int     $questId            ID of the Quest
         * @param   string  $questtexttypeUrl   URL of the Questtexttype
         * @return  int                         Amount of Questtexts for a Quest
         */
        public function getQuesttextCountOfQuest($questId, $questtexttypeUrl=null)
        {
            if(is_null($questtexttypeUrl))
            {
                $data = $this->db->query(
                    'SELECT count(questtexts.id) AS c '.
                    'FROM questtexts '.
                    'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
                    'WHERE questtexts.quest_id = ?',
                    'i',
                    $questId
                );
            }
            else
            {
                $data = $this->db->query(
                    'SELECT count(questtexts.id) AS c '.
                    'FROM questtexts '.
                    'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
                    'WHERE questtexts.quest_id = ? and questtexttypes.url = ?',
                    'is',
                    $questId,
                    $questtexttypeUrl
                );
            }
            if(!empty($data)) {
                return $data[0]['c'];
            }


            return 0;
        }


        /**
         * Get corresponding Questtexts for a Questgroup.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $questgroupId   ID of Questgroup to get the Questtexst for
         * @param   array                   List of Questtexts
         */
        public function getRelatedQuesttextsForQuestgroup($questgroupId)
        {
            return $this->db->query(
                'SELECT questtexts.id, questtexts.text, questtexts.pos, questtexts.quest_id, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
                'FROM questgroups_questtexts '.
                'LEFT JOIN questtexts ON questtexts.id = questgroups_questtexts.questtext_id '.
                'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
                'WHERE questgroups_questtexts.questgroup_id = ?',
                'i',
                $questgroupId
            );
        }


        /**
         * Get the Questtext that was last entered by a Character.
         *
         * @param   int     $characterId    ID of Character
         * @param   array   $questtexts     List of Questtexts to look into
         * @return  array                   Questtext data
         */
        public function pickQuesttextLastEnteredByCharacter($characterId, $questtexts)
        {
            if(count($questtexts) == 0) {
                return null;
            }
            $data = $this->db->query(
                sprintf(
                    'SELECT quest_id '.
                    'FROM quests_characters '.
                    'WHERE character_id = ? AND quest_id IN (%s) AND status = ? '.
                    'ORDER BY created DESC '.
                    'LIMIT 1',
                    implode(',', array_map(function($q) { return intval($q['quest_id']); }, $questtexts))
                ),
                'ii',
                $characterId,
                \hhu\z\models\QuestsModel::QUEST_STATUS_ENTERED
            );
            if(count($data) == 0) {
                return $questtexts[0];
            }
            foreach($questtexts as &$questtext) {
                if($questtext['quest_id'] == $data[0]['quest_id']) {
                    return $questtext;
                }
            }


            return null;
        }


        /**
         * Get all registered Questtexttypes.
         *
         * @return  array   Registered Questtexttypes
         */
        public function getQuesttexttypes()
        {
            return $this->db->query(
                'SELECT id, type, url '.
                'FROM questtexttypes'
            );
        }


        /**
         * Get a Questtexttype by its URL.
         *
         * @param   string  $questtexttypeUrl   URL-type of Questtexttype
         * @return  array                       Questtexttype data
         */
        public function getQuesttexttypeByUrl($questtexttypeUrl)
        {
            $data = $this->db->query(
                'SELECT id, type, url '.
                'FROM questtexttypes '.
                'WHERE url = ?',
                's',
                $questtexttypeUrl
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Add a Questtexts to a Quest.
         *
         * @param   int     $userId             ID of user
         * @param   int     $questId            ID of Quest to add texts to
         * @param   string  $questtexttypeUrl   URL-type of Questtexttype of texts
         * @param   string  $text               Text to add.
         */
        public function addQuesttextToQuest($userId, $questId, $questtexttypeUrl, $text)
        {
            $questtexttype = $this->getQuesttexttypeByUrl($questtexttypeUrl);
            if(is_null($questtexttype)) {
                return;
            }

            // Get position
            $pos = $this->db->query(
                'SELECT COALESCE(MAX(pos),0)+1 AS pos '.
                'FROM questtexts '.
                'WHERE quest_id = ?',
                'i',
                $questId
            );
            $pos = $pos[0]['pos'];

            // Add Questtext
            $this->db->query(
                'INSERT INTO questtexts '.
                '(created_user_id, quest_id, questtexttype_id, pos, text) '.
                'VALUES '.
                '(?, ?, ?, ?, ?)',
                'iiiis',
                $userId, $questId, $questtexttype['id'], $pos,
                $text
            );


            // Return ID
            return $this->db->getInsertId();
        }


        /**
         * Set the media for a Quest text.
         *
         * @param   int $questtextId    ID of Quest text to set media for
         * @param   int $questsmediaId  ID of Questsmedia to set
         */
        public function setQuestmedia($questtextId, $questsmediaId)
        {
            $this->db->query(
                'UPDATE questtexts '.
                'SET questsmedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $questsmediaId,
                $questtextId
            );
        }


        /**
         * Edit a Quest text.
         *
         * @param   int $questtextId    ID of Quest text to edit
         * @param   string  $text       New text
         */
        public function editQuesttext($questtextId, $text)
        {
            $this->db->query(
                'UPDATE questtexts '.
                'SET text = ? '.
                'WHERE id = ?',
                'si',
                $text,
                $questtextId
            );
        }


        /**
         * Copy Quest texts from one Quest to another.
         *
         * @param   int     $userId             ID of copying user
         * @param   int     $sourceQuestId      ID of source Quest
         * @param   int     $targetQuestId      ID of target Quest
         * @param   array   $seminaryMediaIds   Mapping of Seminary-media-IDs from source Seminary to target Seminary (optional)
         */
        public function copyQuesttexts($userId, $sourceQuestId, $targetQuestId, $seminaryMediaIds=null)
        {
            $questtextIds = array();

            // Get Questtexts
            $questtexts = $this->getQuesttextsOfQuest($sourceQuestId);

            // Copy each text
            foreach($questtexts as &$text)
            {
                // Copy text
                $this->db->query(
                    'INSERT INTO questtexts '.
                    '(created_user_id, quest_id, questtexttype_id, pos, text, out_text, abort_text) '.
                    'SELECT ?, ?, questtexttype_id, pos, text, out_text, abort_text '.
                    'FROM questtexts '.
                    'WHERE id = ?',
                    'iii',
                    $userId, $targetQuestId,
                    $text['id']
                );
                $questtextIds[$text['id']] = $this->db->getInsertId();

                // Copy media
                if(!is_null($seminaryMediaIds) && !is_null($text['questsmedia_id']))
                {
                    $this->Media->copyQuestsmedia($userId, $seminaryMediaIds[$text['questsmedia_id']]);
                    $this->db->query(
                        'UPDATE questtexts '.
                        'SET questsmedia_id = ? '.
                        'WHERE id = ?',
                        'ii',
                        $seminaryMediaIds[$text['questsmedia_id']],
                        $questtextIds[$text['id']]
                    );
                }
            }


            return $questtextIds;
        }


        /**
         * Delete a Quest text.
         *
         * @param   array   $questtext  Data of Quest text to delete
         */
        public function deleteQuesttext($questtext)
        {
            // Delete Quest text
            $this->db->query('DELETE FROM questtexts WHERE id = ?', 'i', $questtext['id']);

            // Adjust positions
            $this->db->query(
                'UPDATE questtexts '.
                'SET pos = pos - 1 '.
                'WHERE quest_id = ? AND pos > ?',
                'ii',
                $questtext['quest_id'],
                $questtext['pos']
            );
        }


        /**
         * Delete all Quest texts of a Quest.
         *
         * @param   int $questId    ID of Quest to delete all texts of
         */
        public function deleteQuesttexts($questId)
        {
            $this->db->query('DELETE FROM questtexts WHERE quest_id = ?', 'i', $questId);
        }

    }

?>
