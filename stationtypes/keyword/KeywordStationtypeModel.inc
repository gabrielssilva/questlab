<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\stationtypes;


    /**
     * Model of the StationtypeAgent for keyword access.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class KeywordStationtypeModel extends \hhu\z\models\StationtypeModel
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
            // Copy keyword
            $this->db->query(
                'INSERT INTO stationtypes_keyword '.
                '(station_id, created_user_id, keyword_regex) '.
                'SELECT ?, ?, keyword_regex '.
                'FROM stationtypes_keyword '.
                'WHERE station_id = ?',
                'iii',
                $targetStationId, $userId,
                $sourceStationId
            );
        }


        /**
         * Get the task of a keyword Station
         *
         * @param   int $stationId  ID of Station
         * @return  array           Task data
         */
        public function getKeywordTask($stationId)
        {
            $data = $this->db->query(
                'SELECT keyword_regex '.
                'FROM stationtypes_keyword '.
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
         * Set the keyword (regex) for a Station.
         *
         * @param   int     $userId     ID of creating user
         * @param   int     $stationId  ID ot Station to set keyword for
         * @param   string  $keyword    Keyword (regex)
         */
        public function setKeywordForStation($userId, $stationId, $keyword)
        {
            $this->db->query(
                'INSERT INTO stationtypes_keyword '.
                '(station_id, created_user_id, keyword_regex) '.
                'VALUES '.
                '(?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'created_user_id = ?, keyword_regex = ?',
                'iisis',
                $stationId, $userId, $keyword,
                $userId, $keyword
            );
        }


        /**
         * Save Character group’s submitted answer for a station.
         *
         * @param   int     $stationId          ID of Station
         * @param   int     $charactergroupId   ID of Character group
         * @param   string  $answer             Submitted answer
         */
        public function setCharactergroupSubmission($stationId, $charactergroupId, $answer)
        {
            $this->db->query(
                'INSERT INTO stationtypes_keyword_charactergroups '.
                '(station_id, charactergroup_id, keyword) '.
                'VALUES '.
                '(?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'keyword = ?',
                'iiss',
                $stationId, $charactergroupId, $answer, $answer
            );
        }


        /**
         * Get Character group’s submitted answer for a station.
         *
         * @param   int     $stationId          ID of Station
         * @param   int     $charactergroupId   ID of Character group
         * @return  string                      Submitted answer
         */
        public function getCharactergroupSubmission($stationId, $charactergroupId)
        {
            $data = $this->db->query(
                'SELECT keyword '.
                'FROM stationtypes_keyword_charactergroups '.
                'WHERE station_id = ? AND charactergroup_id = ?',
                'ii',
                $stationId, $charactergroupId
            );
            if(!empty($data)) {
                return $data[0]['keyword'];
            }


            return null;
        }

    }

?>
