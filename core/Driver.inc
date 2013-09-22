<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	
	namespace nre\core;
	
	
	/**
	 * Abstract class for implementing a Driver.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	abstract class Driver
	{
		
		
		
		
		/**
		 * Load the class of a Driver.
		 * 
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @param	string	$driverName	Name of the Driver to load
		 */
		public static function load($driverName)
		{
			// Determine full classname
			$className = self::getClassName($driverName);
			
			try {
				// Load class
				ClassLoader::load($className);
				
				// Validate class
				ClassLoader::check($className, get_class());
			}
			catch(\nre\exceptions\ClassNotValidException $e) {
				throw new \nre\exceptions\DriverNotValidException($e->getClassName());
			}
			catch(\nre\exceptions\ClassNotFoundException $e) {
				throw new \nre\exceptions\DriverNotFoundException($e->getClassName());
			}
		}
		
		
		/**
		 * Instantiate a Driver (Factory Pattern).
		 * 
		 * @param	string	$driverName	Name of the Driver to instantiate
		 */
		public static function factory($driverName, $config)
		{
			// Determine full classname
			$className = self::getClassName($driverName);
			
			
			// Construct and return Driver
			return new $className($config);
		}
		
		
		/**
		 * Determine the classname for the given Driver name.
		 * 
		 * @param	string	$driverName	Driver name to get classname of
		 * @return	string			Classname fore the Driver name
		 */
		private static function getClassName($driverName)
		{
			$className = ClassLoader::concatClassNames($driverName, ClassLoader::stripNamespace(get_class()));
			
			
			return "\\nre\\drivers\\$className";
		}
		
		
		
		
		/**
		 * Construct a new Driver.
		 */
		protected function __construct()
		{
		}
		
	}

?>
