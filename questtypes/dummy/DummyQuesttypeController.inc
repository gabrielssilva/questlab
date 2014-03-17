<?php
	
	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\questtypes;
	
	
	/**
	 * Controller of the Dummy-QuesttypeAgent for testing basic
	 * QuesttypeAgent-functionality.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class DummyQuesttypeController extends \hhu\z\QuesttypeController
	{
		
		
		
		
		/**
		 * Action: index.
		 */
		public function index()
		{
			// Check for submission
			if($this->request->getRequestMethod() == 'POST')
			{
				// Right answer (dummy)
				if(!is_null($this->request->getPostParam('submit'))) {
					$this->setQuestSolved();
				}
				// Wrong answer (dummy)
				else {
					$this->setQuestUnsolved();
				}
			}
		}
		
	}

?>
