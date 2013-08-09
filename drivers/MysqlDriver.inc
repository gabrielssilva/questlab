<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	
	namespace nre\drivers;
	
	
	/**
	 * Implementation of a database driver for MySQL-databases.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class MysqlDriver extends \nre\drivers\DatabaseDriver
	{
		
		
		
		
		/**
		 * Construct a MySQL-driver.
		 * 
		 * @throws	DatamodelException
		 * @param	array	$config	Connection and login settings
		 */
		function __construct($config)
		{
			parent::__construct($config);
			
			// Connect
			$this->connect();
		}
		
		
		
		
		/**
		 * Execute a SQL-query.
		 * 
		 * @param	string	$query	Query to run
		 * @return	array		Result
		 */
		public function	query($query)
		{
			// Return-array
			$data = array();
			
			
			// Execute query
			$result = mysql_query($query, $this->connection);
			
			// Check result
			if(($errno = mysql_errno($this->connection)) > 0) {
				throw new DatamodelException(mysql_error($this->connection), $errno);
			}
			
			// Process result
			if(is_resource($result))
			{
				while($row = mysql_fetch_array($result, MYSQL_ASSOC)) {
					$data[] = $row;
				}
			}
			
			
			// Return data
			return $data;
		}
		
		
		/**
		 * Return the last insert id (of the last insert-query).
		 * 
		 * @return	int	Last insert id
		 */
		public function getInsertId()
		{
			return mysql_insert_id($this->connection);
		}
		
		
		/**
		 * Mask an input for using it in a SQL-query.
		 * 
		 * @param	mixed	$input	Input to mask
		 * @return	mixed		Masked input
		 */
		public function mask($input)
		{
			return mysql_real_escape_string($input, $this->connection);
		}
		
		
		
		
		/**
		 * Establish a connect to a MqSQL-database.
		 * 
		 * @throws	DatamodelException
		 */
		private function connect()
		{
			// Connect
			$con = @mysql_connect(
				$this->config['host'],
				$this->config['user'],
				$this->config['password']
			);
			
			// Check connection
			if($con === false) {
				throw new \nre\exceptions\DatamodelException(mysql_error(), mysql_errno());
			}
			
			// Save connection
			$this->connection = $con;
			
			
			// Select database
			$db = mysql_select_db(
				$this->config['db'],
				$this->connection
			);
			
			// Check database selection
			if(!$db) {
				throw new DatamodelException(mysql_error(), mysql_errno());
			}
			
			
			// Configure connection
			$this->configConnection();
		}
		
		
		/**
		 * Configure the current connection
		 */
		private function configConnection()
		{
			// Set character encoding
			$this->query("SET NAMES 'utf8'", $this->connection);
		}
		
	}

?>
