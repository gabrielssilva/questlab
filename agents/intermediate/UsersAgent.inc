<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\agents\intermediate;
	

	/**
	 * Agent to list registered users and their data.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class UsersAgent extends \nre\agents\IntermediateAgent
	{
		
		
		
		
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
		 * Action: user.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function user(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Userroles', 'user');
		}
		
	}

?>
