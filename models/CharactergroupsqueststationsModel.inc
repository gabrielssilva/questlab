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
     * Model of the CharactergroupsqueststationsAgent to interact with
     * Charactergroupsqueststations-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactergroupsqueststationsModel extends \hhu\z\Model
    {
        /**
         * Status: Entered
         *
         * @var int;
         */
        const STATUS_ENTERED = 0;
        /**
         * Status: Unsolved
         *
         * @var int;
         */
        const STATUS_UNSOLVED = 2;
        /**
         * Status: Solved
         *
         * @var int;
         */
        const STATUS_SOLVED = 3;




        /**
         * Construct a new CharactergroupsqueststationsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get a Station by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int $stationId  ID of Station to get
         * @return  array           Station data
         */
        public function getStationById($stationId)
        {
            $data = $this->db->query(
                'SELECT id, charactergroupsquest_id, stationtype_id, title, url, stationpicture_id, task, latitude, longitude, righttext, wrongtext '.
                'FROM charactergroupsqueststations '.
                'WHERE id = ?',
                'i',
                $stationId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($stationId);
            }


            return $data[0];
        }


        /**
         * Get a Station by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int $stationId  ID of Station to get
         * @return  array           Station data
         */
        public function getStationByUrl($groupsquestId, $stationUrl)
        {
            $data = $this->db->query(
                'SELECT id, charactergroupsquest_id, stationtype_id, title, url, stationpicture_id, task, latitude, longitude, righttext, wrongtext '.
                'FROM charactergroupsqueststations '.
                'WHERE charactergroupsquest_id = ? AND url = ?',
                'is',
                $groupsquestId,
                $stationUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($stationUrl);
            }


            return $data[0];
        }

        /**
         * Get all Stations for a Character groups Quest.
         *
         * @param   int     $questId    ID of the Character groups Quest
         * @return  array               List of Stations
         */
        public function getStationsForQuest($questId)
        {
            return $this->db->query(
                'SELECT id, title, url, stationpicture_id, latitude, longitude '.
                'FROM charactergroupsqueststations '.
                'WHERE charactergroupsquest_id = ? '.
                'ORDER BY pos ASC',
                'i',
                $questId
            );
        }


        /**
         * Get all Stations for a Character groups Quest and a Character group.
         *
         * @param   int     $questId    ID of Character groups Quest
         * @param   int     $groupId    ID of Character group
         * @return  array               List of Station
         */
        public function getStationsForQuestAndGroup($questId, $groupId)
        {
            return $this->db->query(
                'SELECT charactergroupsqueststations.id, charactergroupsqueststations_charactergroups.created, title, url, stationpicture_id, latitude, longitude '.
                'FROM charactergroupsqueststations_charactergroups '.
                'INNER JOIN charactergroupsqueststations ON charactergroupsqueststations.id = charactergroupsqueststations_charactergroups.charactergroupsqueststation_id '.
                'WHERE '.
                    'charactergroupsqueststations_charactergroups.charactergroup_id = ? AND '.
                    'charactergroupsqueststations_charactergroups.status = ? AND '.
                    'charactergroupsquest_id = ? '.
                'ORDER BY charactergroupsqueststations_charactergroups.created ASC',
                'iii',
                $groupId,
                self::STATUS_ENTERED,
                $questId
            );
        }


        /**
         * Mark a Station as entered for a Character group.
         *
         * @param   int $stationId  ID of Station to mark
         * @param   int $groupId    ID of Character group
         */
        public function setStationEntered($stationId, $groupId)
        {
            $this->setStatus($stationId, $groupId, self::STATUS_ENTERED);
        }


        /**
         * Mark a Station as solved for a Character group.
         *
         * @param   int $stationId  ID of Station to mark
         * @param   int $groupId    ID of Character group
         */
        public function setStationSolved($stationId, $groupId)
        {
            $this->setStatus($stationId, $groupId, self::STATUS_SOLVED);
        }


        /**
         * Mark a Station as unsolved for a Character group.
         *
         * @param   int $stationId  ID of Station to mark
         * @param   int $groupId    ID of Character group
         */
        public function setStationUnsolved($stationId, $groupId)
        {
            $this->setStatus($stationId, $groupId, self::STATUS_UNSOLVED);
        }


        /**
         * Check if a Character group has tried to solve a Station.
         *
         * @param   int     $stationId  ID of Station to check
         * @param   int     $groupId    ID of Character group to check
         * @return  bool                Whether the group has tried the station or not
         */
        public function hasCharactergroupTriedStation($stationId, $groupId)
        {
            $data = $this->db->query(
                'SELECT created '.
                'FROM charactergroupsqueststations_charactergroups '.
                'WHERE charactergroupsqueststation_id = ? AND charactergroup_id = ? AND (status = ? OR status = ?)',
                'iiii',
                $stationId,
                $groupId,
                self::STATUS_UNSOLVED,
                self::STATUS_SOLVED
            );
            if(!empty($data)) {
                return $data[0]['created'];
            }


            return false;
        }


        /**
         * Check if a Character group has solved a Station.
         *
         * @param   int $questId    ID of Quest to check
         * @param   int $groupId    ID of Character to check
         * @result  boolean         Whether Character has solved the Quest or not
         */
        public function hasCharactergroupSolvedStation($stationId, $groupId)
        {
            $data = $this->db->query(
                'SELECT created '.
                'FROM charactergroupsqueststations_charactergroups '.
                'WHERE charactergroupsqueststation_id = ? AND charactergroup_id = ? AND status = ?',
                'iii',
                $stationId,
                $groupId,
                self::STATUS_SOLVED
            );
            if(!empty($data)) {
                return $data[0]['created'];
            }


            return false;
        }





        /**
         * Mark a Station for a Character group.
         *
         * @param   int $stationId  ID of Station to mark
         * @param   int $groupId    ID of Character group
         * @param   int $status     Status to set
         */
        private function setStatus($stationId, $groupId, $status)
        {
            // Check if status is already set
            $count = $this->db->query(
                'SELECT count(*) AS c '.
                'FROM charactergroupsqueststations_charactergroups '.
                'WHERE charactergroupsqueststation_id = ? AND charactergroup_id = ? AND status = ?',
                'iii',
                $stationId,
                $groupId,
                $status
            );
            if(!empty($count) && intval($count[0]['c']) > 0) {
                // Do not set status twice
                return;
            }

            // Set status
            $this->db->query(
                'INSERT INTO charactergroupsqueststations_charactergroups '.
                '(charactergroupsqueststation_id, charactergroup_id, status) '.
                'VALUES '.
                '(?, ?, ?) ',
                'iii',
                $stationId,
                $groupId,
                $status
            );
        }

    }

?>
