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
     * Model to interact with the Media-tables.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MediaModel extends \hhu\z\Model
    {




        /**
         * Construct a new MediaModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get a medium by its URL.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $mediaURL   URL-name of the Medium
         * @return  array               Medium data
         */
        public function getMediaByUrl($mediaUrl)
        {
            $data = $this->db->query(
                'SELECT id, name, url, description, mimetype '.
                'FROM media '.
                'WHERE url = ?',
                's',
                $mediaUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($mediaUrl);
            }


            return $data[0];
        }


        /**
         * Get a medium by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int $mediaId    ID of the Medium
         * @return  array           Medium data
         */
        public function getMediaById($mediaId)
        {
            $data = $this->db->query(
                'SELECT id, name, url, description, mimetype '.
                'FROM media '.
                'WHERE id = ?',
                'i',
                $mediaId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($mediaId);
            }


            return $data[0];
        }


        /**
         * Get a Seminary medium by its URL.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $seminaryId         ID of the seminary
         * @param   string  $seminaryMediaUrl   URL-name of the Seminary medium
         * @return  array                       Seminary medium data
         */
        public function getSeminaryMediaByUrl($seminaryId, $seminaryMediaUrl)
        {
            $data = $this->db->query(
                'SELECT id, name, url, description, mimetype '.
                'FROM seminarymedia '.
                'WHERE seminary_id = ? AND url = ?',
                'is',
                $seminaryId,
                $seminaryMediaUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($seminaryId.': '.$seminaryMediaUrl);
            }


            return $data[0];
        }


        /**
         * Get a Seminary medium by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $seminaryMediaId    ID of the Seminary medium
         * @return  array                       Seminary medium data
         */
        public function getSeminaryMediaById($mediaId)
        {
            $data = $this->db->query(
                'SELECT id, name, url, description, mimetype '.
                'FROM seminarymedia '.
                'WHERE id = ?',
                'i',
                $mediaId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($mediaId);
            }


            return $data[0];
        }


        /**
         * Copy all media from a Seminary.
         *
         * @param   int     $userId             ID of creating user
         * @param   int     $sourceSeminaryId   ID of Seminary to copy from
         * @param   int     $targetSeminaryId   ID of Seminary to copy to
         * @return  array                       Mapping of Media-IDs from source Seminary to target Seminary
         */
        public function copySeminaryMedia($userId, $sourceSeminaryId, $targetSeminaryId)
        {
            $seminaryMediaIds = array();
            $copiedFiles = array();

            // Get all media from a Seminary
            $seminaryMedia = $this->db->query(
                'SELECT id '.
                'FROM seminarymedia '.
                'WHERE seminary_id = ?',
                'i',
                $sourceSeminaryId
            );

            // Copy each medium
            try {
                foreach($seminaryMedia as &$medium)
                {
                    // Copy database record
                    $this->db->query(
                        'INSERT INTO seminarymedia '.
                        '(created_user_id, seminary_id, name, url, description, mimetype) '.
                        'SELECT ?, ?, name, url, description, mimetype '.
                        'FROM seminarymedia '.
                        'WHERE id = ?',
                        'iii',
                        $userId, $targetSeminaryId,
                        $medium['id']
                    );
                    $seminaryMediaIds[$medium['id']] = $this->db->getInsertId();

                    // Copy file
                    $sourceFilename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$medium['id'];
                    $targetFilename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$seminaryMediaIds[$medium['id']];
                    if(!copy($sourceFilename, $targetFilename)) {
                        throw new \hhu\z\exceptions\FileCopyException(error_get_last());
                    }
                    $copiedFiles[] = $targetFilename;
                }
            }
            catch(\hhu\z\exceptions\FileCopyException $e) {
                // Cleanup
                foreach($copiedFiles as $filename) {
                    if(file_exists($filename)) {
                        unlink($filename);
                    }
                }
                throw $e;
            }


            // Return new media IDs
            return $seminaryMediaIds;
        }


        /**
         * Delete all media of a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to delete media of
         */
        public function deleteSeminaryMediaOfSeminary($seminaryId)
        {
            // Get all media from a Seminary
            $seminaryMedia = $this->db->query(
                'SELECT id '.
                'FROM seminarymedia '.
                'WHERE seminary_id = ?',
                'i',
                $seminaryId
            );

            // Delete each medium
            foreach($seminaryMedia as &$medium)
            {
                // Delete file
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$medium['id'];
                @unlink($filename);
            }

            // Delete database entries
            $this->db->query('DELETE FROM seminarymedia WHERE seminary_id = ?', 'i', $seminaryId);
        }


        /**
         * Create a new moodpic.
         *
         * @param   int     $userId         ID of user that does the upload
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $filename       Filename of uploading media
         * @param   string  $description    Description for media
         * @param   string  $mimetype       Mimetype of media
         * @param   string  $tmpFilename    Name of temporary uploaded file
         * @return  mixed                   ID of media record or false if upload failed
         */
        public function createMoodpic($userId, $seminaryId, $filename, $description, $mimetype, $tmpFilename)
        {
            $mediaId = false;
            $this->db->setAutocommit(false);

            try {
                // Create Seminary media record
                $mediaId = $this->createSeminaryMedia($userId, $seminaryId, $filename, $description, $mimetype);

                // Upload file
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$mediaId;
                if(!move_uploaded_file($tmpFilename, $filename))
                {
                    $this->db->rollback();
                    $mediaId = false;
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }


            $this->db->setAutocommit(true);
            return $mediaId;
        }


        /**
         * Create a new Avatar picture for a Charactertype by creating a new Seminarymedia and
         * adding it to the list of Avatar pictures.
         *
         * @param   int     $userId         ID of user that does the upload
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $filename       Filename of uploading media
         * @param   string  $description    Description for media
         * @param   string  $mimetype       Mimetype of media
         * @param   string  $tmpFilename    Name of temporary uploaded file
         * @return  mixed                   ID of media record or false if upload failed
         */
        public function createAvatarpicture($userId, $seminaryId, $filename, $description, $mimetype, $tmpFilename)
        {
            $mediaId = false;
            $this->db->setAutocommit(false);

            try {
                // Create Seminary media record
                $mediaId = $this->createSeminaryMedia($userId, $seminaryId, $filename, $description, $mimetype);

                // Add media to Avatar pictures
                $this->db->query(
                    'INSERT INTO avatarpictures '.
                    '(seminarymedia_id, created_user_id) '.
                    'VALUES '.
                    '(?, ?) '.
                    'ON DUPLICATE KEY UPDATE '.
                    'created_user_id = ?',
                    'iii',
                    $mediaId,
                    $userId,
                    $userId
                );

                // Create filename
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$mediaId;
                if(!move_uploaded_file($tmpFilename, $filename))
                {
                    $this->db->rollback();
                    $mediaId = false;
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }


            $this->db->setAutocommit(true);
            return $mediaId;
        }


        /**
         * Copy an Avatar picture.
         *
         * @param   int $userId             ID of creating user
         * @param   int $seminaryMediaId    ID of Seminary media to copy
         */
        public function copyAvatarpicture($userId, $avatarpictureId)
        {
            $this->db->query(
                'INSERT INTO avatarpictures '.
                '(seminarymedia_id, created_user_id) '.
                'VALUES '.
                '(?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'created_user_id = ?',
                'iii',
                $avatarpictureId,
                $userId,
                $userId
            );
        }


        /**
         * Create a new Questgroup picture (Moodpic).
         *
         * @param   int     $userId         ID of user that does the upload
         * @param   int     $seminaryId     ID of Seminary
         * @param   int     $questgroupId   ID of Questgroup to create picture for
         * @param   string  $filename       Filename of uploading media
         * @param   string  $description    Description for media
         * @param   string  $mimetype       Mimetype of media
         * @param   string  $tmpFilename    Name of temporary uploaded file
         * @return  mixed                   ID of media record or false if upload failed
         */
        public function createQuestgrouppicture($userId, $seminaryId, $questgroupId, $filename, $description, $mimetype, $tmpFilename)
        {
            $mediaId = false;
            $this->db->setAutocommit(false);

            try {
                // Create Seminary media record
                $mediaId = $this->createSeminaryMedia($userId, $seminaryId, $filename, $description, $mimetype);

                // Add media to Questgroups pictures
                $this->db->query(
                    'INSERT INTO questgroupspictures '.
                    '(media_id, created_user_id) '.
                    'VALUES '.
                    '(?, ?) '.
                    'ON DUPLICATE KEY UPDATE '.
                    'created_user_id = ?',
                    'iii',
                    $mediaId,
                    $userId,
                    $userId
                );

                // Upload file
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$mediaId;
                if(!move_uploaded_file($tmpFilename, $filename))
                {
                    $this->db->rollback();
                    $mediaId = false;
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }


            $this->db->setAutocommit(true);
            return $mediaId;
        }


        /**
         * Copy a Questgroup picture.
         *
         * @param   int $userId             ID of creating user
         * @param   int $seminaryMediaId    ID of Seminary media to copy
         */
        public function copyQuestgroupspicture($userId, $questgroupspictureId)
        {
            $this->db->query(
                'INSERT INTO questgroupspictures '.
                '(media_id, created_user_id) '.
                'VALUES '.
                '(?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'created_user_id = ?',
                'iii',
                $questgroupspictureId,
                $userId,
                $userId
            );
        }


        /**
         * Create a new Quests media by creating a new Seminarymedia and
         * adding it to the list of Quests media.
         *
         * @param   int     $userId         ID of user that does the upload
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $filename       Filename of uploading media
         * @param   string  $description    Description for media
         * @param   string  $mimetype       Mimetype of media
         * @param   string  $tmpFilename    Name of temporary uploaded file
         * @return  mixed                   ID of media record or false if upload failed
         */
        public function createQuestMedia($userId, $seminaryId, $filename, $description, $mimetype, $tmpFilename)
        {
            $mediaId = false;
            $this->db->setAutocommit(false);

            try {
                // Create Seminary media record
                $mediaId = $this->createSeminaryMedia($userId, $seminaryId, $filename, $description, $mimetype);

                // Add media to Quests media
                $this->db->query(
                    'INSERT INTO questsmedia '.
                    '(media_id, created_user_id) '.
                    'VALUES '.
                    '(?, ?) '.
                    'ON DUPLICATE KEY UPDATE '.
                    'created_user_id = ?',
                    'iii',
                    $mediaId,
                    $userId,
                    $userId
                );

                // Create filename
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$mediaId;
                if(!move_uploaded_file($tmpFilename, $filename))
                {
                    $this->db->rollback();
                    $mediaId = false;
                }
                else {
                    $this->db->commit();
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }


            $this->db->setAutocommit(true);
            return $mediaId;
        }



        /**
         * Copy media of a Quest.
         *
         * @param   int $userId             ID of creating user
         * @param   int $seminaryMediaId    ID of Quest media to copy
         */
        public function copyQuestsmedia($userId, $seminaryMediaId)
        {
            $this->db->query(
                'INSERT INTO questsmedia '.
                '(media_id, created_user_id) '.
                'VALUES '.
                '(?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'created_user_id = ?',
                'iii',
                $seminaryMediaId,
                $userId,
                $userId
            );
        }


        /**
         * Create a new Character groups media by creating a new Seminarymedia and
         * adding it to the list of media for Character groups.
         *
         * @param   int     $userId         ID of user that does the upload
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $filename       Filename of uploading media
         * @param   string  $description    Description for media
         * @param   string  $mimetype       Mimetype of media
         * @param   string  $tmpFilename    Name of temporary uploaded file
         * @return  mixed                   ID of media record or false if upload failed
         */
        public function createCharactergroupMedia($userId, $seminaryId, $filename, $description, $mimetype, $tmpFilename)
        {
            $mediaId = false;
            $this->db->setAutocommit(false);

            try {
                // Create Seminary media record
                $mediaId = $this->createSeminaryMedia($userId, $seminaryId, $filename, $description, $mimetype);

                // Add media to Character groups media
                $this->db->query(
                    'INSERT INTO charactergroupsmedia '.
                    '(seminarymedia_id, created_user_id) '.
                    'VALUES '.
                    '(?, ?) '.
                    'ON DUPLICATE KEY UPDATE '.
                    'created_user_id = ?',
                    'iii',
                    $mediaId,
                    $userId,
                    $userId
                );

                // Create filename
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$mediaId;
                if(!move_uploaded_file($tmpFilename, $filename))
                {
                    $this->db->rollback();
                    $mediaId = false;
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }


            $this->db->setAutocommit(true);
            return $mediaId;
        }


        /**
         * Create a new Achievement media by creating a new Seminarymedia and
         * adding it to the list of media for Achievements.
         *
         * @param   int     $userId         ID of user that does the upload
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $filename       Filename of uploading media
         * @param   string  $description    Description for media
         * @param   string  $mimetype       Mimetype of media
         * @param   string  $tmpFilename    Name of temporary uploaded file
         * @return  mixed                   ID of media record or false if upload failed
         */
        public function createAchievementMedia($userId, $seminaryId, $filename, $description, $mimetype, $tmpFilename)
        {
            $mediaId = false;
            $this->db->setAutocommit(false);

            try {
                // Create Seminary media record
                $mediaId = $this->createSeminaryMedia($userId, $seminaryId, $filename, $description, $mimetype);

                // Add media to Achievements media
                $this->db->query(
                    'INSERT INTO achievementsmedia '.
                    '(seminarymedia_id, created_user_id) '.
                    'VALUES '.
                    '(?, ?) '.
                    'ON DUPLICATE KEY UPDATE '.
                    'created_user_id = ?',
                    'iii',
                    $mediaId,
                    $userId,
                    $userId
                );

                // Create filename
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$mediaId;
                if(!move_uploaded_file($tmpFilename, $filename))
                {
                    $this->db->rollback();
                    $mediaId = false;
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }


            $this->db->setAutocommit(true);
            return $mediaId;
        }


        /**
         * Copy Achievement media.
         *
         * @param   int $userId             ID of creating user
         * @param   int $seminaryMediaId    ID of Seminary media to copy
         */
        public function copyAchievementMedia($userId, $seminaryMediaId)
        {
            $this->db->query(
                'INSERT INTO achievementsmedia '.
                '(seminarymedia_id, created_user_id) '.
                'VALUES '.
                '(?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'created_user_id = ?',
                'iii',
                $seminaryMediaId,
                $userId,
                $userId
            );
        }


        /**
         * Create a new map medium. 
         *
         * @param   int     $userId         ID of user that does the upload
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $filename       Filename of uploading media
         * @param   string  $description    Description for media
         * @param   string  $mimetype       Mimetype of media
         * @param   string  $tmpFilename    Name of temporary uploaded file
         * @return  mixed                   ID of media record or false if upload failed
         */
        public function createMapMedia($userId, $seminaryId, $filename, $description, $mimetype, $tmpFilename)
        {
            $mediaId = false;
            $this->db->setAutocommit(false);

            try {
                // Create Seminary media record
                $mediaId = $this->createSeminaryMedia($userId, $seminaryId, $filename, $description, $mimetype);

                // Upload file
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$mediaId;
                if(!move_uploaded_file($tmpFilename, $filename))
                {
                    $this->db->rollback();
                    $mediaId = false;
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }


            $this->db->setAutocommit(true);
            return $mediaId;
        }


        /**
         * Gather some information about a Seminary medium.
         *
         * The infos are organized in an associative array and contain the
         * following keys: width and height
         *
         * @param   int     $seminarymediaId    ID of Seminary media to get infos for
         * @return  array                       List of infos for Seminary medium
         */
        public function getSeminarymediaInfos($seminarymediaId)
        {
            // Create filename
            $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$seminarymediaId;

            // Get infos
            $infos = array();
            $im = new \Imagick($filename);
            $infos['width'] = $im->getImageWidth();
            $infos['height'] = $im->getImageHeight();


            // Return infos
            return $infos;
        }




        /**
         * Create a new Seminary media.
         *
         * @param   int     $userId         ID of user that does the upload
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $filename       Filename of uploading media
         * @param   string  $description    Description for media
         * @param   string  $mimetype       Mimetype of media
         * @return  mixed                   ID of media record or false if upload failed
         */
        private function createSeminaryMedia($userId, $seminaryId, $filename, $description, $mimetype)
        {
            // Check for existing database record
            $data = $this->db->query(
                'SELECT id '.
                'FROM seminarymedia '.
                'WHERE seminary_id = ? AND url = ?',
                'is',
                $seminaryId,
                \nre\core\Linker::createLinkParam($filename)
            );
            if(!empty($data)) {
                return $data[0]['id'];
            }

            // Create database record
            $this->db->query(
                'INSERT INTO seminarymedia '.
                '(created_user_id, seminary_id, name, url, description, mimetype) '.
                'VALUES '.
                '(?, ? ,? ,?, ?, ?)',
                'iissss',
                $userId,
                $seminaryId,
                $filename,
                \nre\core\Linker::createLinkParam($filename),
                $description,
                $mimetype
            );


            return $this->db->getInsertId();
        }

    }

?>
