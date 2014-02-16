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
	 * Abstract class for implementing a Controller of a ToplevelAgent.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	abstract class ToplevelController extends \hhu\z\Controller
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
		 * 
		 */
		public static $seminary = null;
		/**
		 * Character of current user and Seminary
		 * 
		 * @var array
		 */
		public static $character = null;
		
		
		
		
		/**
		 * Construct a new application Controller.
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
				static::$user = $this->Users->getUserById($this->Auth->getUserId());
				
				// Character
				$controller = $this->agent->getIntermediateAgent()->controller;
				if(in_array(\hhu\z\controllers\SeminaryRoleController::class, class_parents($controller)))
				{
					$seminaryUrl = $this->request->getParam(3);
					static::$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
					static::$character = $this->Characters->getCharacterForUserAndSeminary(static::$user['id'], static::$seminary['id']);
				}
			}
			catch(\nre\exceptions\IdNotFoundException $e) {
			}
			
			// Check permissions
			$this->checkPermission($request, $response);
			
			// Set userdata
			$this->set('loggedUser', static::$user);
			$this->set('loggedSeminary', static::$seminary);
			$this->set('loggedCharacter', static::$character);
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
			$userId = $this->Auth->getUserId();
			
			
			// Do not check error pages
			if($response->getParam(0, 'toplevel') == \nre\core\Config::getDefault('toplevel-error')) {
				return;
			}
			if($response->getParam(1, 'intermediate') == \nre\core\Config::getDefault('intermediate-error')) {
				return;
			}
			
			
			// Determine user roles
			if($userId > 0)
			{
				$userRoles = array();
				$roles = $this->Userroles->getUserrolesForUserById($userId);
				foreach($roles as &$role) {
					$userRoles[] = $role['name'];
				}
			}
			else {
				$userRoles = array('guest');
			}
			
			// Determine permissions of Intermediate Controller for current action
			$controller = $this->agent->getIntermediateAgent()->controller;
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
