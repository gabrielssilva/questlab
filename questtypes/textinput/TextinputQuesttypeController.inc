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
     * Controller of the TextinputQuesttypeAgent for for inserting text.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class TextinputQuesttypeController extends \hhu\z\controllers\QuesttypeController
    {
        /**
         * Required components
         *
         * @var array
         */
        public $components = array('validation', 'questtypedata');
        /**
         * Count of correct answers
         *
         * @var int
         */
        const KEY_QUESTTYPEDATA_N_CORRECT_ANSWRES = 'nCorrectAnswers';

        private $nCorrectAnswers = null;




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
            // Get fields
            $fields = $this->Textinput->getTextinputFields($quest['id']);

            // Save answers
            foreach($fields as &$field)
            {
                $pos = intval($field['number']) - 1;
                $answer = (array_key_exists($pos, $answers)) ? $answers[$pos] : '';
                $this->Textinput->setCharacterSubmission($field['id'], $character['id'], $answer);
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
            // Get right answers
            $fields = $this->Textinput->getTextinputFields($quest['id']);

            // Match regexs with user answers
            $nCorrectAnswers = 0;
            foreach($fields as &$field)
            {
                $pos = intval($field['number']) - 1;
                if(!array_key_exists($pos, $answers)) {
                    continue;
                }
                if(!$this->isMatching($field['regex'], $answers[$pos])) {
                    continue;
                }
                $nCorrectAnswers++;
            }

            // Save count of correct answers
            $this->Questtypedata->set(
                $quest['id'],
                self::KEY_QUESTTYPEDATA_N_CORRECT_ANSWRES,
                $nCorrectAnswers
            );


            // All answers right
            return ($nCorrectAnswers == count($fields));
        }


        /**
         * Action: quest.
         *
         * Display a text with input fields and evaluate if user input
         * matches with stored regular expressions.
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
            $task = $this->Textinput->getTextinputQuest($quest['id']);

            // Get fields
            $fields = $this->Textinput->getTextinputFields($quest['id']);

            // Has Character already solved Quest?
            $solved = $this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']);

            // Get Character answers
            if(!$solved || $this->request->getGetParam('show-answer') == 'true' || $this->request->getGetParam('status') == 'solved')
            {
                foreach($fields as &$field) {
                    $field['answer'] = $this->Textinput->getCharacterSubmission($field['id'], $character['id']);
                }
            }

            // Get count of last correct answers
            $nCorrectAnswers = $this->Questtypedata->get($quest['id'], self::KEY_QUESTTYPEDATA_N_CORRECT_ANSWRES);
            $this->Questtypedata->set(
                $quest['id'],
                self::KEY_QUESTTYPEDATA_N_CORRECT_ANSWRES,
                null
            );


            // Pass data to view
            $this->set('task', $task);
            $this->set('fields', $fields);
            $this->set('nCorrectAnswers', $nCorrectAnswers);
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
            $task = $this->Textinput->getTextinputQuest($quest['id']);

            // Process text
            $textParts = preg_split('/(\$\$)/', ' '.$task['text'].' ');

            // Get fields
            $fields = $this->Textinput->getTextinputFields($quest['id']);

            // Get Character answers
            foreach($fields as &$field)
            {
                $field['answer'] = $this->Textinput->getCharacterSubmission($field['id'], $character['id']);
                $field['right'] = $this->isMatching($field['regex'], $field['answer']);
            }


            // Pass data to view
            $this->set('task', $task);
            $this->set('fields', $fields);
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
            $task = $this->Textinput->getTextinputQuest($quest['id']);
            $text = $task['text'];

            // Get fields
            $fields = $this->Textinput->getTextinputFields($quest['id']);

            // Get field sizes
            $fieldSizes = $this->Textinput->getFieldSizes();

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
                    $fields = $this->request->getPostParam('fields');
                    if(is_null($fields) && !is_array($fields)) {
                        $fields = array();
                    }
                    $fields = array_values($fields);
                    $fieldIndex = 0;
                    foreach($fields as &$field)
                    {
                        // Validate regex
                        $regex = $field['regex'];
                        $fieldValidation = @preg_match($regex, '') !== false;
                        if($fieldValidation !== true)
                        {
                            if(!array_key_exists($fieldIndex, $validations) || !is_array($validations[$fieldIndex])) {
                                $validations[$fieldIndex] = array();
                            }
                            $validations[$fieldIndex] = $this->Validation->addValidationResults($validations[$fieldIndex], 'regex', $fieldValidation);
                        }

                        // Validate size
                        foreach($fieldSizes as $sizeIndex => &$size)
                        {
                            if($size['size'] == $field['size'])
                            {
                                $field['sizeIndex'] = $sizeIndex;
                                break;
                            }
                        }
                        if(!array_key_exists('sizeIndex', $field)) {
                            throw new \nre\exceptions\ParamsNotValidException($fieldIndex);
                        }

                        $fieldIndex++;
                    }

                    // Save and redirect
                    if(!is_null($this->request->getPostParam('save')) && empty($validations))
                    {
                        // Save text
                        $this->Textinput->setTextForQuest(
                            $this->Auth->getUserId(),
                            $quest['id'],
                            $text
                        );

                        // Save field
                        foreach($fields as $index => &$field)
                        {
                            // Add regex modifiers
                            $modifiers = substr($field['regex'], strrpos($field['regex'], $field['regex'][0]) + 1);
                            if(strpos($modifiers, 'u') === false) {
                                $field['regex'] .= 'u';
                            }

                            // Save field
                            $this->Textinput->setFieldForText(
                                $quest['id'],
                                $index + 1,
                                $fieldSizes[$field['sizeIndex']]['id'],
                                $field['regex']
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
            $this->set('fields', $fields);
            $this->set('fieldSizes', $fieldSizes);
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
            $score = preg_match($regex, trim($answer));


            return ($score !== false && $score > 0);
        }

    }

?>
