<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\agents;
	
	
	/**
	 * Abstract class for implementing an application Controller.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	abstract class ToplevelAgent extends \nre\agents\ToplevelAgent
	{
		
		
		
		
		/**
		 * Construct a new ToplevlAgent
		 * 
		 * @param	\nre\core\Request	$request	Current request
		 * @param	\nre\core\Response	$response	Current response
		 * @param	\nre\core\Logger	$log		Logger instance
		 */
		protected function __construct(\nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
		{
			parent::__construct($request, $response, $log);
			
			
			// Set timezone
			date_default_timezone_set(\nre\configs\AppConfig::$app['timeZone']);
		}
	}

?>
