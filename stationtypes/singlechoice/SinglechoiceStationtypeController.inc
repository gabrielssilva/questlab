<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\stationtypes;


    /**
     * Controller of the StationtypeAgent for a single choice task.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SinglechoiceStationtypeController extends \hhu\z\controllers\StationtypeController
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
            $this->Singlechoice->setCharactergroupSubmission(
                $station['id'],
                $charactergroup['id'],
                intval($answer)
            );
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
            // Get question
            $question = $this->Singlechoice->getQuestion($station['id']);


            // ID of answer maches correct one’s
            return $question['answer_id'] == intval($answer);
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
            // Get question
            $question = $this->Singlechoice->getQuestion($station['id']);

            // Get answers
            $answers = $this->Singlechoice->getAnswers($station['id']);

            // Get submission
            if(!is_null($charactergroup)) {
                $question['submission'] = $this->Singlechoice->getCharactergroupSubmission(
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
            $this->set('question', $question);
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
            // Get question
            $question = $this->Singlechoice->getQuestion($station['id']);

            // Get answers
            $answers = $this->Singlechoice->getAnswers($station['id']);

            // Save data
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('save')))
            {
                // Get params
                $corectAnswerIndex = $this->request->getPostParam('answer');
                $corectAnswerIndex = intval($corectAnswerIndex);
                $answers = $this->request->getPostParam('answers');
                if(is_null($answers)) {
                    $answers = array();
                }

                // Save question
                $this->Singlechoice->setQuestion(
                    $this->Auth->getUserId(),
                    $station['id']
                );

                // Save answers
                $correctAnswerId = null;
                $index = 0;
                foreach($answers as $answerIndex => &$answer)
                {
                    $answerId = $this->Singlechoice->setAnswer(
                        $this->Auth->getUserId(),
                        $station['id'],
                        ++$index,
                        $answer['answer']
                    );
                    if($answerIndex == $corectAnswerIndex || is_null($correctAnswerId)) {
                        $correctAnswerId = $answerId;
                    }
                }

                // Delete deleted answers
                $this->Singlechoice->deleteAnswers(
                    $station['id'],
                    count($answers)
                );

                // Set correct answer
                $this->Singlechoice->setCorrectAnswer(
                    $station['id'],
                    $correctAnswerId
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
            $this->set('question', $question);
            $this->set('answers', $answers);
        }

    }

?>
