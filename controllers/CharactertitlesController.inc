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
     * Controller of the CharactertitlesAgent to handle Character titles of a
     * Seminary.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactertitlesController extends \hhu\z\controllers\SeminaryController
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
        public $models = array('charactertitles');
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
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'index'         => array('admin', 'moderator'),
            'create'        => array('admin', 'moderator'),
            'edit'          => array('admin', 'moderator'),
            'delete'        => array('admin', 'moderator')
        );




        /**
         * Action: index.
         *
         * List Character titles.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function index($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character titles
            $titles = $this->Charactertitles->getTitlesForSeminary($seminary['id']);


            // Set titile
            $this->addTitleLocalized('Charactertitles');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('titles', $titles);
        }


        /**
         * Action: create.
         *
         * Create a new Character title for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         */
        public function create($seminaryUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Values
            $titleMale = '';
            $titleFemale = '';
            $fields = array('title_male', 'title_female');
            $validation = array();

            // Create new Charactertype
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $titleMale = $this->request->getPostParam('title_male');
                if($this->Charactertitles->titleExists($seminary['id'], $titleMale)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title_male', 'exist', true);
                }
                $titleFemale = $this->request->getPostParam('title_female');
                if($this->Charactertitles->titleExists($seminary['id'], $titleFemale)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title_female', 'exist', true);
                }

                // Create new Character title
                if($validation === true)
                {
                    $titleId = $this->Charactertitles->createTitle(
                        $this->Auth->getUserId(),
                        $seminary['id'],
                        $titleMale,
                        $titleFemale
                    );
                    $title = $this->Charactertitles->getTitleById($titleId);

                    // Redirect to overview
                    $this->redirect(
                        $this->linker->link(
                            array(
                                'index',
                                $seminary['url']
                            ),
                            1
                        )
                    );
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Set titile
            $this->addTitleLocalized('Create new Charactertitle');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('titleMale', $titleMale);
            $this->set('titleFemale', $titleFemale);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edit.
         *
         * Edit a Character title for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of a Seminary
         * @param   string  $titleHash      Hash of Character title
         */
        public function edit($seminaryUrl, $titleHash)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character title
            $title = $this->Charactertitles->getTitleByHash($titleHash);

            // Values
            $titleMale = $title['title_male'];
            $titleFemale = $title['title_female'];
            $fields = array('title_male', 'title_female');
            $validation = array();

            // Check request method
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $titleMale = $this->request->getPostParam('title_male');
                if($this->Charactertitles->titleExists($seminary['id'], $titleMale, $title['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'title_male', 'exist', true);
                }
                $titleFemale = $this->request->getPostParam('title_female');
                if($this->Charactertitles->titleExists($seminary['id'], $titleFemale, $title['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'title_female', 'exist', true);
                }

                // Edit Character title
                if($validation === true)
                {
                    $this->Charactertitles->editTitle(
                        $title['id'],
                        $titleMale,
                        $titleFemale
                    );
                    $title = $this->Charactertitles->getTitleById($title['id']);

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
            $this->addTitleLocalized('Edit Charactertitle');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('titleMale', $titleMale);
            $this->set('titleFemale', $titleFemale);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: delete.
         *
         * Delete a Character title for a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of a Seminary
         * @param   string  $titleHash      Hash of Character title
         */
        public function delete($seminaryUrl, $titleHash)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character title
            $title = $this->Charactertitles->getTitleByHash($titleHash);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete Character title
                    $this->Charactertitles->deleteTitle($title['id']);
                }

                // Redirect to overview
                $this->redirect($this->linker->link(array('index', $seminary['url']), 1));
            }


            // Set titile
            $this->addTitleLocalized('Delete Charactertitle');
            $this->addTitle($seminary['title']);

            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('title', $title);
        }

    }

?>
