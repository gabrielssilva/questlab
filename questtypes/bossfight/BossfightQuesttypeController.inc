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
     * Controller of the BossfightQuesttypeAgent for a boss-fight.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class BossfightQuesttypeController extends \hhu\z\controllers\QuesttypeController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('media');




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
            // Prepare session
            $this->prepareSession($quest['id']);

            // Remove previous answers
            $this->Bossfight->clearCharacterSubmissions($quest['id'], $character['id']);

            // Save answers
            foreach($_SESSION['quests'][$quest['id']]['stages'] as &$stage) {
                $this->Bossfight->setCharacterSubmission($stage['id'], $character['id']);
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
            return true;
        }


        /**
         * Action: quest.
         *
         * Display a stage with a text and the answers for the following
         * stages.
         *
         * @param   array       $seminary   Current Seminary data
         * @param   array       $questgroup Current Questgroup data
         * @param   array       $quest      Current Quest data
         * @param   array       $character  Current Character data
         * @param   \Exception  $exception  Character submission exception
         */
        public function quest($seminary, $questgroup, $quest, $character, $exception)
        {
            // Get Boss-Fight
            $fight = $this->Bossfight->getBossFight($quest['id']);
            if(!is_null($fight) && !is_null($fight['boss_seminarymedia_id'])) {
                $fight['bossmedia'] = $this->Media->getSeminaryMediaById($fight['boss_seminarymedia_id']);
            }

            // Prepare session
            $this->prepareSession($quest['id']);

            // Get Stage
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('submit_stages')))
            {
                $stages = $this->request->getPostParam('submit_stages');
                $stageId = array_keys($stages)[0];
                $stage = $this->Bossfight->getStageById($stageId);
            }
            else
            {
                $_SESSION['quests'][$quest['id']]['stages'] = array();
                $stage = $this->Bossfight->getFirstStage($quest['id']);
            }

            // Store Stage in session
            if(count($_SESSION['quests'][$quest['id']]['stages']) == 0 || $_SESSION['quests'][$quest['id']]['stages'][count($_SESSION['quests'][$quest['id']]['stages'])-1]['id'] != $stage['id']) {
                $_SESSION['quests'][$quest['id']]['stages'][] = $stage;
            }

            // Calculate lives
            $lives = array(
                'character' => $fight['lives_character'],
                'boss'      => $fight['lives_boss']
            );
            foreach($_SESSION['quests'][$quest['id']]['stages'] as &$stage)
            {
                $lives['character'] += $stage['livedrain_character'];
                $lives['boss'] += $stage['livedrain_boss'];
            }

            // Get Child-Stages
            $childStages = $this->Bossfight->getChildStages($stage['id']);

            // Get answer of Character
            if($this->request->getGetParam('show-answer') == 'true') {
                foreach($childStages as &$childStage) {
                    $childStage['answer'] = $this->Bossfight->getCharacterSubmission($childStage['id'], $character['id']);
                }
            }


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('character', $character);
            $this->set('fight', $fight);
            $this->set('stage', $stage);
            $this->set('lives', $lives);
            $this->set('childStages', $childStages);
        }


        /**
         * Action: submission.
         *
         * Display all stages with the answers the character has
         * choosen.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         */
        public function submission($seminary, $questgroup, $quest, $character)
        {
            // Get Boss-Fight
            $fight = $this->Bossfight->getBossFight($quest['id']);
            if(!is_null($fight['boss_seminarymedia_id'])) {
                $fight['bossmedia'] = $this->Media->getSeminaryMediaById($fight['boss_seminarymedia_id']);
            }

            // Get stages
            $stages = array();
            $stage = $this->Bossfight->getFirstStage($quest['id']);
            while(!is_null($stage))
            {
                $stages[] = $stage;

                $childStages = $this->Bossfight->getChildStages($stage['id']);
                $stage = null;
                foreach($childStages as &$childStage)
                {
                    if($this->Bossfight->getCharacterSubmission($childStage['id'], $character['id']))
                    {
                        $stage = $childStage;
                        break;
                    }
                }
            }

            // Calculate lives
            $stages[0]['lives'] = array(
                'character' => $fight['lives_character'],
                'boss'      => $fight['lives_boss']
            );
            for($i=1; $i<count($stages); $i++)
            {
                $stages[$i]['lives'] = array(
                    'character' => $stages[$i-1]['lives']['character'] + $stages[$i]['livedrain_character'],
                    'boss'      => $stages[$i-1]['lives']['boss'] + $stages[$i]['livedrain_boss'],
                );
            }


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('character', $character);
            $this->set('fight', $fight);
            $this->set('stages', $stages);
        }


        /**
         * TODO Action: edittask.
         *
         * Edit the task of a Quest.
         *
         * @param   array       $seminary   Current Seminary data
         * @param   array       $questgroup Current Questgroup data
         * @param   array       $quest      Current Quest data
         */
        public function edittask($seminary, $questgroup, $quest)
        {
            $fight = $this->Bossfight->getBossFight($quest['id']);
            /*
            if(!is_null($fight['boss_seminarymedia_id'])) {
                $fight['bossmedia'] = $this->Media->getSeminaryMediaById($fight['boss_seminarymedia_id']);
            }
            */

            // Get stages
            $stage = $this->Bossfight->getFirstStage($quest['id']);
            $stage['childs'] = $this->getChildStages($stage['id']);


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('fight', $fight);
            $this->set('stages', $stage);
            //print_r($stage);
        }




        /**
         * Prepare the session to store stage information in
         *
         * @param   int $questId    ID of Quest
         */
        private function prepareSession($questId)
        {
            if(!array_key_exists('quests', $_SESSION)) {
                $_SESSION['quests'] = array();
            }
            if(!array_key_exists($questId, $_SESSION['quests'])) {
                $_SESSION['quests'][$questId] = array();
            }
            if(!array_key_exists('stages', $_SESSION['quests'][$questId])) {
                $_SESSION['quests'][$questId]['stages'] = array();
            }
        }


        /**
         * Get all child-stages of a parent-stage.
         *
         * @param   int $stageId    ID of parent-stage
         * @return  array           List of child-stages
         */
        private function getChildStages($stageId)
        {
            $childStages = $this->Bossfight->getChildStages($stageId);
            if(!empty($childStages)) {
                foreach($childStages as &$stage) {
                    $stage['childs'] = $this->getChildStages($stage['id']);
                }
            }


            return $childStages;
        }

    }

?>
