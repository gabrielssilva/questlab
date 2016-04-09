<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\stationtypes;


    /**
     * Model of the StationtypeAgent for a single choice task.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SinglechoiceStationtypeModel extends \hhu\z\models\StationtypeModel
    {




        /**
         * Copy a Station.
         *
         * @param   int $userId             ID of creating user
         * @param   int $sourceStationId    ID of Station to copy from
         * @param   int $targetStationId    ID of Station to copy to
         * @param   int $seminaryMediaIds   Mapping of SeminaryMedia-IDs from source Seminary to targetSeminary
         */
        public function copyStation($userId, $sourceStationId, $targetStationId, $seminaryMediaIds)
        {
            // Copy question
            $question = $this->getQuestion($sourceStationId);
            $this->db->query(
                'INSERT INTO stationtypes_singlechoice '.
                '(station_id, created_user_id) '.
                'VALUES '.
                '(?, ?)',
                'ii',
                $targetStationId, $userId
            );

            // Copy answers
            $answerIds = array();
            $answers = $this->getAnswers($sourceStationId);
            foreach($answers as &$answer) {
                $this->db->query(
                    'INSERT INTO stationtypes_singlechoice_answers '.
                    '(stationtypes_singlechoice_station_id, pos, answer) '.
                    'SELECT ?, pos, answer '.
                    'FROM stationtypes_singlechoice_answers '.
                    'WHERE id = ?',
                    'ii',
                    $targetStationId,
                    $answer['id']
                );
                $answerIds[$answer['id']] = $this->db->getInsertId();
            }

            // Set correct answer
            if(!is_null($question['answer_id'])) {
                $this->setCorrectAnswer(
                    $targetStationId,
                    $answerIds[$question['answer_id']]
                );
            }
        }


        /**
         * Set the question for a Station.
         * 
         * @param   int $userId     ID of creating user
         * @param   int $stationId  ID of Station to set
         */
        public function setQuestion($userId, $stationId)
        {
            $this->db->query(
                'INSERT INTO stationtypes_singlechoice '.
                '(station_id, created_user_id) '.
                'VALUES '.
                '(?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'created_user_id = ?',
                'iii',
                $stationId,
                $userId,
                $userId
            );
        }


        /**
         * Get the question for a Station.
         *
         * @param   int     $stationId  ID of Station to get question for
         * @return  array               Question data
         */
        public function getQuestion($stationId)
        {
            $data = $this->db->query(
                'SELECT station_id, created, answer_id '.
                'FROM stationtypes_singlechoice '.
                'WHERE station_id = ?',
                'i',
                $stationId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Get all answers for a question.
         *
         * @param   int     $stationId  ID of Station
         * @return  array               List of answers
         */
        public function getAnswers($stationId)
        {
            return $this->db->query(
                'SELECT id, pos, answer '.
                'FROM stationtypes_singlechoice_answers '.
                'WHERE stationtypes_singlechoice_station_id = ? '.
                'ORDER BY pos',
                'i',
                $stationId
            );
        }


        /**
         * Set an answer for a Station.
         *
         * @param   int     $userId     ID of creating user
         * @param   int     $stationId  ID of Station to set answer for
         * @param   int     $pos        Position of answer
         * @param   string  $answer     Answer text
         */
        public function setAnswer($userId, $stationId, $pos, $answer)
        {
            // Check if answer already exists
            $data = $this->db->query(
                'SELECT id '.
                'FROM stationtypes_singlechoice_answers '.
                'WHERE stationtypes_singlechoice_station_id = ? AND pos = ?',
                'ii',
                $stationId,
                $pos
            );

            // Set new answer
            if(!empty($data))
            {
                // Update answer
                $answerId = $data[0]['id'];
                $this->db->query(
                    'UPDATE stationtypes_singlechoice_answers '.
                    'SET answer = ? '.
                    'WHERE id = ?',
                    'si',
                    $answer,
                    $answerId
                );

                return $answerId;
            }
            else
            {
                // Insert new answer
                $this->db->query(
                    'INSERT INTO stationtypes_singlechoice_answers '.
                    '(stationtypes_singlechoice_station_id, pos, answer) '.
                    'VALUES '.
                    '(?, ?, ?)',
                    'iis',
                    $stationId,
                    $pos,
                    $answer
                );

                // Get ID of inserted anser
                return $this->db->getInsertId();
            }
        }


        /**
         * Set the correct answer for a Station/question.
         *
         * @param   int $stationId  ID of Station to set
         * @param   int $answerId   ID of correct answer
         */
        public function setCorrectAnswer($stationId, $answerId)
        {
            $this->db->query(
                'UPDATE stationtypes_singlechoice '.
                'SET answer_id = ? '.
                'WHERE station_id = ?',
                'ii',
                $answerId,
                $stationId
            );
        }


        /**
         * Delete all answers of a Station above a given index.
         *
         * @param   int $stationId  ID of Station to delete answers for
         * @param   int $offset     Offset to delete answers above
         */
        public function deleteAnswers($stationId, $offset)
        {
            // Delete answers
            $this->db->query(
                'DELETE FROM stationtypes_singlechoice_answers '.
                'WHERE stationtypes_singlechoice_station_id = ? AND pos > ?',
                'ii',
                $stationId,
                $offset
            );
        }


        /**
         * Save Character group’s submitted answer for a station/question.
         *
         * @param   int     $stationId          ID of Station/question
         * @param   int     $charactergroupId   ID of Character group
         * @param   int     $answerId           ID of submitted answer
         */
        public function setCharactergroupSubmission($stationId, $charactergroupId, $answerId)
        {
            $this->db->query(
                'INSERT INTO stationtypes_singlechoice_charactergroups '.
                '(stationtypes_singlechoice_station_id, charactergroup_id, answer_id) '.
                'VALUES '.
                '(?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'answer_id = ?',
                'iiii',
                $stationId, $charactergroupId, $answerId, $answerId
            );
        }


        /**
         * Get Character group’s submission for a Station/question.
         *
         * @param   int     $stationId          ID of Station/question
         * @param   int     $charactergroupId   ID of Character group
         * @return  int                         ID of submitted answer
         */
        public function getCharactergroupSubmission($stationId, $charactergroupId)
        {
            $data = $this->db->query(
                'SELECT answer_id '.
                'FROM stationtypes_singlechoice_charactergroups '.
                'WHERE stationtypes_singlechoice_station_id = ? AND charactergroup_id = ?',
                'ii',
                $stationId, $charactergroupId
            );
            if(!empty($data)) {
                return intval($data[0]['answer_id']);
            }


            return null;
        }

    }

?>
