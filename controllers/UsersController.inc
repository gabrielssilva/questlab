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
	 * Controller of the Agent to list registered users and their data.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class UsersController extends \hhu\z\controllers\IntermediateController
	{
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array('admin', 'moderator'),
			'user' => array('admin', 'moderator', 'user'),
			'create' => array('admin', 'moderator'),
			'edit' => array('admin', 'moderator', 'user'),
			'delete' => array('admin')
		);
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('users', 'userroles', 'characters', 'characterroles', 'avatars', 'media');
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('validation');
		
		
		
		
		/**
		 * Action: index.
		 */
		public function index()
		{
			// Get registered users
			$users = $this->Users->getUsers();
			
			
			// Set titile
			$this->addTitleLocalized('Users');
			
			// Pass data to view
			$this->set('users', $users);
		}
		
		
		/**
		 * Action: user.
		 * 
		 * Show a user and its details.
		 * 
		 * @throws	IdNotFoundException
		 * @throws	AccessDeniedException
		 * @param	string	$userUrl	URL-Username of an user
		 */
		public function user($userUrl)
		{
			// Get user
			$user = $this->Users->getUserByUrl($userUrl);
			
			// Check permissions
			if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) == 0 && $user['id'] != IntermediateController::$user['id']) {
				throw new \nre\exceptions\AccessDeniedException();
			}
			
			// Get Characters
			$characters = $this->Characters->getCharactersForUser($user['id']);
			
			// Additional Character information
			foreach($characters as &$character)
			{
				// Seminary roles
				$character['characterroles'] = $this->Characterroles->getCharacterrolesForCharacterById($character['id']);
				$character['characterroles'] = array_map(function($a) { return $a['name']; }, $character['characterroles']);
				
				// Level
				$character['xplevel'] = $this->Characters->getXPLevelOfCharacters($character['id']);
				
				// Avatar
				$avatar = $this->Avatars->getAvatarById($character['avatar_id']);
				if(!is_null($avatar['small_avatarpicture_id']))
				{
					//$character['seminary'] = 
					$character['small_avatar'] = $this->Media->getSeminaryMediaById($avatar['small_avatarpicture_id']);
				}
			}
			
			
			// Set titile
			$this->addTitleLocalized($user['username']);
			$this->addTitleLocalized('Users');
			
			// Pass data to view
			$this->set('user', $user);
			$this->set('characters', $characters);
		}
		
		
		/**
		 * Action: login.
		 * 
		 * Log in a user.
		 */
		public function login()
		{
			$username = '';
			$referrer = null;
			
			// Log the user in
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('login')))
			{
				$username = $this->request->getPostParam('username');
				$referrer = $this->request->getPostParam('referrer');
				$userId = $this->Users->login(
					$username,
					$this->request->getPostParam('password')
				);
			
				if(!is_null($userId))
				{
					$this->Auth->setUserId($userId);
					$user = $this->Users->getUserById($userId);
					
					if(!empty($referrer)) {
						$this->redirect($referrer);
					}
					else {
						$this->redirect($this->linker->link(array($user['url']), 1));
					}
				}
			}
			
			
			// Set titile
			$this->addTitleLocalized('Login');
			
			// Pass data to view
			$this->set('username', $username);
			$this->set('referrer', $referrer);
			$this->set('failed', ($this->request->getRequestMethod() == 'POST'));
		}
		
		
		/**
		 * Action: register.
		 * 
		 * Register a new user.
		 */
		public function register()
		{
			$username = '';
			$prename = '';
			$surname = '';
			$email = '';
			
			$fields = array('username', 'prename', 'surname', 'email', 'password');
			$validation = array();
			
			// Register a new user
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('register')))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$username = $this->request->getPostParam('username');
				if($this->Users->usernameExists($username)) {
					$validation = $this->Validation->addValidationResult($validation, 'username', 'exist', true);
				}
				$prename = $this->request->getPostParam('prename');
				$surname = $this->request->getPostParam('surname');
				$email = $this->request->getPostParam('email');
				if($this->Users->emailExists($email)) {
					$validation = $this->Validation->addValidationResult($validation, 'email', 'exist', true);
				}
				
				
				// Register
				if($validation === true)
				{
					$userId = $this->Users->createUser(
						$username,
						$prename,
						$surname,
						$email,
						$this->request->getPostParam('password')
					);
					$user = $this->Users->getUserById($userId);
					
					// Send mail
					$this->sendRegistrationMail($user);
					
					// Login
					$this->Auth->setUserId($userId);
					
					
					// Redirect to user page
					$this->redirect($this->linker->link(array($user['url']), 1));
				}
			}
			
			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}
			
			
			// Set titile
			$this->addTitleLocalized('Registration');
			
			// Pass data to view
			$this->set('username', $username);
			$this->set('prename', $prename);
			$this->set('surname', $surname);
			$this->set('email', $email);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}
		
		
		/**
		 * Action: logout.
		 *
		 * Log out a user.
		 */
		public function logout()
		{
			// Unset the currently logged in user
			$this->Auth->setUserId(null);
			
			// Redirect
			$this->redirect($this->linker->link(array()));
		}
		
		
		/**
		 * Action: manage.
		 * 
		 * Manage users.
		 */
		public function manage()
		{
			$selectedUsers = array();
			global $sortorder;
			
			if($this->request->getRequestMethod() == 'POST')
			{
				// Set sortorder
				$sortorder = $this->request->getPostParam('sortorder');
				
				// Do action
				$selectedUsers = $this->request->getPostParam('users');
				if(!is_array($selectedUsers)) {
					$selectedUsers = array();
				}
				if(!is_null($this->request->getPostParam('actions')) && count($this->request->getPostParam('actions')) > 0 && !is_null($this->request->getPostParam('users')) && count($this->request->getPostParam('users')) > 0)
				{
					$actions = $this->request->getPostParam('actions');
					$action = array_keys($actions)[0];
				
					switch($action)
					{
						// Add/remove role to/from Characters
						case 'addrole':
						case 'removerole':
							// Determine role and check permissions
							$role = null;
							switch($actions[$action])
							{
								case _('Admin'):
									if(!in_array('admin', \hhu\z\controllers\IntermediateController::$user['roles'])) {
										throw new \nre\exceptions\AccessDeniedException();
									}
									$role = 'admin';
								break;
								case _('Moderator'):
									if(!in_array('admin', \hhu\z\controllers\IntermediateController::$user['roles'])) {
										throw new \nre\exceptions\AccessDeniedException();
									}
									$role = 'moderator';
								break;
								case _('User'):
									if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) <= 0) {
										throw new \nre\exceptions\AccessDeniedException();
									}
									$role = 'user';
								break;
							}
							
							// Add role
							if($action == 'addrole') {
								foreach($selectedUsers as &$userId) {
									$this->Userroles->addUserroleToUser($userId, $role);
								}
							}
							// Remove role
							else {
								foreach($selectedUsers as &$userId) {
									$this->Userroles->removeUserroleFromUser($userId, $role);
								}
							}
						break;
					}
				}
			}
			
			// Get registered users
			$users = $this->Users->getUsers();
			foreach($users as &$user) {
				$user['roles'] = array_map(function($r) { return $r['name']; }, $this->Userroles->getUserrolesForUserById($user['id']));
			}
			
			// Sort users
			$sortorder = (!is_null($sortorder)) ? $sortorder : 'username';
			$sortMethod = 'sortUsersBy'.ucfirst(strtolower($sortorder));
			if(method_exists($this, $sortMethod)) {
				usort($users, array($this, $sortMethod));
			}
			else {
				throw new \nre\exceptions\ParamsNotValidException($sortorder);
			}
			
			
			// Set titile
			$this->addTitleLocalized('Manage users');
			
			// Pass data to view
			$this->set('users', $users);
			$this->set('selectedUsers', $selectedUsers);
			$this->set('sortorder', $sortorder);
		}
		
		
		/**
		 * Action: create.
		 * 
		 * Create a new user.
		 */
		public function create()
		{
			// Values
			$username = '';
			$prename = '';
			$surname = '';
			$email = '';
			$fields = array('username', 'prename', 'surname', 'email', 'password');
			$validation = array();
			
			// Create new user
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$username = $this->request->getPostParam('username');
				if($this->Users->usernameExists($username)) {
					$validation = $this->Validation->addValidationResult($validation, 'username', 'exist', true);
				}
				$prename = $this->request->getPostParam('prename');
				$surname = $this->request->getPostParam('surname');
				$email = $this->request->getPostParam('email');
				if($this->Users->emailExists($email)) {
					$validation = $this->Validation->addValidationResult($validation, 'email', 'exist', true);
				}
				
				// Create
				if($validation === true)
				{
					$userId = $this->Users->createUser(
						$this->request->getPostParam('username'),
						$this->request->getPostParam('prename'),
						$this->request->getPostParam('surname'),
						$this->request->getPostParam('email'),
						$this->request->getPostParam('password')
					);
				
					// Redirect to user
					$user = $this->Users->getUserById($userId);
					$this->redirect($this->linker->link(array($user['url']), 1));
				}
			}
			
			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}
			
			
			// Set titile
			$this->addTitleLocalized('New user');
			
			// Pass data to view
			$this->set('username', $username);
			$this->set('prename', $prename);
			$this->set('surname', $surname);
			$this->set('email', $email);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}
		
		
		/**
		 * Action: edit.
		 * 
		 * Edit a user.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$userUrl	URL-Username of an user
		 */
		public function edit($userUrl)
		{
			// User
			$user = $this->Users->getUserByUrl($userUrl);
			
			// Check permissions
			if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) == 0 && $user['id'] != \hhu\z\controllers\IntermediateController::$user['id']) {
				throw new \nre\exceptions\AccessDeniedException();
			}
			
			// Values
			$username = $user['username'];
			$prename = $user['prename'];
			$surname = $user['surname'];
			$email = $user['email'];
			$fields = array('username', 'prename', 'surname', 'email');
			$validation = array();
			
			// Edit user
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('save')))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$username = $this->request->getPostParam('username');
				if($this->Users->usernameExists($username, $user['id'])) {
					$validation = $this->Validation->addValidationResult($validation, 'username', 'exist', true);
				}
				$password = $this->request->getPostParam('password');
				if(!empty($password)) {
					$validation = $this->Validation->addValidationResults($validation,
						'password',
						$this->Validation->validateParam(
							$this->request->getPostParams(),
							'password'
						)
					);
				}
				$prename = $this->request->getPostParam('prename');
				$surname = $this->request->getPostParam('surname');
				$email = $this->request->getPostParam('email');
				if($this->Users->emailExists($email, $user['id'])) {
					$validation = $this->Validation->addValidationResult($validation, 'email', 'exist', true);
				}
				
				// Save changes
				if($validation === true)
				{
					// Edit user
					$this->Users->editUser(
						$user['id'],
						(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) ? $this->request->getPostParam('username') : $user['username'],
						$this->request->getPostParam('prename'),
						$this->request->getPostParam('surname'),
						$this->request->getPostParam('email'),
						$this->request->getPostParam('password')
					);
					
					// Redirect to entry
					$user = $this->Users->getUserById($user['id']);
					$this->redirect($this->linker->link(array('user', $user['url']), 1));
				}
			}
			
			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}
			
			
			// Set titile
			$this->addTitleLocalized('Edit user');
			
			// Pass data to view
			$this->set('username', $username);
			$this->set('prename', $prename);
			$this->set('surname', $surname);
			$this->set('email', $email);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}
		
		
		/**
		 * Action: delete.
		 * 
		 * Delete a user.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$userUrl	URL-Username of an user
		 */
		public function delete($userUrl)
		{
			// User
			$user = $this->Users->getUserByUrl($userUrl);
			
			// Check request method
			if($this->request->getRequestMethod() == 'POST')
			{
				// Check confirmation
				if(!is_null($this->request->getPostParam('delete')))
				{
					// Delete user
					$this->Users->deleteUser($user['id']);
					
					// Redirect to overview
					$this->redirect($this->linker->link(null, 1));
				}
				
				// Redirect to entry
				$this->redirect($this->linker->link(array('user', $user['url']), 1));
			}
			
			
			// Set titile
			$this->addTitleLocalized('Delete user');
			
			// Show confirmation
			$this->set('user', $user);
		}
		
		
		
		
		/**
		 * Send mail for new user registration.
		 * 
		 * @param	string	$username	Name of newly registered user
		 * @param	string	$email		E‑mail address of newly registered user
		 */
		private function sendRegistrationMail($user)
		{
			// Get system moderators
			$moderators = $this->Users->getUsersWithRole('moderator');
			
			// Send notification mail
			try {
				foreach($moderators as &$moderator)
				{
					\hhu\z\Utils::sendMail(
						$moderator['email'],
						'userregistration',
						true,
						array(
							$moderator,
							$user
						),
						$this->linker
					);
				}
			}
			catch(\hhu\z\exceptions\MailingException $e) {
				$this->log($e->getMessage());
			}
		}
		
		
		/**
		 * Compare two users by their username.
		 * 
		 * @param	array	$a	User a
		 * @param	array	$b	User b
		 * @return	int		Result of comparison
		 */
		private function sortUsersByUsername($a, $b)
		{
			if($a['username'] == $b['username']) {
				return 0;
			}
			
			
			return ($a['username'] < $b['username']) ? -1 : 1;
		}
		
		
		/**
		 * Compare two users by their userroles.
		 * 
		 * @param	array	$a	User a
		 * @param	array	$b	User b
		 * @return	int		Result of comparison
		 */
		private function sortUsersByRole($a, $b)
		{
			if(in_array('admin', $a['roles']))
			{
				if(in_array('admin', $b['roles'])) {
					return 0;
				}
				return -1;
			}
			if(in_array('moderator', $a['roles']))
			{
				if(in_array('admin', $b['roles'])) {
					return 1;
				}
				if(in_array('moderator', $b['roles'])) {
					return 0;
				}
				return -1;
			}
			if(in_array('user', $a['roles']))
			{
				if(in_array('admin', $b['roles']) || in_array('moderator', $b['roles'])) {
					return 1;
				}
				if(in_array('user', $b['roles'])) {
					return 0;
				}
				return -1;
			}
			if(in_array('guest', $a['roles']))
			{
				if(in_array('admin', $b['roles']) || in_array('moderator', $b['roles'])  || in_array('user', $b['roles'])) {
					return 1;
				}
				if(in_array('guest', $b['roles'])) {
					return 0;
				}
				return -1;
			}
			
			
			return 1;
		}
		
		
		/**
		 * Compare two users by their registration date.
		 * 
		 * @param	array	$a	User a
		 * @param	array	$b	User b
		 * @return	int		Result of comparison
		 */
		private function sortUsersByDate($a, $b)
		{
			if($a['created'] == $b['created']) {
				return 0;
			}
			
			
			return ($a['created'] > $b['created']) ? -1 : 1;
		}
		
	}

?>
