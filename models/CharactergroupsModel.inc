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
     * Model of the CharactergroupsAgent to interact with
     * Charactergroups-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactergroupsModel extends \hhu\z\Model
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('charactergroupsquests');




        /**
         * Construct a new CharactergroupsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get Character groups-groups of a Seminary.
         *
         * @param   int     $seminaryId ID of the corresponding Seminary
         * @return  array               Character groups-groups data
         */
        public function getGroupsroupsForSeminary($seminaryId)
        {
            return $this->db->query(
                'SELECT id, name, url, preferred '.
                'FROM charactergroupsgroups '.
                'WHERE seminary_id = ?',
                'i',
                $seminaryId
            );
        }


        /**
         * Get a Character groups-group by its URL.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $seminaryId     ID of the corresponding Seminary
         * @param   string  $groupsgroupUrl URL-name of the Character groups-group
         * @return  array                   Character groups-group data
         */
        public function getGroupsgroupByUrl($seminaryId, $groupsgroupUrl)
        {
            $data = $this->db->query(
                'SELECT id, name, url, preferred '.
                'FROM charactergroupsgroups '.
                'WHERE seminary_id = ? AND url = ?',
                'is',
                $seminaryId, $groupsgroupUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($groupsgroupUrl);
            }


            return $data[0];
        }


        /**
         * Get a Character groups-group by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $groupsgroupId  ID of the Character groups-group
         * @return  array                   Character groups-group data
         */
        public function getGroupsgroupById($groupsgroupId)
        {
            $data = $this->db->query(
                'SELECT id, seminary_id, name, url, preferred '.
                'FROM charactergroupsgroups '.
                'WHERE id = ?',
                'i',
                $groupsgroupId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($groupsgroupId);
            }


            return $data[0];
        }


        /**
         * Check if a Character groups-group name already exists.
         *
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $name           Name to check
         * @param   int     $groupsgroupId  Do not check this ID (for editing)
         * @return  boolean                 Whether name exists or not
         */
        public function characterGroupsgroupNameExists($seminaryId, $name, $groupsgroupId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM charactergroupsgroups '.
                'WHERE seminary_id = ? AND (name = ? OR url = ?)',
                'iss',
                $seminaryId,
                $name,
                \nre\core\Linker::createLinkParam($name)
            );


            return (!empty($data) && (is_null($groupsgroupId) || $groupsgroupId != $data[0]['id']));
        }


        /**
         * Create a new Character groups-group.
         *
         * @param   int     $userId     ID of user
         * @param   int     $seminaryId ID of Seminary
         * @param   string  $name       Name of new groups-group
         * @param   boolean $preferred  Whether groups-group is preferred or not
         * @return  int                 ID of newly created groups-group
         */
        public function createGroupsgroup($userId, $seminaryId, $name, $preferred)
        {
            $this->db->query(
                'INSERT INTO charactergroupsgroups '.
                '(created_user_id, seminary_id, name, url, preferred) '.
                'VALUES '.
                '(?, ?, ?, ?, ?)',
                'iissd',
                $userId,
                $seminaryId,
                $name,
                \nre\core\Linker::createLinkParam($name),
                $preferred
            );


            return $this->db->getInsertId();
        }


        /**
         * Edit a Character groups-group.
         *
         * @param   int     $groupsgroupId  ID of groups-group to edit
         * @param   string  $name           New name of groups-group
         * @param   boolean $preferred      Whether groups-group is preferred or not
         */
        public function editGroupsgroup($groupsgroupId, $name, $preferred)
        {
            $this->db->query(
                'UPDATE charactergroupsgroups '.
                'SET name = ?, url = ?, preferred = ? '.
                'WHERE id = ?',
                'ssdi',
                $name,
                \nre\core\Linker::createLinkParam($name),
                $preferred,
                $groupsgroupId
            );
        }


        /**
         * Copy all Character groups-groups of a Seminary.
         *
         * @param   int     $userId             ID of creating user
         * @param   int     $sourceSeminaryId   ID of Seminary to copy from
         * @param   int     $targetSeminaryId   ID of Seminary to copy to
         * @param   array                       Mapping of Character groups-groups-IDs from source Seminary to target Seminary
         */
        public function copyGroupsgroupsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId)
        {
            $groupsgroupIds = array();

            // Get Character groups
            $groupsgroups = $this->getGroupsroupsForSeminary($sourceSeminaryId);

            // Copy each Groups-group
            foreach($groupsgroups as &$group)
            {
                $this->db->query(
                    'INSERT INTO charactergroupsgroups '.
                    '(created_user_id, seminary_id, name, url, preferred) '.
                    'SELECT ?, ?, name, url, preferred '.
                    'FROM charactergroupsgroups '.
                    'WHERE id = ?',
                    'iii',
                    $userId, $targetSeminaryId,
                    $group['id']
                );
                $groupsgroupIds[$group['id']] = $this->db->getInsertId();
            }


            return $groupsgroupIds;
        }


        /**
         * Delete a Character groups-group.
         *
         * @param   int $groupsgroupId  ID of groups-group to delete
         */
        public function deleteGroupsgroup($groupsgroupId)
        {
            $this->db->query('DELETE FROM charactergroupsgroups WHERE id = ?', 'i', $groupsgroupId);
        }


        /**
         * Delete all Character groups-groups of a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to delete Character groups-groups of
         */
        public function deleteGroupsgroupsOfSeminary($seminaryId)
        {
            // Get Groupsgroups
            $charactergroupsgroups = $this->getGroupsroupsForSeminary($seminaryId);

            // Delete each Groupsgroup
            foreach($charactergroupsgroups as $groupsgroup)
            {
                // Delete Groups
                $this->deleteGroupsOfGroupsgroup($groupsgroup['id']);

                // Delete Groupsquests
                $this->Charactergroupsquests->deleteQuestsOfGroupsgroup($groupsgroup['id']);

                // Delete Groupsgroup
                $this->db->query('DELETE FROM charactergroupsgroups WHERE seminary_id = ?', 'i', $seminaryId);
            }
        }


        /**
         * Get Character groups for a Character groups-group.
         *
         * @param   int     $groupsgroupId  ID of the Character groups-group
         * @param   string  $sortorder      Field to sort by (optional)
         * @return  array                   Character groups
         */
        public function getGroupsForGroupsgroup($groupsgroupId, $sortorder='name')
        {
            // Set sort order
            switch($sortorder)
            {
                case 'xps':
                    $sortorder = 'xps DESC';
                break;
                case 'name':
                default:
                    $sortorder = 'name ASC';
                break;
            }

            // Get and return Character groups
            return $this->db->query(
                'SELECT '.
                    'charactergroups.id, charactergroups.name, charactergroups.url, charactergroups.motto, charactergroups.charactergroupsmedia_id, '.
                    'cache_charactergroups.xps '.
                'FROM charactergroups '.
                'LEFT JOIN cache_charactergroups ON cache_charactergroups.charactergroup_id = charactergroups.id '.
                'WHERE charactergroups.charactergroupsgroup_id = ? '.
                "ORDER BY $sortorder",
                'i',
                $groupsgroupId
            );
        }


        /**
         * Get Character groups for a Character.
         *
         * @param   int     $characterId    ID of the Character
         * @return  array                   Character groups
         */
        public function getGroupsForCharacter($characterId)
        {
            return $this->db->query(
                'SELECT '.
                    'charactergroups.id, charactergroups.charactergroupsgroup_id, charactergroups.name, charactergroups.url, charactergroups.charactergroupsmedia_id, '.
                    'cache_charactergroups.xps, '.
                    'charactergroupsgroups.id AS charactergroupsgroup_id, charactergroupsgroups.name AS charactergroupsgroup_name, charactergroupsgroups.url AS charactergroupsgroup_url '.
                'FROM characters_charactergroups '.
                'LEFT JOIN charactergroups ON charactergroups.id = characters_charactergroups.charactergroup_id '.
                'LEFT JOIN cache_charactergroups ON cache_charactergroups.charactergroup_id = charactergroups.id '.
                'LEFT JOIN charactergroupsgroups ON charactergroupsgroups.id = charactergroups.charactergroupsgroup_id '.
                'WHERE characters_charactergroups.character_id = ?',
                'i',
                $characterId
            );
        }


        /**
         * Get a Character group by its URL.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $groupsgroupId  ID of the Character groups-group
         * @param   string  $groupUrl       URL-name of the Character group
         * @return  array                   Character group data
         */
        public function getGroupByUrl($groupsgroupId, $groupUrl)
        {
            $data = $this->db->query(
                'SELECT '.
                    'charactergroups.id, charactergroups.name, charactergroups.url, charactergroups.motto, charactergroups.charactergroupsmedia_id, '.
                    'cache_charactergroups.xps '.
                'FROM charactergroups '.
                'LEFT JOIN cache_charactergroups ON cache_charactergroups.charactergroup_id = charactergroups.id '.
                'WHERE charactergroups.charactergroupsgroup_id = ? AND url = ?',
                'is',
                $groupsgroupId, $groupUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($groupUrl);
            }


            return $data[0];
        }


        /**
         * Get a Character group by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $groupId    ID of the Character group
         * @return  array               Character group data
         */
        public function getGroupById($groupId)
        {
            $data = $this->db->query(
                'SELECT '.
                    'charactergroups.id, charactergroups.name, charactergroups.url, charactergroups.motto, charactergroups.charactergroupsmedia_id, '.
                    'cache_charactergroups.xps '.
                'FROM charactergroups '.
                'LEFT JOIN cache_charactergroups ON cache_charactergroups.charactergroup_id = charactergroups.id '.
                'WHERE charactergroups.id = ?',
                'i',
                $groupId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($groupId);
            }


            return $data[0];
        }


        /**
         * Get the Character groups for a Quest.
         *
         * @param   int     $questId    ID of the Character groups Quest
         * @return  array               Character groups
         */
        public function getGroupsForQuest($questId)
        {
            $groups = $this->db->query(
                'SELECT charactergroups.id, charactergroups.name, charactergroups.url, charactergroupsquests_groups.created, charactergroupsquests_groups.xps_factor, charactergroupsquests.xps '.
                'FROM charactergroupsquests_groups '.
                'LEFT JOIN charactergroups ON charactergroups.id = charactergroupsquests_groups.charactergroup_id '.
                'LEFT JOIN charactergroupsquests ON charactergroupsquests.id = charactergroupsquests_groups.charactergroupsquest_id '.
                'WHERE charactergroupsquests_groups.charactergroupsquest_id = ? '.
                'ORDER BY xps_factor DESC',
                'i',
                $questId
            );
            foreach($groups as &$group) {
                $group['xps'] = round($group['xps'] * $group['xps_factor'], 1);
            }


            return $groups;
        }


        /**
         * Get Character groups that have entered a Character groups Quest
         * station.
         *
         * @param   int     $stationId  ID of station
         * @return  array               List of groups
         */
        public function getGroupsForQueststation($stationId)
        {
            return $this->db->query(
                'SELECT charactergroups.id, charactergroups.name, charactergroups.url, charactergroupsqueststations_charactergroups.created '.
                'FROM charactergroupsqueststations_charactergroups '.
                'INNER JOIN charactergroups ON charactergroups.id = charactergroupsqueststations_charactergroups.charactergroup_id '.
                'WHERE charactergroupsqueststations_charactergroups.charactergroupsqueststation_id = ? AND status = ? '.
                'ORDER BY charactergroupsqueststations_charactergroups.created ASC',
                'ii',
                $stationId,
                CharactergroupsqueststationsModel::STATUS_ENTERED
            );
        }


        /**
         * Check if a Character group name already exists.
         *
         * @param   int     $groupsgroupId  ID of Character groups-group
         * @param   string  $name           Name to check
         * @param   int     $groupId        Do not check this ID (for editing)
         * @return  boolean                 Whether name exists or not
         */
        public function characterGroupNameExists($groupsgroupId, $name, $groupId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM charactergroups '.
                'WHERE charactergroupsgroup_id = ? AND (name = ? OR url = ?)',
                'iss',
                $groupsgroupId,
                $name,
                \nre\core\Linker::createLinkParam($name)
            );


            return (!empty($data) && (is_null($groupId) || $groupId != $data[0]['id']));
        }


        /**
         * Create a new Character group.
         *
         * @param   int     $userId         ID of user
         * @param   int     $groupsgroupId  ID of Character groups-group
         * @param   string  $name           Name of new group
         * @param   string  $motto          Motto of new group
         * @return  int                     ID of newly created group
         */
        public function createGroup($userId, $groupsgroupId, $name, $motto)
        {
            $this->db->query(
                'INSERT INTO charactergroups '.
                '(created_user_id, charactergroupsgroup_id, name, url, motto) '.
                'VALUES '.
                '(?, ?, ?, ?, ?)',
                'iisss',
                $userId,
                $groupsgroupId,
                $name,
                \nre\core\Linker::createLinkParam($name),
                $motto
            );


            return $this->db->getInsertId();
        }


        /**
         * Set the media for a Character group.
         *
         * @param   int $groupId    ID of Character group to set media for
         * @param   int $mediaId    ID of Character groups media
         */
        public function setMediaForGroup($groupId, $mediaId)
        {
            $this->db->query(
                'UPDATE charactergroups '.
                'SET charactergroupsmedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $mediaId,
                $groupId
            );
        }


        /**
         * Edit a Character group.
         *
         * @param   int     $groupId    ID of Character group to edit
         * @param   string  $name       New name of group
         * @param   string  $motto      New motto of group
         */
        public function editGroup($groupId, $name, $motto)
        {
            $this->db->query(
                'UPDATE charactergroups '.
                'SET name = ?, url = ?, motto = ? '.
                'WHERE id = ?',
                'sssi',
                $name,
                \nre\core\Linker::createLinkParam($name),
                $motto,
                $groupId
            );
        }


        /**
         * Delete a Character group.
         *
         * @param   int $groupId    ID of Character group to delete
         */
        public function deleteGroup($groupId)
        {
            $this->db->query('DELETE FROM charactergroups WHERE id = ?', 'i', $groupId);
        }


        /**
         * Delete all Character groups of a groups-group.
         *
         * @param   int $groupsgroupId  ID of Character groups-group to delete groups of
         */
        public function deleteGroupsOfGroupsgroup($groupsgroupId)
        {
            $this->db->query('DELETE FROM charactergroups WHERE charactergroupsgroup_id = ?', 'i', $groupsgroupId);
        }


        /**
         * Get the rank of a XP-value of a Character.
         *
         * @param   int $groupsgroupId  ID of Seminary
         * @param   int $xps            XP-value to get rank for
         * @return  int                 Rank of XP-value
         */
        public function getXPRank($groupsgroupId, $xps)
        {
            $data = $this->db->query(
                'SELECT count(charactergroups.id) AS c '.
                'FROM charactergroups '.
                'LEFT JOIN cache_charactergroups ON cache_charactergroups.charactergroup_id = charactergroups.id '.
                'WHERE charactergroups.charactergroupsgroup_id = ? AND cache_charactergroups.xps > ?',
                'id',
                $groupsgroupId, $xps
            );
            if(!empty($data)) {
                return $data[0]['c'] + 1;
            }


            return 1;
        }


        /**
         * Add a Character to a Character group.
         *
         * @param   int $groupId        ID of Character group
         * @param   int $characterId    ID of Character to add
         */
        public function addCharacterToCharactergroup($groupId, $characterId)
        {
            $this->db->query(
                'INSERT INTO characters_charactergroups '.
                '(character_id, charactergroup_id) '.
                'VALUES '.
                '(?, ?)',
                'ii',
                $characterId,
                $groupId
            );
        }


        /**
         * Remove a Character from a Character group.
         *
         * @param   int $groupId        ID of Character group
         * @param   int $characterId    ID of Character to remove
         */
        public function removeCharacterFromCharactergroup($groupId, $characterId)
        {
            $this->db->query(
                'DELETE FROM characters_charactergroups '.
                'WHERE charactergroup_id = ? AND character_id = ?',
                'ii',
                $groupId,
                $characterId
            );
        }

    }

?>
