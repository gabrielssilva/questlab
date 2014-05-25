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
	 * Controller of the TextmailAgent for generating a simple text-mail
	 * message.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class TextmailController extends \nre\core\Controller
	{
		
		
		
		
		/**
		 * Prefilter.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::preFilter($request, $response);
			
			
			// Set linker
			$this->set('linker', ($request instanceof \hhu\z\requests\MailRequest && !is_null($request->getLinker())) ? $request->getLinker() : null);
		}
		
		
		/**
		 * Action: index.
		 * 
		 * Create simple text-mail message.
		 */
		public function index()
		{
			$this->set('appname', \nre\configs\AppConfig::$app['name']);
		}
		
	}

?>
