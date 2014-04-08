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
			'edit' => array('admin', 'moderator'),
			'delete' => array('admin')
		);
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('users', 'characters');
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
			
			// Log the user in
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('login')))
			{
				$username = $this->request->getPostParam('username');
				$userId = $this->Users->login(
					$username,
					$this->request->getPostParam('password')
				);
			
				if(!is_null($userId))
				{
					$this->Auth->setUserId($userId);
					$user = $this->Users->getUserById($userId);
			
					$this->redirect($this->linker->link(array($user['url']), 1));
				}
			}
			
			
			// Pass data to view
			$this->set('username', $username);
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
				$prename = $this->request->getPostParam('prename');
				$surname = $this->request->getPostParam('surname');
				$email = $this->request->getPostParam('email');
				
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
			
					// Login
					$this->Auth->setUserId($userId);
					$user = $this->Users->getUserById($userId);
			
					// Redirect to user page
					$this->redirect($this->linker->link(array($user['url']), 1));
				}
			}
			
			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}
			
			
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
		 * Action: create.
		 * 
		 * Create a new user.
		 */
		public function create()
		{
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// Create new user
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
			
			// Check request method
			if($this->request->getRequestMethod() == 'POST')
			{
				// Save changes
				if(!is_null($this->request->getPostParam('save')))
				{
					// Edit user
					$this->Users->editUser(
						$user['id'],
						$this->request->getPostParam('username'),
						$this->request->getPostParam('prename'),
						$this->request->getPostParam('surname'),
						$this->request->getPostParam('email'),
						$this->request->getPostParam('password')
					);
					$user = $this->Users->getUserById($user['id']);
				}
				
				
				// Redirect to entry
				$this->redirect($this->linker->link(array($user['url']), 1));
			}
			
			
			// Pass data to view
			$this->set('user', $user);
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
			
			
			// Show confirmation
			$this->set('user', $user);
		}
		
		
	}

?>
