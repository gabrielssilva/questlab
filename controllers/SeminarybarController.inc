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
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('characters', 'quests', 'questgroups');
		
		
		
		
		/**
		 * Action: index.
		 */
		public function index()
		{
			if(is_null(IntermediateController::$seminary)) {
				return;
			}
			
			// Get Seminary
			$seminary = IntermediateController::$seminary;
			
			// Get Character
			$character = IntermediateController::$character;
			$character['xplevel'] = $this->Characters->getXPLevelOfCharacters($character['id']);
			$character['rank'] = $this->Characters->getXPRank($seminary['id'], $character['xps']);
			
			// Get “last” Quest
			$lastQuest = $this->Quests->getLastQuestForCharacter($character['id']);
			if(!is_null($lastQuest)) {
				$lastQuest['questgroup'] = $this->Questgroups->getQuestgroupById($lastQuest['questgroup_id']);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('character', $character);
			$this->set('lastQuest', $lastQuest);
		}
		
	}

?>
