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
	 * Agent to display Quests.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestsAgent extends \nre\agents\IntermediateAgent
	{
		
		
		
		
		/**
		 * Action: quest.
		 */
		public function quest(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}
		
	}

?>
