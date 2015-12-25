<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\stationtypes;


    /**
     * Controller of the StationtypeAgent for keyword access.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class KeywordStationtypeController extends \hhu\z\controllers\StationtypeController
    {




        /**
         * Save the answer of a Character group for a Station.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $questgroup     Current Questgroup data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         * @param   array   $charactergroup Current Character group data
         * @param   array   $answer         Character group answer for the Station
         */
        public function saveAnswer($seminary, $groupsgroup, $quest, $station, $charactergroup, $answer)
        {
            $this->Keyword->setCharactergroupSubmission($station['id'], $charactergroup['id'], $answer);
        }


        /**
         * Check if answer of a Character group for a Station matches the correct one.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $questgroup     Current Questgroup data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         * @param   array   $charactergroup Current Character group data
         * @param   array   $answer         Character group answer for the Station
         * @return  boolean                 True/false for a right/wrong answer
         */
        public function matchAnswer($seminary, $groupsgroup, $quest, $station, $charactergroup, $answer)
        {
            // Get right answers
            $task = $this->Keyword->getKeywordTask($station['id']);

            // Match regex with user answers
            return $this->isMatching($task['keyword_regex'], $answer);
        }


        /**
         * Action: quest.
         *
         * Show the task of a Station.
         *
         * @param   array       $seminary       Current Seminary data
         * @param   array       $questgroup     Current Questgroup data
         * @param   array       $quest          Current Quest data
         * @param   array       $station        Current Station data
         * @param   array       $charactergroup Current Character group data
         */
        public function quest($seminary, $groupsgroup, $quest, $station, $charactergroup)
        {
        }




        /**
         * Check if an Character answer matches a Regex.
         *
         * @param   string  $regex  Regex to match against
         * @param   string  $answer Character answer to match
         * @return  boolean     Whether answer matches Regex or not
         */
        private function isMatching($regex, $answer)
        {
            $score = preg_match($regex, trim($answer));


            return ($score !== false && $score > 0);
        }

    }

?>
