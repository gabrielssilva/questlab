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
     * Controller of the CharactertypesAgent to handle Charactertyes of a
     * Seminary.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactertypesController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required components
         *
         * @var array
         */
        public $components = array('validation');
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('charactertypes', 'xplevels', 'avatars', 'media');
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'index'     => array('admin', 'moderator', 'user'),
            'create'    => array('admin', 'moderator', 'user'),
            'edit'      => array('admin', 'moderator', 'user'),
            'delete'    => array('admin', 'moderator', 'user')
        );




        /**
         * Action: index.
         *
         * List Character types.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function index($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Check permissions
            if(
                (is_null(self::$character) && count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) == 0) &&
                $seminary['created_user_id'] != self::$user['id']
            ) {
                throw new \nre\exceptions\AccessDeniedException();
            }

            // Get Character types
            $charactertypes = $this->Charactertypes->getCharacterTypesForSeminary($seminary['id']);

            // Get Avatars
            $xplevels = $this->Xplevels->getXPLevelsForSeminary($seminary['id']);
            if(count($xplevels) > 0)
            {
                foreach($charactertypes as &$type)
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
            $this->addTitleLocalized('Charactertypes');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('xplevels', $xplevels);
            $this->set('charactertypes', $charactertypes);
        }


        /**
         * Action: create.
         *
         * Create new Character type for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function create($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Check permissions
            if(
                $seminary['created_user_id'] != self::$user['id'] &&
                (is_null(self::$character) && count(array_intersect(array('admin'), \hhu\z\controllers\IntermediateController::$user['roles'])) == 0)
            ) {
                throw new \nre\exceptions\AccessDeniedException();
            }

            // Values
            $name = '';
            $fields = array('charactertypename');
            $validation = array();

            // Create new Charactertype
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $name = $this->request->getPostParam('charactertypename');
                if($this->Charactertypes->charactertypeNameExists($seminary['id'], $name)) {
                    $validation = $this->Validation->addValidationResult($validation, 'charactertypename', 'exist', true);
                }

                // Create new Charactertype
                if($validation === true)
                {
                    $charactertypeId = $this->Charactertypes->createCharactertype(
                        $this->Auth->getUserId(),
                        $seminary['id'],
                        $name
                    );
                    $charactertype = $this->Charactertypes->getCharactertypeById($charactertypeId);

                    // Redirect to editing
                    $this->redirect($this->linker->link(array('edit', $seminary['url'], $charactertype['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('Create new Charactertype');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('name', $name);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edit.
         *
         * Edit Character type for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-title of a Seminary
         * @param   string  $charactertypeUrl   URL-title of Character type
         */
        public function edit($seminaryUrl, $charactertypeUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Check permissions
            if(
                $seminary['created_user_id'] != self::$user['id'] &&
                (is_null(self::$character) && count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) == 0)
            ) {
                throw new \nre\exceptions\AccessDeniedException();
            }

            // Get Character type
            $charactertype = $this->Charactertypes->getCharactertypeByUrl($seminary['id'], $charactertypeUrl);

            // XP-levels
            $xplevels = $this->Xplevels->getXPLevelsForSeminary($seminary['id']);
            foreach($xplevels as &$xplevel)
            {
                try {
                    $xplevel['avatar'] = $this->Avatars->getAvatarByTypeAndLevel($seminary['id'], $charactertype['url'], $xplevel['level']);
                }
                catch(\nre\exceptions\IdNotFoundException $e) {
                    // No Avatar available
                }
            }

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

            // Values
            $name = $charactertype['name'];
            $fields = array('charactertypename');
            $validation = array();
            $avatarVariants = array('portrait', 'avatar');
            $avatarsValidation = true;

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $name = $this->request->getPostParam('charactertypename');
                if($this->Charactertypes->charactertypeNameExists($seminary['id'], $name, $charactertype['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'charactertypename', 'exist', true);
                }

                // Validate and upload avatars
                if(array_key_exists('avatars', $_FILES))
                {
                    foreach($xplevels as &$xplevel)
                    {
                        if(array_key_exists($xplevel['id'], $_FILES['avatars']['error']))
                        {
                            foreach($avatarVariants as &$variant)
                            {
                                if(array_key_exists($variant, $_FILES['avatars']['error'][$xplevel['id']]) && $_FILES['avatars']['error'][$xplevel['id']][$variant] !== UPLOAD_ERR_NO_FILE)
                                {
                                    $avatar = array(
                                        'name'      => $_FILES['avatars']['name'][$xplevel['id']][$variant],
                                        'type'      => $_FILES['avatars']['type'][$xplevel['id']][$variant],
                                        'tmp_name'  => $_FILES['avatars']['tmp_name'][$xplevel['id']][$variant],
                                        'error'     => $_FILES['avatars']['error'][$xplevel['id']][$variant],
                                        'size'      => $_FILES['avatars']['size'][$xplevel['id']][$variant]
                                    );
                                    $avatarValidation = true;

                                    // Check error
                                    if($avatar['error'] !== UPLOAD_ERR_OK) {
                                        $avatarValidation = $this->Validation->addValidationResult($avatarValidation, 'avatar', 'error', $avatar['error']);
                                    }

                                    // Check mimetype
                                    $avatarMimetype = null;
                                    $avatar['mimetype'] = \hhu\z\Utils::getMimetype($avatar['tmp_name'], $avatar['type']);
                                    foreach($mimetypes as &$mimetype) {
                                        if($mimetype['mimetype'] == $avatar['mimetype']) {
                                            $avatarMimetype = $mimetype;
                                            break;
                                        }
                                    }
                                    if(is_null($avatarMimetype)) {
                                        $avatarValidation = $this->Validation->addValidationResult($avatarValidation, 'avatar', 'mimetype', $avatar['mimetype']);
                                    }
                                    elseif($avatar['size'] > $avatarMimetype['size']) {
                                        $avatarValidation = $this->Validation->addValidationResult($avatarValidation, 'avatar', 'size', $avatarMimetype['size']);
                                    }

                                    // Add validation result
                                    if(!$avatarValidation !== true)
                                    {
                                        if(!is_array($avatarsValidation)) {
                                            $avatarsValidation = array();
                                        }
                                        if(!array_key_exists($xplevel['id'], $avatarsValidation)) {
                                            $avatarsValidation[$xplevel['id']] = array();
                                        }
                                        $avatarsValidation[$xplevel['id']][$variant] = $avatarValidation;
                                    }

                                    // Upload avatar
                                    if($avatarValidation === true)
                                    {
                                        $avatar['media_id'] = $this->Media->createAvatarPicture(
                                            $this->Auth->getUserId(),
                                            $seminary['id'],
                                            sprintf('avatar-%d-%d-%s', $charactertype['id'], $xplevel['id'], $variant),
                                            '',
                                            $avatar['mimetype'],
                                            $avatar['tmp_name']
                                        );

                                        // Set avatar
                                        if($variant == 'portrait') {
                                            $this->Avatars->setAvatarPortraitForTypeAndLevel(
                                                $this->Auth->getUserId(),
                                                $charactertype['id'],
                                                $xplevel['id'],
                                                $avatar['media_id']
                                            );
                                        }
                                        else {
                                            $this->Avatars->setAvatarForTypeAndLevel(
                                                $this->Auth->getUserId(),
                                                $charactertype['id'],
                                                $xplevel['id'],
                                                $avatar['media_id']
                                            );
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // Edit Charactertype
                if($validation === true && $avatarsValidation === true)
                {
                    $this->Charactertypes->editCharactertype(
                        $charactertype['id'],
                        $name
                    );
                    $charactertype = $this->Charactertypes->getCharactertypeById($charactertype['id']);

                    // Redirect to overview
                    $this->redirect($this->linker->link(array('index', $seminary['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('Edit Charactertype');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('charactertype', $charactertype);
            $this->set('xplevels', $xplevels);
            $this->set('name', $name);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
            $this->set('avatarsValidation', $avatarsValidation);
            $this->set('avatarVariants', $avatarVariants);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: delete.
         *
         * Delete Character type for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-title of a Seminary
         * @param   string  $charactertypeUrl   URL-title of Character type
         */
        public function delete($seminaryUrl, $charactertypeUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Check permissions
            if(
                $seminary['created_user_id'] != self::$user['id'] &&
                (is_null(self::$character) && count(array_intersect(array('admin'), \hhu\z\controllers\IntermediateController::$user['roles'])) == 0)
            ) {
                throw new \nre\exceptions\AccessDeniedException();
            }

            // Get Character type
            $charactertype = $this->Charactertypes->getCharactertypeByUrl($seminary['id'], $charactertypeUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete Character type
                    $this->Charactertypes->deleteCharactertype($charactertype['id']);
                }

                // Redirect to overview
                $this->redirect($this->linker->link(array('index', $seminary['url']), 1));
            }


            // Set titile
            $this->addTitleLocalized('Delete Charactertype');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('charactertype', $charactertype);
        }

    }

?>
