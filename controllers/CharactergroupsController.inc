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
     * Controller of the CharactergroupsAgent to display Character groups.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactergroupsController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'charactergroups', 'charactergroupsquests', 'charactergroupsachievements', 'characters', 'avatars', 'media');
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
            'index'             => array('admin', 'moderator', 'user'),
            'groupsgroup'       => array('admin', 'moderator', 'user'),
            'creategroupsgroup' => array('admin', 'moderator', 'user'),
            'editgroupsgroup'   => array('admin', 'moderator', 'user'),
            'deletegroupsgroup' => array('admin', 'moderator', 'user'),
            'group'             => array('admin', 'moderator', 'user'),
            'managegroup'       => array('admin', 'moderator', 'user'),
            'creategroup'       => array('admin', 'moderator', 'user'),
            'editgroup'         => array('admin', 'moderator', 'user'),
            'deletegroup'       => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'index'             => array('admin', 'moderator', 'user'),
            'groupsgroup'       => array('admin', 'moderator', 'user'),
            'creategroupsgroup' => array('admin', 'moderator'),
            'editgroupsgroup'   => array('admin', 'moderator'),
            'deletegroupsgroup' => array('admin', 'moderator'),
            'group'             => array('admin', 'moderator', 'user'),
            'managegroup'       => array('admin', 'moderator'),
            'creategroup'       => array('admin', 'moderator'),
            'editgroup'         => array('admin', 'moderator', 'user'),
            'deletegroup'       => array('admin', 'moderator')
        );




        /**
         * Action: index.
         *
         * Show Character groups-groups for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         */
        public function index($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-groups
            $groupsgroups = $this->Charactergroups->getGroupsroupsForSeminary($seminary['id']);


            // Set titile
            $this->addTitleLocalized('Character Groups');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroups', $groupsgroups);
        }


        /**
         * Action: groupsgroups.
         *
         * Show Character groups for a Character groups-group of a
         * Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         */
        public function groupsgroup($seminaryUrl, $groupsgroupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups
            $groups = $this->Charactergroups->getGroupsForGroupsgroup($groupsgroup['id'], 'xps');

            // Get Character groups-group Quests
            $quests = $this->Charactergroupsquests->getQuestsForCharactergroupsgroup($groupsgroup['id']);

            // Get Achievements
            $achievements = array();
            if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) {
                $achievements = $this->Charactergroupsachievements->getAchievementsForCharactergroupsgroup(
                    $groupsgroup['id']
                );
            }


            // Set titile
            $this->addTitle($groupsgroup['name']);
            $this->addTitleLocalized('Character Groups');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('groups', $groups);
            $this->set('quests', $quests);
            $this->set('achievements', $achievements);
        }


        /**
         * Action: creategroupsgroups.
         *
         * Create a new Character groups-group for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         */
        public function creategroupsgroup($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Values
            $charactergroupsgroupname = '';
            $preferred = false;
            $fields = array('charactergroupsgroupname');
            $validation = array();

            // Create a new Character groups-group
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $charactergroupsgroupname = $this->request->getPostParam('charactergroupsgroupname');
                if($this->Charactergroups->characterGroupsgroupNameExists($charactergroupsgroupname)) {
                    $validation = $this->Validation->addValidationResult($validation, 'charactergroupsgroupname', 'exist', true);
                }
                $preferred = !is_null($this->request->getPostParam('preferred'));

                // Create groups-group
                if($validation === true)
                {
                    $groupsgroupId = $this->Charactergroups->createGroupsgroup(
                        $this->Auth->getUserId(),
                        $seminary['id'],
                        $charactergroupsgroupname,
                        $preferred
                    );

                    // Redirect to groups-group page
                    $groupsgroup = $this->Charactergroups->getGroupsgroupById($groupsgroupId);
                    $this->redirect($this->linker->link(array('groupsgroup', $seminary['url'], $groupsgroup['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('New Character groups-group');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('charactergroupsgroupname', $charactergroupsgroupname);
            $this->set('preferred', $preferred);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: editgroupsgroups.
         *
         * Edit a Character groups-group of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         */
        public function editgroupsgroup($seminaryUrl, $groupsgroupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Values
            $charactergroupsgroupname = $groupsgroup['name'];
            $preferred = $groupsgroup['preferred'];
            $fields = array('charactergroupsgroupname');
            $validation = array();

            // Edit Character groups-group
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $charactergroupsgroupname = $this->request->getPostParam('charactergroupsgroupname');
                if($this->Charactergroups->characterGroupsgroupNameExists($charactergroupsgroupname, $groupsgroup['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'charactergroupsgroupname', 'exist', true);
                }
                $preferred = !is_null($this->request->getPostParam('preferred'));

                // Edit groups-group
                if($validation === true)
                {
                    $this->Charactergroups->editGroupsgroup(
                        $groupsgroup['id'],
                        $charactergroupsgroupname,
                        $preferred
                    );

                    // Redirect to user page
                    $groupsgroup = $this->Charactergroups->getGroupsgroupById($groupsgroup['id']);
                    $this->redirect($this->linker->link(array('groupsgroup', $seminary['url'], $groupsgroup['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('Edit Character groups-group');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('charactergroupsgroupname', $charactergroupsgroupname);
            $this->set('preferred', $preferred);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: deletegroupsgroups.
         *
         * Delete a Character groups-group of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         */
        public function deletegroupsgroup($seminaryUrl, $groupsgroupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete seminary
                    $this->Charactergroups->deleteGroupsgroup($groupsgroup['id']);

                    // Redirect to overview
                    $this->redirect($this->linker->link(array('index', $seminary['url']), 1));
                }

                // Redirect to entry
                $this->redirect($this->linker->link(array('groupsgroup', $seminary['url'], $groupsgroup['url']), 1));
            }


            // Set titile
            $this->addTitleLocalized('Delete Character groups-group');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
        }


        /**
         * Action: group.
         *
         * Show a Character group for a Character groups-group of a
         * Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $groupUrl       URL-Title of a Character group
         */
        public function group($seminaryUrl, $groupsgroupUrl, $groupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character group
            $group = $this->Charactergroups->getGroupByUrl($groupsgroup['id'], $groupUrl);
            $group['characters'] = $this->Characters->getCharactersForGroup($group['id']);
            $group['rank'] = $this->Charactergroups->getXPRank($groupsgroup['id'], $group['xps']);

            // Get Character avatars
            foreach($group['characters'] as &$character)
            {
                $avatar = $this->Avatars->getAvatarById($character['avatar_id']);
                if(!is_null($avatar['small_avatarpicture_id'])) {
                    $character['small_avatar'] = $this->Media->getSeminaryMediaById($avatar['small_avatarpicture_id']);
                }
            }

            // Get Character groups Quests
            $quests = $this->Charactergroupsquests->getQuestsForGroup($group['id']);

            // Get Achievements
            $achievements = $this->Charactergroupsachievements->getAchievedAchievementsForGroup(
                $group['id']
            );


            // Set titile
            $this->addTitle($group['name']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('group', $group);
            $this->set('quests', $quests);
            $this->set('achievements', $achievements);
        }


        /**
         * Action: managegroup.
         *
         * Manage a Character group for a Character groups-group of a
         * Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $groupUrl       URL-Title of a Character group
         */
        public function managegroup($seminaryUrl, $groupsgroupUrl, $groupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character group
            $group = $this->Charactergroups->getGroupByUrl($groupsgroup['id'], $groupUrl);

            // Manage
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('actions')) && count($this->request->getPostParam('actions')) > 0) // && !is_null($this->request->getPostParam('characters')) && count($this->request->getPostParam('characters')) > 0)
            {
                $actions = $this->request->getPostParam('actions');
                $action = array_keys($actions)[0];
                $selectedCharacters = $this->request->getPostParam('characters');

                switch($action)
                {
                    // Add Characters to group
                    case 'addcharacters':
                        foreach($selectedCharacters as &$characterId)
                        {
                            $this->Charactergroups->addCharacterToCharactergroup($group['id'], $characterId);
                            // Check Achievements
                            $this->Achievement->checkAchievements($seminary['id'], $characterId, array('character', 'achievement'));
                        }
                    break;
                    // Remove Characters from group
                    case 'removecharacters':
                        foreach($selectedCharacters as &$characterId) {
                            $this->Charactergroups->removeCharacterFromCharactergroup($group['id'], $characterId);
                        }
                    break;
                }
            }

            // Get additional data for group
            $group['characters'] = $this->Characters->getCharactersForGroup($group['id']);
            $group['rank'] = $this->Charactergroups->getXPRank($groupsgroup['id'], $group['xps']);

            // Get Character avatars
            foreach($group['characters'] as &$character)
            {
                $avatar = $this->Avatars->getAvatarById($character['avatar_id']);
                if(!is_null($avatar['small_avatarpicture_id'])) {
                    $character['small_avatar'] = $this->Media->getSeminaryMediaById($avatar['small_avatarpicture_id']);
                }
            }

            // Get Character groups Quests
            $quests = $this->Charactergroupsquests->getQuestsForGroup($group['id']);

            // Get all Characters of Seminary
            $groupCharacterIds = array_map(function($c) { return $c['id']; }, $group['characters']);
            $seminaryCharacters = $this->Characters->getCharactersForSeminary($seminary['id'], true);
            $characters = array();
            foreach($seminaryCharacters as &$character) {
                if(!in_array($character['id'], $groupCharacterIds)) {
                    $characters[] = $character;
                }
            }


            // Set titile
            $this->addTitle($group['name']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('group', $group);
            $this->set('quests', $quests);
            $this->set('characters', $characters);
        }


        /**
         * Action: creategroup.
         *
         * Create a Character group for a Character groups-group of a
         * Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         */
        public function creategroup($seminaryUrl, $groupsgroupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['icons'];

            // Values
            $charactergroupname = '';
            $motto = '';
            $fields = array('charactergroupname', 'motto');
            $validation = array();

            // Create a new Character groups-group
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $charactergroupname = $this->request->getPostParam('charactergroupname');
                if($this->Charactergroups->characterGroupNameExists($groupsgroup['id'], $charactergroupname)) {
                    $validation = $this->Validation->addValidationResult($validation, 'charactergroupname', 'exist', true);
                }
                $motto = $this->request->getPostParam('motto');

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

                // Create group
                if($validation === true)
                {
                    $groupId = $this->Charactergroups->createGroup(
                        $this->Auth->getUserId(),
                        $groupsgroup['id'],
                        $charactergroupname,
                        $motto
                    );
                    $group = $this->Charactergroups->getGroupById($groupId);

                    // Upload icon
                    if(!is_null($icon))
                    {
                        $mediaId = $this->Media->createCharactergroupMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('charactergroup-%s', $group['url']),
                            '',
                            $icon['mimetype'],
                            $icon['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Charactergroups->setMediaForGroup($group['id'], $mediaId);
                        }
                    }

                    // Redirect to group page
                    $this->redirect($this->linker->link(array('group', $seminary['url'], $groupsgroup['url'], $group['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set title
            $this->addTitleLocalized('New %s Character group', $groupsgroup['name']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('charactergroupname', $charactergroupname);
            $this->set('motto', $motto);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: editgroup.
         *
         * Edit a Character group for a Character groups-group of a
         * Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $groupUrl       URL-Title of a Character group
         */
        public function editgroup($seminaryUrl, $groupsgroupUrl, $groupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character group
            $group = $this->Charactergroups->getGroupByUrl($groupsgroup['id'], $groupUrl);
            $group['characters'] = $this->Characters->getCharactersForGroup($group['id']);

            // Check permission
            if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) == 0 && !in_array(\hhu\z\controllers\SeminaryController::$character['id'], array_map(function($c) { return $c['id']; }, $group['characters']))) {
                throw new \nre\exceptions\AccessDeniedException();
            }

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['icons'];

            // Values
            $charactergroupname = $group['name'];
            $motto = $group['motto'];
            $fields = array('charactergroupname', 'motto');
            $validation = array();

            // Edit Character group
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $charactergroupname = (count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) ? $this->request->getPostParam('charactergroupname') : $group['name'];
                if($this->Charactergroups->characterGroupNameExists($groupsgroup['id'], $charactergroupname, $group['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'charactergroupname', 'exist', true);
                }
                $motto = $this->request->getPostParam('motto');

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

                // Edit group
                if($validation === true)
                {
                    $this->Charactergroups->editGroup(
                        $group['id'],
                        $charactergroupname,
                        $motto
                    );
                    $group = $this->Charactergroups->getGroupById($group['id']);

                    // Upload icon
                    if(!is_null($icon))
                    {
                        $mediaId = $this->Media->createCharactergroupMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('charactergroup-%s', $group['url']),
                            '',
                            $icon['mimetype'],
                            $icon['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Charactergroups->setMediaForGroup($group['id'], $mediaId);
                        }
                    }

                    // Redirect to user page
                    $this->redirect($this->linker->link(array('group', $seminary['url'], $groupsgroup['url'], $group['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set title
            $this->addTitleLocalized('Edit %s Character group', $groupsgroup['name']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('group', $group);
            $this->set('charactergroupname', $charactergroupname);
            $this->set('motto', $motto);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: deletegroup.
         *
         * Delete a Character group for a Character groups-group of a
         * Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of a Seminary
         * @param   string  $groupsgroupUrl     URL-Title of a Character groups-group
         * @param   string  $groupUrl       URL-Title of a Character group
         */
        public function deletegroup($seminaryUrl, $groupsgroupUrl, $groupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character group
            $group = $this->Charactergroups->getGroupByUrl($groupsgroup['id'], $groupUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete seminary
                    $this->Charactergroups->deleteGroup($group['id']);

                    // Redirect to overview
                    $this->redirect($this->linker->link(array('groupsgroup', $seminary['url'], $groupsgroup['url']), 1));
                }

                // Redirect to entry
                $this->redirect($this->linker->link(array('group', $seminary['url'], $groupsgroup['url'], $group['url']), 1));
            }


            // Set title
            $this->addTitleLocalized('Delete %s Character group', $groupsgroup['name']);
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('group', $group);
        }

    }

?>
