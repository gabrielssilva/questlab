<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\questtypes;


    /**
     * Model of the MultiplechoiceQuesttypeAgent for multiple choice.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MultiplechoiceQuesttypeModel extends \hhu\z\models\QuesttypeModel
    {




        /**
         * Copy a Quest
         *
         * @param   int $userId             ID of creating user
         * @param   int $sourceQuestId      ID of Quest to copy from
         * @param   int $targetQuestId      ID of Quest to copy to
         * @param   int $seminaryMediaIds   Mapping of SeminaryMedia-IDs from source Seminary to targetSeminary
         */
        public function copyQuest($userId, $sourceQuestId, $targetQuestId, $seminaryMediaIds)
        {
            // Get questions
            $questions = $this->getQuestionsOfQuest($sourceQuestId);

            // Copy each question
            foreach($questions as &$question)
            {
                // Copy question
                $this->db->query(
                    'INSERT INTO questtypes_multiplechoice '.
                    '(created_user_id, quest_id, pos, question) '.
                    'SELECT ?, ?, pos, question '.
                    'FROM questtypes_multiplechoice '.
                    'WHERE id = ?',
                    'iii',
                    $userId, $targetQuestId,
                    $question['id']
                );
                $targetQuestionId = $this->db->getInsertId();

                // Copy answers
                $this->db->query(
                    'INSERT INTO questtypes_multiplechoice_answers '.
                    '(created_user_id, questtypes_multiplechoice_id, pos, answer, tick) '.
                    'SELECT ?, ?, pos, answer, tick '.
                    'FROM questtypes_multiplechoice_answers '.
                    'WHERE questtypes_multiplechoice_id = ?',
                    'iii',
                    $userId, $targetQuestionId,
                    $question['id']
                );
            }
        }


        /**
         * Get the count of multiple choice questions for a Quest.
         *
         * @param   int $questId    ID of Quest to get count for
         * @return  int         Conut of questions
         */
        public function getQuestionsCountOfQuest($questId)
        {
            $data = $this->db->query(
                'SELECT count(id) AS c '.
                'FROM questtypes_multiplechoice '.
                'WHERE quest_id = ?',
                'i',
                $questId
            );
            if(!empty($data)) {
                return $data[0]['c'];
            }


            return 0;
        }


        /**
         * Get all multiple choice questions of a Quest.
         *
         * @param   int $questId    ID of Quest
         * @return  array           Multiple choice questions
         */
        public function getQuestionsOfQuest($questId)
        {
            return $this->db->query(
                'SELECT id, pos, question '.
                'FROM questtypes_multiplechoice '.
                'WHERE quest_id = ?',
                'i',
                $questId
            );
        }


        /**
         * Get one multiple choice question of a Quest.
         *
         * @param   int $questId    ID of Quest
         * @param   int $pos        Position of question
         * @return  array           Question data
         */
        public function getQuestionOfQuest($questId, $pos)
        {
            $data = $this->db->query(
                'SELECT id, pos, question '.
                'FROM questtypes_multiplechoice '.
                'WHERE quest_id = ? AND pos = ?',
                'ii',
                $questId, $pos
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Get all answers of a multiple choice question.
         *
         * @param   int $questionId ID of multiple choice question
         * @return  array           Answers of question
         */
        public function getAnswersOfQuestion($questionId)
        {
            return $this->db->query(
                'SELECT id, pos, answer, tick '.
                'FROM questtypes_multiplechoice_answers '.
                'WHERE questtypes_multiplechoice_id = ?',
                'i',
                $questionId
            );
        }


        /**
         * Save Character’s submitted answer for one option.
         *
         * @param   int $answerId   ID of multiple choice answer
         * @param   int $characterId    ID of Character
         * @param   boolean $answer     Submitted answer for this option
         */
        public function setCharacterSubmission($answerId, $characterId, $answer)
        {
            $this->db->query(
                'INSERT INTO questtypes_multiplechoice_characters '.
                '(questtypes_multiplechoice_answer_id, character_id, ticked) '.
                'VALUES '.
                '(?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'ticked = ?',
                'iiii',
                $answerId, $characterId, $answer, $answer
            );
        }


        /**
         * Get answer of one option submitted by Character.
         *
         * @param   int $answerId   ID of multiple choice answer
         * @param   int $characterId    ID of Character
         * @return  boolean         Submitted answer of Character or false
         */
        public function getCharacterSubmission($answerId, $characterId)
        {
            $data = $this->db->query(
                'SELECT ticked '.
                'FROM questtypes_multiplechoice_characters '.
                'WHERE questtypes_multiplechoice_answer_id = ? AND character_id = ? ',
                'ii',
                $answerId, $characterId
            );
            if(!empty($data)) {
                return $data[0]['ticked'];
            }


            return false;
        }


        /**
         * Set a question for a multiplechoice Quest.
         *
         * @param   int $userId     ID of user
         * @param   int $questId    ID of Quest to set question for
         * @param   int $pos        Position of question
         * @param   string  $question   Question text
         */
        public function setQuestionForQuest($userId, $questId, $pos, $question)
        {
            $this->db->query(
                'INSERT INTO questtypes_multiplechoice '.
                '(created_user_id, quest_id, pos, question) '.
                'VALUES '.
                '(?, ?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'question = ?',
                'iiiss',
                $userId,
                $questId,
                $pos,
                $question,
                $question
            );
        }


        /**
         * Delete questions of a Quest.
         *
         * @param   int $questId    ID of Quest to delete question of
         * @param   int $offset     Only delete questions after this position
         */
        public function deleteQuestionsOfQuest($questId, $offset)
        {
            $this->db->query(
                'DELETE FROM questtypes_multiplechoice '.
                'WHERE quest_id = ? AND pos > ?',
                'ii',
                $questId,
                $offset
            );
        }


        /**
         * Set an answer for a question.
         *
         * @param   int $userId     ID of user
         * @param   int $questId    ID of Quest to set answer for
         * @param   int $questionPos    Position of question
         * @param   int $answerPos  Position of answer
         * @param   string  $answer     Answer text
         * @param   boolean $tick       Whether answer is correct or not
         */
        public function setAnswerForQuestion($userId, $questId, $questionPos, $answerPos, $answer, $tick)
        {
            // Get question
            $question = $this->getQuestionOfQuest($questId, $questionPos);
            if(is_null($question)) {
                return;
            }

            // Add answer
            $this->db->query(
                'INSERT INTO questtypes_multiplechoice_answers '.
                '(created_user_id, questtypes_multiplechoice_id, pos, answer, tick) '.
                'VALUES '.
                '(?, ?, ?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'answer = ?, tick = ?',
                'iiisisi',
                $userId,
                $question['id'],
                $answerPos,
                $answer,
                $tick,
                $answer,
                $tick
            );
        }


        /**
         * Delete answers of a question.
         *
         * @param   int $questId    ID of Quest to delete answers for
         * @param   int $questionPos    Position of question
         * @param   int $offset     Only delete answers after this position
         */
        public function deleteAnswersOfQuestion($questId, $questionPos, $offset)
        {
            // Get question
            $question = $this->getQuestionOfQuest($questId, $questionPos);
            if(is_null($question)) {
                return;
            }

            // Delete answer
            $this->db->query(
                'DELETE FROM questtypes_multiplechoice_answers '.
                'WHERE questtypes_multiplechoice_id = ? AND pos > ?',
                'ii',
                $question['id'],
                $offset
            );
        }

    }

?>
