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
     * Controller of the DragndropQuesttypeAgent for Drag&Drop.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class DragndropQuesttypeController extends \hhu\z\controllers\QuesttypeController
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
            // Get Drag&Drop field
            $dndField = $this->Dragndrop->getDragndrop($quest['id']);

            // Get Drops
            $drops = $this->Dragndrop->getDrops($dndField['quest_id']);

            // Save user answers
            foreach($drops as &$drop)
            {
                // Determine user answer
                $answer = null;
                if(array_key_exists($drop['id'], $answers) && !empty($answers[$drop['id']]))
                {
                    $a = intval(substr($answers[$drop['id']], 4));
                    if($a !== false && $a > 0) {
                        $answer = $a;
                    }
                }

                // Update database record
                $this->Dragndrop->setCharacterSubmission($drop['id'], $character['id'], $answer);
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
            // Get Drag&Drop field
            $dndField = $this->Dragndrop->getDragndrop($quest['id']);

            // Get Drags
            $drags = $this->Dragndrop->getDrags($dndField['quest_id'], true);

            // Match drags with user answers
            foreach($drags as &$drag)
            {
                $founds = array_keys($answers, 'drag'.$drag['id']);
                if(count($founds) != 1) {
                    return false;
                }
                if(!$this->Dragndrop->dragMatchesDrop($drag['id'], $founds[0])) {
                    return false;
                }
            }


            // Set status
            return true;
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
            // Get Drag&Drop field
            $dndField = $this->Dragndrop->getDragndrop($quest['id']);
            if(!is_null($dndField) && !is_null($dndField['questmedia_id'])) {
                $dndField['media'] = $this->Media->getSeminaryMediaById($dndField['questmedia_id']);
            }

            // Get Drags
            $drags = array();
            if(!is_null($dndField))
            {
                $dragsByIndex = $this->Dragndrop->getDrags($dndField['quest_id']);
                foreach($dragsByIndex as &$drag) {
                    $drag['media'] = $this->Media->getSeminaryMediaById($drag['questmedia_id']);
                    $drags[$drag['id']] = $drag;
                }
            }

            // Get Drops
            $drops = array();
            if(!is_null($dndField)) {
                $drops = $this->Dragndrop->getDrops($dndField['quest_id']);
            }

            // Get Character answers
            if($this->request->getGetParam('show-answer') == 'true' || !$this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']) || $this->request->getGetParam('status') == 'solved')
            {
                foreach($drops as &$drop)
                {
                    $drop['answer'] = $this->Dragndrop->getCharacterSubmission($drop['id'], $character['id']);
                    if(!is_null($drop['answer']))
                    {
                        $drop['answer'] = $drags[$drop['answer']];
                        unset($drags[$drop['answer']['id']]);
                    }
                }
            }


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('field', $dndField);
            $this->set('drops', $drops);
            $this->set('drags', $drags);
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
            // Get Drag&Drop field
            $dndField = $this->Dragndrop->getDragndrop($quest['id']);
            $dndField['media'] = $this->Media->getSeminaryMediaById($dndField['questmedia_id']);

            // Get Drags
            $drags = array();
            $dragsByIndex = $this->Dragndrop->getDrags($dndField['quest_id']);
            foreach($dragsByIndex as &$drag) {
                $drag['media'] = $this->Media->getSeminaryMediaById($drag['questmedia_id']);
                $drags[$drag['id']] = $drag;
            }

            // Get Drops
            $drops = $this->Dragndrop->getDrops($dndField['quest_id']);

            // Get Character answers
            foreach($drops as &$drop)
            {
                $drop['answer'] = $this->Dragndrop->getCharacterSubmission($drop['id'], $character['id']);
                if(!is_null($drop['answer']))
                {
                    $drop['answer'] = $drags[$drop['answer']];
                    unset($drags[$drop['answer']['id']]);
                }
            }


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('field', $dndField);
            $this->set('drops', $drops);
            $this->set('drags', $drags);
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
            // Get Drag&Drop field
            $dndField = $this->Dragndrop->getDragndrop($quest['id']);
            if(!is_null($dndField)) {
                $dndField['media'] = $this->Media->getSeminaryMediaById($dndField['questmedia_id']);
            }

            // Get Drop-items
            $drops = array();
            if(!is_null($dndField)) {
                $drops = $this->Dragndrop->getDrops($dndField['quest_id']);
            }

            // Get Drag-items
            $drags = array();
            if(!is_null($dndField))
            {
                $drags = $this->Dragndrop->getDrags($dndField['quest_id']);
                foreach($drags as &$drag)
                {
                    $drag['media'] = $this->Media->getSeminaryMediaById($drag['questmedia_id']);
                    $drag['drops'] = array_map(function($d) { return $d['id']; }, $this->Dragndrop->getDropsForDrag($drag['id']));
                }
            }

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['questtypes'];

            // Values
            $step = 0;
            $steps = 2;
            $validation = true;
            $dragsValidation = true;

            // Save submitted data
            if($this->request->getRequestMethod() == 'POST')
            {
                // Get current step
                $step = max(0, min(2, intval($this->request->getPostParam('step'))));

                // Drag&Drop-field (background image)
                if($step == 0)
                {
                    // Validate zone
                    $zone = null;
                    if(!empty($_FILES) && array_key_exists('zone', $_FILES) && $_FILES['zone']['error'] != UPLOAD_ERR_NO_FILE)
                    {
                        $zone = $_FILES['zone'];

                        // Check error
                        if($zone['error'] !== UPLOAD_ERR_OK) {
                            $validation = $this->Validation->addValidationResult($validation, 'zone', 'error', $zone['error']);
                        }

                        // Check mimetype
                        $mediaMimetype = null;
                        $zone['mimetype'] = \hhu\z\Utils::getMimetype($zone['tmp_name'], $zone['type']);
                        foreach($mimetypes as &$mimetype) {
                            if($mimetype['mimetype'] == $zone['mimetype']) {
                                $mediaMimetype = $mimetype;
                                break;
                            }
                        }
                        if(is_null($mediaMimetype)) {
                            $validation = $this->Validation->addValidationResult($validation, 'zone', 'mimetype', $zone['mimetype']);
                        }
                        elseif($zone['size'] > $mediaMimetype['size']) {
                            $validation = $this->Validation->addValidationResult($validation, 'zone', 'size', $mediaMimetype['size']);
                        }
                    }

                    // Set zone
                    if($validation === true)
                    {
                        // Upload background image
                        $mediaId = $this->Media->createQuestMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('quest-dnd-%s', $quest['url']),
                            '',
                            $zone['mimetype'],
                            $zone['tmp_name']
                        );
                        if($mediaId !== false)
                        {
                            // Create Drag&Drop zone
                            $this->Dragndrop->createDragndrop(
                                $this->Auth->getUserId(),
                                $quest['id'],
                                $mediaId
                            );
                        }

                        // Reload Drag&Drop field
                        $dndField = $this->Dragndrop->getDragndrop($quest['id']);
                        $dndField['media'] = $this->Media->getSeminaryMediaById($dndField['questmedia_id']);
                    }
                }
                // Drop-items
                elseif($step == 1)
                {
                    // Get new Drop-items and organize them
                    $dropsNew = array();
                    $dropsUpdate = array();
                    foreach($this->request->getPostParam('drops') as $drop)
                    {
                        if(array_key_exists('id', $drop)) {
                            $dropsUpdate[$drop['id']] = $drop;
                        }
                        else {
                            $dropsNew[] = $drop;
                        }
                    }

                    // Update Drop-items
                    foreach($drops as $drop)
                    {
                        if(array_key_exists($drop['id'], $dropsUpdate))
                        {
                            $drop = $dropsUpdate[$drop['id']];
                            $this->Dragndrop->editDrop($drop['id'], $drop['width'], $drop['height'], $drop['x'], $drop['y']);
                        }
                        else {
                            $this->Dragndrop->deleteDrop($drop['id']);
                        }
                    }
                    // Add new Drop-items
                    foreach($dropsNew as $drop) {
                        $this->Dragndrop->addDrop($dndField['quest_id'], $drop['width'], $drop['height'], $drop['x'], $drop['y']);
                    }

                    // Reload Drop-items
                    $drops = $this->Dragndrop->getDrops($dndField['quest_id']);
                }
                // Drag-items
                elseif($step == 2)
                {
                    // Get new Drop-items and organize them
                    $dragsNew = array();
                    $dragsUpdate = array();
                    foreach($this->request->getPostParam('drags') as $index => $drag)
                    {
                        // Get file
                        if(array_key_exists($index, $_FILES['drags']['error']) && $_FILES['drags']['error'][$index] !== UPLOAD_ERR_NO_FILE)
                        {
                            $drag['file'] = array(
                                'name'      => $_FILES['drags']['name'][$index],
                                'type'      => $_FILES['drags']['type'][$index],
                                'tmp_name'  => $_FILES['drags']['tmp_name'][$index],
                                'error'     => $_FILES['drags']['error'][$index],
                                'size'      => $_FILES['drags']['size'][$index]
                            );

                            // Validate file
                            $dragValidation = true;

                            // Check error
                            if($drag['file']['error'] !== UPLOAD_ERR_OK) {
                                $dragValidation = $this->Validation->addValidationResult($dragValidation, 'file', 'error', $drag['file']['error']);
                            }

                            // Check mimetype
                            $dragMimetype = null;
                            $drag['file']['mimetype'] = \hhu\z\Utils::getMimetype($drag['file']['tmp_name'], $drag['file']['type']);
                            foreach($mimetypes as &$mimetype) {
                                if($mimetype['mimetype'] == $drag['file']['mimetype']) {
                                    $dragMimetype = $mimetype;
                                    break;
                                }
                            }
                            if(is_null($dragMimetype)) {
                                $dragValidation = $this->Validation->addValidationResult($dragValidation, 'file', 'mimetype', $drag['file']['mimetype']);
                            }
                            elseif($drag['file']['size'] > $dragMimetype['size']) {
                                $dragValidation = $this->Validation->addValidationResult($dragValidation, 'file', 'size', $dragMimetype['size']);
                            }

                            // Add validation result
                            if($dragValidation !== true)
                            {
                                if(!is_array($dragsValidation)) {
                                    $dragsValidation = array();
                                }
                                $dragsValidation[$index] = $dragValidation;
                            }

                            // Upload Drag-item file
                            if($dragValidation === true)
                            {
                                $drag['file']['media_id'] = $this->Media->createQuestMedia(
                                    $this->Auth->getUserId(),
                                    $seminary['id'],
                                    sprintf('quest-dnd-%s-%s', substr($quest['url'], 0, 25), substr($drag['file']['name'], 0, 25)),
                                    '',
                                    $drag['file']['mimetype'],
                                    $drag['file']['tmp_name']
                                );
                            }
                        }

                        // Add to array
                        if(array_key_exists('id', $drag)) {
                            $dragsUpdate[$drag['id']] = $drag;
                        }
                        else {
                            $dragsNew[] = $drag;
                        }
                    }

                    // Update Drag-items
                    foreach($drags as $drag)
                    {
                        if(array_key_exists($drag['id'], $dragsUpdate))
                        {
                            $drag = $dragsUpdate[$drag['id']];
                            // Edit Drag-items
                            if(array_key_exists('file', $drag) && array_key_exists('media_id', $drag['file'])) {
                                $this->Dragndrop->editDrag($drag['id'], $drag['file']['media_id']);
                            }
                            // Set correct Drop-items for Drag-item
                            $this->Dragndrop->setDropsForDrag(
                                $this->Auth->getUserId(),
                                $drag['id'],
                                array_key_exists('drops', $drag) ? array_keys($drag['drops']) : array()
                            );
                        }
                        else {
                            $this->Dragndrop->deleteDrag($drag['id']);
                        }
                    }
                    // Add new Drag-items
                    foreach($dragsNew as $drag)
                    {
                        if(array_key_exists('file', $drag) && array_key_exists('media_id', $drag['file']))
                        {
                            // Create Drag-item
                            $dragId = $this->Dragndrop->addDrag($dndField['quest_id'], $drag['file']['media_id']);

                            // Set Drop-items for Drag-item
                            $this->Dragndrop->setDropsForDrag(
                                $this->Auth->getUserId(),
                                $dragId,
                                array_key_exists('drops', $drag) ? array_keys($drag['drops']) : array()
                            );
                        }
                    }

                    // Reload Drag-items
                    $drags = $this->Dragndrop->getDrags($dndField['quest_id']);
                    foreach($drags as &$drag)
                    {
                        $drag['media'] = $this->Media->getSeminaryMediaById($drag['questmedia_id']);
                        $drag['drops'] = array_map(function($d) { return $d['id']; }, $this->Dragndrop->getDropsForDrag($drag['id']));
                    }
                }

                // Go to next/previous step
                if(!is_null($this->request->getPostParam('prev'))) {
                    $step--;
                }
                else {
                    $step++;
                }

                // Redirect after last step
                if($step > $steps)
                {
                    if($validation === true && $dragsValidation === true) {
                        $this->redirect($this->linker->link(array('quest', $seminary['url'], $questgroup['url'], $quest['url']), 1));
                    }
                    else {
                        $step--;
                    }
                }
            }


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('zone', $dndField);
            $this->set('drops', $drops);
            $this->set('drags', $drags);
            $this->set('mimetypes', $mimetypes);
            $this->set('step', $step);
            $this->set('validation', $validation);
            $this->set('dragsValidation', $dragsValidation);
        }

    }

?>
