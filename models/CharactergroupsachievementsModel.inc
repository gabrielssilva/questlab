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
     * Model to interact with Charactergroupsachievements-tables.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactergroupsachievementsModel extends \hhu\z\Model
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('media');




        /**
         * Construct a new CharactergroupsachievementsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get an Achievement by its URL.
         *
         * @param   int     $groupsgroupId  ID of Character groups-group
         * @param   string  $achievementUrl URL-title of Achievement
         * @return  array                   Achievement data
         */
        public function getAchievementByUrl($groupsgroupId, $achievementUrl)
        {
            $data = $this->db->query(
                'SELECT id, charactergroupsgroup_id, pos, title, url, hash, description, achievementsmedia_id '.
                'FROM charactergroupsachievements '.
                'WHERE charactergroupsgroup_id = ? AND url = ?',
                'is',
                $groupsgroupId, $achievementUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($achievementUrl);
            }


            return $data[0];
        }


        /**
         * Get an Achievement by its ID.
         *
         * @param   int     $achievementId  ID of Achievement
         * @return  array                   Achievement data
         */
        public function getAchievementById($achievementId)
        {
            $data = $this->db->query(
                'SELECT id, charactergroupsgroup_id, pos, title, url, hash, description, achievementsmedia_id '.
                'FROM charactergroupsachievements '.
                'WHERE id = ?',
                'i',
                $achievementId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($achievementId);
            }


            return $data[0];
        }


        /**
         * Get an Achievement by its hash.
         *
         * @param   string  $achievementHash    Hash of Achievement
         * @return  array                       Achievement data
         */
        public function getAchievementByHash($achievementHash)
        {
            $data = $this->db->query(
                'SELECT id, charactergroupsgroup_id, pos, title, url, hash, description, achievementsmedia_id '.
                'FROM charactergroupsachievements '.
                'WHERE hash = ?',
                's',
                $achievementHash
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($achievementHash);
            }


            return $data[0];
        }


        /**
         * Get all achieved Achievements for a Character group.
         *
         * @param   int     $charactergroupId   ID of Character group
         * @return  array                       Achievements data
         */
        public function getAchievedAchievementsForGroup($charactergroupId)
        {
            return $this->db->query(
                'SELECT id, charactergroupsgroup_id, charactergroupsachievements_charactergroups.created, pos, title, url, hash, description, achievementsmedia_id '.
                'FROM charactergroupsachievements '.
                'INNER JOIN charactergroupsachievements_charactergroups ON charactergroupsachievements_charactergroups.charactergroupsachievement_id = charactergroupsachievements.id '.
                'WHERE charactergroupsachievements_charactergroups.charactergroup_id = ? '.
                'ORDER BY charactergroupsachievements_charactergroups.created DESC',
                'i',
                $charactergroupId
            );
        }


        /**
         * Get all Achievements for a Character groups-group.
         *
         * @param   int     $groupsgroupId  ID of Character groups-group
         * @return  array                   List of Achievements
         */
        public function getAchievementsForCharactergroupsgroup($groupsgroupId)
        {
            return $this->db->query(
                'SELECT id, charactergroupsgroup_id, pos, title, url, hash, description, achievementsmedia_id '.
                'FROM charactergroupsachievements '.
                'WHERE charactergroupsgroup_id = ? '.
                'ORDER BY pos ASC',
                'i',
                $groupsgroupId
            );
        }


        /**
         * Set an Achievement as achieved for a Character group.
         *
         * @param   int $achievementId      ID of Achievement
         * @param   int $charactergroupId   ID of Character group
         */
        public function setAchievementAchieved($achievementId, $charactergroupId)
        {
            $this->db->query(
                'INSERT INTO charactergroupsachievements_charactergroups '.
                '(charactergroupsachievement_id, charactergroup_id) '.
                'VALUES '.
                '(?, ?)',
                'ii',
                $achievementId, $charactergroupId
            );
        }


        /**
         * Check if a Character group has achieved an Achievement.
         *
         * @param   int $achievementId      ID of Achievement
         * @param   int $charactergroupId   ID of Character group
         * @return  boolean                 Whether Character group has achieved the Achievement or not
         */
        public function hasCharactergroupAchievedAchievement($achievementId, $charactergroupId)
        {
            $data = $this->db->query(
                'SELECT charactergroupsachievement_id, charactergroup_id, created '.
                'FROM charactergroupsachievements_charactergroups '.
                'WHERE charactergroupsachievement_id = ? AND charactergroup_id = ?',
                'ii',
                $achievementId, $charactergroupId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return false;
        }


        /**
         * Check if an Achievement title already exists.
         *
         * @param   int     $groupsgroupId  ID of Character groups-group
         * @param   string  $title          Achievement title to check
         * @param   int     $achievementId  Do not check this ID (for editing)
         * @return  boolean                 Whether Achievement title exists or not
         */
        public function achievementTitleExists($groupsgroupId, $title, $achievementId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM charactergroupsachievements '.
                'WHERE charactergroupsgroup_id = ? AND (title = ? OR url = ?)',
                'iss',
                $groupsgroupId,
                $title,
                \nre\core\Linker::createLinkParam($title)
            );


            return (!empty($data) && (is_null($achievementId) || $achievementId != $data[0]['id']));
        }


        /**
         * Create a new Achievement for a Character groups-group.
         *
         * @param   int     $userId         ID of creating user
         * @param   int     $groupsgroupId  ID of Character groups->group
         * @param   string  $title          Title of new Achievement
         * @param   string  $description    Description of new Achievement
         * @return  int                     ID of newly created Achievement
         */
        public function createAchievement($userId, $groupsgroupId, $title, $description)
        {
            // Get position
            $pos = $this->db->query(
                'SELECT COALESCE(MAX(pos),0)+1 AS pos '.
                'FROM charactergroupsachievements '.
                'WHERE charactergroupsgroup_id = ?',
                'i',
                $groupsgroupId
            );
            $pos = $pos[0]['pos'];

            // Create Achievement
            $this->db->query(
                'INSERT INTO charactergroupsachievements '.
                '(created_user_id, charactergroupsgroup_id, pos, title, url, hash, description) '.
                'VALUES '.
                '(?, ?, ?, ?, ?, ?, ?)',
                'iiissss',
                $userId,
                $groupsgroupId,
                $pos,
                $title,
                \nre\core\Linker::createLinkParam($title),
                \hhu\z\Utils::createRandomHash(),
                $description
            );


            // Return ID
            return $this->db->getInsertId();
        }


        /**
         * Move an Achievement up (decrement position) or down (increment
         * position).
         *
         * @param   array   $achievement    Achievement to move
         * @param   boolean $up             True for moving up, false for down
         */
        public function moveAchievement($achievement, $up)
        {
            $this->db->setAutocommit(false);
            try {
                // Set temporary position
                $this->db->query(
                    'UPDATE charactergroupsachievements '.
                    'SET pos = 0 '.
                    'WHERE id = ?',
                    'i',
                    $achievement['id']
                );
                // Switch entry
                $this->db->query(
                    'UPDATE charactergroupsachievements '.
                    'SET pos = ? '.
                    'WHERE charactergroupsgroup_id = ? AND pos = ?',
                    'iii',
                    $achievement['pos'],
                    $achievement['charactergroupsgroup_id'],
                    $achievement['pos'] + ($up ? -1 : 1)
                );
                // Set new position
                $this->db->query(
                    'UPDATE charactergroupsachievements '.
                    'SET pos = ? '.
                    'WHERE id = ?',
                    'ii',
                    $achievement['pos'] + ($up ? -1 : 1),
                    $achievement['id']
                );

                $this->db->commit();
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }
            $this->db->setAutocommit(true);
        }


        /**
         * Edit an Achievement of a Seminary.
         *
         * @param   int     $achievementId  ID of Achievement to edit
         * @param   string  $title          New title of Achievement
         * @param   string  $description    New description of Achievement
         */
        public function editAchievement($achievementId, $title, $description)
        {
            $this->db->query(
                'UPDATE charactergroupsachievements '.
                'SET title = ?, url = ?, description = ? '.
                'WHERE id = ?',
                'sssi',
                $title,
                \nre\core\Linker::createLinkParam($title),
                $description,
                $achievementId
            );
        }


        /**
         * Set the icon for an Achievement.
         *
         * @param   int $achievementId          ID of Achievement to set media for
         * @param   int $achievementsmediaId    ID of achievementsmedia to set
         */
        public function setIconForAchievement($achievementId, $achievementsmediaId)
        {
            $this->db->query(
                'UPDATE charactergroupsachievements '.
                'SET achievementsmedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $achievementsmediaId,
                $achievementId
            );
        }


        /**
         * Copy all Achievements of a Seminary.
         *
         * @param   int     $userId                     ID of creating user
         * @param   array   $characterGroupsgroupIds    Mapping of Character groups-group IDs from source Seminary to target Seminary
         * @param   array   $seminaryMediaIds           Mapping of Seminarymedia-IDs from source Seminary to target Seminary
         */
        public function copyAchievementsOfSeminary($userId, $characterGroupsgroupIds, $seminaryMediaIds=null)
        {
            // Store target achievement-IDs
            $achievementIds = array();

            // Traverse each Character groups-group
            foreach($characterGroupsgroupIds as $sourceGroupsgroupId => $targetGroupsgroupId)
            {
                // Get Achievements
                $achievements = $this->getAchievementsForCharactergroupsgroup($sourceGroupsgroupId);

                // Copy each Achievements
                foreach($achievements as &$achievement)
                {
                    // Copy Achievement
                    $this->db->query(
                        'INSERT INTO charactergroupsachievements '.
                        '(created_user_id, charactergroupsgroup_id, pos, title, url, hash, description) '.
                        'SELECT ?, ?, pos, title, url, ?, description '.
                        'FROM charactergroupsachievements '.
                        'WHERE id = ?',
                        'iisi',
                        $userId, $targetGroupsgroupId,
                        \hhu\z\Utils::createRandomHash(),
                        $achievement['id']
                    );
                    $achievementIds[$achievement['id']] = $this->db->getInsertId();

                    // Copy media
                    if(!is_null($seminaryMediaIds) && !is_null($achievement['achievementsmedia_id']))
                    {
                        $this->Media->copyAchievementMedia($userId, $seminaryMediaIds[$achievement['achievementsmedia_id']]);
                        $this->db->query(
                            'UPDATE charactergroupsachievements '.
                            'SET achievementsmedia_id = ? '.
                            'WHERE id = ?',
                            'ii',
                            $seminaryMediaIds[$achievement['achievementsmedia_id']],
                            $achievementIds[$achievement['id']]
                        );
                    }
                }
            }
        }


        /**
         * Delete an Achievement.
         *
         * @param   array   $achievement    Achievement to delete
         */
        public function deleteAchievement($achievement)
        {
            $this->db->setAutocommit(false);
            try {
                // Delete Achievement
                $this->db->query(
                    'DELETE FROM charactergroupsachievements '.
                    'WHERE id = ?',
                    'i',
                    $achievement['id']
                );

                // Adjust positions
                $this->db->query(
                    'UPDATE charactergroupsachievements '.
                    'SET pos = pos - 1 '.
                    'WHERE charactergroupsgroup_id = ? AND pos > ?',
                    'ii',
                    $achievement['charactergroupsgroup_id'],
                    $achievement['pos']
                );

                $this->db->commit();
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }

            $this->db->setAutocommit(true);
        }

    }

?>
