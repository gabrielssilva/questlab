<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\questtypes;


    /**
     * Model of the CrosswordQuesttypeAgent for solving a crossword.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CrosswordQuesttypeModel extends \hhu\z\models\QuesttypeModel
    {




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
            // Copy words
            $this->db->query(
                'INSERT INTO questtypes_crossword_words '.
                '(quest_id, question, word, vertical, pos_x, pos_y) '.
                'SELECT ?, question, word, vertical, pos_x, pos_y '.
                'FROM questtypes_crossword_words '.
                'WHERE quest_id = ?',
                'ii',
                $targetQuestId,
                $sourceQuestId
            );
        }


        /**
         * Delete a Quest.
         * 
         * @param   int $questId    ID of Quest to delete
         */
        public function deleteQuest($questId)
        {
            $this->db->query('DELETE FROM questtypes_crossword_words WHERE quest_id = ?', 'i', $questId);
        }


        /**
         * Get all words for a crossword-Quest.
         *
         * @param   int     $questId    ID of Quest
         * @return  array               Words
         */
        public function getWordsForQuest($questId)
        {
            return $this->db->query(
                'SELECT id, question, word, vertical, pos_x, pos_y '.
                'FROM questtypes_crossword_words '.
                'WHERE quest_id = ? ',
                'i',
                $questId
            );
        }


        /**
         * Save Character’s submitted answer for one crossword-word.
         *
         * @param   int     $wordId         ID of word
         * @param   int     $characterId    ID of Character
         * @param   string  $answer         Submitted answer for this word
         */
        public function setCharacterSubmission($wordId, $characterId, $answer)
        {
            $this->db->query(
                'INSERT INTO questtypes_crossword_words_characters '.
                '(questtypes_crossword_word_id, character_id, answer) '.
                'VALUES '.
                '(?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'answer = ?',
                'iiss',
                $wordId, $characterId, $answer,
                $answer
            );
        }


        /**
         * Get answer of one crossword-word submitted by Character.
         *
         * @param   int     $wordId         ID of word
         * @param   int     $characterId    ID of Character
         * @return  int                     Submitted answer for this word or null
         */
        public function getCharacterSubmission($wordId, $characterId)
        {
            $data = $this->db->query(
                'SELECT answer '.
                'FROM questtypes_crossword_words_characters '.
                'WHERE questtypes_crossword_word_id = ? AND character_id = ? ',
                'ii',
                $wordId, $characterId
            );
            if(!empty($data)) {
                return $data[0]['answer'];
            }


            return null;
        }

    }

?>
