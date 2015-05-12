<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\questtypes;


    /**
     * Model of the SubmitQuesttypeAgent for a submit task.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SubmitQuesttypeModel extends \hhu\z\models\QuesttypeModel
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('uploads');




        /**
         * Copy a Quest
         *
         * @param   int $userId             ID of creating user
         * @param   int $sourceQuestId      ID of Quest to copy from
         * @param   int $targetQuestId      ID of Quest to copy to
         * @param   int $seminaryMediaIds   Mapping of SeminaryMedia-IDs from source Seminary to targetSeminary
         */
        public function copyQuest($userId, $sourceQuestId, $targetQuestId, $seminaryMediaIds)
        {
        }


        /**
         * Save Character’s submitted upload.
         *
         * @param   int $seminaryId ID of Seminary
         * @param   int $questId    ID of Quest
         * @param   int $userId     ID of user
         * @param   int $characterId    ID of Character
         * @param   array   $file       Submitted upload
         * @param   string  $filename   Name of submitted file
         */
        public function setCharacterSubmission($seminaryId, $questId, $userId, $characterId, $file, $filename)
        {
            // Save file on harddrive
            $uploadId = $this->Uploads->uploadSeminaryFile($userId, $seminaryId, $file['name'], $filename, $file['tmp_name'], $file['type']);
            if($uploadId === false) {
                return false;
            }

            // Create database record
            $this->db->query(
                'INSERT INTO questtypes_submit_characters '.
                '(quest_id, character_id, upload_id) '.
                'VALUES '.
                '(?, ?, ?) ',
                'iii',
                $questId, $characterId, $uploadId
            );


            return true;
        }


        /**
         * Add a comment for the answer of a Character.
         *
         * @param   int $userId     ID of user that comments
         * @param   int $submissionId   ID of Character answer to comment
         * @param   string  $comment    Comment text
         */
        public function addCommentForCharacterAnswer($userId, $submissionId, $comment)
        {
            $this->db->query(
                'INSERT INTO questtypes_submit_characters_comments '.
                '(created_user_id, questtypes_submit_character_id, comment) '.
                'VALUES '.
                '(?, ?, ?)',
                'iis',
                $userId,
                $submissionId,
                $comment
            );
        }


        /**
         * Get all uploads submitted by Character.
         *
         * @param   int $questId    ID of Quest
         * @param   int $characterId    ID of Character
         * @return  array           Text submitted by Character or NULL
         */
        public function getCharacterSubmissions($questId, $characterId)
        {
            return $this->db->query(
                'SELECT id, created, upload_id '.
                'FROM questtypes_submit_characters '.
                'WHERE quest_id = ? AND character_id = ? '.
                'ORDER BY created ASC',
                'ii',
                $questId, $characterId
            );
        }


        /**
         * Get allowed mimetypes for uploading a file.
         *
         * @param   int $seminaryId ID of Seminary
         * @return  array           Allowed mimetypes
         */
        public function getAllowedMimetypes($seminaryId)
        {
            return $this->db->query(
                'SELECT id, mimetype, size '.
                'FROM questtypes_submit_mimetypes '.
                'WHERE seminary_id = ?',
                'i',
                $seminaryId
            );
        }


        /**
         * Get all comments for a Character submission.
         *
         * @param   int $characterSubmissionId  ID of Character submission
         * @return  array               Comments for this submission
         */
        public function getCharacterSubmissionComments($characterSubmissionId)
        {
            return $this->db->query(
                'SELECT id, created, created_user_id, comment '.
                'FROM questtypes_submit_characters_comments '.
                'WHERE questtypes_submit_character_id = ?',
                'i',
                $characterSubmissionId
            );
        }

    }

?>
