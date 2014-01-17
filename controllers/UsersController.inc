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
	class UsersController extends \hhu\z\Controller
	{
		
		
		
		
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
		 * @param	string	$userUrl	URL-Username of an user
		 */
		public function user($userUrl)
		{
			// Get user
			$user = $this->Users->getUserByUrl($userUrl);
			
			
			// Pass data to view
			$this->set('user', $user);
		}
		
		
	}

?>
