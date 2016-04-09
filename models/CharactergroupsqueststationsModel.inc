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
         * Required models
         *
         * @var array
         */
        public $models = array('stationtypes');




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
                'SELECT id, charactergroupsquest_id, stationtype_id, title, url, stationpicture_id, prolog, task, latitude, longitude, righttext, wrongtext, rightimage_id, rightav_id, wrongimage_id, wrongav_id '.
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
         * Get a Station by its URL.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $groupsquestId  ID of Character groups Quest
         * @param   string  $stationUrl     URL-title of Station to get
         * @return  array                   Station data
         */
        public function getStationByUrl($groupsquestId, $stationUrl)
        {
            $data = $this->db->query(
                'SELECT id, charactergroupsquest_id, stationtype_id, title, url, stationpicture_id, prolog, task, latitude, longitude, righttext, wrongtext, rightimage_id, rightav_id, wrongimage_id, wrongav_id '.
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
         * Get a Station by its Hash.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $stationUrl Hash of Station to get
         * @return  array               Station data
         */
        public function getStationByHash($stationHash)
        {
            $data = $this->db->query(
                'SELECT id, charactergroupsquest_id, stationtype_id, title, url, stationpicture_id, prolog, task, latitude, longitude, righttext, wrongtext, rightimage_id, rightav_id, wrongimage_id, wrongav_id '.
                'FROM charactergroupsqueststations '.
                'WHERE url = ?',
                's',
                $stationHash
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($stationHash);
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
                'SELECT id, stationtype_id, title, url, stationpicture_id, latitude, longitude, rightimage_id, rightav_id, wrongimage_id, wrongav_id '.
                'FROM charactergroupsqueststations '.
                'WHERE charactergroupsquest_id = ? '.
                'ORDER BY pos ASC',
                'i',
                $questId
            );
        }


        /**
         * Get all Stations for a Character groups Quest that have been entered
         * by a Character group.
         *
         * @param   int     $questId    ID of Character groups Quest
         * @param   int     $groupId    ID of Character group
         * @return  array               List of Station
         */
        public function getEnteredStationsForQuestAndGroup($questId, $groupId)
        {
            return $this->getStationsForQuestAndGroup($questId, $groupId, self::STATUS_ENTERED);
        }


        /**
         * Get all Stations for a Character groups Quest that have been solved 
         * by a Character group.
         *
         * @param   int     $questId    ID of Character groups Quest
         * @param   int     $groupId    ID of Character group
         * @return  array               List of Station
         */
        public function getSolvedStationsForQuestAndGroup($questId, $groupId)
        {
            return $this->getStationsForQuestAndGroup($questId, $groupId, self::STATUS_SOLVED);
        }


        /**
         * Copy all Character groups Quest Stations of a Seminary.
         *
         * @param   int     $userId                     ID of creating user
         * @param   array   $charactergroupsquestIds    Mapping of Character groups Quest-IDs from source Seminary to target Seminary
         * @param   array   $seminaryMediaIds           Mapping of Seminary-media-IDs from source Seminary to target Seminary (optional)
         */
        public function copyStationsOfSeminary($userId, $charactergroupsquestIds, $seminaryMediaIds)
        {
            // Go through each Quest
            foreach($charactergroupsquestIds as $sourceQuestId => $targetQuestId)
            {
                // Get Stations
                $stations = $this->getStationsForQuest($sourceQuestId);

                // Copy each station
                foreach($stations as &$station)
                {
                    // Copy Station
                    $this->db->query(
                        'INSERT INTO charactergroupsqueststations '.
                        '(charactergroupsquest_id, stationtype_id, title, url, pos, stationpicture_id, prolog, task, latitude, longitude, righttext, wrongtext, rightimage_id, rightav_id, wrongimage_id, wrongav_id) '.
                        'SELECT ?, stationtype_id, title, url, pos, ?, prolog, task, latitude, longitude, righttext, wrongtext, ?, ?, ?, ? '.
                        'FROM charactergroupsqueststations '.
                        'WHERE id = ?',
                        'iiiiiii',
                        $targetQuestId,
                        (!is_null($station['stationpicture_id'])) ? $seminaryMediaIds[$station['stationpicture_id']] : null,
                        (!is_null($station['rightimage_id'])) ? $seminaryMediaIds[$station['rightimage_id']] : null,
                        (!is_null($station['rightav_id'])) ? $seminaryMediaIds[$station['rightav_id']] : null,
                        (!is_null($station['wrongimage_id'])) ? $seminaryMediaIds[$station['wrongimage_id']] : null,
                        (!is_null($station['wrongav_id'])) ? $seminaryMediaIds[$station['wrongav_id']] : null,
                        $station['id']
                    );
                    $targetStationId = $this->db->getInsertId();

                    // Copy content
                    $stationtype = $this->Stationtypes->getStationtypeById($station['stationtype_id']);
                    if(!is_null($stationtype['classname']))
                    {
                        // Load Stationtype Model
                        \hhu\z\models\StationtypeModel::load($stationtype['classname']);

                        // Construct Station Model
                        $stationtypeModel = \hhu\z\models\StationtypeModel::factory($stationtype['classname']);

                        // Copy content
                        $stationtypeModel->copyStation($userId, $station['id'], $targetStationId, $seminaryMediaIds);
                    }
                }
            }
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
         * Check if a Character group has entered a Station.
         *
         * @param   int     $stationId  ID of Station to check
         * @param   int     $groupId    ID of Character group to check
         * @return  bool                Whether the group has tried the station or not
         */
        public function hasCharactergroupEnteredStation($stationId, $groupId)
        {
            $data = $this->db->query(
                'SELECT created '.
                'FROM charactergroupsqueststations_charactergroups '.
                'WHERE charactergroupsqueststation_id = ? AND charactergroup_id = ? AND status >= ?',
                'iii',
                $stationId,
                $groupId,
                self::STATUS_ENTERED
            );
            if(!empty($data)) {
                return $data[0]['created'];
            }


            return false;
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
         * Check if a Character groups Quest Station title already exists.
         *
         * @param   int     $questId    ID of Character groups Quest
         * @param   string  $title      Station title to check
         * @param   int     $stationId  Do not check this ID (for editing)
         * @return  boolean             Whether Station title exists or not
         */
        public function stationTitleExists($questId, $title, $stationId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM charactergroupsqueststations '.
                'WHERE charactergroupsquest_id = ? AND (title = ? OR url = ?)',
                'iss',
                $questId,
                $title,
                \nre\core\Linker::createLinkParam($title)
            );

            return (!empty($data) && (is_null($stationId) || $stationId != $data[0]['id']));
        }


        /**
         * Set the media for a Character groups Quest Station.
         *
         * @param   int $stationId  ID of Station to upload media for
         * @param   int $mediaId    ID of Station media
         */
        public function setPictureForStation($stationId, $mediaId)
        {
            $this->db->query(
                'UPDATE charactergroupsqueststations '.
                'SET stationpicture_id = ? '.
                'WHERE id = ?',
                'ii',
                $mediaId,
                $stationId
            );
        }


        /**
         * Set the image for the right-text.
         *
         * @param   int $stationId  ID of Station to set image for
         * @param   int $mediaId    ID of Seminary media to set
         */
        public function setRightImageForStation($stationId, $mediaId)
        {
            $this->setMediaForStation($stationId, $mediaId, 'rightimage_id');
        }


        /**
         * Set the audio/video for the right-text.
         *
         * @param   int $stationId  ID of Station to set audio/video for
         * @param   int $mediaId    ID of Seminary media to set
         */
        public function setRightAVForStation($stationId, $mediaId)
        {
            $this->setMediaForStation($stationId, $mediaId, 'rightav_id');
        }


        /**
         * Set the image for the wrong-text.
         *
         * @param   int $stationId  ID of Station to set image for
         * @param   int $mediaId    ID of Seminary media to set
         */
        public function setWrongImageForStation($stationId, $mediaId)
        {
            $this->setMediaForStation($stationId, $mediaId, 'wrongimage_id');
        }


        /**
         * Set the audio/video for the wrong-text.
         *
         * @param   int $stationId  ID of Station to set audio/video for
         * @param   int $mediaId    ID of Seminary media to set
         */
        public function setWrongAvForStation($stationId, $mediaId)
        {
            $this->setMediaForStation($stationId, $mediaId, 'wrongav_id');
        }


        /**
         * Create a new Character groups Quest Station.
         *
         * @param   int     $questId        ID of Quest to create the Station for
         * @param   int     $stationtypeId  ID of Station type
         * @param   string  $title          Title
         * @param   string  $prolog         Prolog
         * @param   string  $task           Task description
         * @param   int     $latitude       GPS latitude
         * @param   int     $longitude      GPS longitude
         * @param   string  $righttext      Text for correctly solved task
         * @param   string  $wrongtext      Text for failed task
         * @return  int                     ID of newly created station
         */
        public function createStation($questId, $stationtypeId, $title, $prolog, $task, $latitude, $longitude, $righttext, $wrongtext)
        {
            // Get position
            $pos = $this->db->query(
                'SELECT COALESCE(MAX(pos),0)+1 AS pos '.
                'FROM charactergroupsqueststations '.
                'WHERE charactergroupsquest_id = ?',
                'i',
                $questId
            );
            $pos = $pos[0]['pos'];

            // Create Station
            $this->db->query(
                'INSERT INTO charactergroupsqueststations '.
                '(charactergroupsquest_id, stationtype_id, title, url, pos, prolog, task, latitude, longitude, righttext, wrongtext) '.
                'VALUES '.
                '(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)',
                'iississddss',
                $questId, $stationtypeId, $title,
                \hhu\z\Utils::createRandomHash(), $pos,
                $prolog, $task, $latitude, $longitude, $righttext, $wrongtext
            );

            
            // Return ID of newly created Station
            return $this->db->getInsertId();
        }


        /**
         * Edit a Character groups Quest Station.
         *
         * @param   int     $stationId      ID of Station to edit
         * @param   int     $stationtypeId  ID of Station type
         * @param   string  $title          Title
         * @param   string  $prolog         Prolog
         * @param   string  $task           Task description
         * @param   int     $latitude       GPS latitude
         * @param   int     $longitude      GPS longitude
         * @param   string  $righttext      Text for correctly solved task
         * @param   string  $wrongtext      Text for failed task
         */
        public function editStation($stationId, $stationtypeId, $title, $prolog, $task, $latitude, $longitude, $righttext, $wrongtext)
        {
            $this->db->query(
                'UPDATE charactergroupsqueststations '.
                'SET stationtype_id = ?, title = ?, prolog = ?, task = ?, latitude = ?, longitude = ?, righttext = ?, wrongtext = ? '.
                'WHERE id = ?',
                'isssddssi',
                $stationtypeId, $title,
                $prolog, $task, $latitude, $longitude, $righttext, $wrongtext,
                $stationId
            );
        }


        /**
         * Delete a Character-group Quest station.
         *
         * @param   int $stationId  ID of Station to delete
         */
        public function deleteStation($stationId)
        {
            $this->db->query(
                'DELETE FROM charactergroupsqueststations '.
                'WHERE ID = ?',
                'i',
                $stationId
            );
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


        /**
         * Add a medium for a Character groups Quest Station.
         *
         * @param   int     $stationId  ID of Station to upload media for
         * @param   int     $mediaId    ID of Seminary media
         * @param   string  $field      Field name to set media to
         */
        private function setMediaForStation($stationId, $mediaId, $field)
        {
            $this->db->query(
                sprintf(
                    'UPDATE charactergroupsqueststations '.
                    'SET %s = ? '.
                    'WHERE id = ?',
                    $field
                ),
                'ii',
                $mediaId,
                $stationId
            );
        }


        /**
         * Get all Stations for a Character groups Quest with a minimum status.
         *
         * @param   int     $questId    ID of Character groups Quest
         * @param   int     $groupId    ID of Character group
         * @param   int     $statusMin  Minimum status
         * @return  array               List of Station
         */
        private function getStationsForQuestAndGroup($questId, $groupId, $statusMin)
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
                $statusMin,
                $questId
            );
        }

    }

?>
