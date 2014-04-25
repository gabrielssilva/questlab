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
	 * Controller of the Agent to display and manage userroles.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class UserrolesController extends \hhu\z\Controller
	{
		
		
		
		
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
			// Get userroles
			$roles = $this->Userroles->getUserrolesForUserByUrl($userUrl);
			
			
			// Pass data to view
			$this->set('roles', $roles);
		}
		
		
	}

?>
