<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\controllers\components;
	
	
	/**
	 * Component to handle authentication and authorization.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class AuthComponent extends \nre\core\Component
	{
		/**
		 * Key to save a user-ID as
		 * 
		 * @var string
		 */
		const KEY_USER_ID = 'user_id';
		
		
		
		
		/**
		 * Construct a new Auth-component.
		 */
		public function __construct()
		{
			// Start session
			if(session_id() === '') {
				session_start();
			}
		}
		
		
		
		
		/**
		 * Set the ID of the user that is currently logged in.
		 * 
		 * @param	int	$userId	ID of the currently logged in user
		 */
		public function setUserId($userId)
		{
			if(is_null($userId)) {
				unset($_SESSION[self::KEY_USER_ID]);
			}
			else {
				$_SESSION[self::KEY_USER_ID] = $userId;
			}
		}
		
		
		/**
		 * Get the ID of the user that is currently logged in.
		 * 
		 * @return	int	ID of the currently logged in user
		 */
		public function getUserId()
		{
			if(array_key_exists(self::KEY_USER_ID, $_SESSION)) {
				return $_SESSION[self::KEY_USER_ID];
			}
		
			
			return null;
		}
	
	}

?>
