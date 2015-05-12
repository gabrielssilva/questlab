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
     * Model to interact with Avatars-tables.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class AvatarsModel extends \hhu\z\Model
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('media');




        /**
         * Construct a new AvatarsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get an Avatar by its ID
         *
         * @param   int $avatarId   ID of Avatar
         * @return  array           Avatar data
         */
        public function getAvatarById($avatarId)
        {
            $data = $this->db->query(
                'SELECT id, charactertype_id, xplevel_id, avatarpicture_id, small_avatarpicture_id '.
                'FROM avatars '.
                'WHERE id = ?',
                'i',
                $avatarId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Get an Avatar by its Character type and XP-level.
         *
         * @param   int $seminaryId     ID of Seminary
         * @param   string  $charactertypeUrl   URL-title of Character type
         * @param   int $xplevel        XP-level
         * @return  array               Avatar data
         */
        public function getAvatarByTypeAndLevel($seminaryId, $charactertypeUrl, $xplevel)
        {
            $data = $this->db->query(
                'SELECT avatars.id, charactertype_id, xplevel_id, avatarpicture_id, small_avatarpicture_id '.
                'FROM avatars '.
                'INNER JOIN charactertypes ON charactertypes.id = avatars.charactertype_id '.
                'INNER JOIN xplevels ON xplevels.id = avatars.xplevel_id AND xplevels.seminary_id = charactertypes.seminary_id '.
                'WHERE charactertypes.seminary_id = ? AND charactertypes.url = ? AND xplevels.level = ?',
                'isi',
                $seminaryId,
                $charactertypeUrl,
                $xplevel
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($charactertypeUrl);
            }


            return $data[0];
        }


        /**
         * Get an Avatar by its Character type and XP-level.
         *
         * @param   int $charactertypeId    ID of Character type
         * @param   int $xplevelId      ID of XP-level
         * @return  array               Avatar data
         */
        public function getAvatarByTypeAndLevelId($charactertypeId, $xplevelId)
        {
            $data = $this->db->query(
                'SELECT id, charactertype_id, xplevel_id, avatarpicture_id, small_avatarpicture_id '.
                'FROM avatars '.
                'WHERE charactertype_id = ? AND xplevel_id = ?',
                'ii',
                $charactertypeId,
                $xplevelId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($charactertypeId.'-'.$xplevelId);
            }


            return $data[0];
        }


        /**
         * Set the picture for an Avatar.
         *
         * @param   int $userId         ID of creating user
         * @param   int $charactertypeId    ID of Charactertype of Avatar
         * @param   int $xplevelId      ID of XP-level of Avatar
         * @param   int $avatarpictureId    ID of Avatar picture to set
         */
        public function setAvatarForTypeAndLevel($userId, $charactertypeId, $xplevelId, $avatarpictureId)
        {
            $this->db->query(
                'INSERT INTO avatars '.
                '(created_user_id, charactertype_id, xplevel_id, avatarpicture_id) '.
                'VALUES '.
                '(?, ?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'avatarpicture_id = ?',
                'iiiii',
                $userId,
                $charactertypeId,
                $xplevelId,
                $avatarpictureId,
                $avatarpictureId
            );
        }


        /**
         * Set the portrait picture for an Avatar.
         *
         * @param   int $userId         ID of creating user
         * @param   int $charactertypeId    ID of Charactertype of Avatar
         * @param   int $xplevelId      ID of XP-level of Avatar
         * @param   int $avatarpictureId    ID of Avatar portrait picture to set
         */
        public function setAvatarPortraitForTypeAndLevel($userId, $charactertypeId, $xplevelId, $avatarpictureId)
        {
            $this->db->query(
                'INSERT INTO avatars '.
                '(created_user_id, charactertype_id, xplevel_id, small_avatarpicture_id) '.
                'VALUES '.
                '(?, ?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'small_avatarpicture_id = ?',
                'iiiii',
                $userId,
                $charactertypeId,
                $xplevelId,
                $avatarpictureId,
                $avatarpictureId
            );
        }


        /**
         * Copy all Avatars from a Seminary.
         *
         * @param   int     $userId             ID of copying user
         * @param   array   $charactertypeIds   Mapping of Charactertype-IDs from source Seminary to target Seminary
         * @param   array   $xplevelIds         Mapping of XP-level-IDs from source Seminary to targetSeminary
         * @param   array   $seminaryMediaIds   Mapping of Seminarymedia-IDs from source Seminary to target Seminary
         */
        public function copyAvatars($userId, $charactertypeIds, $xplevelIds, $seminaryMediaIds)
        {
            // Copy Avatars
            foreach($charactertypeIds as $sourceCharactertypeId => $targetCharactertypeId)
            {
                foreach($xplevelIds as $sourceXplevelId => $targetXplevelId)
                {
                    try {
                        // Get Avatar
                        $avatar = $this->getAvatarByTypeAndLevelId($sourceCharactertypeId, $sourceXplevelId);

                        // Copy media
                        $this->Media->copyAvatarpicture($userId, $seminaryMediaIds[$avatar['avatarpicture_id']]);
                        $this->Media->copyAvatarpicture($userId, $seminaryMediaIds[$avatar['small_avatarpicture_id']]);

                        // Copy Avatar
                        $this->db->query(
                            'INSERT INTO avatars '.
                            '(created_user_id, charactertype_id, xplevel_id, avatarpicture_id, small_avatarpicture_id) '.
                            'VALUES '.
                            '(?, ?, ?, ?, ?)',
                            'iiiii',
                            $userId,
                            $targetCharactertypeId,
                            $targetXplevelId,
                            $seminaryMediaIds[$avatar['avatarpicture_id']],
                            $seminaryMediaIds[$avatar['small_avatarpicture_id']]
                        );
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                        // Not all combinations of charactertypes and XP-levels exist
                    }
                }
            }
        }

    }

?>
