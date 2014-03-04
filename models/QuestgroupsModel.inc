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
	 * Model to interact with Questgroups-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgroupsModel extends \hhu\z\Model
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('questgroupshierarchy', 'quests');
		
		
		
		
		/**
		 * Construct a new QuestgroupsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all Questgroups for a Questgroup hierarchy.
		 * 
		 * @param	int	$hierarchyId		ID of the Questgroup hierarchy to get Questgroups for
		 * @param	int	$parentQuestgroupId	ID of the parent Questgroup hierarchy
		 * @return	array				Questgroups for the given hierarchy
		 */
		public function getQuestgroupsForHierarchy($hierarchyId, $parentQuestgroupId=null)
		{
			if(is_null($parentQuestgroupId))
			{
				return $this->db->query(
					'SELECT id, questgroupshierarchy_id, pos, title, url '.
					'FROM questgroups '.
					'WHERE questgroups.questgroupshierarchy_id = ? AND parent_questgroup_id IS NULL '.
					'ORDER BY questgroups.pos ASC',
					'i',
					$hierarchyId
				);
			}
			else
			{
				return $this->db->query(
					'SELECT id, questgroupshierarchy_id, pos, title, url '.
					'FROM questgroups '.
					'WHERE questgroups.questgroupshierarchy_id = ? AND parent_questgroup_id = ? '.
					'ORDER BY questgroups.pos ASC',
					'ii',
					$hierarchyId, $parentQuestgroupId
				);
			}
		}
		
		
		/**
		 * Get a Questgroup by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	array			Questgroup data
		 */
		public function getQuestgroupById($questgroupId)
		{
			$data = $this->db->query(
				'SELECT id, questgroupshierarchy_id, parent_questgroup_id, pos, title, url, questgroupspicture_id '.
				'FROM questgroups '.
				'WHERE questgroups.id = ?',
				'i',
				$questgroupId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questgroupId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Questgroup by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$seminaryId	ID of the corresponding seminary
		 * @param	string	$questgroupURL	URL-title of a Questgroup
		 * @return	array			Questgroup data
		 */
		public function getQuestgroupByUrl($seminaryId, $questgroupUrl)
		{
			$data = $this->db->query(
				'SELECT questgroups.id, questgroups.questgroupshierarchy_id, questgroups.parent_questgroup_id, questgroups.pos, questgroups.title, questgroups.url, questgroups.questgroupspicture_id '.
				'FROM questgroups '.
				'LEFT JOIN questgroupshierarchy ON questgroupshierarchy.id = questgroups.questgroupshierarchy_id '.
				'WHERE questgroupshierarchy.seminary_id = ? AND questgroups.url = ?',
				'is',
				$seminaryId, $questgroupUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questgroupUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get texts of a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	array			Texts of this Questgroup
		 */
		public function getQuestgroupTexts($questgroupId)
		{
			return $this->db->query(
				'SELECT id, pos, text '.
				'FROM questgrouptexts '.
				'WHERE questgroup_id = ? '.
				'ORDER BY pos ASC',
				'i',
				$questgroupId
			);
		}
		
		
		/**
		 * Get the next Questgroup.
		 * 
		 * Determine the next Questgroup. If there is no next Questgroup
		 * on the same level as the given Quest then the followed-up
		 * Questgroup from a higher hierarchy level is returned.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to get next Questgroup of
		 * @return	array			Questgroup data
		 */
		public function getNextQuestgroup($questgroupId)
		{
			$currentQuestgroup = $this->getQuestgroupById($questgroupId);
			$nextQuestgroup = $this->_getNextQuestgroup($currentQuestgroup['parent_questgroup_id'], $currentQuestgroup['pos']);
			while(is_null($nextQuestgroup) && !is_null($currentQuestgroup['parent_questgroup_id']))
			{
				$currentQuestgroup = $this->getQuestgroupById($currentQuestgroup['parent_questgroup_id']);
				$nextQuestgroup = $this->_getNextQuestgroup($currentQuestgroup['parent_questgroup_id'], $currentQuestgroup['pos']);
			}
			
			
			return $nextQuestgroup;
		}
		
		
		/**
		 * Get the previous Questgroup.
		 * 
		 * Determine the previous Questgroup. If there is no previous
		 * Questgroup on the same level as the given Quest then the
		 * followed-up Questgroup from a higher hierarchy level is
		 * returned.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to get previous Questgroup of
		 * @return	array			Questgroup data
		 */
		public function getPreviousQuestgroup($questgroupId)
		{
			$currentQuestgroup = $this->getQuestgroupById($questgroupId);
			$previousQuestgroup = $this->_getPreviousQuestgroup($currentQuestgroup['parent_questgroup_id'], $currentQuestgroup['pos']);
			while(is_null($previousQuestgroup) && !is_null($currentQuestgroup['parent_questgroup_id']))
			{
				$currentQuestgroup = $this->getQuestgroupById($currentQuestgroup['parent_questgroup_id']);
				$previousQuestgroup = $this->_getPreviousQuestgroup($currentQuestgroup['parent_questgroup_id'], $currentQuestgroup['pos']);
			}
			
			
			return $previousQuestgroup;
		}
		
		
		/**
		 * Determine if the given Character has solved the Quests form
		 * this Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to check
		 * @param	int	$characterId	ID of Character to check
		 * @result	boolean			Whether Character has solved the Questgroup or not
		 */
		public function hasCharacterSolvedQuestgroup($questgroupId, $characterId)
		{
			$currentQuestgroup = $this->getQuestgroupById($questgroupId);
			$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($currentQuestgroup['questgroupshierarchy_id']);
			$lastChildQuestgroupshierarchy = array_pop($childQuestgroupshierarchy);
			while(!is_null($lastChildQuestgroupshierarchy))
			{
				$questgroups = $this->getQuestgroupsForHierarchy($lastChildQuestgroupshierarchy['id'], $currentQuestgroup['id']);
				$currentQuestgroup = array_pop($questgroups);
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($currentQuestgroup['questgroupshierarchy_id']);
				$lastChildQuestgroupshierarchy = array_pop($childQuestgroupshierarchy);
			}
			
			$quests = $this->Quests->getQuestsForQuestgroup($currentQuestgroup['id']);
			$lastQuest = array_pop($quests);
			
			
			return $this->Quests->hasCharacterSolvedQuest($lastQuest['id'], $characterId);
		}
		
		
		
		
		/**
		 * Get the next (direct) Questgroup.
		 * 
		 * @param	int	$parentQuestgroupId	ID of parent Questgroup to get next Questgroup of
		 * @param	int	$questgroupPos		Position of Questgroup to get next Questgroup of
		 * @return	array				Data of next Questgroup or NULL
		 */
		private function _getNextQuestgroup($parentQuestgroupId, $questgroupPos)
		{
			if(!is_null($parentQuestgroupId))
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups '.
					'WHERE parent_questgroup_id = ? AND pos = ? + 1',
					'ii',
					$parentQuestgroupId, $questgroupPos
				);
			}
			else
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups '.
					'WHERE parent_questgroup_id IS NULL AND pos = ? + 1',
					'i',
					$questgroupPos
				);
			}
			if(empty($data)) {
				return null;
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get the previous (direct) Questgroup.
		 * 
		 * @param	int	$parentQuestgroupId	ID of parent Questgroup to get previous Questgroup of
		 * @param	int	$questgroupPos		Position of Questgroup to get previous Questgroup of
		 * @return	array				Data of previous Questgroup or NULL
		 */
		private function _getPreviousQuestgroup($parentQuestgroupId, $questgroupPos)
		{
			if(!is_null($parentQuestgroupId))
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups '.
					'WHERE parent_questgroup_id = ? AND pos = ? - 1',
					'ii',
					$parentQuestgroupId, $questgroupPos
				);
			}
			else
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups '.
					'WHERE parent_questgroup_id IS NULL AND pos = ? - 1',
					'i',
					$questgroupPos
				);
			}
			if(empty($data)) {
				return null;
			}
			
			
			return $data[0];
		}
		
	}

?>
