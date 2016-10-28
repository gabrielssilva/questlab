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
     * Model to handle files to upload.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class UploadsModel extends \hhu\z\Model
    {




        /**
         * Construct a new UploadsModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Upload a file and create a database record.
         *
         * @param   int     $userId         ID of user that uploads the file
         * @param   int     $seminaryId     ID of Seminary
         * @param   string  $name           Name of file to upload
         * @param   string  $filename       Filename of file to upload
         * @param   string  $tmpFilename    Name of temporary uploaded file
         * @param   string  $mimetype       Mimetype of file to upload
         * @return  mixed                   ID of database record or false
         */
        public function uploadSeminaryFile($userId, $seminaryId, $name, $filename, $tmpFilename, $mimetype)
        {
            $uploadId = false;
            $this->db->setAutocommit(false);

            try {
                // Create database record
                $this->db->query(
                    'INSERT INTO seminaryuploads '.
                    '(created_user_id, seminary_id, name, url, mimetype) '.
                    'VALUES '.
                    '(?, ? ,? ,?, ?)',
                    'iisss',
                    $userId,
                    $seminaryId,
                    $name,
                    \nre\core\Linker::createLinkParam($filename),
                    $mimetype
                );
                $uploadId = $this->db->getInsertId();

                // Create filename
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminaryuploads'].DS.$filename;
                if(!move_uploaded_file($tmpFilename, $filename))
                {
                    $this->db->rollback();
                    $uploadId = false;
                }
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }


            $this->db->setAutocommit(true);
            return $uploadId;
        }


        /**
         * Get an upload by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int $seminaryuploadId   ID of the uploaded file
         * @return  array                   Upload data
         */
        public function getSeminaryuploadById($seminaryuploadId)
        {
            $data = $this->db->query(
                'SELECT id, created, created_user_id, seminary_id, name, url, mimetype, public '.
                'FROM seminaryuploads '.
                'WHERE id = ?',
                'i',
                $seminaryuploadId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($seminaryuploadId);
            }


            return $data[0];
        }


        /**
         * Get an upload by its URL.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   int     $seminaryId         ID of Seminary
         * @param   int     $seminaryuploadUrl  ID of the uploaded file
         * @return  array                       Upload data
         */
        public function getSeminaryuploadByUrl($seminaryId, $seminaryuploadUrl)
        {
            $data = $this->db->query(
                'SELECT id, created, created_user_id, seminary_id, name, url, mimetype, public '.
                'FROM seminaryuploads '.
                'WHERE seminary_id = ? AND url = ?',
                'is',
                $seminaryId,
                $seminaryuploadUrl
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($seminaryuploadUrl);
            }


            return $data[0];
        }


        /**
         * Delete a Seminary upload.
         *
         * @param   int $uploadId   ID of Seminary upload to delete
         */
        public function deleteSeminaryupload($uploadId)
        {
            $this->db->setAutocommit(false);

            try {
                // Get Upload
                $upload = $this->getSeminaryuploadById($uploadId);

                // Delete database record
                $this->db->query(
                    'DELETE FROM seminaryuploads '.
                    'WHERE id = ?',
                    'i',
                    $uploadId
                );

                // Delete file
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminaryuploads'].DS.$upload['url'];
                unlink($filename);
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
            }

            $this->db->setAutocommit(true);
        }


        /**
         * Delete all Seminary uploads of a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to delete all Uploads of
         */
        public function deleteSeminaryUploadsOfSeminary($seminaryId)
        {
            // Get all uploads from a Seminary
            $seminaryUploads = $this->db->query(
                'SELECT id, url '.
                'FROM seminaryuploads '.
                'WHERE seminary_id = ?',
                'i',
                $seminaryId
            );

            // Delete each upload
            foreach($seminaryUploads as &$upload)
            {
                // Delete file
                $filename = ROOT.DS.\nre\configs\AppConfig::$dirs['seminaryuploads'].DS.$upload['url'];
                @unlink($filename);
            }

            // Delete database entries
            $this->db->query('DELETE FROM seminaryuploads WHERE seminary_id = ?', 'i', $seminaryId);
        }

    }

?>
