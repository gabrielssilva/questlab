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
     * Controller of the QuestgroupsAgent to display Questgroups.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuestgroupshierarchyController extends \hhu\z\controllers\SeminaryController
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
        public $models = array('seminaries', 'questgroupshierarchy', 'questgroups');
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'create'    => array('admin', 'moderator', 'user'),
            'edit'      => array('admin', 'moderator', 'user'),
            'moveup'    => array('admin', 'moderator', 'user'),
            'movedown'  => array('admin', 'moderator', 'user'),
            'delete'    => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'create'    => array('admin'),
            'edit'      => array('admin'),
            'moveup'    => array('admin'),
            'movedown'  => array('admin'),
            'delete'    => array('admin')
        );




        /**
         * Action: create.
         *
         * Create a new Questgroupshierarchy.
         *
         * @param   string  $seminaryUrl    URL-title of a Seminary
         */
        public function create($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get parent Questgroupshierarchy
            $parentQuestgroupshierarchy = $this->Questgroupshierarchy->getHierarchyOfSeminary($seminary['id']);

            // Values
            $titleSingular = '';
            $titlePlural = '';
            $validation = array();

            // Create Questgroupshierarchy
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $titleSingular = $this->request->getPostParam('title_singular');
                $validation = $this->Validation->addValidationResults(
                    $validation,
                    'titleSingular',
                    $this->Validation->validate($titleSingular, \nre\configs\AppConfig::$validation['questgroupshierarchytitle'])
                );
                if($this->Questgroupshierarchy->questgroupshierarchyTitleSingularExists($titleSingular, $seminary['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'titleSingular', 'exist', true);
                }
                $titlePlural = $this->request->getPostParam('title_plural');
                $validation = $this->Validation->addValidationResults(
                    $validation,
                    'titlePlural',
                    $this->Validation->validate($titlePlural, \nre\configs\AppConfig::$validation['questgroupshierarchytitle'])
                );
                if($this->Questgroupshierarchy->questgroupshierarchyTitleSingularExists($titlePlural, $seminary['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'titlePlural', 'exist', true);
                }

                // Validate parent Questgroupshierarchy
                $parentQuestgroupshierarchyIndex = null;
                foreach($parentQuestgroupshierarchy as $index => &$parentHierarchy)
                {
                    $parentHierarchy['selected'] = ($parentHierarchy['url'] == $this->request->getPostParam('parent'));
                    if($parentHierarchy['selected']) {
                        $parentQuestgroupshierarchyIndex = $index;
                    }
                }

                // Create new Questgroupshierarchy
                if($validation === true)
                {
                    $questgroupshierarchyId = $this->Questgroupshierarchy->createQuestgroupshierarchy(
                        $this->Auth->getUserId(),
                        $seminary['id'],
                        (!is_null($parentQuestgroupshierarchyIndex) ? $parentQuestgroupshierarchy[$parentQuestgroupshierarchyIndex]['id'] : null),
                        $titleSingular,
                        $titlePlural
                    );
                    $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyById($questgroupshierarchyId);

                    // Redirect
                    $this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
                }
            }

            // Get validation settings
            $validationSettings = array(
                'title' => \nre\configs\AppConfig::$validation['title']
            );


            // Set titile
            $this->addTitleLocalized('Create Questgroupshierarchy');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('titleSingular', $titleSingular);
            $this->set('titlePlural', $titlePlural);
            $this->set('parentQuestgroupshierarchy', $parentQuestgroupshierarchy);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edit.
         *
         * Edit a Questgroupshierarchy.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl            URL-title of Seminary
         * @param   string  $questgroupshierarchyUrl    URL-title of Questgroupshierarchy
         */
        public function edit($seminaryUrl, $questgroupshierarchyUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroupshierarchy
            $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyByUrl($seminary['id'], $questgroupshierarchyUrl);

            // Values
            $titleSingular = $questgroupshierarchy['title_singular'];
            $titlePlural = $questgroupshierarchy['title_plural'];
            $validation = array();

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $titleSingular = $this->request->getPostParam('title_singular');
                $validation = $this->Validation->addValidationResults(
                    $validation,
                    'titleSingular',
                    $this->Validation->validate($titleSingular, \nre\configs\AppConfig::$validation['questgroupshierarchytitle'])
                );
                if($this->Questgroupshierarchy->questgroupshierarchyTitleSingularExists($titleSingular, $seminary['id'], $questgroupshierarchy['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'titleSingular', 'exist', true);
                }
                $titlePlural = $this->request->getPostParam('title_plural');
                $validation = $this->Validation->addValidationResults(
                    $validation,
                    'titlePlural',
                    $this->Validation->validate($titlePlural, \nre\configs\AppConfig::$validation['questgroupshierarchytitle'])
                );
                if($this->Questgroupshierarchy->questgroupshierarchyTitleSingularExists($titlePlural, $seminary['id'], $questgroupshierarchy['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'titlePlural', 'exist', true);
                }


                // Edit Questgroup
                if($validation === true)
                {
                    $this->Questgroupshierarchy->editQuestgroupshierarchy(
                        $questgroupshierarchy['id'],
                        $titleSingular,
                        $titlePlural
                    );
                    $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyById($questgroupshierarchy['id']);

                    // Redirect to Seminary page
                    $this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
                }
            }

            // Get validation settings
            $validationSettings = array(
                'title' => \nre\configs\AppConfig::$validation['title']
            );


            // Set titile
            $this->addTitleLocalized('Edit Questgroupshierarchy');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('titleSingular', $titleSingular);
            $this->set('titlePlural', $titlePlural);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: moveup.
         *
         * Move a Questgroupshierarchy up (decrement position).
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl            URL-title of Seminary
         * @param   string  $questgroupshierarchyUrl    URL-title of Questgroupshierarchy
         */
        public function moveup($seminaryUrl, $questgroupshierarchyUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroupshierarchy
            $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyByUrl($seminary['id'], $questgroupshierarchyUrl);

            // Set position
            $this->Questgroupshierarchy->moveQuestgroupshierarchy($questgroupshierarchy, true);


            // Redirect
            $referer = $this->request->getGetParam('referer');
            if(!is_null($referer))
            {
                try {
                    $questgroup = $this->Questgroups->getQuestgroupById($referer);
                    $this->redirect($this->linker->link(array('questgroups', 'questgroup', $seminary['url'], $questgroup['url'])));
                }
                catch(IdNotFoundException $e) {
                }
            }
            $this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
        }


        /**
         * Action: movedown.
         *
         * Move a Questgroupshierarchy down (increment position).
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl            URL-title of Seminary
         * @param   string  $questgroupshierarchyUrl    URL-title of Questgroupshierarchy
         */
        public function movedown($seminaryUrl, $questgroupshierarchyUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroupshierarchy
            $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyByUrl($seminary['id'], $questgroupshierarchyUrl);

            // Set position
            $this->Questgroupshierarchy->moveQuestgroupshierarchy($questgroupshierarchy, false);


            // Redirect
            $referer = $this->request->getGetParam('referer');
            if(!is_null($referer))
            {
                try {
                    $questgroup = $this->Questgroups->getQuestgroupById($referer);
                    $this->redirect($this->linker->link(array('questgroups', 'questgroup', $seminary['url'], $questgroup['url'])));
                }
                catch(IdNotFoundException $e) {
                }
            }
            $this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
        }


        /**
         * Action: delete.
         *
         * Delete a Questgroupshierarchy.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl            URL-title of Seminary
         * @param   string  $questgroupshierarchyUrl    URL-title of Questgroupshierarchy
         */
        public function delete($seminaryUrl, $questgroupshierarchyUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Questgroupshierarchy
            $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyByUrl($seminary['id'], $questgroupshierarchyUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete Questgroupshierarchy
                    $this->Questgroupshierarchy->deleteQuestgroupshierarchy($questgroupshierarchy['id']);
                }

                // Redirect to Seminary page
                $this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
            }


            // Set titile
            $this->addTitleLocalized('Delete Questgroupshierarchy');

            // Show confirmation
            $this->set('seminary', $seminary);
            $this->set('questgroupshierarchy', $questgroupshierarchy);
        }

    }

?>
