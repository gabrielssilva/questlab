<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\agents\toplevel;
	
	
	/**
	 * Agent to return a JSON-string used by AJAX.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class AjaxAgent extends \hhu\z\agents\ToplevelAgent
	{
		
		
		
		
		/**
		 * Construct a new AjaxAgent.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 * @param	Logger		$log		Logger instance
		 */
		protected function __construct(\nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
		{
			parent::__construct($request, $response, $log);
			
			
			$this->setLanguage($request);
		}
		
		
		/**
		 * Action: index.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function index(\nre\core\Request $request, \nre\core\Response $response)
		{
		}
		
		
		
		
		/**
		 * Set requested language.
		 * 
		 * @param	Request		$request	Current request
		 */
		private function setLanguage(\nre\core\Request $request)
		{
			// Set domain
			$domain = \nre\configs\AppConfig::$app['genericname'];
			
			// Get language
			$locale = $request->getGetParam('lang', 'language');
			if(is_null($locale)) {
				return;
			}
			
			// Load translation
			putenv("LC_ALL=$locale");
			setlocale(LC_ALL, $locale);
			bindtextdomain($domain, ROOT.DS.\nre\configs\AppConfig::$dirs['locale']);
			textdomain($domain);
		}
		
	}

?>
