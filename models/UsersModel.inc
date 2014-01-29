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
		
		
		/**
		 * Log a user in if its credentials are valid.
		 * 
		 * @throws	DatamodelException
		 * @param	string	$username	The name of the user to log in
		 * @param	string	$password	Plaintext password of the user to log in
		 */
		public function login($username, $password)
		{
			$data = $this->db->query('SELECT id, password FROM users WHERE username = ?', 's', $username);
			if(!empty($data))
			{
				$data = $data[0];
				if($this->verify($password, $data['password'])) {
					return $data['id'];
				}
			}
			
			
			return null;
		}
		
		
		/**
		 * Create a new user.
		 * 
		 * @param	string	$username	Username of the user to create
		 * @param	string	$email		E‑Mail-Address of the user to create
		 * @param	string	$password	Password of the user to create
		 * @return	int			ID of the newly created user
		 */
		public function createUser($username, $email, $password)
		{
			$this->db->query(
				'INSERT INTO users '.
				'(username, url, email, password) '.
				'VALUES '.
				'(?, ?, ?, ?)',
				'ssss',
				$username,
				\nre\core\Linker::createLinkParam($username),
				$email,
				$this->hash($password)
			);
			
			
			return $this->db->getInsertId();
		}
		
		
		/**
		 * Edit a user.
		 * 
		 * @throws	DatamodelException
		 * @param	int	$userId		ID of the user to delete
		 * @param	string	$username	New name of user
		 * @param	string	$email		Changed e‑mail-address of user
		 * @param	string	$password	Changed plaintext password of user
		 */
		public function editUser($userId, $username, $email, $password)
		{
			try {
				// Update user data
				$this->db->query(
					'UPDATE users '.
					'SET username = ?, url = ?, email = ? '.
					'WHERE id = ?',
					'sssi',
					$username,
					\nre\core\Linker::createLinkParam($username),
					$email,
					$userId
				);
				
				// Set new password
				if(!empty($password))
				{
					$this->db->query(
						'UPDATE users '.
						'SET password = ? '.
						'WHERE id = ?',
						'si',
						$this->hash($password),
						$userId
					);
				}
			}
			catch(Exception $e) {
				$this->db->rollback();
				$this->db->setAutocommit(true);
				throw $e;
			}
			$this->db->setAutocommit(true);
		}
		
		
		/**
		 * Delete a user.
		 * 
		 * @param	int	$userId	ID of the user to delete
		 */
		public function deleteUser($userId)
		{
			$this->db->query('DELETE FROM users WHERE id = ?', 'i', $userId);
		}
		
		
		
		
		/**
		 * Hash a password.
		 * 
		 * @param	string	$password	Plaintext password
		 * @return	string			Hashed password
		 */
		public function hash($password)
		{
			return password_hash($password, PASSWORD_DEFAULT);
		}
		
		
		/**
		 * Verify a password.
		 * 
		 * @param	string	$password	Plaintext password to verify
		 * @param	string	$hash		Hashed password to match with
		 * @return	boolean			Verified
		 */
		private function verify($password, $hash)
		{
			return password_verify($password, $hash);
		}
		
	}

?>
