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
	 * Class for safely loading classes.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class ClassLoader
	{
		
		
		
		
		/**
		 * Load a class.
		 * 
		 * @throws	ClassNotFoundException
		 * @param	string		$fullClassName	Name of the class to load
		 */
		public static function load($fullClassName)
		{
			// Determine folder to look in
			$className = explode('\\', $fullClassName);
			$className = array_slice($className, substr_count(\nre\configs\AppConfig::$app['namespace'], '\\'));
			
			// Determine filename
			$fileName = ROOT.DS.implode(DS, $className). \nre\configs\CoreConfig::getFileExt('includes');
			
			
			// Check file
			if(!file_exists($fileName))
			{
				throw new \nre\exceptions\ClassNotFoundException(
					$fullClassName
				);
			}
			
			// Include file
			include_once($fileName);
		}
		
		
		/**
		 * Check inheritance of a class.
		 * 
		 * @throws	ClassNotValidException
		 * @param	string	$className		Name of the class to check
		 * @param	string	$parentClassName	Name of the parent class
		 */
		public static function check($className, $parentClassName)
		{
			// Check if class is subclass of parent class
			if(!is_subclass_of($className, $parentClassName)) {
				throw new \nre\exceptions\ClassNotValidException(
					$className
				);
			}
		}
		
		
		/**
		 * Strip the namespace from a class name.
		 * 
		 * @param	string	$class	Name of a class including its namespace
		 * @return			Name of the given class without its namespace
		 */
		public static function stripNamespace($class)
		{
			return array_slice(explode('\\', $class), -1)[0];
		}
		
		
		/**
		 * Strip the class type from a class name.
		 * 
		 * @param	string	$className	Name of a class
		 * @return				Name of the given class without its class type
		 */
		public static function stripClassType($className)
		{
			return preg_replace('/^(.*)[A-Z][^A-Z]+$/', '$1', $className);
		}
		
		
		/**
		 * Strip the namespace and the class type of a full class name
		 * to get only its name.
		 * 
		 * @param	string	$class	Full name of a class
		 * @return			Only the name of the given class
		 */
		public static function getClassName($class)
		{
			return self::stripClassType(self::stripNamespace($class));
		}
		
		
		/**
		 * Concatenate strings to a class name following the CamelCase
		 * pattern.
		 * 
		 * @param	string	$className1	Arbitrary number of strings to concat
		 * @return	string			Class name as CamelCase
		 */
		public static function concatClassNames($className1)
		{
			return implode('', array_map(
				function($arg) {
					return ucfirst(strtolower($arg));
				},
				func_get_args()
			));
		}
		
	}

?>
