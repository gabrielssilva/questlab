<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\controllers;


    /**
     * Controller of the LibraryAgent to list Quest topics.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class LibraryController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('questtopics', 'seminaries', 'quests', 'questgroups');
        /**
         * Required components
         *
         * @var array
         */
        public $components = array('validation');
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'index'     => array('admin', 'moderator', 'user'),
            'topic'     => array('admin', 'moderator', 'user'),
            'manage'    => array('admin', 'moderator', 'user'),
            'create'    => array('admin', 'moderator', 'user'),
            'edit'      => array('admin', 'moderator', 'user'),
            'delete'    => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'index'     => array('admin', 'moderator', 'user', 'guest'),
            'topic'     => array('admin', 'moderator', 'user', 'guest'),
            'manage'    => array('admin', 'moderator'),
            'create'    => array('admin', 'moderator'),
            'edit'      => array('admin', 'moderator'),
            'delete'    => array('admin', 'moderator')
        );




        /**
         * Action: index.
         *
         * List Questtopics of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of Seminary
         */
        public function index($seminaryUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character
            $character = SeminaryController::$character;

            // Get Quest topics
            $totalQuestcount = 0;
            $totalCharacterQuestcount = 0;
            $questtopics = $this->Questtopics->getQuesttopicsForSeminary($seminary['id']);
            foreach($questtopics as &$questtopic)
            {
                // Get Quest count
                $questtopic['questcount'] = $this->Questtopics->getQuestCountForQuesttopic($questtopic['id']);
                $totalQuestcount += $questtopic['questcount'];

                // Get Character progress
                $questtopic['characterQuestcount'] = $this->Questtopics->getCharacterQuestCountForQuesttopic($questtopic['id'], $character['id']);
                $totalCharacterQuestcount += $questtopic['characterQuestcount'];
            }


            // Set title
            $this->addTitleLocalized('Library');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('totalQuestcount', $totalQuestcount);
            $this->set('totalCharacterQuestcount', $totalCharacterQuestcount);
            $this->set('questtopics', $questtopics);
        }


        /**
         * Action: topic.
         *
         * Show a Questtopic and its Quests with Questsubtopics.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of Seminary
         * @param   string  $questtopicUrl  URL-Title of Questtopic
         */
        public function topic($seminaryUrl, $questtopicUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character
            $character = SeminaryController::$character;

            // Get Questtopic
            $questtopic = $this->Questtopics->getQuesttopicByUrl($seminary['id'], $questtopicUrl);
            $questtopic['questcount'] = $this->Questtopics->getQuestCountForQuesttopic($questtopic['id']);
            $questtopic['characterQuestcount'] = $this->Questtopics->getCharacterQuestCountForQuesttopic($questtopic['id'], $character['id']);

            // Get Quests
            $quests = array();
            foreach($this->Quests->getQuestsForQuesttopic($questtopic['id']) as $quest)
            {
                if($this->Quests->hasCharacterEnteredQuest($quest['id'], $character['id']) || count(array_intersect(array('admin', 'moderator'), self::$character['characterroles'])) > 0)
                {
                    // Get Subtopics
                    $quest['subtopics'] = $this->Questtopics->getQuestsubtopicsForQuest($quest['id']);

                    $quests[] = $quest;
                }
            }


            // Set title
            $this->addTitle($questtopic['title']);
            $this->addTitleLocalized('Library');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questtopic', $questtopic);
            $this->set('quests', $quests);
        }


        /**
         * Action: manage.
         *
         * Manage a Questtopic and its Quests with Questsubtopics.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of Seminary
         * @param   string  $questtopicUrl  URL-Title of Questtopic
         */
        public function manage($seminaryUrl, $questtopicUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questtopic
            $questtopic = $this->Questtopics->getQuesttopicByUrl($seminary['id'], $questtopicUrl);

            // Get Questsubtopics
            $questsubtopics = $this->Questtopics->getSubtopicsForQuesttopic($questtopic['id']);

            // Set Questsubtopics for Quests
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('questsubtopics')))
            {
                $selectedSubtopics = $this->request->getPostParam('questsubtopics');

                // Set subtopics of Quests
                $quests = $this->Quests->getQuestsForQuesttopic($questtopic['id']);
                foreach($quests as &$quest)
                {
                    $subtopics = (array_key_exists($quest['id'], $selectedSubtopics)) ? $selectedSubtopics[$quest['id']] : array();
                    $this->Questtopics->setQuestsubtopicsForQuest($quest['id'], array_keys($subtopics));
                }

                // Add Quest
                $addQuestId = $this->request->getPostParam('addquest');
                if(!empty($addQuestId))
                {
                    $subtopics = (array_key_exists('addquest', $selectedSubtopics)) ? $selectedSubtopics['addquest'] : array();
                    if(!empty($subtopics)) {
                        $this->Questtopics->setQuestsubtopicsForQuest($addQuestId, array_keys($subtopics));
                    }
                }

                // Redirect
                $this->redirect($this->linker->link(array('topic', $seminary['url'], $questtopic['url']), 1));
            }

            // Get Quests
            $quests = $this->Quests->getQuestsForQuesttopic($questtopic['id']);
            foreach($quests as &$quest)
            {
                // Get Subtopics
                $quest['subtopics'] = $this->Questtopics->getQuestsubtopicsForQuest($quest['id']);
                $quest['subtopics'] = array_map(function($t) { return $t['id']; }, $quest['subtopics']);
            }

            // Get all Quests
            $allQuests = $this->Quests->getQuestsForSeminary($seminary['id']);


            // Set title
            $this->addTitle($questtopic['title']);
            $this->addTitleLocalized('Library');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questtopic', $questtopic);
            $this->set('questsubtopics', $questsubtopics);
            $this->set('quests', $quests);
            $this->set('allQuests', $allQuests);
        }


        /**
         * Action: create.
         *
         * Create a new Questtopic for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of Seminary
         */
        public function create($seminaryUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Values
            $title = '';
            $fields = array('title');
            $validation = array();

            // Create new Questtopic
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Questtopics->questtopicTitleExists($title)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }

                // Create
                if($validation === true)
                {
                    $questtopicId = $this->Questtopics->createQuesttopic(
                        $this->Auth->getUserId(),
                        $seminary['id'],
                        $title
                    );
                    $questtopic = $this->Questtopics->getQuesttopicById($questtopicId);

                    // Redirect to Questtopic
                    $this->redirect($this->linker->link(array('topic', $seminary['url'], $questtopic['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set title
            $this->addTitleLocalized('New Questtopic');
            $this->addTitleLocalized('Library');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('title', $title);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edit.
         *
         * Edit a Questtopic of a Seminary and its Questsubtopics.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of Seminary
         * @param   string  $questtopicUrl  URL-Title of Questtopic
         */
        public function edit($seminaryUrl, $questtopicUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questtopic
            $questtopic = $this->Questtopics->getQuesttopicByUrl($seminary['id'], $questtopicUrl);

            // Get Questsubtopics
            $questsubtopics = $this->Questtopics->getSubtopicsForQuesttopic($questtopic['id']);

            // Values
            $questtopicTitle = $questtopic['title'];
            $subtopicsTitles = array();
            foreach($questsubtopics as &$questsubtopic) {
                $subtopicsTitles[$questsubtopic['id']] = $questsubtopic['title'];
            }
            $deleteSubtopics = null;
            $subtopicTitle = '';
            $validations = array(
                'edit'          => true,
                'edit-subtopics'    => true,
                'create-subtopic'   => true
            );

            // Edit
            $action = null;
            if($this->request->getRequestMethod() == 'POST')
            {
                // Edit Questtopic
                if(!is_null($this->request->getPostParam('edit')))
                {
                    $action = 'edit';

                    // Get params and validate them
                    $validations[$action] = $this->Validation->validateParams($this->request->getPostParams(), array('title'));
                    $questtopicTitle = $this->request->getPostParam('title');
                    if($this->Questtopics->questsubtopicTitleExists($questtopicTitle, $questtopic['id'])) {
                        $validations[$action] = $this->Validation->addValidationResult($validations[$action], 'title', 'exist', true);
                    }

                    // Edit
                    if($validations[$action] === true)
                    {
                        $this->Questtopics->editQuesttopic(
                            $questtopic['id'],
                            $questtopicTitle
                        );
                        $questtopic = $this->Questtopics->getQuesttopicById($questtopic['id']);

                        // Redirect
                        $this->redirect($this->linker->link(array('topic', $seminary['url'], $questtopic['url']), 1));
                    }
                }

                // Edit and delete Questsubtopics
                elseif(!is_null($this->request->getPostParam('edit-subtopics')))
                {
                    $action = 'edit-subtopics';

                    // Get params and validate them
                    $subtopicsTitles = $this->request->getPostParam('subtopics');
                    $deleteSubtopics = $this->request->getPostParam('delete-subtopics');
                    foreach($questsubtopics as &$questsubtopic)
                    {
                        if(!is_null($deleteSubtopics) && array_key_exists($questsubtopic['id'], $deleteSubtopics)) {
                            continue;
                        }

                        $title = $subtopicsTitles[$questsubtopic['id']];
                        $subtopicValidation = $this->Validation->validate($title, \nre\configs\AppConfig::$validation['title']);
                        if($subtopicValidation !== true)
                        {
                            if(!is_array($validations['edit-subtopics'])) {
                                $validations['edit-subtopics'] = array();
                            }
                            if(!array_key_exists($questsubtopic['id'], $validations['edit-subtopics']) || !is_array($validations['edit-subtopics'][$questsubtopic['id']])) {
                                $validations['edit-subtopics'][$questsubtopic['id']] = array();
                            }
                            //$validations['edit-subtopics'][$questsubtopic['id']]['title'] = $subtopicValidation;
                            $validations['edit-subtopics'][$questsubtopic['id']] = $this->Validation->addValidationResults($validations['edit-subtopics'][$questsubtopic['id']], 'title', $subtopicValidation);
                        }
                        if($this->Questtopics->questsubtopicTitleExists($questtopic['id'], $title, $questsubtopic['id']))
                        {
                            if(!is_array($validations['edit-subtopics'])) {
                                $validations['edit-subtopics'] = array();
                            }
                            if(!array_key_exists($questsubtopic['id'], $validations['edit-subtopics']) || !is_array($validations['edit-subtopics'][$questsubtopic['id']])) {
                                $validations['edit-subtopics'][$questsubtopic['id']] = array();
                            }
                            $validations['edit-subtopics'][$questsubtopic['id']] = $this->Validation->addValidationResult($validations['edit-subtopics'][$questsubtopic['id']], 'title', 'exist', true);
                        }
                    }

                    // Edit and delete
                    if($validations['edit-subtopics'] === true)
                    {
                        foreach($questsubtopics as &$questsubtopic)
                        {
                            // Delete
                            if(!is_null($deleteSubtopics) && array_key_exists($questsubtopic['id'], $deleteSubtopics)) {
                                $this->Questtopics->deleteQuestsubtopic($questsubtopic['id']);
                            }
                            // Edit
                            elseif(!is_null($subtopicsTitles) && array_key_exists($questsubtopic['id'], $subtopicsTitles))
                            {
                                $title = $subtopicsTitles[$questsubtopic['id']];
                                $this->Questtopics->editQuestsubtopic($questsubtopic['id'], $title);
                            }
                        }

                        // Redirect
                        $this->redirect($this->linker->link(array($seminary['url'], $questtopic['url']), 2));
                    }
                }

                // Create Questsubtopic
                elseif(!is_null($this->request->getPostParam('create-subtopic')))
                {
                    $action = 'create-subtopic';

                    // Get params and validate them
                    $validations[$action] = $this->Validation->validateParams($this->request->getPostParams(), array('title'));
                    $subtopicTitle = $this->request->getPostParam('title');
                    if($this->Questtopics->questsubtopicTitleExists($questtopic['id'], $subtopicTitle)) {
                        $validations[$action] = $this->Validation->addValidationResult($validations[$action], 'title', 'exist', true);
                    }

                    // Create
                    if($validations[$action] === true)
                    {
                        $this->Questtopics->createQuestsubtopic(
                            $this->Auth->getUserId(),
                            $questtopic['id'],
                            $subtopicTitle
                        );
                        $subtopicTitle = '';

                        // Redirect
                        $this->redirect($this->linker->link(null, 4));
                    }
                }
            }

            // Get validation settings
            $validationSettings = array(
                'title' => \nre\configs\AppConfig::$validation['title']
            );


            // Set title
            $this->addTitleLocalized('Edit Questtopic');
            $this->addTitleLocalized('Library');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questtopicTitle', $questtopicTitle);
            $this->set('subtopicsTitles', $subtopicsTitles);
            $this->set('deleteSubtopics', $deleteSubtopics);
            $this->set('subtopicTitle', $subtopicTitle);
            $this->set('action', $action);
            $this->set('validations', $validations);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: delete.
         *
         * Delete a Questtopic of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of Seminary
         * @param   string  $questtopicUrl  URL-Title of Questtopic
         */
        public function delete($seminaryUrl, $questtopicUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questtopic
            $questtopic = $this->Questtopics->getQuesttopicByUrl($seminary['id'], $questtopicUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete seminary
                    $this->Questtopics->deleteQuesttopic($questtopic['id']);

                    // Redirect to overview
                    $this->redirect($this->linker->link(array('index', $seminary['url']), 1));
                }
            }


            // Set title
            $this->addTitleLocalized('Delete Questtopic');
            $this->addTitleLocalized('Library');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questtopic', $questtopic);
        }

    }

?>
