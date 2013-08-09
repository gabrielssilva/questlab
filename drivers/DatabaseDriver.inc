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
	 * Abstract class for implementing a database driver.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	abstract class DatabaseDriver extends \nre\core\Driver
	{
		/**
		 * Connection and login settings
		 * 
		 * @var array
		 */
		protected $config;
		/**
		 * Connection resource
		 * 
		 * @var resource
		 */
		protected $connection = null;
		
		
		
		
		/**
		 * Execute a SQL-query.
		 * 
		 * @param	string	$query	Query to run
		 * @return	array		Result
		 */
		public abstract function query($query);
		
				
		/**
		 * Return the last insert id (of the last insert-query).
		 * 
		 * @return	int	Last insert id
		 */
		public abstract function getInsertId();
		
		
		/**
		 * Mask an input for using it in a SQL-query.
		 * 
		 * @param	mixed	$input	Input to mask
		 * @return	mixed		Masked input
		 */
		public abstract function mask($input);
		
		
		
		
		/**
		 * Construct a new database driver.
		 * 
		 * @param	array	$config	Connection and login settings
		 */
		protected function __construct($config)
		{
			parent::__construct();
			
			// Save values
			$this->config = $config;
		}
		
	}

?>
