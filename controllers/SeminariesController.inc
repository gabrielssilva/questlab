<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\controllers;


    /**
     * Controller of the Agent to list registered seminaries.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SeminariesController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('users', 'seminaries', 'characterroles', 'charactertypes', 'xplevels', 'questgroupshierarchy', 'questgroups', 'questgrouptexts', 'quests', 'questtexts', 'media');
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
            'index' => array('admin', 'moderator', 'user'),
            'seminary' => array('admin', 'moderator', 'user'),
            'create' => array('admin', 'moderator'),
            'edit' => array('admin', 'moderator', 'user'),
            'copy' => array('admin', 'moderator', 'user'),
            'delete' => array('admin', 'moderator', 'user'),
            'calculatexps' => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'seminary' => array('admin', 'moderator', 'user', 'guest'),
            'edit' => array('admin'),
            'copy' => array('admin'),
            'delete' => array('admin'),
            'calculatexps' => array('admin', 'moderator')
        );




        /**
         * Action: index.
         *
         * List registered seminaries.
         */
        public function index()
        {
            // Get seminaries
            $seminaries = $this->Seminaries->getSeminaries();

            // Get additional data
            foreach($seminaries as &$seminary)
            {
                $description = \hhu\z\Utils::shortenString($seminary['description'], 100, 120);
                $seminary['description'] = $description.(strlen($description) < strlen($seminary['description']) ? ' …' : null);
                $seminary['creator'] = $this->Users->getUserById($seminary['created_user_id']);
                $seminary['charactertypes'] = $this->Charactertypes->getCharacterTypesForSeminary($seminary['id']);
                $seminary['xplevels'] = $this->Xplevels->getXPLevelsForSeminary($seminary['id']);

                // Character of currently logged-in user
                try {
                    $seminary['usercharacter'] = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
                    $seminary['usercharacter']['characterroles'] = $this->Characterroles->getCharacterrolesForCharacterById($seminary['usercharacter']['id']);
                    $seminary['xps'] = $this->Seminaries->getTotalXPs($seminary['id']);
                }
                catch(\nre\exceptions\IdNotFoundException $e) {
                }

            }


            // Set titile
            $this->addTitleLocalized('Seminaries');

            // Pass data to view
            $this->set('seminaries', $seminaries);
        }


        /**
         * Action: seminary.
         *
         * Show a seminary and its details.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a seminary
         */
        public function seminary($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Created user
            $seminary['creator'] = $this->Users->getUserById($seminary['created_user_id']);

            // Get Character
            $character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);

            // Questgrouphierarchy and Questgroups
            $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyOfSeminary($seminary['id']);
            foreach($questgroupshierarchy as &$hierarchy)
            {
                // Get Questgroups
                $hierarchy['questgroups'] = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id']);

                // Get additional data
                foreach($hierarchy['questgroups'] as $i => &$questgroup)
                {
                    // Check permission of Questgroups
                    if($i >= 1 && count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) == 0)
                    {
                        if(!$this->Questgroups->hasCharacterSolvedQuestgroup($hierarchy['questgroups'][$i-1]['id'], $character['id']))
                        {
                            $hierarchy['questgroups'] = array_slice($hierarchy['questgroups'], 0, $i);
                            break;
                        }
                    }

                    // Get first Questgroup text
                    $text = $this->getFirstQuestgroupText($questgroup['id']);
                    if(!is_null($text))
                    {
                        $questgroup['text'] = \hhu\z\Utils::shortenString($text, 100, 120).' …';
                    }

                    // Get Character XPs
                    $questgroup['character_xps'] = $this->Questgroups->getAchievedXPsForQuestgroup($questgroup['id'], $character['id']);

                    // Get Media
                    $questgroup['picture'] = null;
                    try {
                        $questgroup['picture'] = $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']);
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                    }
                }
            }


            // Set titile
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('questgroupshierarchy', $questgroupshierarchy);
        }


        /**
         * Action: create.
         *
         * Create a new Seminary.
         */
        public function create()
        {
            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

            // Values
            $title = '';
            $course = '';
            $description = '';
            $fields = array('title', 'course');
            $validation = array();

            // Create a new Seminary
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Seminaries->seminaryTitleExists($title)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $course = $this->request->getPostParam('course');
                $description = $this->request->getPostParam('description');

                // Validate moodpic
                $moodpic = null;
                if(!empty($_FILES) && array_key_exists('moodpic', $_FILES) && $_FILES['moodpic']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $moodpic = $_FILES['moodpic'];

                    // Check error
                    if($moodpic['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'error', $moodpic['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $moodpic['mimetype'] = \hhu\z\Utils::getMimetype($moodpic['tmp_name'], $moodpic['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $moodpic['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'mimetype', $moodpic['mimetype']);
                    }
                    elseif($moodpic['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'size', $mediaMimetype['size']);
                    }
                }

                // Create new Seminary
                if($validation === true)
                {
                    $seminaryId = $this->Seminaries->createSeminary(
                        $this->Auth->getUserId(),
                        $title,
                        $course,
                        $description
                    );
                    $seminary = $this->Seminaries->getSeminaryById($seminaryId);

                    // Upload moodpic
                    if(!is_null($moodpic))
                    {
                        $mediaId = $this->Media->createMoodpic(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('seminarymoodpic-%s', $seminary['url']),
                            '',
                            $moodpic['mimetype'],
                            $moodpic['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Seminaries->setMoodpicForSeminary($seminary['id'], $mediaId);
                        }
                    }

                    // Redirect to Seminary overview
                    $this->redirect($this->linker->link('index', 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('New seminary');

            // Pass data to view
            $this->set('title', $title);
            $this->set('course', $course);
            $this->set('description', $description);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edit.
         *
         * Edit a seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a seminary
         */
        public function edit($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

            // Values
            $title = $seminary['title'];
            $course = $seminary['course'];
            $description = $seminary['description'];
            $fields = array('title', 'course');
            $validation = array();

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Seminaries->seminaryTitleExists($title, $seminary['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $course = $this->request->getPostParam('course');
                $description = $this->request->getPostParam('description');

                // Validate moodpic
                $moodpic = null;
                if(!empty($_FILES) && array_key_exists('moodpic', $_FILES) && $_FILES['moodpic']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $moodpic = $_FILES['moodpic'];

                    // Check error
                    if($moodpic['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'error', $moodpic['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $moodpic['mimetype'] = \hhu\z\Utils::getMimetype($moodpic['tmp_name'], $moodpic['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $moodpic['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'mimetype', $moodpic['mimetype']);
                    }
                    elseif($moodpic['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'moodpic', 'size', $mediaMimetype['size']);
                    }
                }

                // Edit Seminary
                if($validation === true)
                {
                    $this->Seminaries->editSeminary(
                        $seminary['id'],
                        $title,
                        $course,
                        $description
                    );
                    $seminary = $this->Seminaries->getSeminaryById($seminary['id']);

                    // Update moodpic
                    if(!is_null($moodpic))
                    {
                        $mediaId = $this->Media->createMoodpic(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('seminarymoodpic-%s', $seminary['url']),
                            '',
                            $moodpic['mimetype'],
                            $moodpic['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Seminaries->setMoodpicForSeminary($seminary['id'], $mediaId);
                        }
                    }

                    // Redirect to entry
                    $this->redirect($this->linker->link(array('seminary', $seminary['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('Edit seminary');

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('title', $title);
            $this->set('course', $course);
            $this->set('description', $description);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Copy a Seminary and selected content.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a seminary
         */
        public function copy($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Values
            $title = sprintf('%s (%s)', $seminary['title'], _('Copy'));
            $course = $seminary['course'];
            $description = $seminary['description'];
            $elements = array();
            $fields = array('title', 'course');
            $validation = array();
            $exception = null;

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Seminaries->seminaryTitleExists($title)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $course = $this->request->getPostParam('course');
                $description = $this->request->getPostParam('description');
                $elements = $this->request->getPostParam('elements');
                if(!is_array($elements)) {
                    $elements = array();
                }

                // Copy Seminary
                if($validation === true)
                {
                    try {
                        $seminaryId = $this->Seminaries->copySeminary(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            $title,
                            $course,
                            $description,
                            array_key_exists('seminaryfields', $elements),
                            array_key_exists('media', $elements),
                            array_key_exists('questgroupshierarchy', $elements),
                            array_key_exists('questgroups', $elements),
                            array_key_exists('quests', $elements),
                            array_key_exists('questtopics', $elements),
                            array_key_exists('charactertypes', $elements),
                            array_key_exists('xplevels', $elements),
                            array_key_exists('avatars', $elements),
                            array_key_exists('achievements', $elements),
                            array_key_exists('charactergroupsgroups', $elements),
                            array_key_exists('charactergroupsquests', $elements),
                            array_key_exists('map', $elements)
                        );
                        $seminary = $this->Seminaries->getSeminaryById($seminaryId);

                        // Redirect to overview
                        $this->redirect($this->linker->link('index', 1));
                    }
                    catch(\hhu\z\exceptions\QuesttypeModelNotValidException $e) {
                        $exception = $e;
                    }
                    catch(\hhu\z\exceptions\QuesttypeModelNotFoundException $e) {
                        $exception = $e;
                    }
                    catch(\hhu\z\exceptions\FileCopyException $e) {
                        $exception = $e;
                    }
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('title', $title);
            $this->set('course', $course);
            $this->set('description', $description);
            $this->set('elements', $elements);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
            $this->set('exception', $exception);
        }


        /**
         * Action: delete.
         *
         * Delete a seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a seminary
         */
        public function delete($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete seminary
                    $this->Seminaries->deleteSeminary($seminary['id']);

                    // Redirect to overview
                    $this->redirect($this->linker->link(null, 1));
                }

                // Redirect to entry
                $this->redirect($this->linker->link(array('seminary', $seminary['url']), 1));
            }


            // Set titile
            $this->addTitleLocalized('Delete seminary');

            // Show confirmation
            $this->set('seminary', $seminary);
        }


        /**
         * Action: calculatexps.
         *
         * (Re-) Calculate the amount of achievable XPs for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function calculatexps($seminaryUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // (Re-) Calculate XPs
            $this->Seminaries->calculateXPsForSeminary($seminary['id']);

            // Redirect to Questgroup
            $this->redirect($this->linker->link(array('seminary', $seminary['url']), 1));
        }




        /**
         * Get the first text of a Questgroup.
         *
         * @param   int $questgroupId   ID of a Questgroup
         * @return  string          First text of this Questgroup or NULL
         */
        private function getFirstQuestgroupText($questgroupId)
        {
            // Text of Questgroup itself
            $questgroupTexts = $this->Questgrouptexts->getQuestgroupTexts($questgroupId);
            if(!empty($questgroupTexts)) {
                return $questgroupTexts[0]['text'];
            }

            // Text of first Quest
            $quest = $this->Quests->getFirstQuestOfQuestgroup($questgroupId);
            if(!is_null($quest))
            {
                $questText = $this->Questtexts->getFirstQuestText($quest['id']);
                if(!is_null($questText)) {
                    return $questText;
                }
            }

            // Text of ChildQuestgroups
            $questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroupId);
            $childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
            foreach($childQuestgroupshierarchy as &$hierarchy)
            {
                // Get Questgroups
                $questgroups = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id'], $questgroupId);
                foreach($questgroups as &$group)
                {
                    $childQuestgroupText = $this->getFirstQuestgroupText($group['id']);
                    if(!is_null($childQuestgroupText)) {
                        return $childQuestgroupText;
                    }
                }
            }


            // No text found
            return null;
        }

    }

?>
