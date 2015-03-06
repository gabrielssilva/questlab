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
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function quest(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}
		
		
		/**
		 * Action: submissions.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function submissions(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}
		
		
		/**
		 * Action: submission.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function submission(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}


		/**
		 * Action: create.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function create(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}


		/**
		 * Action: edit.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function edit(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}


		/**
		 * Action: edittask.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function edittask(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}


		/**
		 * Action: edittexts.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function edittexts(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}


		/**
		 * Action: delete.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function delete(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4), true);
		}
		
	}

?>
