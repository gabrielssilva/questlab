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
		public $models = array('characters', 'quests', 'questgroups', 'achievements', 'charactergroups', 'avatars', 'media');
		
		
		
		
		/**
		 * Action: index.
		 */
		public function index()
		{
			// Do not render at first
			$this->set('render', false);
			
			// Get Seminary
			$seminary = SeminaryController::$seminary;
			if(is_null($seminary)) {
				return;
			}
			
			// Get Character
			$character = SeminaryController::$character;
			if(is_null($character)) {
				return;
			}
			$character['xplevel'] = $this->Characters->getXPLevelOfCharacters($character['id']);
			$character['rank'] = $this->Characters->getXPRank($seminary['id'], $character['xps']);
			
			// Get “last” Quest
			$lastQuest = $this->Quests->getLastQuestForCharacter($character['id']);
			if(!is_null($lastQuest)) {
				$lastQuest['questgroup'] = $this->Questgroups->getQuestgroupById($lastQuest['questgroup_id']);
			}
			
			// Get last achieved Achievement
			$achievements = $this->Achievements->getAchievedAchievementsForCharacter($character['id']);
			$lastAchievement = array_shift($achievements);
			
			// Get Character group members
			$characterGroups = array();
			foreach($this->Charactergroups->getGroupsForCharacter($character['id']) as $group)
			{
				$groupsgroup = $this->Charactergroups->getGroupsgroupById($group['charactergroupsgroup_id']);
				if($groupsgroup['preferred'])
				{
					$group['members'] = $this->Characters->getCharactersForGroup($group['id']);
					$characterGroups[] = $group;
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('character', $character);
			$this->set('lastQuest', $lastQuest);
			$this->set('lastAchievement', $lastAchievement);
			$this->set('characterGroups', $characterGroups);
			// Render now
			$this->set('render', true);
		}
		
	}

?>
