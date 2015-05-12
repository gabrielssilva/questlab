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
     * Abstract class for implementing a Controller of an IntermediateAgent.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    abstract class IntermediateController extends \hhu\z\Controller
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('users', 'userroles', 'seminaries', 'characters');
        /**
         * Current user
         *
         * @var array
         */
        public static $user = null;
        /**
         * Title information
         *
         * @var array
         */
        private $title = array();




        /**
         * Construct a new IntermediateController.
         *
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @param   string      $layoutName Name of the current Layout
         * @param   string      $action     Current Action
         * @param   \nre\core\Agent $agent      Corresponding Agent
         */
        public function __construct($layoutName, $action, $agent)
        {
            parent::__construct($layoutName, $action, $agent);
        }



        /**
         * Prefilter that is executed before running the Controller.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::preFilter($request, $response);

            // Get userdata
            try {
                self::$user = $this->Users->getUserById($this->Auth->getUserId());
                self::$user['roles'] = array_map(function($r) { return $r['name']; }, $this->Userroles->getUserrolesForUserById(self::$user['id']));
            }
            catch(\nre\exceptions\IdNotFoundException $e) {
            }

            // Check permissions
            $this->checkPermission($request, $response);

            // Set userdata
            $this->set('loggedUser', self::$user);
        }


        /**
         * Postfilter that is executed after running the Controller.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function postFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::postFilter($request, $response);
        }


        /**
         * Return current title information.
         *
         * @return  string  Title information
         */
        public function getTitle()
        {
            return $this->title;
        }




        /**
         * Add a piece of information to the current title.
         *
         * @param   string  $title Title information
         */
        protected function addTitle($title)
        {
            $this->title[] = $title;
        }


        /**
         * Add a piece of information to the current title and localize
         * it.
         *
         * @param   string  $title Title information
         */
        protected function addTitleLocalized($title)
        {
            $title = gettext($title);

            $args = func_get_args();
            if(count($args) > 0) {
                $title = call_user_func_array(
                    'sprintf',
                    array_merge(
                        array($title),
                        array_slice($args, 1)
                    )
                );
            }


            $this->title[] = $title;
        }




        /**
         * Check user permissions.
         *
         * @throws  \nre\exceptions\AccessDeniedException
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        private function checkPermission(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Determine user
            $userRoles = array('guest');
            if(!is_null(self::$user)) {
                $userRoles = self::$user['roles'];
            }


            // Do not check error pages
            if($response->getParam(0, 'toplevel') == \nre\core\Config::getDefault('toplevel-error')) {
                return;
            }
            if($response->getParam(1, 'intermediate') == \nre\core\Config::getDefault('intermediate-error')) {
                return;
            }

            // Determine permissions of Intermediate Controller for current action
            $controller = $this->agent->controller;
            $action = $this->request->getParam(2, 'action');
            if(!property_exists($controller, 'permissions')) {
                return; // Allow if nothing is specified
            }
            if(!array_key_exists($action, $controller->permissions)) {
                return; // Allow if Action is not specified
            }
            $permissions = $controller->permissions[$action];


            // Check permissions
            if(count(array_intersect($userRoles, $permissions)) == 0) {
                throw new \nre\exceptions\AccessDeniedException();
            }
        }

    }

?>
