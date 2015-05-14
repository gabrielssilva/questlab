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
         * Required components
         *
         * @var array
         */
        public $components = array('validation');

        private $validationSettings = array(
            'bossname' => array(
                'minlength' => 1,
                'maxlength' => 32
            ),
            'lives_boss' => array(
                'minlength' => 1,
                'regex'     => '/^(\d*)$/'
            ),
            'lives_character' => array(
                'minlength'     => 1,
                'regex'         => '/^(\d*)$/'
            )
        );




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
            // Get Fight
            $fight = $this->Bossfight->getBossFight($quest['id']);
            if(!is_null($fight['boss_seminarymedia_id'])) {
                $fight['bossmedia'] = $this->Media->getSeminaryMediaById($fight['boss_seminarymedia_id']);
            }

            // Get Character
            $character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);

            // Create (pseudo) tree
            $tree = $this->createStageTree($fight['lives_character'], $fight['lives_boss']);
            $this->attachStages($quest['id'], $tree);

            // TODO Test
            print_r($this->createStageTree2($quest['id'], $fight['lives_character'], $fight['lives_boss']));

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['questtypes'];

            // Values
            $step = 1;
            $steps = 1;
            $bossname = $fight['bossname'];
            $livesCharacter = $fight['lives_character'];
            $livesBoss = $fight['lives_boss'];
            $fields = array('bossname', 'lives_boss', 'lives_character');
            $validation = true;

            // Save submitted data
            if($this->request->getRequestMethod() == 'POST')
            {
                // Get current step
                $step = max(0, min($steps, intval($this->request->getPostParam('step'))));

                // Bossfight
                if($step == 0)
                {
                    // Get params and validate them
                    $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields, $this->validationSettings);
                    $bossname = $this->request->getPostParam('bossname');
                    $livesCharacter = $this->request->getPostParam('lives_character');
                    $livesBoss = $this->request->getPostParam('lives_boss');

                    // Validate image
                    $bossimage = null;
                    if(!empty($_FILES) && array_key_exists('bossimage', $_FILES) && $_FILES['bossimage']['error'] != UPLOAD_ERR_NO_FILE)
                    {
                        $bossimage = $_FILES['bossimage'];

                        // Check error
                        if($bossimage['error'] !== UPLOAD_ERR_OK) {
                            $validation = $this->Validation->addValidationResult($validation, 'bossimage', 'error', $bossimage['error']);
                        }

                        // Check mimetype
                        $bossimageMimetype = null;
                        $bossimage['mimetype'] = \hhu\z\Utils::getMimetype($bossimage['tmp_name'], $bossimage['type']);
                        foreach($mimetypes as &$mimetype)
                        {
                            if($mimetype['mimetype'] == $bossimage['mimetype']) {
                                $bossimageMimetype = $mimetype;
                                break;
                            }
                        }
                        if(is_null($bossimageMimetype)) {
                            $validation = $this->Validation->addValidationResult($validation, 'bossimage', 'mimetype', $bossimage['mimetype']);
                        }
                        elseif($bossimage['size'] > $bossimageMimetype['size']) {
                            $validation = $this->Validation->addValidationResult($validation, 'bossimage', 'size', $bossimageMimetype['size']);
                        }
                    }

                    // Set Bossfight data
                    if($validation === true)
                    {
                        // Upload boss image
                        $mediaId = $this->Media->createQuestMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('quest-bossfight-%s', $quest['url']),
                            '',
                            $bossimage['mimetype'],
                            $bossimage['tmp_name']
                        );

                        // Save data
                        if(!is_null($fight))
                        {
                            // Edit Bossfight
                            $this->Bossfight->editBossFight(
                                $quest['id'],
                                $bossname,
                                ($mediaId !== false ? $mediaId : $fight['boss_seminarymedia_id']),
                                $livesCharacter,
                                $livesBoss
                            );

                            // TODO Delete needless stages
                        }
                        elseif($mediaId !== false)
                        {
                            // Create new Bossfight
                            $this->Bossfight-createBossFight(
                                $this->Auth->getUserId(),
                                $quest['id'],
                                $bossname,
                                $mediaId,
                                $livesCharacter,
                                $livesBoss
                            );
                        }

                        // Reload fight
                        $fight = $this->Bossfight->getBossFight($quest['id']);
                        if(!is_null($fight['boss_seminarymedia_id'])) {
                            $fight['bossmedia'] = $this->Media->getSeminaryMediaById($fight['boss_seminarymedia_id']);
                        }
                        $tree = $this->createStageTree($fight['lives_character'], $fight['lives_boss']);
                        $this->attachStages($quest['id'], $tree);
                    }
                }
                // Stages
                elseif($step == 1)
                {
                    // Get stages
                    $stages = $this->request->getPostParam('stages');

                    // Save stages
                    foreach($tree as $i => &$v)
                    {
                        if(array_key_exists($i, $stages))
                        {
                            foreach($v as $j => &$h)
                            {
                                if(array_key_exists($j, $stages[$i]))
                                {
                                    /*
                                    $text = $stages[$i][$j]['text'];
                                    $question = $stages[$i][$j]['question'];
                                    if(array_key_exists('stage', $h) && !empty($h['stage']))
                                    {
                                        // TODO Edit stage
                                        $stageId = $h['stage']['id'];
                                        var_dump($stageId);
                                    }
                                    else
                                    {
                                        // TODO Create new stage
                                        var_dump('create stage');
                                    }
                                    */
                                }
                            }
                        }
                    }
                }

                // Go to next/previous step
                // Go to next/previous step
                if($validation === true)
                {
                    if(!is_null($this->request->getPostParam('prev'))) {
                        $step--;
                    }
                    else {
                        $step++;
                    }
                    if($step > $steps) {
                        // TODO Redirect
                        //$this->redirect($this->linker->link(array('quest', $seminary['url'], $questgroup['url'], $quest['url']), 1));
                    }
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = $this->validationSettings[$field];
            }


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('character', $character);
            $this->set('fight', $fight);
            $this->set('step', $step);
            $this->set('tree', $tree);
            $this->set('bossname', $bossname);
            $this->set('livesCharacter', $livesCharacter);
            $this->set('livesBoss', $livesBoss);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
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


        private function createStageTree($livesCharacter, $livesBoss)
        {
            $c = max($livesCharacter, $livesBoss) * 2;
            $tree = array();

            $tree[0] = array(
                array(
                    'lives_character'   => $livesCharacter,
                    'lives_boss'        => $livesBoss
                )
            );
            for($i=1; $i<$c; $i++ )
            {
                $treeitem = array();
                $n = pow(2, $i);
                for($j=0; $j<$n/2; $j++)
                {
                    if(array_key_exists($j, $tree[$i-1]))
                    {
                        if($tree[$i-1][$j]['lives_character'] > 0 && $tree[$i-1][$j]['lives_boss'] > 0 && $tree[$i-1][$j]['lives_boss'] - 1 >= 0)
                        {
                            $treeitem[$j*2] = array(
                                'lives_character'   => $tree[$i-1][$j]['lives_character'],
                                'lives_boss'        => $tree[$i-1][$j]['lives_boss'] - 1,
                            );
                        }
                        if($tree[$i-1][$j]['lives_character'] > 0 && $tree[$i-1][$j]['lives_boss'] > 0 && $tree[$i-1][$j]['lives_character'] - 1 >= 0)
                        {
                            $treeitem[$j*2+1] = array(
                                'lives_character'   => $tree[$i-1][$j]['lives_character'] - 1,
                                'lives_boss'        => $tree[$i-1][$j]['lives_boss'],
                            );
                        }
                    }
                }

                $tree[] = $treeitem;
            }


            return $tree;
        }


        private function createStageTree2($questId, $livesCharacter, $livesBoss)
        {
            // Create tree root
            $tree = array();
            $tree[0] = array(
                'lives_character'   => $livesCharacter,
                'lives_boss'        => $livesBoss
            );

            // Get first stage
            $stage = $this->Bossfight->getFirstStage($questId);
            $tree[0]['stage'] = $stage;

            // Start recursion
            $this->createStageTreeRec($questId, $stage, $tree);


            // Return tree
            return $tree;
        }


        private function createStageTreeRec($questId, $stage, &$tree)
        {
            // Get child stages
            $childStages = $this->Bossfight->getChildStages($stage['id']);
            foreach($childStages as $childStage)
            {
                $this->createStageTreeRec($questId, $childStage, $tree);
            }
        }


        private function attachStages($questId, &$tree)
        {
            foreach($tree as $i => &$v)
            {
                if($i == 0) {
                    $v[0]['stage'] = $this->Bossfight->getFirstStage($questId);
                }
                else
                {
                    $childStages = null;
                    foreach($v as $j => &$h)
                    {
                        if(is_null($childStages))
                        {
                            $childStages = range(0, 1);
                            if(array_key_exists('stage', $tree[$i-1][floor($j/2)]) && !empty($tree[$i-1][floor($j/2)]['stage']))
                            {
                                $stages = $this->Bossfight->getChildStages($tree[$i-1][floor($j/2)]['stage']['id']);
                                if(!empty($stages)) {
                                    $childStages = $stages;
                                }
                            }
                            $tree[$i-1][floor($j/2)]['childstages'] = $childStages;
                            $h['stage'] = (count($childStages) > 0) ? $childStages[0] : array();
                        }
                        else {
                            $h['stage'] = (count($childStages) > 1) ? $childStages[1] : array();
                            $childStages = null;
                        }
                    }
                }
            }
        }

    }

?>
