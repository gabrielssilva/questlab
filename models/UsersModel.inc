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
	 * Model of the UsersAgent to list users and get their data.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class UsersModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new UsersModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get registered users.
		 * 
		 * @return	array	Users
		 */
		public function getUsers()
		{
			return $this->db->query(
				'SELECT id, created, username, url, surname, prename, email '.
				'FROM users '.
				'ORDER BY username ASC'
			);
		}
		
		
		/**
		 * Get a user and its data by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$userId	ID of an user
		 * @return	array		Userdata
		 */
		public function getUserById($userId)
		{			
			// Get user
			$user = $this->db->query(
				'SELECT id, created, username, url, surname, prename, email '.
				'FROM users '.
				'WHERE id = ?',
				'i',
				$userId
			);
			if(empty($user)) {
				throw new \nre\exceptions\IdNotFoundException($userId);
			}
			
			
			return $user[0];
		}
		
		
		/**
		 * Get a user and its data by its URL-username.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$userUrl	URL-Username of an user
		 * @return	array			Userdata
		 */
		public function getUserByUrl($userUrl)
		{			
			// Get user
			$user = $this->db->query(
				'SELECT id, created, username, url, surname, prename, email '.
				'FROM users '.
				'WHERE url = ?',
				's',
				$userUrl
			);
			if(empty($user)) {
				throw new \nre\exceptions\IdNotFoundException($userUrl);
			}
			
			
			return $user[0];
		}
		
	}

?>
