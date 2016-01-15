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
     * Controller of the CharactergroupsqueststationAgent to display Character
     * groups Quest stations.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactergroupsqueststationsController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'charactergroups', 'charactergroupsquests', 'charactergroupsqueststations', 'stationtypes', 'media');
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
            'station'   => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'index'     => array('admin', 'moderator', 'user'),
            'station'   => array('admin', 'moderator', 'user')
        );




        /**
         * Action: index.
         * 
         * Show all stations of a Character groups Quest.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         */
        public function index($seminaryUrl, $groupsgroupUrl, $questUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Character group
            $charactergroup = null;
            $character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
            $charactergroups = $this->Charactergroups->getGroupsForCharacter($character['id']);
            if(!empty($charactergroups)) {
                // TODO Multiple Character groups
                $charactergroup = $charactergroups[0];
            }

            // Get Stations
            $stations = null;
            if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) {
                $stations = $this->Charactergroupsqueststations->getStationsForQuest($quest['id']);
            }
            elseif(!is_null($charactergroup)) {
                $stations = $this->Charactergroupsqueststations->getStationsForQuestAndGroup($quest['id'], $charactergroup['id']);
            }


            // Pass data to view
            $this->set('stations', $stations);
            $this->set('hasgroup', !is_null($charactergroup));
        }


        /**
         * Action: station.
         *
         * Show a station of a Character groups Quest.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         * @param   string  $stationUrl     URL of station
         */
        public function station($seminaryUrl, $groupsgroupUrl, $questUrl, $stationUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Station
            $station = $this->Charactergroupsqueststations->getStationByUrl($quest['id'], $stationUrl);
            if(!is_null($station['stationpicture_id'])) {
                $station['picture'] = $this->Media->getSeminaryMediaById($station['stationpicture_id']);
            }

            // Get Character group
            $charactergroup = null;
            $character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
            $charactergroups = $this->Charactergroups->getGroupsForCharacter($character['id']);
            if(!empty($charactergroups)) {
                // TODO Multiple Character groups
                $charactergroup = $charactergroups[0];
            }

            // TODO Check permissions

            // Set status “entered”
            if(!is_null($charactergroup)) {
                $this->Charactergroupsqueststations->setStationEntered($station['id'], $charactergroup['id']);
            }

            // Get Character groups-groups
            $groups = null;
            if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0)
            {
                $groups = $this->Charactergroups->getGroupsForQueststation($station['id']);
                foreach($groups as &$group) {
                    $group['solved'] = $this->Charactergroupsqueststations->hasCharactergroupSolvedStation(
                        $station['id'],
                        $group['id']
                    );
                }
            }

            // Task
            $task = null;
            $stationtype = $this->Stationtypes->getStationtypeById($station['stationtype_id']);
            if(!is_null($stationtype['classname'])) {
                $task = $this->renderTask($stationtype['classname'], $seminary, $groupsgroup, $quest, $station, $charactergroup);
            }
            else
            {
                // Mark Station as solved
                if(!is_null($charactergroup)) {
                    $this->Charactergroupsqueststations->setStationSolved($station['id'], $charactergroup['id']);
                }
            }

            // Status
            $solved = false;
            $tried = false;
            if(!is_null($charactergroup)) {
                $solved = $this->Charactergroupsqueststations->hasCharactergroupSolvedStation($station['id'], $charactergroup['id']);
                if(!$solved) {
                    $tried = $this->Charactergroupsqueststations->hasCharactergroupTriedStation($station['id'], $charactergroup['id']);
                }
            }


            // Set title
            $this->addTitle($station['title']);
            $this->addTitle($quest['title']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
            $this->set('station', $station);
            $this->set('task', $task);
            $this->set('groups', $groups);
            $this->set('solved', $solved);
            $this->set('tried', $tried);
        }


        /**
         * Action: create.
         *
         * Create a new Character groups Quest Station for a Character
         * groups Quest.
         *
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         */
        public function create($seminaryUrl, $groupsgroupUrl, $questUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Quest types
            $stationtypes = $this->Stationtypes->getStationtypes();
            foreach($stationtypes as &$stationtype) {
                $stationtype['selected'] = false;
            }

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['icons'];

            // Values
            $title = '';
            $prolog = '';
            $task = '';
            $longitude = null;
            $latitude = null;
            $rightText = '';
            $wrongText = '';
            $fields = array('title');
            $validation = array();

            // Create a new Station
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Charactergroupsqueststations->stationTitleExists($quest['id'], $title)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $prolog = $this->request->getPostParam('prolog');
                $task = $this->request->getPostParam('task');
                $longitude = $this->request->getPostParam('longitude');
                $latitude = $this->request->getPostParam('latitude');
                $rightText = $this->request->getPostParam('rightText');
                $wrongText = $this->request->getPostParam('wrongText');

                // Validate Stationtype
                $stationtypeIndex = null;
                foreach($stationtypes as $index => &$stationtype)
                {
                    $stationtype['selected'] = ($stationtype['url'] == $this->request->getPostParam('stationtype'));
                    if($stationtype['selected']) {
                        $stationtypeIndex = $index;
                    }
                }
                if(is_null($stationtypeIndex)) {
                    throw new \nre\exceptions\ParamsNotValidException($stationtype);
                }

                // Validate icon
                $icon = null;
                if(!empty($_FILES) && array_key_exists('icon', $_FILES) && $_FILES['icon']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $icon = $_FILES['icon'];

                    // Check error
                    if($icon['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'error', $icon['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $icon['mimetype'] = \hhu\z\Utils::getMimetype($icon['tmp_name'], $icon['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $icon['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'mimetype', $icon['mimetype']);
                    }
                    elseif($icon['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'size', $mediaMimetype['size']);
                    }
                }

                // Create new Station
                if($validation === true)
                {
                    $stationId = $this->Charactergroupsqueststations->createStation(
                        $quest['id'],
                        $stationtypes[$stationtypeIndex]['id'],
                        $title,
                        $prolog,
                        $task,
                        $latitude,
                        $longitude,
                        $rightText,
                        $wrongText
                    );
                    $station = $this->Charactergroupsqueststations->getStationById($stationId);

                    // Upload icon
                    if(!is_null($icon))
                    {
                        $mediaId = $this->Media->createQuestMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('charactergroupsqueststation-%s', $station['url']),
                            '',
                            $icon['mimetype'],
                            $icon['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Charactergroupsqueststations->setPictureForStation($station['id'], $mediaId);
                        }
                    }

                    // Redirect to Station page
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


            // Set title
            $this->addTitleLocalized('Create Station');
            $this->addTitle($quest['title']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
            $this->set('title', $title);
            $this->set('prolog', $prolog);
            $this->set('task', $task);
            $this->set('longitude', $longitude);
            $this->set('latitude', $latitude);
            $this->set('righttext', $rightText);
            $this->set('wrongtext', $wrongText);
            $this->set('mimetypes', $mimetypes);
            $this->set('stationtypes', $stationtypes);
            $this->set('validation', $validation);
        }


        /**
         * Action: edit.
         *
         * Edit a Station of a Character groups Quest.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         * @param   string  $stationUrl     URL of station
         */
        public function edit($seminaryUrl, $groupsgroupUrl, $questUrl, $stationUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Station
            $station = $this->Charactergroupsqueststations->getStationByUrl($quest['id'], $stationUrl);

            // Get Quest types
            $stationtypes = $this->Stationtypes->getStationtypes();
            foreach($stationtypes as &$stationtype) {
                $stationtype['selected'] = ($stationtype['id'] == $station['stationtype_id']);
            }

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['icons'];

            // Values
            $title = $station['title'];
            $prolog = $station['prolog'];
            $task = $station['task'];
            $longitude = $station['longitude'];
            $latitude = $station['latitude'];
            $rightText = $station['righttext'];
            $wrongText = $station['wrongtext'];
            $fields = array('title');
            $validation = array();

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && (!is_null($this->request->getPostParam('edit')) || !is_null($this->request->getPostParam('edit-task'))))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Charactergroupsqueststations->stationTitleExists($quest['id'], $title, $station['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $prolog = $this->request->getPostParam('prolog');
                $task = $this->request->getPostParam('task');
                $longitude = $this->request->getPostParam('longitude');
                $latitude = $this->request->getPostParam('latitude');
                $rightText = $this->request->getPostParam('rightText');
                $wrongText = $this->request->getPostParam('wrongText');

                // Validate Stationtype
                $stationtypeIndex = null;
                foreach($stationtypes as $index => &$stationtype)
                {
                    $stationtype['selected'] = ($stationtype['url'] == $this->request->getPostParam('stationtype'));
                    if($stationtype['selected']) {
                        $stationtypeIndex = $index;
                    }
                }
                if(is_null($stationtypeIndex)) {
                    throw new \nre\exceptions\ParamsNotValidException($stationtype);
                }

                // Validate icon
                $icon = null;
                if(!empty($_FILES) && array_key_exists('icon', $_FILES) && $_FILES['icon']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $icon = $_FILES['icon'];

                    // Check error
                    if($icon['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'error', $icon['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $icon['mimetype'] = \hhu\z\Utils::getMimetype($icon['tmp_name'], $icon['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $icon['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'mimetype', $icon['mimetype']);
                    }
                    elseif($icon['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'icon', 'size', $mediaMimetype['size']);
                    }
                }

                // Edit Station
                if($validation === true)
                {
                    $this->Charactergroupsqueststations->editStation(
                        $station['id'],
                        $stationtypes[$stationtypeIndex]['id'],
                        $title,
                        $prolog,
                        $task,
                        $latitude,
                        $longitude,
                        $rightText,
                        $wrongText
                    );
                    $station = $this->Charactergroupsqueststations->getStationById($station['id']);

                    // Upload icon
                    if(!is_null($icon))
                    {
                        $mediaId = $this->Media->createQuestMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('charactergroupsqueststation-%s', $station['url']),
                            '',
                            $icon['mimetype'],
                            $icon['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Charactergroupsqueststations->setPictureForStation($station['id'], $mediaId);
                        }
                    }

                    // Redirect
                    if(!is_null($this->request->getPostParam('edit-task'))) {
                        // To task editing
                        $this->redirect(
                            $this->linker->link(
                                array(
                                    'edittask',
                                    $seminary['url'],
                                    $groupsgroup['url'],
                                    $quest['url'],
                                    $station['url']
                                ),
                                1
                            )
                        );
                    }
                    else {
                        // To Station page
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
            }


            // Set title
            $this->addTitleLocalized('Edit Station');
            $this->addTitle($station['title']);
            $this->addTitle($quest['title']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
            $this->set('title', $title);
            $this->set('prolog', $prolog);
            $this->set('task', $task);
            $this->set('longitude', $longitude);
            $this->set('latitude', $latitude);
            $this->set('righttext', $rightText);
            $this->set('wrongtext', $wrongText);
            $this->set('mimetypes', $mimetypes);
            $this->set('stationtypes', $stationtypes);
            $this->set('validation', $validation);
        }


        /**
         * TODO Action: edittask.
         *
         * Edit the task of a Character groups Quest Station.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         * @param   string  $stationUrl     URL of station
         */
        public function edittask($seminaryUrl, $groupsgroupUrl, $questUrl, $stationUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Station
            $station = $this->Charactergroupsqueststations->getStationByUrl($quest['id'], $stationUrl);

            // Render editing task
            $task = null;
            $stationtype = $this->Stationtypes->getStationtypeById($station['stationtype_id']);
            if(!is_null($stationtype['classname'])) {
                $task = $this->renderTaskEditing($stationtype['classname'], $seminary, $groupsgroup, $quest, $station);
            }


            // Set title
            $this->addTitleLocalized('Edit Station task');
            $this->addTitle($station['title']);
            $this->addTitle($quest['title']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
            $this->set('task', $task);
        }


        /**
         * Action: delete.
         *
         * Delete a Station of a Character groups Quest.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         * @param   string  $stationUrl     URL of station
         */
        public function delete($seminaryUrl, $groupsgroupUrl, $questUrl, $stationUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups-group Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Station
            $station = $this->Charactergroupsqueststations->getStationByUrl($quest['id'], $stationUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete seminary
                    $this->Charactergroupsqueststations->deleteStation(
                        $station['id']
                    );

                    // Redirect to overview
                    $this->redirect(
                        $this->linker->link(
                            array(
                                'charactergroupsquests',
                                'quest',
                                $seminary['url'],
                                $groupsgroup['url'],
                                $quest['url']
                            ),
                            0, true, null, true, 'stations'
                        )
                    );
                }

                // Redirect to entry
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


            // Set title
            $this->addTitleLocalized('Delete Station');
            $this->addTitle($station['title']);
            $this->addTitle($quest['title']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('quest', $quest);
            $this->set('station', $station);
        }




        /**
         * Render and handle the task of a Station.
         *
         * @param   string  $stationtypeClassname   Name of the class for the Stationtype of a Station
         * @param   array   $seminary               Seminary data
         * @param   array   $questgroup             Questgroup data
         * @param   array   $quest                  Quest data
         * @param   array   $station                Station data
         * @param   array   $charactergroup         Charactergroup data
         * @return  string                          Rendered output
         */
        private function renderTask($stationtypeClassname, $seminary, $groupsgroup, $quest, $station, $charactergroup)
        {
            $task = null;
            try {
                // Generate request and response
                $request = clone $this->request;
                $response = $this->createStationtypeResponse('quest', $seminary, $groupsgroup, $quest, $station, $charactergroup);

                // Load Stationtype Agent
                $stationtypeAgent = $this->loadStationtypeAgent($stationtypeClassname, $request, $response);

                // Solve Quest
                if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('submit')))
                {
                    // Get user answers
                    $answer = $this->request->getPostParam('answer');

                    // Save answers in database
                    try {
                        // save answer
                        if(!is_null($charactergroup)) {
                            if(!$this->Charactergroupsqueststations->hasCharactergroupSolvedStation($station['id'], $charactergroup['id'])) {
                                $stationtypeAgent->saveAnswer($seminary, $groupsgroup, $quest, $station, $charactergroup, $answer);
                            }
                        }

                        // Match answer with correct one
                        $status = $stationtypeAgent->matchAnswer(
                            $seminary,
                            $groupsgroup,
                            $quest,
                            $station,
                            $charactergroup,
                            $answer
                        );
                        if($status === true)
                        {
                            if(!is_null($charactergroup))
                            {
                                // Mark Station as solved
                                $this->Charactergroupsqueststations->setStationSolved($station['id'], $charactergroup['id']);
                            }

                            // Redirect
                            $this->redirect($this->linker->link(array(), 6, true, null, false, 'task'));
                        }
                        elseif($status === false)
                        {
                            if(!is_null($charactergroup)) {
                                // Mark Station as unsolved
                                $this->Charactergroupsqueststations->setStationUnsolved(
                                    $station['id'],
                                    $charactergroup['id']
                                );
                            }

                            // Redirect
                            $this->redirect($this->linker->link(array(), 6, true, null, false, 'task'));
                        }
                        else {
                            // Redirect
                            $this->redirect($this->linker->link(array(), 6, true, null, false, 'task'));
                        }
                    }
                    catch(\hhu\z\exceptions\SubmissionNotValidException $e) {
                        $response->addParam($e);
                    }
                }

                // Render Task
                $task = $this->runStationtypeAgent($stationtypeAgent, $request, $response);
            }
            catch(\nre\exceptions\ViewNotFoundException $e) {
                $task = $e->getMessage();
            }
            catch(\nre\exceptions\ActionNotFoundException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeModelNotValidException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeModelNotFoundException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeControllerNotValidException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeControllerNotFoundException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeAgentNotValidException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\stationtypeAgentNotFoundException $e) {
                $task = $e->getMessage();
            }


            // Return rendered output
            return $task;
        }


        /**
         * Render editing of a Station task.
         *
         * @param   string  $stationtypeClassname   Name of the class for the Stationtype of a Station
         * @param   array   $seminary               Seminary data
         * @param   array   $groupsgroup            Groupsgroup data
         * @param   array   $quest                  Quest data
         * @param   array   $station                Station data
         * @return  string                          Rendered output
         */
        private function renderTaskEditing($stationtypeClassname, $seminary, $groupsgroup, $quest, $station)
        {
            $task = null;
            try {
                // Generate request and response
                $request = clone $this->request;
                $response = $this->createStationtypeResponse('edittask', $seminary, $groupsgroup, $quest, $station);

                // Load Stationtype Agent
                $stationtypeAgent = $this->loadStationtypeAgent($stationtypeClassname, $request, $response);

                // Render Task
                $task = $this->runStationtypeAgent($stationtypeAgent, $request, $response);
            }
            catch(\nre\exceptions\ViewNotFoundException $e) {
                $task = $e->getMessage();
            }
            catch(\nre\exceptions\ActionNotFoundException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeModelNotValidException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeModelNotFoundException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeControllerNotValidException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeControllerNotFoundException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\StationtypeAgentNotValidException $e) {
                $task = $e->getMessage();
            }
            catch(\hhu\z\exceptions\stationtypeAgentNotFoundException $e) {
                $task = $e->getMessage();
            }


            // Return rendered output
            return $task;
        }


        /**
         * Create a response for the Stationtype rendering.
         *
         * @param   string  $action     Action to run
         * @param   mixed   $param      Additional parameters to add to the response
         * @return  \nre\core\Response  Generated response
         */
        private function createStationtypeResponse($action, $param1)
        {
            // Clone current response
            $response = clone $this->response;
            // Clear parameters
            $response->clearParams(1);

            // Add Action
            $response->addParams(
                null,
                $action
            );

            // Add additional parameters
            foreach(array_slice(func_get_args(), 1) as $param) {
                $response->addParam($param);
            }


            // Return response
            return $response;
        }


        /**
         * Load and construct the StationtypeAgent for a Stationtype.
         *
         * @param   string                  $stationtypeClassname   Name of the class for the Stationtype of a Station
         * @param   \nre\core\Request       $request                Request
         * @param   \nre\core\Response      $response               Response
         * @return  \hhu\z\agents\StationtypeAgent                    Stationtype Agent
         */
        private function loadStationtypeAgent($stationtypeClassname, $request, $response)
        {
            // Load Agent
            \hhu\z\agents\StationtypeAgent::load($stationtypeClassname);


            // Construct and return Agent
            return \hhu\z\agents\StationtypeAgent::factory($stationtypeClassname, $request, $response);
        }


        /**
         * Run and render the Agent for a StationtypeAgent and return ist output.
         *
         * @param   \nre\core\Agent     $stationtypeAgent   StationtypeAgent to run and render
         * @param   \nre\core\Request   $request            Request
         * @param   \nre\core\Response  $response           Response
         * @return  string                                  Rendered output
         */
        private function runStationtypeAgent($stationtypeAgent, $request, $response)
        {
            // Run Agent
            $stationtypeAgent->run($request, $response);


            // Render and return output
            return $stationtypeAgent->render();
        }

    }

?>
