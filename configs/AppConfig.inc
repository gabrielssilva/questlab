<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace nre\configs;
	
	
	/**
	 * Application configuration.
	 * 
	 * This class contains static variables with configuration values for
	 * the specific application.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	final class AppConfig
	{
		
		/**
		 * Application values
		 * 
		 * @static
		 * @var array
		 */
		public static $app = array(
			'namespace'		=>	'hhu\\z\\',
			'timeZone'		=>	'Europe/Berlin'
		);
		
		
		/**
		 * Default values
		 * 
		 * @static
		 * @var array
		 */
		public static $defaults = array(
			'toplevel'		=>	'html',
			'toplevel-error'	=>	'fault',
			'intermediate'		=>	'introduction',
			'intermediate-error'	=>	'error'
		);
		
		
		/**
		 * Routes
		 *
		 * @static
		 * @var array
		 */
		public static $routes = array(
			//array('<pattern>', '<replace>', '<is_last>')
		);


		/**
		 * Reverse routes
		 * 
		 * @static
		 * @var array
		 */
		public static $reverseRoutes = array(
			//array('<pattern>', '<replace>', '<is_last>')
		);
		
	}

?>
