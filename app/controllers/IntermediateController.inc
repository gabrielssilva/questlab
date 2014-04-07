<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\controllers;
	
	
	/**
	 * Abstract class for implementing a Controller of an IntermediateAgent.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
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
		 * Current Seminary
		 * 
		 * var array
		 */
		public static $seminary = null;
		/**
		 * Character of current user and Seminary
		 * 
		 * @var array
		 */
		public static $character = null;
		
		
		
		
		/**
		 * Construct a new IntermediateController.
		 * 
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @throws	ModelNotValidException
		 * @throws	ModelNotFoundException
		 * @throws	ViewNotFoundException
		 * @param	string	$layoutName	Name of the current Layout
		 * @param	string	$action		Current Action
		 * @param	Agent	$agent		Corresponding Agent
		 */
		public function __construct($layoutName, $action, $agent)
		{
			parent::__construct($layoutName, $action, $agent);
		}
		
		
		
		/**
		 * Prefilter that is executed before running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::preFilter($request, $response);
			
			// Get userdata
			try {
				self::$user = $this->Users->getUserById($this->Auth->getUserId());
				
				// Determine user roles
				self::$user['roles'] = array();
				$roles = $this->Userroles->getUserrolesForUserById(self::$user['id']);
				foreach($roles as &$role) {
					self::$user['roles'][] = $role['name'];
				}
				
				// Character
				$controller = $this->agent->controller;
				if(is_subclass_of($controller, '\hhu\z\controllers\SeminaryRoleController'))
				{
					$seminaryUrl = $this->request->getParam(3);
					self::$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
					self::$character = $this->Characters->getCharacterForUserAndSeminary(self::$user['id'], self::$seminary['id']);
				}
			}
			catch(\nre\exceptions\IdNotFoundException $e) {
			}
			
			// Check permissions
			$this->checkPermission($request, $response);
			
			// Set userdata
			$this->set('loggedUser', self::$user);
			$this->set('loggedSeminary', self::$seminary);
			$this->set('loggedCharacter', self::$character);
		}
		
		
		/**
		 * Postfilter that is executed after running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function postFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::postFilter($request, $response);
		}
		
		
		
		
		/**
		 * Check user permissions.
		 * 
		 * @throws AccessDeniedException
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
				return;	// Allow if nothing is specified
			}
			if(!array_key_exists($action, $controller->permissions)) {
				return;	// Allow if Action is not specified
			}
			$permissions = $controller->permissions[$action];
			
			
			// Check permissions
			if(count(array_intersect($userRoles, $permissions)) == 0) {
				throw new \nre\exceptions\AccessDeniedException();
			}
		}
		
	}

?>
