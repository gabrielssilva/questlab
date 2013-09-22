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
	 * Class that holds several web-specific methods and properties.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class WebUtils
	{
		/**
		 * HTTP-statuscode 403: Forbidden
		 * 
		 * @var int
		 */
		const HTTP_FORBIDDEN = 403;
		/**
		 * HTTP-statuscode 404: Not Found
		 * 
		 * @var int
		 */
		const HTTP_NOT_FOUND = 404;
		/**
		 * HTTP-statuscode 503: Service Unavailable
		 * 
		 * @var int
		 */
		const HTTP_SERVICE_UNAVAILABLE = 503;
		
		/**
		 * HTTP-header strings
		 * 
		 * @var array
		 */
		public static $httpStrings = array(
			200	=>	'OK',
			304	=>	'Not Modified',
			403	=>	'Forbidden',
			404	=>	'Not Found',
			503	=>	'Service Unavailable'
		);
		
		
		
		
		/**
		 * Get the HTTP-header of a HTTP-statuscode
		 * 
		 * @param	int	$httpStatusCode	HTTP-statuscode
		 * @return	string			HTTP-header of HTTP-statuscode
		 */
		public static function getHttpHeader($httpStatusCode)
		{
			if(!array_key_exists($httpStatusCode, self::$httpStrings)) {
				$httpStatusCode = 200;
			}
			
			
			return sprintf("HTTP/1.1 %d %s\n", $httpStatusCode, self::$httpStrings[$httpStatusCode]);
		}
		
	}

?>
