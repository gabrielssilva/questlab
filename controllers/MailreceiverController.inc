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
	 * Controller of the MailreceiverAgent to generate a mail receiver
	 * salutation.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MailreceiverController extends \nre\core\Controller
	{
		
		
		
		
		/**
		 * Action: index.
		 */
		public function index($user)
		{
			$this->set('user', $user);
		}
		
	}

?>
