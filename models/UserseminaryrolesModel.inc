<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\models;
	
	
	/**
	 * Model to interact with userseminaryroles-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class UserseminaryrolesModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new UserseminaryrolesModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all userseminaryroles for an user referenced by its ID.
		 * 
		 * @param	int	$userId	ID of an user
		 * @return	array		Userseminaryroles for an user
		 */
		public function getUserseminaryrolesForUserById($userId, $seminaryId)
		{
			return $this->db->query(
				'SELECT userseminaryroles.id, userseminaryroles.created, userseminaryroles.name '.
				'FROM users_userseminaryroles '.
				'LEFT JOIN userseminaryroles ON userseminaryroles.id = users_userseminaryroles.userseminaryrole_id '.
				'WHERE users_userseminaryroles.user_id = ? AND users_userseminaryroles.seminary_id = ?',
				'ii',
				$userId, $seminaryId
			);
		}
		
		
		/**
		 * Get all userseminaryroles for an user referenced by its
		 * URL-username.
		 * 
		 * @param	string	$userUrl	URL-Username of an user
		 * @return	array			Userseminaryroles for an user
		 */
		public function getUserrolesForUserByUrl($userUrl)
		{
			return $this->db->query(
				'SELECT userroles.id, userroles.created, userroles.name '.
				'FROM users '.
				'LEFT JOIN users_userseminaryroles ON users_userseminaryroles.user_id = users.id '.
				'LEFT JOIN userseminaryroles ON userseminaryroles.id = users_userseminaryroles.userseminaryrole_id '.
				'WHERE users.url = ?',
				's',
				$userUrl
			);
		}
		
	}

?>
