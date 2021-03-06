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
     * Controller of the Agent to list registered users and their data.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactersController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'characters', 'users', 'charactergroups', 'charactertypes', 'charactertitles', 'seminarycharacterfields', 'avatars', 'media', 'quests', 'questgroups', 'questtopics', 'xplevels');
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
            'character' => array('admin', 'moderator', 'user'),
            'register'  => array('admin', 'moderator', 'user'),
            'manage'    => array('admin', 'moderator', 'user'),
            'edit'      => array('admin', 'moderator', 'user'),
            'delete'    => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'index'     => array('admin', 'moderator'),
            'character' => array('admin', 'moderator', 'user'),
            'manage'    => array('admin', 'moderator'),
            'edit'      => array('admin', 'moderator', 'user'),
            'delete'    => array('admin', 'moderator')
        );




        /**
         * Action: index.
         *
         * List registered Characters for a Seminary
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $all            Whether to list all Characters at once or not (optional)
         */
        public function index($seminaryUrl, $all=null)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Seminarycharacterfields
            $characterfields = $this->Seminarycharacterfields->getFieldsForSeminary($seminary['id']);

            // Set sort order and page
            $sortorder = 'name';
            $charactername = null;
            $page = 1;
            if($this->request->getRequestMethod() == 'GET')
            {
                $sortorder = $this->request->getGetParam('sortorder');
                $sortorder = !empty($sortorder) ? $sortorder : 'name';
                $charactername = (!is_null($this->request->getGetParam('charactername'))) ? $this->request->getGetParam('charactername') : $charactername;
                $page = $this->request->getGetParam('page');
                $page = !empty($page) ? intval($page) : 1;
            }

            // Get registered Characters
            $limit = ($all != 'all') ? \nre\configs\AppConfig::$misc['lists_limit'] : null;
            $offset = ($all != 'all') ? max((intval($page) - 1), 0) * $limit : 0;
            $charactersCount = $this->Characters->getCharactersForSeminaryCount($seminary['id'], $charactername);
            $characters = $this->Characters->getCharactersForSeminarySorted($seminary['id'], $sortorder, $charactername, $limit, $offset);
            foreach($characters as &$character)
            {
                $character['user'] = $this->Users->getUserById($character['user_id']);
                $character['characterroles'] = array_map(function($r) { return $r['name']; }, $this->Characterroles->getCharacterrolesForCharacterById($character['id']));
                $character['characterfields'] = array();
                foreach($this->Seminarycharacterfields->getFieldsForCharacter($character['id']) as $value) {
                    $character['characterfields'][$value['url']] = $value;
                }
                try {
                    $character['xplevel'] = $this->Xplevels->getXPLevelById($character['xplevel_id']);
                }
                catch(\nre\exceptions\IdNotFoundException $e) {
                    // No XP-level
                }
                try {
                    $character['avatar'] = $this->Avatars->getAvatarByTypeAndLevel($seminary['id'], $character['charactertype_url'], $character['xplevel']['level']);
                }
                catch(\nre\exceptions\IdNotFoundException $e) {
                    // No Avatar available
                }
            }


            // Set titile
            $this->addTitleLocalized('Characters');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('characters', $characters);
            $this->set('charactersCount', $charactersCount);
            $this->set('characterfields', $characterfields);
            $this->set('sortorder', $sortorder);
            $this->set('charactername', $charactername);
            $this->set('all', $all);
            $this->set('page', $page);
            $this->set('limit', $limit);
        }


        /**
         * Action: character.
         *
         * Show a Charater and its details.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $characterUrl   URL-name of a Charater
         */
        public function character($seminaryUrl, $characterUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
            $seminary['achievable_xps'] = $this->Seminaries->getTotalXPs($seminary['id']);

            // Get Character
            $character = $this->Characters->getCharacterByUrl($seminary['id'], $characterUrl);
            try {
                $character['xplevel'] = $this->Xplevels->getXPLevelById($character['xplevel_id']);
            }
            catch(\nre\exceptions\IdNotFoundException $e) {
                // No XP-level
            }
            $character['rank'] = $this->Characters->getXPRank($seminary['id'], $character['xps']);
            if(!is_null($character['avatar_id'])) {
                $character['avatar'] = $this->Avatars->getAvatarById($character['avatar_id']);
            }
            if(!is_null($character['charactertitle_id']) && !is_null($character['gender']))
            {
                $title = $this->Charactertitles->getTitleById($character['charactertitle_id']);
                $character['title'] = $title[($character['gender']) ? 'title_male' : 'title_female'];
            }

            // Get User
            $user = $this->Users->getUserById($character['user_id']);

            // Get Character groups
            $groups = $this->Charactergroups->getGroupsForCharacter($character['id']);
            foreach($groups as &$group) {
                $group['groupsgroup'] = $this->Charactergroups->getGroupsgroupById($group['charactergroupsgroup_id']);
            }

            // Get Achievements
            $achievements = $this->Achievements->getAchievedAchievementsForCharacter($character['id']);

            // Get Achievements with deadline (milestones)
            $milestones = $this->Achievements->getDeadlineAchievements($seminary['id']);
            foreach($milestones as &$milestone) {
                $milestone['achieved'] = $this->Achievements->hasCharacterAchievedAchievement($milestone['id'], $character['id']);
            }

            // Get ranking
            $ranking = array(
                'superior' => $this->Characters->getSuperiorCharacters($seminary['id'], $character['xps'], \nre\configs\AppConfig::$misc['ranking_range']),
                'inferior' => $this->Characters->getInferiorCharacters($seminary['id'], $character['id'], $character['xps'], \nre\configs\AppConfig::$misc['ranking_range'])
            );
            foreach($ranking['superior'] as &$c)
            {
                if(!is_null($c['charactertitle_id']) && !is_null($c['gender']))
                {
                    $title = $this->Charactertitles->getTitleById($c['charactertitle_id']);
                    $c['title'] = $title[($c['gender']) ? 'title_male' : 'title_female'];
                }
            }
            foreach($ranking['inferior'] as &$c)
            {
                if(!is_null($c['charactertitle_id']) && !is_null($c['gender']))
                {
                    $title = $this->Charactertitles->getTitleById($c['charactertitle_id']);
                    $c['title'] = $title[($c['gender']) ? 'title_male' : 'title_female'];
                }
            }

            // Get Quest topics
            $questtopics = $this->Questtopics->getQuesttopicsForSeminary($seminary['id']);
            foreach($questtopics as &$questtopic)
            {
                $questtopic['questcount'] = $this->Questtopics->getQuestCountForQuesttopic($questtopic['id']);
                $questtopic['characterQuestcount'] = $this->Questtopics->getCharacterQuestCountForQuesttopic($questtopic['id'], $character['id']);
            }

            // Get “last” Quest
            $lastQuest = null;
            if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0)
            {
                $lastQuest = $this->Quests->getLastQuestForCharacter($character['id']);
                if(!is_null($lastQuest)) {
                    $lastQuest['questgroup'] = $this->Questgroups->getQuestgroupById($lastQuest['questgroup_id']);
                }
            }


            // Set titile
            $this->addTitle($character['name']);
            $this->addTitleLocalized('Characters');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('character', $character);
            $this->set('user', $user);
            $this->set('groups', $groups);
            $this->set('achievements', $achievements);
            $this->set('milestones', $milestones);
            $this->set('ranking', $ranking);
            $this->set('questtopics', $questtopics);
            $this->set('lastQuest', $lastQuest);
        }


        /**
         * Acton: register.
         *
         * Register a new character for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @throws  \nre\exceptions\ParamsNotValidException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function register($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Check for already existing Character
            try {
                $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
                throw new \nre\exceptions\AccessDeniedException();
            }
            catch(\nre\exceptions\IdNotFoundException $e) {
                // This should be the case
            }


            // Character types
            $types = $this->Charactertypes->getCharacterTypesForSeminary($seminary['id']);

            // Character fields
            $fields = $this->Seminarycharacterfields->getFieldsForSeminary($seminary['id']);

            // Register Character
            $charactername = '';
            $gender = null;
            $validation = true;
            $fieldsValidation = true;
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Validate Character properties
                $validation = $this->Validation->validateParams($this->request->getPostParams(), array('charactername'));
                $charactername = $this->request->getPostParam('charactername');
                if($this->Characters->characterNameExists($charactername)) {
                    $validation = $this->Validation->addValidationResult($validation, 'charactername', 'exist', true);
                }
                $gender = $this->request->getPostParam('gender');

                // Validate type
                $typeIndex = null;
                foreach($types as $index => &$type)
                {
                    $type['selected'] = ($type['url'] == $this->request->getPostParam('type'));
                    if($type['selected']) {
                        $typeIndex = $index;
                    }
                }
                if(is_null($typeIndex)) {
                    $validation = $this->Validation->addValidationResult($validation, 'type', 'exist', false);
                }

                // Validate gender
                if(is_null($gender) || ($gender !== "0" && $gender !== "1")) {
                    $validation = $this->Validation->addValidationResult($validation, 'gender', 'correct', false);
                }

                // Validate fields
                $fieldsValues = $this->request->getPostParam('fields');
                foreach($fields as &$field)
                {
                    if(!array_key_exists($field['url'], $fieldsValues)) {
                        throw new \nre\exceptions\ParamsNotValidException($index);
                    }
                    $field['uservalue'] = $fieldsValues[$field['url']];
                    if($field['required'])
                    {
                        $fieldValidation = $this->Validation->validate($fieldsValues[$field['url']], array('regex'=>$field['regex']));
                        if($fieldValidation !== true)
                        {
                            if(!is_array($fieldsValidation)) {
                                $fieldsValidation = array();
                            }
                            $fieldsValidation[$field['url']] = $fieldValidation;
                        }
                    }
                }

                // Register
                if($validation === true && $fieldsValidation === true)
                {
                    $characterId = $this->Characters->createCharacter(
                        $this->Auth->getUserId(),
                        $types[$typeIndex]['id'],
                        $charactername,
                        intval($gender)
                    );
                    $character = $this->Characters->getCharacterById(
                        $characterId
                    );

                    // Add Seminary fields
                    foreach($fields as &$field) {
                        if(!empty($fieldsValues[$field['url']])) {
                            $this->Seminarycharacterfields->setSeminaryFieldOfCharacter($field['id'], $characterId, $fieldsValues[$field['url']]);
                        }
                    }

                    // Set roles for owners and admins
                    if(in_array('admin', \hhu\z\controllers\IntermediateController::$user['roles']) || $seminary['created_user_id'] == \hhu\z\controllers\IntermediateController::$user['id']) {
                        $this->Characterroles->addCharacterroleToCharacter($characterId, 'admin');
                    }

                    // Send mail
                    $this->sendRegistrationMail($character);

                    // Redirect
                    $this->redirect($this->linker->link(array('seminaries')));
                }
            }

            // Get XP-levels
            $xplevels = $this->Xplevels->getXPLevelsForSeminary($seminary['id']);

            // Get Avatars
            if(count($xplevels) > 0)
            {
                foreach($types as &$type)
                {
                    try {
                        $type['avatar'] = $this->Avatars->getAvatarByTypeAndLevel($seminary['id'], $type['url'], $xplevels[0]['level']);
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                        // No Avatar available
                    }
                }
            }


            // Set titile
            $this->addTitleLocalized('Create Character');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('types', $types);
            $this->set('fields', $fields);
            $this->set('charactername', $charactername);
            $this->set('validation', $validation);
            $this->set('fieldsValidation', $fieldsValidation);
            $this->set('xplevels', $xplevels);
        }


        /**
         * Action: manage.
         *
         * Manage Characters.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function manage($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Set sort order and page
            $selectedCharacters = array();
            $sortorder = 'name';
            if($this->request->getRequestMethod() == 'POST')
            {
                // Set sortorder
                $sortorder = $this->request->getPostParam('sortorder');
                $sortorder = !empty($sortorder) ? $sortorder : 'name';

                // Do action
                $selectedCharacters = $this->request->getPostParam('characters');
                if(!is_array($selectedCharacters)) {
                    $selectedCharacters = array();
                }
                if(!is_null($this->request->getPostParam('actions')) && count($this->request->getPostParam('actions')) > 0 && !is_null($this->request->getPostParam('characters')) && count($this->request->getPostParam('characters')) > 0)
                {
                    $actions = $this->request->getPostParam('actions');
                    $action = array_keys($actions)[0];

                    switch($action)
                    {
                        // Add/remove role to/from Characters
                        case 'addrole':
                        case 'removerole':
                            // Determine role and check permissions
                            $role = null;
                            switch($actions[$action])
                            {
                                case _('Admin'):
                                    if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) <= 0 && !in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) {
                                        throw new \nre\exceptions\AccessDeniedException();
                                    }
                                    $role = 'admin';
                                break;
                                case _('Moderator'):
                                    if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) <= 0 && !in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) {
                                        throw new \nre\exceptions\AccessDeniedException();
                                    }
                                    $role = 'moderator';
                                break;
                                case _('User'):
                                    if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) <= 0 && count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) <= 0) {
                                        throw new \nre\exceptions\AccessDeniedException();
                                    }
                                    $role = 'user';
                                break;
                            }

                            // Add role
                            if($action == 'addrole') {
                                foreach($selectedCharacters as &$characterId) {
                                    $this->Characterroles->addCharacterroleToCharacter($characterId, $role);
                                }
                            }
                            // Remove role
                            else {
                                foreach($selectedCharacters as &$characterId) {
                                    $this->Characterroles->removeCharacterroleFromCharacter($characterId, $role);
                                }
                            }
                        break;
                    }
                }
            }

            // Get Seminarycharacterfields
            $characterfields = $this->Seminarycharacterfields->getFieldsForSeminary($seminary['id']);

            // Get registered Characters
            $characters = $this->Characters->getCharactersForSeminarySorted($seminary['id'], $sortorder);
            foreach($characters as &$character)
            {
                try {
                    $character['xplevel'] = $this->Xplevels->getXPLevelById($character['xplevel_id']);
                }
                catch(\nre\exceptions\IdNotFoundException $e) {
                    // No XP-level
                }
                if(!is_null($character['avatar_id'])) {
                    $character['avatar'] = $this->Avatars->getAvatarById($character['avatar_id']);
                }
                $character['user'] = $this->Users->getUserById($character['user_id']);
                $character['characterroles'] = array_map(function($r) { return $r['name']; }, $this->Characterroles->getCharacterrolesForCharacterById($character['id']));
                $character['characterfields'] = array();
                foreach($this->Seminarycharacterfields->getFieldsForCharacter($character['id']) as $value) {
                    $character['characterfields'][$value['url']] = $value;
                }
            }


            // Set titile
            $this->addTitleLocalized('Manage Characters');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('characters', $characters);
            $this->set('characterfields', $characterfields);
            $this->set('selectedCharacters', $selectedCharacters);
            $this->set('sortorder', $sortorder);
        }


        /**
         * Acton: edit.
         *
         * Edit a new character for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @throws  \nre\exceptions\ParamsNotValidException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $characterUrl   URL-name of a Charater
         */
        public function edit($seminaryUrl, $characterUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character
            $character = $this->Characters->getCharacterByUrl($seminary['id'], $characterUrl);

            // Check permissions
            if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) == 0 && $character['id'] != \hhu\z\controllers\SeminaryController::$character['id']) {
                throw new \nre\exceptions\AccessDeniedException();
            }

            // Get User
            $user = $this->Users->getUserById($character['user_id']);

            // Character types
            $types = $this->Charactertypes->getCharacterTypesForSeminary($seminary['id']);
            foreach($types as &$type) {
                $type['selected'] = ($type['url'] == $character['charactertype_url']);
            }

            // Character titles
            $titles = $this->Charactertitles->getTitlesForCharacter(
                $character['id']
            );

            // Character fields
            $fields = $this->Seminarycharacterfields->getFieldsForSeminary($seminary['id']);
            foreach($fields as &$field)
            {
                $userValue = $this->Seminarycharacterfields->getSeminaryFieldOfCharacter($field['id'], $character['id']);
                if(!empty($userValue)) {
                    $field['uservalue'] = $userValue['value'];
                }
            }

            // Values
            $charactername = $character['name'];
            $gender = $character['gender'];
            $charactertitle = null;
            if(!is_null($character['charactertitle_id'])) {
                foreach($titles as &$title) {
                    if($title['id'] == $character['charactertitle_id']) {
                        $charactertitle = $title;
                    }
                }
            }
            $validation = array();
            $fieldsValidation = true;

            // Edit Character
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Validate Character properties
                $validation = $this->Validation->validateParams($this->request->getPostParams(), array('charactername'));
                $charactername = (count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) ? $this->request->getPostParam('charactername') : $character['name'];
                if($this->Characters->characterNameExists($charactername, $character['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'charactername', 'exist', true);
                }
                $gender = $this->request->getPostParam('gender');
                $charactertitleId = $this->request->getPostParam('title');

                // Validate type
                $typeIndex = null;
                foreach($types as $index => &$type)
                {
                    $type['selected'] = (count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) ? ($type['url'] == $this->request->getPostParam('type')) : ($type['url'] == $character['charactertype_url']);
                    if($type['selected']) {
                        $typeIndex = $index;
                    }
                }
                if(is_null($typeIndex)) {
                    $validation = $this->Validation->addValidationResult($validation, 'type', 'exist', false);
                }

                // Validate gender
                if(is_null($gender) || ($gender !== "0" && $gender !== "1")) {
                    $validation = $this->Validation->addValidationResult($validation, 'gender', 'correct', false);
                }

                // Validate title
                $charactertitle = null;
                if(!is_null($charactertitleId))
                {
                    $charatcretitle = null;
                    $charactertitleId = intval($charactertitleId);
                    foreach($titles as &$title) {
                        if($title['id'] === $charactertitleId) {
                            $charactertitle = $title;
                            break;
                        }
                    }
                }

                // Validate fields
                $fieldsValues = $this->request->getPostParam('fields');
                foreach($fields as &$field)
                {
                    if(!array_key_exists($field['url'], $fieldsValues)) {
                        throw new \nre\exceptions\ParamsNotValidException($index);
                    }
                    $field['uservalue'] = $fieldsValues[$field['url']];
                    if($field['required'])
                    {
                        $fieldValidation = $this->Validation->validate($fieldsValues[$field['url']], array('regex'=>$field['regex']));
                        if($fieldValidation !== true)
                        {
                            if(!is_array($fieldsValidation)) {
                                $fieldsValidation = array();
                            }
                            $fieldsValidation[$field['url']] = $fieldValidation;
                        }
                    }
                }

                // Edit
                if($validation === true && $fieldsValidation === true)
                {
                    $this->Characters->editCharacter(
                        $character['id'],
                        $types[$typeIndex]['id'],
                        $charactername,
                        intval($gender),
                        (!is_null($charactertitle)) ? $charactertitle['id'] : null
                    );

                    // Set Seminary fields
                    foreach($fields as &$field) {
                        if(!empty($fieldsValues[$field['url']])) {
                            $this->Seminarycharacterfields->setSeminaryFieldOfCharacter($field['id'], $character['id'], $fieldsValues[$field['url']]);
                        }
                    }

                    // Redirect
                    $character = $this->Characters->getCharacterById($character['id']);
                    $this->redirect($this->linker->link(array('character', $seminary['url'], $character['url']), 1));
                }
            }

            // Get XP-levels
            $xplevels = $this->Xplevels->getXPLevelsForSeminary($seminary['id']);

            // Get validation settings
            $validationSettings = array();
            $validationSettings['charactername'] = \nre\configs\AppConfig::$validation['charactername'];


            // Set titile
            $this->addTitleLocalized('Edit Character');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('types', $types);
            $this->set('titles', $titles);
            $this->set('fields', $fields);
            $this->set('charactername', $charactername);
            $this->set('gender', $gender);
            $this->set('charactertitle', $charactertitle);
            $this->set('validation', $validation);
            $this->set('fieldsValidation', $fieldsValidation);
            $this->set('validationSettings', $validationSettings);
            $this->set('xplevels', $xplevels);
        }


        /**
         * Action: delete.
         *
         * Delete a Character.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $characterUrl   URL-name of a Charater
         */
        public function delete($seminaryUrl, $characterUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character
            $character = $this->Characters->getCharacterByUrl($seminary['id'], $characterUrl);

            // Get User
            $user = $this->Users->getUserById($character['user_id']);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete Character
                    $this->Characters->deleteCharacter($character['id']);

                    // Redirect to overview
                    $this->redirect($this->linker->link(array('index', $seminary['url']), 1));
                }

                // Redirect to entry
                $this->redirect($this->linker->link(array('index', $seminary['url'], $character['url']), 1));
            }


            // Set titile
            $this->addTitleLocalized('Delete Character');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('character', $character);
            $this->set('user', $user);
        }




        /**
         * Send mail for new Character registration.
         *
         * @param   arary   $newCharacter   Newly registered Character
         */
        private function sendRegistrationMail($newCharacter)
        {
            // Get Seminary moderators
            $characters = $this->Characters->getCharactersWithCharacterRole(self::$seminary['id'], 'moderator');

            // Send notification mail
            try {
                foreach($characters as &$character)
                {
                    $moderator = $this->Users->getUserById($character['user_id']);
                    if($moderator['mailing']) {
                        \hhu\z\Utils::sendMail(
                            $moderator['email'],
                            'characterregistration',
                            true,
                            array(
                                $moderator,
                                \hhu\z\controllers\SeminaryController::$seminary,
                                \hhu\z\controllers\IntermediateController::$user,
                                $newCharacter
                            ),
                            $this->linker
                        );
                    }
                }
            }
            catch(\hhu\z\exceptions\MailingException $e) {
                $this->log($e->getMessage());
            }
        }

    }

?>
