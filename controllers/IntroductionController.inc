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
	 * Controller of the Agent to show an introduction page.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class IntroductionController extends \hhu\z\controllers\IntermediateController
	{
		
		
		
		
		/**
		 * Action: index.
		 */
		public function index()
		{
			// Pass data to view
			$this->set('userId', $this->Auth->getUserId());
		}
		
	}

?>
