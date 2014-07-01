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
	 * Agent to display Questgroups.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgroupsAgent extends \nre\agents\IntermediateAgent
	{
		
		
		
		
		/**
		 * Action: questgroup.
		 */
		public function questgroup(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
		}
		

		/**
		 * Action: edit.
		 */
		public function edit(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
		}


		/**
		 * Action: edittexts.
		 */
		public function edittexts(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
		}
		

		/**
		 * Action: delete.
		 */
		public function delete(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
		}
		
	}

?>
