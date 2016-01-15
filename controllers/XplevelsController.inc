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
     * Controller of the XplevelsAgent to handle XP-levels of a
     * Seminary.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class XplevelsController extends \hhu\z\controllers\SeminaryController
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
        public $models = array('xplevels');
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'manage' => array('admin', 'moderator', 'user')
        );




        /**
         * Action: manage.
         *
         * Manage XP-levels.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function manage($seminaryUrl)
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

            // Get XP-levels
            $xplevels = $this->Xplevels->getXPLevelsForSeminary($seminary['id']);

            // Values
            $xplevelsValues = array();
            foreach($xplevels as &$xplevel) {
                $xplevelsValues[$xplevel['id']] = $xplevel;
            }
            $deletes = array();
            $validations = array(
                'edit'      => true,
                'create'    => true
            );

            // Edit
            $action = null;
            if($this->request->getRequestMethod() == 'POST')
            {
                // Edit and delete XP-levels
                if(!is_null($this->request->getPostParam('edit')))
                {
                    $action = 'edit';

                    // Get params
                    $xplevelsValues = $this->request->getPostParam('xplevels');
                    $deletes = $this->request->getPostParam('deletes');

                    // Validate params
                    if(!is_array($deletes)) {
                        $deletes = array();
                    }
                    foreach($xplevels as &$xplevel)
                    {
                        if(array_key_exists($xplevel['id'], $deletes)) {
                            continue;
                        }

                        $xplevelValidation = $this->Validation->validateParams($xplevelsValues[$xplevel['id']], array('xps'));
                        if($xplevelValidation !== true)
                        {
                            if(!is_array($validations['edit'])) {
                                $validations['edit'] = array();
                            }
                            if(!array_key_exists($xplevel['id'], $validations['edit']) || !is_array($validations['edit'][$xplevel['id']])) {
                                $validations['edit'][$xplevel['id']] = array();
                            }
                            $validations['edit'][$xplevel['id']] = $this->Validation->addValidationResults($validations['edit'][$xplevel['id']], 'xps', $xplevelValidation);
                        }
                    }

                    // Edit and delete
                    if($validations['edit'] === true)
                    {
                        $xplevels = array_reverse($xplevels);
                        foreach($xplevels as &$xplevel)
                        {
                            // Delete
                            if(array_key_exists($xplevel['id'], $deletes)) {
                                $this->Xplevels->deleteXPLevel($xplevel);
                            }
                            // Edit
                            elseif(array_key_exists($xplevel['id'], $xplevelsValues))
                            {
                                $this->Xplevels->editXPLevel(
                                    $xplevel['id'],
                                    $xplevelsValues[$xplevel['id']]['xps']
                                );
                            }
                        }

                        // Redirect
                        $this->redirect($this->linker->link(null, 3));
                    }
                }

                // Create XP-level
                if(!is_null($this->request->getPostParam('create')))
                {
                    $action = 'create';

                    // Get params and validate them
                    $xplevelnew = $this->request->getPostParam('xplevelnew');
                    $validations[$action] = $this->Validation->validateParams($xplevelnew, array('xps'));

                    // Create
                    if($validations[$action] === true)
                    {
                        $this->Xplevels->createXPLevel(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            $xplevelnew['xps']
                        );

                        // Redirect
                        $this->redirect($this->linker->link(null, 3));
                    }
                }
            }

            // Get validation settings
            $validationSettings = array(
                'xps' => \nre\configs\AppConfig::$validation['xps']
            );


            // Set titile
            $this->addTitleLocalized('Manage XP-levels');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('xplevels', $xplevels);
            $this->set('xplevelsValues', $xplevelsValues);
            $this->set('deletes', $deletes);
            $this->set('action', $action);
            $this->set('validations', $validations);
            $this->set('validationSettings', $validationSettings);
        }

    }

?>
