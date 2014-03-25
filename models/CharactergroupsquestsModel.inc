<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\models;
	
	
	/**
	 * Model of the CharactergroupsquestsAgent to interact with
	 * Charactergroupsquests-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactergroupsquestsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new CharactergroupsquestsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get Character groups Quests of a Character groups-groups.
		 * 
		 * @param	int	$groupsgroupId	ID of the Character groups-group
		 * @return	array			Character groups Quest data
		 */
		public function getQuestsForCharactergroupsgroup($groupsgroupId)
		{
			return $this->db->query(
				'SELECT id, questgroups_id, title, url '.
				'FROM charactergroupsquests '.
				'WHERE charactergroupsgroup_id = ?',
				'i',
				$groupsgroupId
			);
		}
		
		
		/**
		 * Get a Character groups Quest by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$groupsgroupId	ID of the Character groups-group
		 * @param	string	$questUrl	URL-title of the Character groups Quest
		 * @return	array			Character groups Quest data
		 */
		public function getQuestByUrl($groupsgroupId, $questUrl)
		{
			$data = $this->db->query(
				'SELECT id, questgroups_id, title, url, description, xps, rules, won_text, lost_text, questsmedia_id '.
				'FROM charactergroupsquests '.
				'WHERE charactergroupsgroup_id = ? AND url = ?',
				'is',
				$groupsgroupId,
				$questUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get the Character groups for a Quest.
		 * 
		 * @param	int	$questId	ID of the Character groups Quest
		 * @return	array			Character groups
		 */
		public function getGroupsForQuest($questId)
		{
			$groups = $this->db->query(
				'SELECT charactergroups.id, charactergroups.name, charactergroups.url, charactergroupsquests_groups.created, charactergroupsquests_groups.xps_factor, charactergroupsquests.xps '.
				'FROM charactergroupsquests_groups '.
				'LEFT JOIN charactergroups ON charactergroups.id = charactergroupsquests_groups.charactergroup_id '.
				'LEFT JOIN charactergroupsquests ON charactergroupsquests.id = charactergroupsquests_groups.charactergroupsquest_id '.
				'WHERE charactergroupsquests_groups.charactergroupsquest_id = ?',
				'i',
				$questId
			);
			foreach($groups as &$group) {
				$group['xps'] = round($group['xps'] * $group['xps_factor'], 1);
			}
			
			
			return $groups;
		}
		
		
		/**
		 * Get Character groups Quests for a Character group.
		 * 
		 * @param	int	$groupId	ID of the Character group
		 * @return	array			Character groups Quests
		 */
		public function getQuestsForGroup($groupId)
		{
			$quests = $this->db->query(
				'SELECT charactergroupsquests.id, charactergroupsquests_groups.created, charactergroupsquests.title, charactergroupsquests.url, charactergroupsquests.xps, charactergroupsquests_groups.xps_factor '.
				'FROM charactergroupsquests_groups '.
				'LEFT JOIN charactergroupsquests ON charactergroupsquests.id = charactergroupsquests_groups.charactergroupsquest_id '.
				'WHERE charactergroupsquests_groups.charactergroup_id = ?',
				'i',
				$groupId
			);
			foreach($quests as &$quest) {
				$quest['group_xps'] = round($quest['xps'] * $quest['xps_factor'], 1);
			}
			
			
			return $quests;
		}
		
		
	}

?>
