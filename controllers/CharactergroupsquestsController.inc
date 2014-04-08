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
	 * Controller of the CharactergroupsquestsAgent to display Character
	 * groups Quests.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactergroupsquestsController extends \hhu\z\controllers\SeminaryRoleController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'charactergroups', 'charactergroupsquests', 'media');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'quest' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'quest' => array('admin', 'moderator', 'user')
		);
		
		
		
		
		/**
		 * Action: quest.
		 * 
		 * Show a Character groups Quest for a Character groups-group
		 * of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$groupsgroupUrl		URL-Title of a Character groups-group
		 * @param	string	$questUrl		URL-Title of a Character groups Quest
		 */
		public function quest($seminaryUrl, $groupsgroupUrl, $questUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			if(!is_null($seminary['media_id'])) {
				$seminary['media'] = $this->Media->getMediaById($seminary['media_id']);
			}
			
			// Get Character groups-group
			$groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);
			
			// Get Character groups-group Quests
			$quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);
			
			// Get Character groups-groups
			$groups = $this->Charactergroupsquests->getGroupsForQuest($quest['id']);
			
			// Media
			$questmedia = null;
			if(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getSeminaryMediaById($quest['questsmedia_id']);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroup', $groupsgroup);
			$this->set('quest', $quest);
			$this->set('groups', $groups);
			$this->set('media', $questmedia);
		}
		
	}

?>
