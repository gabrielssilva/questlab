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
         * Minimum similarity value for two submissions
         *
         * @var float
         */
        const SIMILARITY_MIN = 0.8;

        /**
         * Required models
         *
         * @var array
         */
        public $models = array('uploads');
        /**
         * Supported mimetypes
         *
         * @var array
         */
        private $mimetypes = array('application/pdf');




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
         * Delete a Quest.
         * 
         * @param   int $questId    ID of Quest to delete
         */
        public function deleteQuest($questId)
        {
            $this->db->query('DELETE FROM questtypes_submit_characters WHERE quest_id = ?', 'i', $questId);
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

            // Index submission for similarity calculation
            $this->addDocument(
                $this->db->getInsertId(),
                ROOT.DS.\nre\configs\AppConfig::$dirs['seminaryuploads'].DS.$filename
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
         * @param   int     $seminaryId ID of Seminary
         * @return  array               Allowed mimetypes
         */
        public function getAllowedMimetypes($seminaryId)
        {
            $mimetypes = array();
            foreach(\nre\configs\AppConfig::$mimetypes['questtypes'] as $mimetype) {
                if(in_array($mimetype['mimetype'], $this->mimetypes)) {
                    $mimetypes[] = $mimetype;
                }
            }


            return $mimetypes;
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


        /**
         * Get similar submissions for a Character submission.
         *
         * @param   int     $seminaryId     ID of Seminary
         * @param   int     $questId        ID of Quest
         * @param   int     $characterId    ID of Character
         * @param   int     $submissionId   ID of submission
         * @return  array                   List of submissions
         */
        public function getSimilarSubmissions($seminaryId, $questId, $characterId, $submissionId)
        {
            // List of submissions with high similarity
            $similarSubmissions = array();

            // Get IDFs
            $idf_N = $this->getIDF_total($seminaryId);
            $idf_n = $this->getIDF_docs($seminaryId);

            // Get stored TFs of submission
            $tfsA = $this->getTFs($submissionId);

            // Get submissions of same task
            $submissions = $this->getSubmissionsForQuest(
                $questId,
                $characterId,
                $submissionId
            );

            // Iterate through submissions of same task
            foreach($submissions as &$submission)
            {
                // Check if similarity has already be calculated
                if(is_null($submission['similarity']))
                {
                    // Get stored TFs of submissions to compare to
                    $tfsB = $this->getTFs($submission['id']);

                    // Calculate similarity
                    $submission['similarity'] = \hhu\z\lib\Similarity::compare(
                        $tfsA,
                        $tfsB,
                        $idf_N,
                        $idf_n
                    );

                    // Save similarity
                    $this->setSimilarity(
                        $submissionId,
                        $submission['id'],
                        $submission['similarity']
                    );
                }

                // Add high simnilarities to list
                if($submission['similarity'] >= self::SIMILARITY_MIN) {
                    $similarSubmissions[] = $submission;
                }
            }


            return $similarSubmissions;
        }




        /**
         * Index a submission as document.
         *
         * @param   int     $submissionId   ID of submission
         * @param   string  $filename       Full file path of document to read
         */
        private function addDocument($submissionId, $filename)
        {
            // Read document
            $document = \hhu\z\lib\Similarity::readDocument($filename);
            if($document === false) {
                return false;
            }

            // Split document into terms
            $terms = \hhu\z\lib\Similarity::splitNgrams($document);

            // Update global values
            $this->addTerms($submissionId, $terms);
        }


        /**
         * Add terms to the corpus, stored in database.
         *
         * @param   int     $submissionId   ID of submission
         * @param   array   $terms          List of (non-unique) terms
         */
        private function addTerms($submissionId, $terms)
        {
            $this->db->setAutocommit(false);
            try {
                // Calculate IDF: n (n_term)
                $uniqueTerms = array();
                foreach($terms as &$term)
                {
                    if(!in_array($term, $uniqueTerms))
                    {
                        // Add term to database
                        $this->db->query(
                            'INSERT IGNORE INTO questtypes_submit_terms '.
                            '(term) '.
                            'VALUES '.
                            '(?)',
                            's',
                            $term
                        );
                        $uniqueTerms[] = $term;
                    }

                    // Link term to submission
                    $this->db->query(
                        'INSERT INTO questtypes_submit_submissions_terms '.
                        '(submission_id, term_id, tf) '.
                        'SELECT ?, questtypes_submit_terms.id, 1 '.
                        'FROM questtypes_submit_terms '.
                        'WHERE term = ? '.
                        'ON DUPLICATE KEY UPDATE '.
                        'tf = tf + 1',
                        'is',
                        $submissionId,
                        $term
                    );
                }
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }

            $this->db->setAutocommit(true);
        }


        /**
         * Get all submissions for a Quest including similarity values to the
         * given submission, excluding the submissions of the given Character.
         *
         * @param   int     $questId        ID of Quest
         * @param   int     $characterId    ID of Character to exclude submissions of
         * @param   int     $submissionId   ID of submission to get similarity values for
         * @return  array                   List of submissions
         */
        private function getSubmissionsForQuest($questId, $characterId, $submissionId)
        {
            return $this->db->query(
                'SELECT questtypes_submit_characters.id, questtypes_submit_characters.created, questtypes_submit_characters.quest_id, character_id, upload_id, questtypes_submit_similarities.similarity '.
                'FROM questtypes_submit_characters '.
                'LEFT JOIN questtypes_submit_similarities ON questtypes_submit_similarities.submission_id1 = ? AND questtypes_submit_similarities.submission_id2 = questtypes_submit_characters.id '.
                'WHERE quest_id = ? AND character_id != ?',
                'iii',
                $submissionId,
                $questId, $characterId
            );
        }


        /**
         * Get Term Frequency (TF) values for a submission.
         *
         * @param   int     $submissionId   ID of submission
         * @return  array                   Associative array with term as key and frequency as value
         */
        private function getTFs($submissionId)
        {
            // Read terms
            $terms = $this->db->query(
                'SELECT term, tf '.
                'FROM questtypes_submit_submissions_terms '.
                'INNER JOIN questtypes_submit_terms ON questtypes_submit_terms.id = questtypes_submit_submissions_terms.term_id '.
                'WHERE submission_id = ?',
                'i',
                $submissionId
            );

            // Convert to TFs
            $tfs = array();
            foreach($terms as &$term) {
                $tfs[$term['term']] = $term['tf'];
            }


            // Return TFs
            return $tfs;
        }


        /**
         * Get total count of submissions for a Seminary.
         *
         * @param   int $seminaryId ID of Seminary
         * @return  int             Total count of submissions
         */
        private function getIDF_total($seminaryId)
        {
            $data = $this->db->query(
                'SELECT count(questtypes_submit_characters.id) as c '.
                'FROM charactertypes '.
                'INNER JOIN characters ON characters.charactertype_id = charactertypes.id '.
                'INNER JOIN questtypes_submit_characters ON questtypes_submit_characters.character_id = characters.id '.
                'WHERE charactertypes.seminary_id = ?',
                'i',
                $seminaryId
            );
            if(!empty($data)) {
                return $data[0]['c'];
            }


            return 0;
        }


        /**
         * Get count of submissions each term is in for a Seminary.
         *
         * @param   int     $seminaryId ID of Seminary
         * @return  array   Associatve array wtih terms as keys and counts as values
         */
        private function getIDF_docs($seminaryId)
        {
            $terms = $this->db->query(
                'SELECT questtypes_submit_terms.term, count(*) AS c '.
                'FROM charactertypes '.
                'INNER JOIN characters ON characters.charactertype_id = charactertypes.id '.
                'INNER JOIN questtypes_submit_characters ON questtypes_submit_characters.character_id = characters.id '.
                'INNER JOIN questtypes_submit_submissions_terms ON questtypes_submit_submissions_terms.submission_id = questtypes_submit_characters.id '.
                'INNER JOIN questtypes_submit_terms ON questtypes_submit_terms.id = questtypes_submit_submissions_terms.term_id '.
                'WHERE charactertypes.seminary_id = ? '.
                'GROUP BY questtypes_submit_terms.term',
                'i',
                $seminaryId
            );

            $idfs = array();
            foreach($terms as &$term) {
                $idfs[$term['term']] = $term['c'];
            }


            return $idfs;
        }


        /**
         * Save the similarity of two submissions.
         *
         * @param   int     $submissionId1  ID of submission
         * @param   int     $submissionId2  ID of submission
         * @param   float   $similarity     Similarity of both submissions
         */
        private function setSimilarity($submissionId1, $submissionId2, $similarity)
        {
            $this->db->query(
                'INSERT INTO questtypes_submit_similarities '.
                '(submission_id1, submission_id2, similarity) '.
                'VALUES '.
                '(?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'similarity = ?',
                'iidd',
                $submissionId1, $submissionId2, $similarity,
                $similarity
            );
            $this->db->query(
                'INSERT INTO questtypes_submit_similarities '.
                '(submission_id1, submission_id2, similarity) '.
                'VALUES '.
                '(?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'similarity = ?',
                'iidd',
                $submissionId2, $submissionId1, $similarity,
                $similarity
            );
        }
    }

?>
