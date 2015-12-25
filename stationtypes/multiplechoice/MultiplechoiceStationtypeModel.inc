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
     * Model of the StationtypeAgent for a multiple choice task.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MultiplechoiceStationtypeModel extends \hhu\z\models\StationtypeModel
    {




        /**
         * Get all answers for a Station
         *
         * @param   int     $stationId  ID of Station
         * @return  array               List of answers
         */
        public function getAnswers($stationId)
        {
            return $this->db->query(
                'SELECT id, pos, answer, tick '.
                'FROM stationtypes_multiplechoice '.
                'WHERE station_id = ? '.
                'ORDER BY pos',
                'i',
                $stationId
            );
        }


        /**
         * Save Character group’s submitted answer for a station.
         *
         * @param   int     $stationId          ID of Station
         * @param   int     $charactergroupId   ID of Character group
         * @param   string  $answer             Submitted answer
         */
        public function setCharactergroupSubmission($answerId, $charactergroupId, $answer)
        {
            $this->db->query(
                'INSERT INTO stationtypes_multiplechoice_charactergroups '.
                '(stationtypes_multiplechoice_id, charactergroup_id, ticked) '.
                'VALUES '.
                '(?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'ticked = ?',
                'iiii',
                $answerId, $charactergroupId, $answer, $answer
            );
        }

    }

?>
