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
	 * Controller of the HtmlAgent to display a HTML-page.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class HtmlController extends \nre\core\Controller
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
			
			
			// Set content-type
			$this->response->addHeader("Content-type: text/html; charset=utf-8");
			
			// Start session
			session_start();
		}
		
		
		/**
		 * Action: index.
		 * 
		 * Create the HTML-structure.
		 */
		public function index()
		{
			// Set the name of the current IntermediateAgent as page title
			$this->set('title', $this->request->getParam(1, 'intermediate'));
		}
		
	}

?>
