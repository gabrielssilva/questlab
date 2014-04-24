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
	 * Controller of the CharactergroupsAgent to display Character groups.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactergroupsController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'charactergroups', 'charactergroupsquests', 'characters', 'avatars', 'media');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'quest' => array('admin', 'moderator', 'user'),
			'manage' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'quest'		=> array('admin', 'moderator', 'user'),
			'manage'	=> array('admin', 'moderator')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * Show Character groups-groups for a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 */
		public function index($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character groups-groups
			$groupsgroups = $this->Charactergroups->getGroupsroupsForSeminary($seminary['id']);
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroups', $groupsgroups);
		}
		
		
		/**
		 * Action: groupsgroups.
		 * 
		 * Show Character groups for a Character groups-group of a
		 * Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$groupsgroupUrl		URL-Title of a Character groups-group
		 */
		public function groupsgroup($seminaryUrl, $groupsgroupUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character groups-group
			$groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);
			
			// Get Character groups
			$groups = $this->Charactergroups->getGroupsForGroupsgroup($groupsgroup['id']);
			
			// Get Character groups-group Quests
			$quests = $this->Charactergroupsquests->getQuestsForCharactergroupsgroup($groupsgroup['id']);
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroup', $groupsgroup);
			$this->set('groups', $groups);
			$this->set('quests', $quests);
		}
		
		
		/**
		 * Action: group.
		 * 
		 * Show a Character group for a Character groups-group of a
		 * Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$groupsgroupUrl		URL-Title of a Character groups-group
		 * @param	string	$groupUrl		URL-Title of a Character group
		 */
		public function group($seminaryUrl, $groupsgroupUrl, $groupUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character groups-group
			$groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);
			
			// Get Character group
			$group = $this->Charactergroups->getGroupByUrl($groupsgroup['id'], $groupUrl);
			$group['characters'] = $this->Characters->getCharactersForGroup($group['id']);
			$group['rank'] = $this->Charactergroups->getXPRank($groupsgroup['id'], $group['xps']);
			
			// Get Character avatars
			foreach($group['characters'] as &$character)
			{
				$avatar = $this->Avatars->getAvatarById($character['avatar_id']);
				if(!is_null($avatar['small_avatarpicture_id'])) {
					$character['small_avatar'] = $this->Media->getSeminaryMediaById($avatar['small_avatarpicture_id']);
				}
			}
			
			// Get Character groups Quests
			$quests = $this->Charactergroupsquests->getQuestsForGroup($group['id']);
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroup', $groupsgroup);
			$this->set('group', $group);
			$this->set('quests', $quests);
		}
		
		
		/**
		 * Action: managegroup.
		 *
		 * Manage a Character group for a Character groups-group of a
		 * Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$groupsgroupUrl		URL-Title of a Character groups-group
		 * @param	string	$groupUrl		URL-Title of a Character group
		 */
		public function managegroup($seminaryUrl, $groupsgroupUrl, $groupUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character groups-group
			$groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);
			
			// Get Character group
			$group = $this->Charactergroups->getGroupByUrl($groupsgroup['id'], $groupUrl);
			
			// Manage
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('actions')) && count($this->request->getPostParam('actions')) > 0) // && !is_null($this->request->getPostParam('characters')) && count($this->request->getPostParam('characters')) > 0)
			{
				$actions = $this->request->getPostParam('actions');
				$action = array_keys($actions)[0];
				$selectedCharacters = $this->request->getPostParam('characters');
				
				switch($action)
				{
					// Add Characters to group
					case 'addcharacters':
						var_dump("hier");
						foreach($selectedCharacters as &$characterId) {
							var_dump("add ".$characterId);
							$this->Charactergroups->addCharacterToCharactergroup($group['id'], $characterId);
						}
					break;
					// Remove Characters from group
					case 'removecharacters':
						foreach($selectedCharacters as &$characterId) {
							$this->Charactergroups->removeCharacterFromCharactergroup($group['id'], $characterId);
						}
					break;
				}
			}
			
			// Get additional data for group
			$group['characters'] = $this->Characters->getCharactersForGroup($group['id']);
			$group['rank'] = $this->Charactergroups->getXPRank($groupsgroup['id'], $group['xps']);
			
			// Get Character avatars
			foreach($group['characters'] as &$character)
			{
				$avatar = $this->Avatars->getAvatarById($character['avatar_id']);
				if(!is_null($avatar['small_avatarpicture_id'])) {
					$character['small_avatar'] = $this->Media->getSeminaryMediaById($avatar['small_avatarpicture_id']);
				}
			}
			
			// Get Character groups Quests
			$quests = $this->Charactergroupsquests->getQuestsForGroup($group['id']);
			
			// Get all Characters of Seminary
			$groupCharacterIds = array_map(function($c) { return $c['id']; }, $group['characters']);
			$seminaryCharacters = $this->Characters->getCharactersForSeminary($seminary['id']);
			$characters = array();
			foreach($seminaryCharacters as &$character) {
				if(!in_array($character['id'], $groupCharacterIds)) {
					$characters[] = $character;
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroup', $groupsgroup);
			$this->set('group', $group);
			$this->set('quests', $quests);
			$this->set('characters', $characters);
		}
		
	}

?>
