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
	 * Controller of the Agent to display a sidebar with Seminary related
	 * information.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class SeminarybarController extends \hhu\z\Controller
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
			
			// Set userdata
			$this->set('loggedUser', IntermediateController::$user);
			$this->set('loggedSeminary', IntermediateController::$seminary);
			$this->set('loggedCharacter', IntermediateController::$character);
		}
		
		
		/**
		 * Action: index.
		 */
		public function index()
		{
		}
		
	}

?>
