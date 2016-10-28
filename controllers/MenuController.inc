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
     * Controller of the Agent to display a menu.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MenuController extends \hhu\z\Controller
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('pages');




        /**
         * Prefilter.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::preFilter($request, $response);

            // Set userdata
            $this->set('loggedUser', IntermediateController::$user);
            $this->set('loggedCharacter', SeminaryController::$character);
            $this->set('loggedSeminary', SeminaryController::$seminary);
        }


        /**
         * Action: index.
         */
        public function index()
        {
            // Get additional pages
            $pages = $this->Pages->getPages();


            // Pass data to view
            $this->set('pages', $pages);
        }

    }

?>
