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
     * Controller of the PagesAgent to manage additional pages.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class PagesController extends \hhu\z\controllers\IntermediateController
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
        public $models = array('pages');
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'index'    => array('admin')
            /*
            'create'    => array('admin', 'moderator'),
            'edit'      => array('admin', 'moderator'),
            'delete'    => array('admin')
            */
        );




        /**
         * Action: index.
         *
         * List all registered pages.
         */
        public function index()
        {
            // Get registered pages
            $pages = $this->Pages->getPages();


            // Pass data to view
            $this->set('pages', $pages);
        }


        /**
         * Action: page.
         *
         * Show a page.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $pageUrl URL of page to show
         */
        public function page($pageUrl)
        {
            // Get page
            $page = $this->Pages->getPageByUrl($pageUrl);


            // Pass data to view
            $this->set('page', $page);
        }


        /**
         * Action: create.
         *
         * Create a new page.
         */
        public function create()
        {
            // Values
            $title = '';
            $fields = array('title');
            $validation = array();

            // Create new page
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Pages->titleExists($title)) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }

                // Create
                if($validation === true)
                {
                    $pageId = $this->Pages->createPage(
                        $this->Auth->getUserId(),
                        $title
                    );

                    // Redirect to page
                    $page = $this->Pages->getPageById($pageId);
                    $this->redirect($this->linker->link(array('page', $page['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Pass data to view
            $this->set('title', $title);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: edit.
         *
         * Edit page.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $pageUrl    URL of page to edit
         */
        public function edit($pageUrl)
        {
            // Get page
            $page = $this->Pages->getPageByUrl($pageUrl);

            // Values
            $title = $page['title'];
            $text = $page['text'];
            $fields = array('title');
            $validation = array();

            // Edit content
            if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('save')))
            {
                // Get params and validate them
                $validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
                $title = $this->request->getPostParam('title');
                if($this->Pages->titleExists($title, $page['id'])) {
                    $validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
                }
                $text = $this->request->getPostParam('text');

                // Edit
                if($validation === true)
                {
                    $this->Pages->editPage(
                        $page['id'],
                        $title,
                        $text
                    );

                    // Redirect to entry
                    $this->redirect($this->linker->link(array('page', $page['url']), 1));
                }
            }

            // Get validation settings
            $validationSettings = array();
            foreach($fields as &$field) {
                $validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
            }


            // Pass data to view
            $this->set('page', $page);
            $this->set('title', $title);
            $this->set('text', $text);
            $this->set('validation', $validation);
            $this->set('validationSettings', $validationSettings);
        }


        /**
         * Action: delete.
         *
         * Delete a page.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $pageUrl    URL of page to delete
         */
        public function delete($pageUrl)
        {
            // Get page
            $page = $this->Pages->getPageByUrl($pageUrl);

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Check confirmation
                if(!is_null($this->request->getPostParam('delete')))
                {
                    // Delete page
                    $this->Pages->deletePage($page);

                    // Redirect to overview
                    $this->redirect($this->linker->link(null, 1));
                }

                // Redirect to entry
                $this->redirect($this->linker->link(array('page', $page['url']), 1));
            }


            // Set titile
            $this->addTitleLocalized('Delete page');

            // Show confirmation
            $this->set('page', $page);
        }

    }

?>
