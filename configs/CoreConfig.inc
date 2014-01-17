<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	
	namespace nre\configs;
	
	
	/**
	 * Core configuration.
	 * 
	 * This class contains static variables with configuration values.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	final class CoreConfig
	{
		
		/**
		 * Core values
		 * 
		 * @static
		 * @var array
		 */
		public static $core = array(
			'namespace'		=>	'nre\\',
		);
		
		
		/**
		 * Directories
		 * 
		 * @static
		 * @var array
		 */
		public static $dirs = array(
			'core'		=>	'core',
			'publicDir'	=>	'www'
		);
		
		
		/**
		 * File extensions
		 * 
		 * @static
		 * @var array
		 */
		public static $fileExts = array(
			'default'		=>	'inc',
			'views'			=>	'tpl',
			'logs'			=>	'log',
		);
		
		
		/**
		 * Default values
		 * 
		 * @static
		 * @var array
		 */
		public static $defaults = array(
			'action'		=>	'index',
			'errorFile'		=>	'error',
			'inlineErrorFile'	=>	'inlineerror'
		);
		
		
		/**
		 * Miscellaneous settings
		 * 
		 * @static
		 * @var array
		 */
		public static $misc = array(
			'fileExtDot'		=>	'.'
		);
		
		
		/**
		 * Logging settings
		 * 
		 * @static
		 * @var array
		 */
		public static $log = array(
			'filename'		=>	'errors',
			'format'		=>	'Fehler %d: %s in %s, Zeile %d'
		);
		
		
		/**
		 * Class-specific settings
		 * 
		 * @static
		 * @var array
		 */
		public static $classes = array(
			'linker'	=> array(
				'url'		=> array(
					'length'	=>	50,
					'delimiter'	=>	'-'
				)
			)
		);
		
		
		
		
		/**
		 * Determine the directory for a specific classtype.
		 * 
		 * @param	string	$classType	Classtype to get directory of
		 * @return	string			Directory of given classtype
		 */
		public static function getClassDir($classType)
		{
			// Default directory (for core classes)
			$classDir = self::$dirs['core'];
			
			// Configurable directory
			if(array_key_exists($classType, self::$dirs)) {
				$classDir = self::$dirs[$classType];
			}
			else
			{
				// Default directory for classtype
				if(is_dir(ROOT.DS.$classType)) {
					$classDir = $classType;
				}
			}
			
			
			// Return directory
			return $classDir;
		}
		
		
		/**
		 * Determine the file extension for a specific filetype.
		 * 
		 * @param	string	$fileType	Filetype to get file extension of
		 * @return	string			File extension of given filetype
		 */
		public static function getFileExt($fileType)
		{
			// Default file extension
			$fileExt = self::$fileExts['default'];
			
			// Configurable file extension
			if(array_key_exists($fileType, self::$fileExts)) {
				$fileExt = self::$fileExts[$fileType];
			}
			
			
			// Return file extension
			return self::$misc['fileExtDot'].$fileExt;
		}
		
	}

?>
