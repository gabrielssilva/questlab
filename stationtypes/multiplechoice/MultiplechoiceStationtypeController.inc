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
     * Controller of the StationtypeAgent for a multiple choice task.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MultiplechoiceStationtypeController extends \hhu\z\controllers\StationtypeController
    {
        /**
         * Required models
         */
        public $models = array('charactergroupsqueststations');




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
            $answers = (!is_array($answer)) ? array() : $answer;
            $solutions = $this->Multiplechoice->getAnswers($station['id']);
            foreach($solutions as &$solution)
            {
                $answer = (array_key_exists($solution['pos']-1, $answers)) ? true : false;
                $this->Multiplechoice->setCharactergroupSubmission($solution['id'], $charactergroup['id'], $answer);
            }
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
            $answers = (!is_array($answer)) ? array() : $answer;
            $solutions = $this->Multiplechoice->getAnswers($station['id']);
            foreach($solutions as &$solution)
            {
                if(is_null($solution['tick'])) {
                    continue;
                }
                if($solution['tick']) {
                    if(!array_key_exists($solution['pos']-1, $answers)) {
                        return false;
                    }
                }
                else {
                    if(array_key_exists($solution['pos']-1, $answers)) {
                        return false;
                    }
                }
            }


            // All questions correct answerd
            return true;
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
            // Get answers
            $answers = $this->Multiplechoice->getAnswers($station['id']);
            if(!is_null($charactergroup)) {
                foreach($answers as &$answer) {
                    $answer['submission'] = $this->Multiplechoice->getCharactergroupSubmission(
                        $answer['id'],
                        $charactergroup['id']
                    );
                }
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
            $this->set('answers', $answers);
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
            // Get questions
            $answers = $this->Multiplechoice->getAnswers($station['id']);

            // Save data
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('save')))
            {
                // Get params
                $answers = $this->request->getPostParam('answers');
                if(is_null($answers)) {
                    $answers = array();
                }
                $answers = array_values($answers);

                // Save answers
                foreach($answers as $answerIndex => &$answer)
                {
                    $this->Multiplechoice->setAnswer(
                        $this->Auth->getUserId(),
                        $station['id'],
                        $answerIndex + 1,
                        $answer['answer'],
                        array_key_exists('tick', $answer)
                    );
                }

                // Delete deleted answers
                $this->Multiplechoice->deleteAnswers(
                    $station['id'],
                    count($answers)
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


            // Pass data to view
            $this->set('task', $station['task']);
            $this->set('answers', $answers);
        }

    }

?>
