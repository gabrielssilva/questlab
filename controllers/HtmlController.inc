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
	class HtmlController extends \hhu\z\Controller
	{
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('notification');
		
		
		
		
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
		}
		
		
		/**
		 * Postfilter that is executed after running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function postFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			// Get title
			$this->set('title', $this->getTitle());
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
			
			// Set userdata
			$this->set('loggedUser', IntermediateController::$user);
			$this->set('loggedSeminary', SeminaryController::$seminary);
			$this->set('loggedCharacter', SeminaryController::$character);
			
			// Set notifications
			$this->set('notifications', $this->Notification->getNotifications());
		}
		
		
		
		
		/**
		 * Get title information from IntermediateController if possible
		 * and create a title.
		 * 
		 * @return	string	Title for the current page
		 */
		private function getTitle()
		{
			$title = array();
			
			// Get title of IntermediateController
			$intermediateController = $this->agent->getIntermediateAgent()->controller;
			if($intermediateController instanceof \hhu\z\controllers\IntermediateController) {
				$title = $intermediateController->getTitle();
			}
			if(!is_array($title)) {
				$title = array($title);
			}
			
			// Add application name
			$title[] = \nre\configs\AppConfig::$app['name'];
			
			
			// Return title with delimiter
			return implode(\nre\configs\AppConfig::$misc['title_delimiter'], $title);
		}
		
	}

?>
