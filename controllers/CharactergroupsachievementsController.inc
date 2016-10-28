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
     * Controller of the Agent to list Charactegroupsachievements.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactergroupsachievementsController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'charactergroupsachievements', 'charactergroups', 'media');
        /**
         * Required components
         *
         * @var array
         */
        public $components = array('validation', 'notification');
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'achievement'   => array('admin', 'moderator', 'user'),
            'create'        => array('admin', 'moderator', 'user'),
            'moveup'        => array('admin', 'moderator', 'user'),
            'movedown'      => array('admin', 'moderator', 'user'),
            'edit'          => array('admin', 'moderator', 'user'),
            'manage'        => array('admin', 'moderator', 'user'),
            'delete'        => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'achievement'   => array('admin', 'moderator', 'user'),
            'create'        => array('admin'),
            'moveup'        => array('admin', 'moderator'),
            'movedown'      => array('admin', 'moderator'),
            'edit'          => array('admin', 'moderator'),
            'manage'        => array('admin', 'moderator'),
            'delete'        => array('admin')
        );




        /**
         * Action: achievement.
         *
         * Let a Character group achieve an achievement.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-Title of Seminary
         * @param   string  $groupsgroupUrl     URL-title of Character groups-group
         * @param   string  $achievementHash    Hash of Character groups achievement
         */
        public function achievement($seminaryUrl, $groupsgroupUrl, $achievementHash)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Achievement
            $achievement = $this->Charactergroupsachievements->getAchievementByHash(
                $achievementHash
            );

            // Get Character group(s)
            $charactergroups = null;
            $charactergroup = null;
            $notify = true;
            if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) {
                $charactergroups = $this->Charactergroups->getGroupsForGroupsgroup($groupsgroup['id']);
                $notify = false;
            }
            else
            {
                $character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
                $charactergroups = $this->Charactergroups->getGroupsForCharacter($character['id']);
                if(count($charactergroups) == 1) {
                    $charactergroup = $charactergroups[0];
                }
            }
            // Select group by parameter
            $selectedCharactergroupId = $this->request->getPostParam('charactergroup');
            if(!is_null($selectedCharactergroupId))
            {
                $selectedCharactergroupId = intval($selectedCharactergroupId);
                foreach($charactergroups as &$group) {
                    if($group['id'] == $selectedCharactergroupId) {
                        $charactergroup = $group;
                        break;
                    }
                }
            }

            // Set Achievement achieved for Character group
            if(!is_null($charactergroup))
            {
                if(!$this->Charactergroupsachievements->hasCharactergroupAchievedAchievement(
                    $achievement['id'],
                    $charactergroup['id']
                )) {
                    // Set achieved-status
                    $this->Charactergroupsachievements->setAchievementAchieved(
                        $achievement['id'],
                        $charactergroup['id']
                    );

                    // Set notification
                    if($notify) {
                        $this->Notification->addNotification(
                            \hhu\z\controllers\components\NotificationComponent::TYPE_CHARACTERGROUPSACHIEVEMENT,
                            $achievement['title'],
                            $this->linker->link(
                                array(
                                    'charactergroups',
                                    'group',
                                    $seminary['url'],
                                    $groupsgroup['url'],
                                    $charactergroup['url']
                                ), 0, true, null, true, 'achievements'
                            ),
                            (!is_null($achievement['achievementsmedia_id']) ? $this->linker->link(
                                array(
                                    'media',
                                    'charactergroupsachievement',
                                    $seminary['url'],
                                    $groupsgroup['url'],
                                    $achievement['url']
                                )
                            ) : null)
                        );
                    }
                }

                // Redirect
                $this->redirect(
                    $this->linker->link(
                        array(
                            'charactergroups',
                            'group',
                            $seminary['url'],
                            $groupsgroup['url'],
                            $charactergroup['url']
                        ), 0, true, null, true, 'achievements'
                    )
                );
            }


            // TODO Set title
            $this->addTitle($achievement['title']);
            $this->addTitle(sprintf(_('%s-Achievements'), $groupsgroup['name']));
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('achievement', $achievement);
            $this->set('charactergroups', $charactergroups);
            $this->set('charactergroup', $charactergroup);
        }


        /**
         * Action: manage.
         *
         * Manage Achievements of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of Seminary
         * @param   string  $groupsgroupUrl URL-title of Character groups-group
         */
        public function manage($seminaryUrl, $groupsgroupUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Achievements
            $achievements = $this->Charactergroupsachievements->getAchievementsForCharactergroupsgroup(
                $groupsgroup['id']
            );


            // TODO Set title
            $this->addTitleLocalized('Manage Achievements');
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('achievements', $achievements);
        }


        /**
         * Action: create.
         *
         * Create a new Achievement.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of Seminary
         * @param   string  $groupsgroupUrl URL-title of Character groups-group
         */
        public function create($seminaryUrl, $groupsgroupUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['icons'];

            // Values
            $title = '';
            $description = '';
            $fields = array('title');
            $validation = array();

            // Create Achievement
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Charactergroupsachievements->achievementTitleExists($groupsgroup['id'], $title)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $description = $this->request->getPostParam('description');

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

                // Create Achievement
                if($validation === true)
                {
                    $achievementId = $this->Charactergroupsachievements->createAchievement(
                        $this->Auth->getUserId(),
                        $groupsgroup['id'],
                        $title,
                        $description
                    );
                    $achievement = $this->Charactergroupsachievements->getAchievementById($achievementId);

                    // Upload icon
                    if(!is_null($icon))
                    {
                        $mediaId = $this->Media->createAchievementMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('charactergroupsachievement-%d', $achievement['id']),
                            $achievement['title'],
                            $icon['mimetype'],
                            $icon['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Charactergroupsachievements->setIconForAchievement(
                                $achievement['id'],
                                $mediaId
                            );
                        }
                    }

                    // Redirect to condition editing
                    $this->redirect(
                        $this->linker->link(array(
                            'manage',
                            $seminary['url'],
                            $groupsgroup['url']
                        ), 1, true, null, true, 'achievements'
                    ));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // TODO Set title
            $this->addTitleLocalized('Create Achievement');
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('title', $title);
            $this->set('description', $description);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: moveup.
         *
         * Move an Achievement up (decrement position).
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of Seminary
         * @param   string  $groupsgroupUrl URL-title of Character groups-group
         * @param   string  $achievementUrl URL-title of Achievement
         */
        public function moveup($seminaryUrl, $groupsgroupUrl, $achievementUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Achievement
            $achievement = $this->Charactergroupsachievements->getAchievementByUrl($groupsgroup['id'], $achievementUrl);

            // Set position
            $this->Charactergroupsachievements->moveAchievement($achievement, true);


            // Redirect
            $this->redirect(
                $this->linker->link(
                    array(
                        'manage',
                        $seminary['url'],
                        $groupsgroup['url']
                    ), 1, true, null, false, $achievement['url']
                )
            );
        }


        /**
         * Action: movedown.
         *
         * Move an Achievement down (increment position).
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of Seminary
         * @param   string  $groupsgroupUrl URL-title of Character groups-group
         * @param   string  $achievementUrl URL-title of Achievement
         */
        public function movedown($seminaryUrl, $groupsgroupUrl, $achievementUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Achievement
            $achievement = $this->Charactergroupsachievements->getAchievementByUrl($groupsgroup['id'], $achievementUrl);

            // Set position
            $this->Charactergroupsachievements->moveAchievement($achievement, false);


            // Redirect
            $this->redirect(
                $this->linker->link(
                    array(
                        'manage',
                        $seminary['url'],
                        $groupsgroup['url']
                    ), 1, true, null, false, $achievement['url']
                )
            );
        }


        /**
         * Action: edit.
         *
         * Edit an Achievement.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of Seminary
         * @param   string  $groupsgroupUrl URL-title of Character groups-group
         * @param   string  $achievementUrl URL-title of Achievement to edit
         */
        public function edit($seminaryUrl, $groupsgroupUrl, $achievementUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Achievement
            $achievement = $this->Charactergroupsachievements->getAchievementByUrl(
                $groupsgroup['id'],
                $achievementUrl
            );

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['icons'];

            // Values
            $title = $achievement['title'];
            $description = $achievement['description'];
            $fields = array('title');
            $validation = array();

            // Edit Achievement
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Charactergroupsachievements->achievementTitleExists($groupsgroup['id'], $title, $achievement['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $description = $this->request->getPostParam('description');

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

                // Edit Achievement
                if($validation === true)
                {
                    $this->Charactergroupsachievements->editAchievement(
                        $achievement['id'],
                        $title,
                        $description
                    );

                    // Upload icon
                    if(!is_null($icon))
                    {
                        $mediaId = $this->Media->createAchievementMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            sprintf('charactergroupsachievement-%d', $achievement['id']),
                            $achievement['title'],
                            $icon['mimetype'],
                            $icon['tmp_name']
                        );
                        if($mediaId !== false) {
                            $this->Charactergroupsachievements->setIconForAchievement(
                                $achievement['id'],
                                $mediaId
                            );
                        }
                    }

                    // Redirect
                    $this->redirect(
                        $this->linker->link(
                            array(
                                'manage',
                                $seminary['url'],
                                $groupsgroup['url']
                            ), 1, true, null, false, $achievement['url']
                        )
                    );
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // TODO Set title
            $this->addTitleLocalized('Edit Achievement');
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('achievement', $achievement);
            $this->set('title', $title);
            $this->set('description', $description);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: delete.
         *
         * Delete an Achievement.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of Seminary
         * @param   string  $groupsgroupUrl URL-title of Character groups-group
         * @param   string  $achievementUrl URL-title of Achievement
         */
        public function delete($seminaryUrl, $groupsgroupUrl, $achievementUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Achievement
            $achievement = $this->Charactergroupsachievements->getAchievementByUrl($groupsgroup['id'], $achievementUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete seminary
                    $this->Charactergroupsachievements->deleteAchievement($achievement);
                }

                // Redirect to entry
                $this->redirect(
                    $this->linker->link(
                        array(
                            'manage',
                            $seminary['url'],
                            $groupsgroup['url']
                        ),
                        1
                    )
                );
            }


            // Set titile
            $this->addTitleLocalized('Delete seminary');
            $this->addTitle($groupsgroup['name']);
            $this->addTitle($seminary['title']);

            // Show confirmation
            $this->set('seminary', $seminary);
            $this->set('groupsgroup', $groupsgroup);
            $this->set('achievement', $achievement);
        }
    }

?>
