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
		 * Get count of registered users.
		 * 
		 * @param	string	$username	Only get users with the given username (optional)
		 * @return	int			Count of users
		 */
		public function getUsersCount($username=null)
		{
			$data = $this->db->query(
				'SELECT count(DISTINCT id) AS c '.
				'FROM users '.
				(!is_null($username) ? sprintf('WHERE username LIKE \'%%%s%%\'', $username) : null )
			);
			if(!empty($data)) {
				return $data[0]['c'];
			}
			
			
			return 0;
		}
		
		
		/**
		 * Get registered users.
		 * 
		 * @throws	\nre\exceptions\ParamsNotValidException
		 * @param	string	$sort		Field to sort by
		 * @param	string	$username	Only get users with the given username (optional)
		 * @param	int	$limit		Limit amount of Characters (optional)
		 * @param	int	$offset		Offset (optional)
		 * @return	array			Users
		 */
		public function getUsers($sort, $username=null, $limit=null, $offset=0)
		{
			switch($sort)
			{
				case 'username':
				case 'created':
					$orders = array(
						'username'	=> 'ASC',
						'created'	=> 'DESC'
					);
					
					return $this->db->query(
						'SELECT id, created, username, url, surname, prename, email, mailing '.
						'FROM users '.
						(!is_null($username) ? sprintf('WHERE username LIKE \'%%%s%%\' ', $username) : null).
						sprintf('ORDER BY %s %s ', $sort, $orders[$sort]).
						(!empty($limit) ? sprintf('LIMIT %d, %d', $offset, $limit) : null)
					);
				break;
				case 'role':
					return $this->db->query(
						'SELECT DISTINCT users.id, users.created, users.username, users.url, users.surname, users.prename, users.email, users.mailing '.
						'FROM users '.
						'LEFT JOIN users_userroles ON users_userroles.user_id = users.id '.
						'LEFT JOIN userroles ON userroles.id = users_userroles.user_id '.
						(!is_null($username) ? sprintf('WHERE username LIKE \'%%%s%%\' ', $username) : null).
						'ORDER BY userroles.id IS NULL, userroles.id ASC '.
						(!empty($limit) ? sprintf('LIMIT %d, %d', $offset, $limit) : null)
					);
				break;
				default:
					throw new \nre\exceptions\ParamsNotValidException($sort);
				break;
			}
		}
		
		
		/**
		 * Get users with the given user role.
		 * 
		 * @param	string	$userrole	User role
		 * @return	array			List of users
		 */
		public function getUsersWithRole($userrole)
		{
			return $this->db->query(
				'SELECT users.id, users.created, users.username, users.url, users.surname, users.prename, users.email, users.mailing'.
				'FROM users '.
				'LEFT JOIN users_userroles ON users_userroles.user_id = users.id '.
				'LEFT JOIN userroles ON userroles.id = users_userroles.userrole_id '.
				'WHERE userroles.name = ? '.
				'ORDER BY username ASC',
				's',
				$userrole
			);
		}
		
		
		/**
		 * Get a user and its data by its ID.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	int	$userId	ID of an user
		 * @return	array		Userdata
		 */
		public function getUserById($userId)
		{			
			// Get user
			$user = $this->db->query(
				'SELECT id, created, username, url, surname, prename, email, mailing '.
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
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$userUrl	URL-Username of an user
		 * @return	array			Userdata
		 */
		public function getUserByUrl($userUrl)
		{			
			// Get user
			$user = $this->db->query(
				'SELECT id, created, username, url, surname, prename, email, mailing '.
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
		 * @throws	\nre\exceptions\DatamodelException
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
		 * Check if an username already exists.
		 * 
		 * @param	string	$username	Username to check
		 * @param	int	$userId		Do not check this ID (for editing)
		 * @return	boolean			Whether username exists or not
		 */
		public function usernameExists($username, $userId=null)
		{
			$data = $this->db->query(
				'SELECT id '.
				'FROM users '.
				'WHERE username = ? OR url = ?',
				'ss',
				$username,
				\nre\core\Linker::createLinkParam($username)
			);
			
			
			return (!empty($data) && (is_null($userId) || $userId != $data[0]['id']));
		}
		
		
		/**
		 * Check if an e‑mail address already exists.
		 * 
		 * @param	string	$email	E‑mail address to check
		 * @param	int	$userId	Do not check this ID (for editing)
		 * @return	boolean		Whether e‑mail address exists or not
		 */
		public function emailExists($email, $userId=null)
		{
			$data = $this->db->query(
				'SELECT id '.
				'FROM users '.
				'WHERE email = ?',
				's',
				$email
			);
			
			
			return (!empty($data) && (is_null($userId) || $userId != $data[0]['id']));
		}
		
		
		/**
		 * Create a new user.
		 * 
		 * @param	string	$username	Username of the user to create
		 * @param	string	$prename	Prename of the user to create
		 * @param	string	$surname	Surname of the user to create
		 * @param	string	$email		E‑Mail-Address of the user to create
		 * @param	string	$password	Password of the user to create
		 * @return	int			ID of the newly created user
		 */
		public function createUser($username, $prename, $surname, $email, $password)
		{
			$userId = null;
			$this->db->setAutocommit(false);
			try {
				// Create user
				$this->db->query(
					'INSERT INTO users '.
					'(username, url, surname, prename, email, password) '.
					'VALUES '.
					'(?, ?, ?, ?, ?, ?)',
					'ssssss',
					$username,
					\nre\core\Linker::createLinkParam($username),
					$surname,
					$prename,
					$email,
					$this->hash($password)
				);
				$userId = $this->db->getInsertId();
				
				// Add role “user”
				$this->db->query(
					'INSERT INTO users_userroles '.
					'(user_id, userrole_id) '.
					'SELECT ?, userroles.id '.
					'FROM userroles '.
					'WHERE userroles.name = ?',
					'is',
					$userId,
					'user'
				);
			}
			catch(Exception $e) {
				$this->db->rollback();
				$this->db->setAutocommit(true);
				throw $e;
			}
			$this->db->setAutocommit(true);
			
			
			return $userId;
		}
		
		
		/**
		 * Edit a user.
		 * 
		 * @throws	\nre\exceptions\DatamodelException
		 * @param	int	$userId		ID of the user to delete
		 * @param	string	$username	New name of user
		 * @param	string	$prename	Prename of the user to create
		 * @param	string	$surname	Surname of the user to create
		 * @param	string	$email		Changed e‑mail-address of user
		 * @param	string	$password	Changed plaintext password of user
		 * @param	bool	$mailing	Whether to activate mailing or not
		 */
		public function editUser($userId, $username, $prename, $surname, $email, $password, $mailing)
		{
			$this->db->setAutocommit(false);
			try {
				// Update user data
				$this->db->query(
					'UPDATE users '.
					'SET username = ?, url = ?, prename = ?, surname = ?, email = ?, mailing = ? '.
					'WHERE id = ?',
					'sssssii',
					$username,
					\nre\core\Linker::createLinkParam($username),
					$prename,
					$surname,
					$email,
					$mailing,
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
			if(!function_exists('password_hash')) {
				\hhu\z\lib\Password::load();
			}
			
			
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
			if(!function_exists('password_verify')) {
				\hhu\z\lib\Password::load();
			}
			
			
			return password_verify($password, $hash);
		}
		
	}

?>
