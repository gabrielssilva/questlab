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
	 * Abstract class for implementing a Controller for a Seminary and its
	 * concepts.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	abstract class SeminaryRoleController extends \hhu\z\controllers\IntermediateController
	{
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('achievement', 'auth');
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'userseminaryroles', 'characters', 'achievements');
		/**
		 * Data of currently logged in user if any
		 * 
		 * @var array
		 */
		public static $user = null;
		
		
		
		
		/**
		 * Construct a new SeminaryRole Controller.
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
			
			// Check permissions
			$this->checkPermission($request, $response);
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
			// Do not check index page
			if(is_null($request->getParam(3))) {
				return;
			}
			
			// Determine user and seminary
			$userId = $this->Auth->getUserId();
			$seminary = $this->Seminaries->getSeminaryByUrl($request->getParam(3));
			
			// Determine user seminary roles
			$userSeminaryRoles = array();
			$roles = $this->Userseminaryroles->getUserseminaryrolesForUserById($userId, $seminary['id']);
			foreach($roles as &$role) {
				$userSeminaryRoles[] = $role['name'];
			}
			
			
			// Determine permissions for current action
			$action = $this->request->getParam(2, 'action');
			if(!property_exists($this, 'seminaryPermissions')) {
				return;	// Allow if nothing is specified
			}
			if(!array_key_exists($action, $this->seminaryPermissions)) {
				return;	// Allow if Action is not specified
			}
			$permissions = $this->seminaryPermissions[$action];
			
			
			// Check permissions
			if(count(array_intersect($userSeminaryRoles, $permissions)) == 0) {
				throw new \nre\exceptions\AccessDeniedException();
			}
		}
		
	}

?>
