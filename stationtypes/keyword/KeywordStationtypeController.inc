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
         * Required models
         */
        public $models = array('charactergroupsqueststations');
        /**
         * Required components
         *
         * @var array
         */
        public $components = array('validation', 'questtypedata');




        /**
         * Save the answer of a Character group for a Station.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
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
         * @param   array   $groupsgroup    Current Groups group data
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
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         * @param   array   $charactergroup Current Character group data
         */
        public function quest($seminary, $groupsgroup, $quest, $station, $charactergroup)
        {
            // Get submission
            $submission = null;
            if(!is_null($charactergroup)) {
                $submission = $this->Keyword->getCharactergroupSubmission(
                    $station['id'],
                    $charactergroup['id']
                );
            }

            // Get status
            $tried = false;
            if(!is_null($charactergroup)) {
                $tried = $this->Charactergroupsqueststations->hasCharactergroupTriedStation(
                    $station['id'],
                    $charactergroup['id']
                );
            }


            // Pass data to view
            $this->set('submission', $submission);
            $this->set('tried', $tried);
        }


        /**
         * Action: edittask.
         *
         * Edit the task of a Station.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         */
        public function edittask($seminary, $groupsgroup, $quest, $station)
        {
            // Get right answers
            $task = $this->Keyword->getKeywordTask($station['id']);

            // Values
            $keyword = $task['keyword_regex'];
            $validations = array();

            // Save data
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('save')))
            {
                // Get params and validate them
                $keyword = $this->request->getPostParam('keyword');

                // Validate regex
                $keywordValidation = @preg_match($keyword, '') !== false;
                if($keywordValidation !== true) {
                    $validations = $this->Validation->addValidationResult($validations, 'keyword', 'regex', $keywordValidation);
                }

                // Save and redirect
                if(empty($validations))
                {
                    // Save keyword
                    $this->Keyword->setKeywordForStation(
                        $this->Auth->getUserId(),
                        $station['id'],
                        $keyword
                    );

                    // Redirect
                    $this->redirect(
                        $this->linker->link(
                            array(
                                'station',
                                $seminary['url'],
                                $groupsgroup['url'],
                                $quest['url'],
                                $station['url']
                            ),
                            1
                        )
                    );
                }
            }


            // Pass data to view
            $this->set('keyword', $keyword);
            $this->set('validations', $validations);
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
            // Check regex
            if(empty($regex)) {
                return false;
            }

            // Execute regex
            $score = preg_match($regex, trim($answer));


            // Return result
            return ($score !== false && $score > 0);
        }

    }

?>
