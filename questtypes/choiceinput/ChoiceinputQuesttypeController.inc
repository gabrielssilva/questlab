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
     * Controller of the ChoiceinputQuesttypeAgent for choosing between
     * predefined input values.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class ChoiceinputQuesttypeController extends \hhu\z\controllers\QuesttypeController
    {
        /**
         * Required components
         *
         * @var array
         */
        public $components = array('validation');




        /**
         * Save the answers of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $answers    Character answers for the Quest
         */
        public function saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
        {
            // Get lists
            $choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);

            // Save answers
            foreach($choiceLists as &$list)
            {
                $pos = intval($list['number']) - 1;
                $answer = (array_key_exists($pos, $answers)) ? $answers[$pos] : null;
                $this->Choiceinput->setCharacterSubmission($list['id'], $character['id'], $answer);
            }
        }


        /**
         * Save additional data for the answers of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $data       Additional (POST-) data
         */
        public function saveDataForCharacterAnswers($seminary, $questgroup, $quest, $character, $data)
        {
        }


        /**
         * Check if answers of a Character for a Quest match the correct ones.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $answers    Character answers for the Quest
         * @return  boolean         True/false for a right/wrong answer or null for moderator evaluation
         */
        public function matchAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
        {
            // Get lists
            $choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);

            // Match lists with user answers
            foreach($choiceLists as &$list)
            {
                $pos = intval($list['number']) - 1;
                if(!array_key_exists($pos, $answers)) {
                    return false;
                }
                if($list['questtypes_choiceinput_choice_id'] != $answers[$pos]) {
                    return false;
                }
            }


            // All answers right
            return true;
        }


        /**
         * Action: quest.
         *
         * Display a text with lists with predefined values.
         *
         * @param   array       $seminary   Current Seminary data
         * @param   array       $questgroup Current Questgroup data
         * @param   array       $quest      Current Quest data
         * @param   array       $character  Current Character data
         * @param   \Exception  $exception  Character submission exception
         */
        public function quest($seminary, $questgroup, $quest, $character, $exception)
        {
            // Get Task
            $task = $this->Choiceinput->getChoiceinputQuest($quest['id']);

            // Get lists
            $choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);
            foreach($choiceLists as &$list) {
                $list['values'] = $this->Choiceinput->getChoiceinputChoices($list['id']);
            }

            // Get Character answers
            if($this->request->getGetParam('show-answer') == 'true' || !$this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id'])  || $this->request->getGetParam('status') == 'solved') {
                foreach($choiceLists as &$list) {
                    $list['answer'] = $this->Choiceinput->getCharacterSubmission($list['id'], $character['id']);
                }
            }


            // Pass data to view
            $this->set('task', $task);
            $this->set('choiceLists', $choiceLists);
        }


        /**
         * Action: submission.
         *
         * Show the submission of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         */
        public function submission($seminary, $questgroup, $quest, $character)
        {
            // Get Task
            $task = $this->Choiceinput->getChoiceinputQuest($quest['id']);

            // Get lists
            $choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);
            foreach($choiceLists as &$list)
            {
                $list['values'] = $this->Choiceinput->getChoiceinputChoices($list['id']);
                $list['answer'] = $this->Choiceinput->getCharacterSubmission($list['id'], $character['id']);
                $list['right'] = ($list['questtypes_choiceinput_choice_id'] == $list['answer']);
            }


            // Pass data to view
            $this->set('task', $task);
            $this->set('choiceLists', $choiceLists);
        }


        /**
         * Action: edittask.
         *
         * Edit the task of a Quest.
         *
         * @param   array       $seminary   Current Seminary data
         * @param   array       $questgroup Current Questgroup data
         * @param   array       $quest      Current Quest data
         */
        public function edittask($seminary, $questgroup, $quest)
        {
            // Get Task
            $task = $this->Choiceinput->getChoiceinputQuest($quest['id']);
            $text = $task['text'];

            // Get lists
            $choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);
            foreach($choiceLists as &$list)
            {
                $list['choices'] = $this->Choiceinput->getChoiceinputChoices($list['id']);
                foreach($list['choices'] as $index => &$choice) {
                    //$choice['correct'] = ($choice['id'] == $list['questtypes_choiceinput_choice_id']);
                    if($choice['id'] == $list['questtypes_choiceinput_choice_id']) {
                        $list['answer'] = $index;
                    }
                    $choice = $choice['text'];
                }
                //$list = $list['choices'];
            }

            // Values
            $validations = array();

            // Save data
            if($this->request->getRequestMethod() == 'POST')
            {
                if(!is_null($this->request->getPostParam('preview')) || !is_null($this->request->getPostParam('save')))
                {
                    // Get params and validate them
                    if(is_null($this->request->getPostParam('text'))) {
                        throw new \nre\exceptions\ParamsNotValidException('text');
                    }
                    $text = $this->request->getPostParam('text');
                    if(is_null($this->request->getPostParam('lists'))) {
                        throw new \nre\exceptions\ParamsNotValidException('lists');
                    }
                    $choiceLists = $this->request->getPostParam('lists');
                    $choiceLists = array_values($choiceLists);
                    foreach($choiceLists as $listIndex => &$list)
                    {
                        // Validate choices
                        if(!array_key_exists('choices', $list)) {
                            throw new \nre\exceptions\ParamsNotValidException('choices');
                        }
                        $choiceIndex = 0;
                        $answer = null;
                        foreach($list['choices'] as $index => &$choice)
                        {
                            // Validate choice
                            $choiceValidation = $this->Validation->validate($choice, \nre\configs\AppConfig::$validation['choice']);
                            if($choiceValidation !== true)
                            {
                                if(!array_key_exists($listIndex, $validations) || !is_array($validations[$listIndex])) {
                                    $validations[$listIndex] = array();
                                }
                                if(!array_key_exists('choices', $validations[$listIndex])) {
                                    $validations[$listIndex]['choices'] = array();
                                }
                                $validations[$listIndex]['choices'][$choiceIndex] = $choiceValidation;
                            }

                            $choiceIndex++;
                            if(array_key_exists('answer', $list) && $list['answer'] == $index) {
                                $answer = $choiceIndex;
                            }
                        }

                        // Validate correct answer
                        if(is_null($answer))
                        {
                            if(!array_key_exists($listIndex, $validations) || !is_array($validations[$listIndex])) {
                                $validations[$listIndex] = array();
                            }
                            if(!array_key_exists('answer', $validations[$listIndex])) {
                                $validations[$listIndex]['answer'] = array();
                            }
                            $validations[$listIndex] = $this->Validation->addValidationResult($validations[$listIndex], 'answer', 'exist', true);
                        }
                    }

                    // Save and redirect
                    if(!is_null($this->request->getPostParam('save')) && empty($validations))
                    {
                        // Save text
                        $this->Choiceinput->setTextForQuest(
                            $this->Auth->getUserId(),
                            $quest['id'],
                            $text
                        );

                        // Save lists and choices
                        foreach($choiceLists as $listIndex => &$list)
                        {
                            // Save list
                            $this->Choiceinput->setListForText(
                                $quest['id'],
                                $listIndex + 1,
                                $list['choices'],
                                $list['answer'] + 1
                            );
                        }

                        // Redirect
                        $this->redirect($this->linker->link(array('quest', $seminary['url'], $questgroup['url'], $quest['url']), 1));
                    }
                }
            }


            // Pass data to view
            $this->set('task', $task);
            $this->set('text', $text);
            $this->set('choiceLists', $choiceLists);
            $this->set('validations', $validations);
        }

    }

?>
