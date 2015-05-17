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
     * Controller of the MapAgent to display a map.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MapController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'map', 'media');
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
            'edit'  => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'index' => array('admin', 'moderator', 'user'),
            'edit'  => array('admin', 'moderator')
        );




        /**
         * Action: index.
         *
         * Draw the map.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of Seminary
         */
        public function index($seminaryUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get map
            $map = $this->Map->getMapOfSeminary($seminary['id']);

            // Check permissions
            if(is_null($map) && count(array_intersect(array('admin','moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) == 0) {
                throw new \nre\exceptions\IdNotFoundException($seminaryUrl);
            }


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('map', $map);
        }


        /**
         * Action: edit.
         *
         * Edit the map of a Seminary.
         *
         * @param   string  $seminaryUrl    URL-Title of Seminary
         */
        public function edit($seminaryUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get map
            $map = $this->Map->getMapOfSeminary($seminary['id']);

            // Get allowed mimetypes
            $mimetypes = \nre\configs\AppConfig::$mimetypes['map'];

            // Values
            $validation = true;

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                // Validate media (map file)
                $media = null;
                if(!empty($_FILES) && array_key_exists('media', $_FILES) && $_FILES['media']['error'] != UPLOAD_ERR_NO_FILE)
                {
                    $media = $_FILES['media'];

                    // Check error
                    if($media['error'] !== UPLOAD_ERR_OK) {
                        $validation = $this->Validation->addValidationResult($validation, 'media', 'error', $media['error']);
                    }

                    // Check mimetype
                    $mediaMimetype = null;
                    $media['mimetype'] = \hhu\z\Utils::getMimetype($media['tmp_name'], $media['type']);
                    foreach($mimetypes as &$mimetype) {
                        if($mimetype['mimetype'] == $media['mimetype']) {
                            $mediaMimetype = $mimetype;
                            break;
                        }
                    }
                    if(is_null($mediaMimetype)) {
                        $validation = $this->Validation->addValidationResult($validation, 'media', 'mimetype', $media['mimetype']);
                    }
                    elseif($media['size'] > $mediaMimetype['size']) {
                        $validation = $this->Validation->addValidationResult($validation, 'media', 'size', $mediaMimetype['size']);
                    }
                }

                // Edit map
                if($validation === true)
                {
                    // Update media
                    if(!is_null($media))
                    {
                        $seminarymediaId = $this->Media->createMapMedia(
                            $this->Auth->getUserId(),
                            $seminary['id'],
                            $media['name'],
                            sprintf('map of %s', $seminary['title']),
                            $media['type'],
                            $media['tmp_name']
                        );
                        if($seminarymediaId > 0) {
                            $this->Map->setMapOfSeminary($seminary['id'], $seminarymediaId);
                        }
                    }

                    // Redirect
                    $this->redirect($this->linker->link(array('index', $seminary['url']), 1));
                }
            }

            // Set titile
            //$this->addTitleLocalized('Delete Quest');
            //$this->addTitle($seminary['title']);


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('map', $map);
            $this->set('mimetypes', $mimetypes);
            $this->set('validation', $validation);
        }

    }

?>
