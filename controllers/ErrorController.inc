<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\controllers;
	
	
	/**
	 * Controller of the Agent to show an error page.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class ErrorController extends \hhu\z\Controller
	{
		
		
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * Set HTTP-header and print an error message.
		 * 
		 * @param	int	$httpStatusCode	HTTP-statuscode of the error that occurred
		 */
		public function index($httpStatusCode)
		{
			// Set HTTP-header
			if(!array_key_exists($httpStatusCode, \nre\core\WebUtils::$httpStrings)) {
				$httpStatusCode = 200;
			}
			$this->response->addHeader(\nre\core\WebUtils::getHttpHeader($httpStatusCode));
			
			// Display statuscode and message
			$this->set('code', $httpStatusCode);
			$this->set('string', \nre\core\WebUtils::$httpStrings[$httpStatusCode]);
			$this->set('userId', $this->Auth->getUserId());
		}
		
	}

?>
