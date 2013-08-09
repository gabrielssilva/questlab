<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	
	namespace nre\models;
	
	
	/**
	 * Default implementation of a database model.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class DatabaseModel extends \nre\core\Model
	{
		
		/**
		 * Database connection
		 * 
		 * @static
		 * @var object
		 */
		private static $db = NULL;
		
		
		
		
		/**
		 * Construct a new datamase model.
		 * 
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @throws	DatamodelException
		 * @param	string	$databaseType	Database type
		 * @param	array	$config		Connection settings
		 */
		function __construct($databaseType, $config)
		{
			parent::__construct();
			
			// Load database driver
			$this->loadDriver($databaseType);
			
			// Establish database connection
			$this->connect($databaseType, $config);
		}
		
		
		
		
		/**
		 * Execute a SQL-query.
		 * 
		 * @param	string	$query	Query to run
		 * @param	mixed	…	Query parameters
		 * @return	array		Result
		 */
		protected function query($query)
		{
			// Mask parameters
			$args = array($query);
			foreach(array_slice(func_get_args(), 1) as $arg) {
				$args[] = self::$db->mask($arg);
			}
			
			// Format query
			$query = call_user_func_array(
				'sprintf',
				$args
			);
			
			// Execute query
			$data = self::$db->query($query);
			
			
			// Return data
			return $data;
		}
		
		
		/**
		 * Return the last insert id (of the last insert-query).
		 * 
		 * @return	int	Last insert id
		 */
		protected function getInsertId()
		{
			return self::$db->getInsertId();
		}
		
		
		
		
		/**
		 * Load the database driver.
		 * 
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @param	string	$driverName	Name of the database driver
		 */
		private static function loadDriver($driverName)
		{
			\nre\core\Driver::load($driverName);
			
		}
		
		
		/**
		 * Establish a connection to the database.
		 * 
		 * @throws	DatamodelException
		 * @param	string	$driverName	Name of the database driver
		 */
		private static function connect($driverName, $config)
		{
			if(self::$db === NULL) {
				self::$db = \nre\core\Driver::factory($driverName, $config);
			}
		}
		
	}

?>
