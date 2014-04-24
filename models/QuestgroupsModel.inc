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
		 * Questgroup-status: Entered
		 * 
		 * @var int;
		 */
		const QUESTGROUP_STATUS_ENTERED = 0;
		
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('questgroupshierarchy', 'quests', 'questtexts');
		
		
		
		
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
			// Get Questgroups
			$questgroups = array();
			if(is_null($parentQuestgroupId))
			{
				$questgroups = $this->db->query(
					'SELECT questgroups.id, questgroups_questgroupshierarchy.questgroupshierarchy_id, questgroups_questgroupshierarchy.pos, questgroups.title, questgroups.url, questgroups.questgroupspicture_id '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE questgroups_questgroupshierarchy.questgroupshierarchy_id = ? AND questgroups_questgroupshierarchy.parent_questgroup_id IS NULL '.
					'ORDER BY questgroups_questgroupshierarchy.pos ASC',
					'i',
					$hierarchyId
				);
			}
			else
			{
				$questgroups = $this->db->query(
					'SELECT questgroups.id, questgroups_questgroupshierarchy.questgroupshierarchy_id, questgroups_questgroupshierarchy.pos, questgroups.title, questgroups.url, questgroups.questgroupspicture_id '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE questgroups_questgroupshierarchy.questgroupshierarchy_id = ? AND questgroups_questgroupshierarchy.parent_questgroup_id = ? '.
					'ORDER BY questgroups_questgroupshierarchy.pos ASC',
					'ii',
					$hierarchyId, $parentQuestgroupId
				);
			}
			
			
			// Return Questgroups
			return $questgroups;
		}
		
		
		/**
		 * Get all Questgroups for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			List of Questgroups
		 */
		public function getQuestgroupsForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT id, title, url '.
				'FROM questgroups '.
				'WHERE seminary_id = ? '.
				'ORDER BY title ASC',
				'i',
				$seminaryId
			);
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
				'SELECT id, title, url, questgroupspicture_id '.
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
				'SELECT id, title, url, questgroupspicture_id '.
				'FROM questgroups '.
				'WHERE seminary_id = ? AND url = ?',
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
		 * Get first texts of a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	array			First Text of this Questgroup
		 */
		public function getFirstQuestgroupText($questgroupId)
		{
			$data = $this->db->query(
				'SELECT id, pos, text '.
				'FROM questgrouptexts '.
				'WHERE questgroup_id = ? '.
				'ORDER BY pos ASC '.
				'LIMIT 1',
				'i',
				$questgroupId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
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
			$currentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($currentQuestgroup['id']);
			if(empty($currentQuestgroup['hierarchy'])) {
				return null;
			}
			
			$nextQuestgroup = $this->_getNextQuestgroup($currentQuestgroup['hierarchy']['parent_questgroup_id'], $currentQuestgroup['hierarchy']['questgroup_pos']);
			if(is_null($nextQuestgroup) && !is_null($currentQuestgroup['hierarchy']['parent_questgroup_id'])) {
				$nextQuestgroup = $this->getNextQuestgroup($currentQuestgroup['hierarchy']['parent_questgroup_id']);
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
			$currentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($currentQuestgroup['id']);
			if(empty($currentQuestgroup['hierarchy'])) {
				return null;
			}
			
			$previousQuestgroup = $this->_getPreviousQuestgroup($currentQuestgroup['hierarchy']['parent_questgroup_id'], $currentQuestgroup['hierarchy']['questgroup_pos']);
			if(is_null($previousQuestgroup) && !is_null($currentQuestgroup['hierarchy']['parent_questgroup_id'])) {
				$previousQuestgroup = $this->getPreviousQuestgroup($currentQuestgroup['hierarchy']['parent_questgroup_id']);
			}
			
			
			return $previousQuestgroup;
		}
		
		
		/**
		 * Mark a Questgroup as entered for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark as entered
		 * @param	int	$characterId	ID of Character that entered the Quest
		 */
		public function setQuestgroupEntered($questgroupId, $characterId)
		{
			$this->setQuestgroupStatus($questgroupId, $characterId, self::QUESTGROUP_STATUS_ENTERED, false);
		}
		
		
		/**
		 * Determine if the given Character has entered a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to check
		 * @param	int	$characterId	ID of Character to check
		 * @result	boolean			Whether Character has entered the Questgroup or not
		 */
		public function hasCharacterEnteredQuestgroup($questgroupId, $characterId)
		{
			$count = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM questgroups_characters '.
				'WHERE questgroup_id = ? AND character_id = ? AND status IN (?)',
				'iii',
				$questgroupId,
				$characterId,
				self::QUESTGROUP_STATUS_ENTERED
			);
			
			
			return (!empty($count) && intval($count[0]['c']) > 0);
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
			// Get data of Questgroup
			$questgroup = $this->getQuestgroupById($questgroupId);
			
			// Chack all Quests
			$currentQuest = $this->Quests->getFirstQuestOfQuestgroup($questgroup['id']);
			if(!is_null($currentQuest))
			{
				if(!$this->Quests->hasCharacterSolvedQuest($currentQuest['id'], $characterId)) {
					return false;
				}
				
				// Get next Quests
				$nextQuests = !is_null($currentQuest) ? $this->Quests->getNextQuests($currentQuest['id']) : null;
				while(!is_null($currentQuest) && !empty($nextQuests))
				{
					// Get choosed Quest
					$currentQuest = null;
					foreach($nextQuests as &$nextQuest) {
						if($this->Quests->hasCharacterEnteredQuest($nextQuest['id'], $characterId)) {
							$currentQuest = $nextQuest;
						}
					}
					
					// Check Quest
					if(is_null($currentQuest)) {
						return false;
					}
					
					// Check status
					if(!$this->Quests->hasCharacterSolvedQuest($currentQuest['id'], $characterId)) {
						return false;
					}
					
					$nextQuests = !is_null($currentQuest) ? $this->Quests->getNextQuests($currentQuest['id']) : null;
				}
			}
			
			// Check all child Questgroups
			$questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			if(!empty($questgroup['hierarchy']))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroup['hierarchy']['id']);
				foreach($childQuestgroupshierarchy as &$hierarchy)
				{
					// Get Questgroups
					$questgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroup['id']);
					foreach($questgroups as &$group) {
						if(!$this->hasCharacterSolvedQuestgroup($group['id'], $characterId)) {
							return false;
						}
					}
				}
			}
			
			
			return true;
		}
		
		
		/**
		 * Get all related Questgroups of a Questtext.
		 * 
		 * @param	int	$questtextId	ID of the questtext
		 * @return	array			Sidequests for the questtext
		 */
		public function getRelatedQuestsgroupsOfQuesttext($questtextId)
		{
			return $this->db->query(
				'SELECT questgroups.id, questgroups_questtexts.questtext_id, questgroups.title, questgroups.url, questgroups_questtexts.entry_text '.
				'FROM questgroups_questtexts '.
				'INNER JOIN questgroups ON questgroups.id = questgroups_questtexts.questgroup_id '.
				'WHERE questgroups_questtexts.questtext_id = ?',
				'i',
				$questtextId
			);
		}
		
		
		/**
		 * Get all related Questgroups of a Quest.
		 * 
		 * @param	int	$questId	ID of the quest
		 * @return	array			Sidequests for the quest
		 */
		public function getRelatedQuestsgroupsOfQuest($questId)
		{
			return $this->db->query(
				'SELECT questgroups_questtexts.questgroup_id AS id '.
				'FROM quests '.
				'INNER JOIN questtexts ON questtexts.quest_id = quests.id '.
				'INNER JOIN questgroups_questtexts ON questgroups_questtexts.questtext_id = questtexts.id '.
				'WHERE quests.id = ?',
				'i',
				$questId
			);
			
		}
		
		
		/**
		 * Calculate cumulated data for a Questgroup, its
		 * sub-Questgroups and all its Quests.
		 * 
		 * @param	int	$questgroupId		ID of Questgroup
		 * @param	int	$characterId		ID of Character
		 * @param	array	$calculatedQuests	IDs of already calculated Quests
		 * @return	array				Cumulated data for Questgroup
		 */
		public function getCumulatedDataForQuestgroup($questgroupId, $characterId=null, &$calculatedQuests=array())
		{
			// Cumulated data
			$data = array(
				'xps'		=> 0,
				'character_xps'	=> 0
			);
			
			// Current Questgroup
			$questgroup = $this->getQuestgroupById($questgroupId);
			
			// Quests of current Questgroup
			$quest = $this->Quests->getFirstQuestOfQuestgroup($questgroup['id']);
			if(!is_null($quest))
			{
				$questData = $this->getCumulatedDataForQuest($quest, $characterId, $calculatedQuests);
				$data['xps'] += $questData['xps'];
				$data['character_xps'] += $questData['character_xps'];
			}
			
			// XPs of child Questgroups
			$questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			if(!empty($questgroupHierarchy))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
				foreach($childQuestgroupshierarchy as &$hierarchy)
				{
					$questgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroup['id']);
					foreach($questgroups as &$questgroup)
					{
						$childData = $this->getCumulatedDataForQuestgroup($questgroup['id'], $characterId, $calculatedQuests);
						$data['xps'] += $childData['xps'];
						$data['character_xps'] += $childData['character_xps'];
					}
				}
			}
			
			
			// Return cumulated data
			return $data;
		}
		
		
		/**
		 * Calculate cumulated data of the given Quest, its following
		 * Quests and its related Questgroups.
		 * 
		 * @param	array	$quest			Quest data
		 * @param	int	$characterId		ID of Character
		 * @param	array	$calculatedQuests	IDs of already calculated Quests
		 * @return	array				Cumulated data for Quest
		 */
		public function getCumulatedDataForQuest($quest, $characterId=null, &$calculatedQuests=array())
		{
			// Cumulated data
			$data = array(
				'xps'		=> $quest['xps'],
				'character_xps'	=> (!is_null($characterId) && $this->Quests->hasCharacterSolvedQuest($quest['id'], $characterId)) ? $quest['xps'] : 0
			);
			
			// Related Questgroups
			$relatedQuestgroups = $this->getRelatedQuestsgroupsOfQuest($quest['id']);
			foreach($relatedQuestgroups as &$relatedQuestgroup)
			{
				$relatedData = $this->getCumulatedDataForQuestgroup($relatedQuestgroup['id'], $characterId, $calculatedQuests);
				$data['xps'] += $relatedData['xps'];
				$data['character_xps'] += $relatedData['character_xps'];
			}
			
			// Next Quests
			$nextQuests = $this->Quests->getNextQuests($quest['id']);
			$allNextData = array(
				'xps'		=> array(0),
				'character_xps'	=> array(0),
			);
			foreach($nextQuests as &$nextQuest)
			{
				if(!in_array($nextQuest['id'], $calculatedQuests))
				{
					$nextData = $this->getCumulatedDataForQuest($nextQuest, $characterId, $calculatedQuests);
					$allNextData['xps'][] = $nextData['xps'];
					$allNextData['character_xps'][] = $nextData['character_xps'];
					$calculatedQuests[] = $nextQuest['id'];
				}
			}
			$data['xps'] += max($allNextData['xps']);
			$data['character_xps'] += max($allNextData['character_xps']);
			
			
			// Return cumulated data
			return $data;
		}
		
		
				/**
		 * Summarize XPs of all Quests for a Questgroup and its
		 * sub-Questgroups solved by a Character.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup
		 * @param	int	$characterId	ID of Character
		 * @return	int			Sum of XPs
		 */
		public function getAchievedXPsForQuestgroup($questgroupId, $characterId)
		{
			// Sum of XPs
			$xps = 0;
			
			// Current Questgroup
			$questgroup = $this->getQuestgroupById($questgroupId);
			
			// Quests of current Questgroup
			$quest = $this->Quests->getFirstQuestOfQuestgroup($questgroup['id']);
			if(!is_null($quest)) {
				$xps += $this->getAchievedXPsForQuest($quest, $characterId);
			}
			
			// XPs of child Questgroups
			$questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			if(empty($questgroupHierarchy)) {
				return $xps;
			}
			$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
			foreach($childQuestgroupshierarchy as &$hierarchy)
			{
				$questgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroup['id']);
				foreach($questgroups as &$questgroup) {
					$xps += $this->getAchievedXPsForQuestgroup($questgroup['id'], $characterId);
				}
			}
			
			
			// Return summarized XPs
			return $xps;
		}
		
		
		/**
		 * Summarize XPs of the given Quest, its following Quests and
		 * its related Questgroups solved by a Character.
		 * 
		 * @param	int	$quest		Quest to summarize XPs for
		 * @param	int	$characterId	ID of Character
		 * @return	int			Sum of XPs
		 */
		public function getAchievedXPsForQuest($quest, $characterId)
		{
			$xps = 0;
			
			// XPs for the given Quest
			if($this->Quests->hasCharacterSolvedQuest($quest['id'], $characterId))
			{
				$xps += $quest['xps'];
				
				// Next Quests
				$nextQuests = $this->Quests->getNextQuests($quest['id']);
				foreach($nextQuests as &$nextQuest)
				{
					if($this->Quests->hasCharacterEnteredQuest($nextQuest['id'], $characterId))
					{
						$xps += $this->getAchievedXPsForQuest($nextQuest, $characterId);
						break;
					}
				}
			}
			
			// Related Questgroups
			$relatedQuestgroups = $this->getRelatedQuestsgroupsOfQuest($quest['id']);
			foreach($relatedQuestgroups as &$relatedQuestgroup) {
				$xps += $this->getAchievedXPsForQuestgroup($relatedQuestgroup['id'], $characterId);
			}
			
			
			// Return summarized XPs
			return $xps;
		}
		
		
		/**
		 * Create a new Questgroup.
		 * 
		 * @param	int	$userId		User-ID that creates the new character
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	string	$title		Title for new Questgroup
		 * @return	int			ID of new Questgroup
		 */
		public function createQuestgroup($userId, $seminaryId, $title)
		{
			$this->db->query(
				'INSERT INTO questgroups '.
				'(created_user_id, seminary_id, title, url) '.
				'VALUES '.
				'(?, ?, ?, ?)',
				'iiss',
				$userId,
				$seminaryId,
				$title,
				\nre\core\Linker::createLinkParam($title)
			);
			
			
			return $this->db->getInsertId();
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
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE parent_questgroup_id = ? AND pos = ? + 1',
					'ii',
					$parentQuestgroupId, $questgroupPos
				);
			}
			else
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
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
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE parent_questgroup_id = ? AND pos = ? - 1',
					'ii',
					$parentQuestgroupId, $questgroupPos
				);
			}
			else
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
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
		
		
		/**
		 * Mark a Questgroup for a Character.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to mark
		 * @param	int	$characterId	ID of Character to mark the Questgroup for
		 * @param	int	$status		Questgroup status to mark
		 * @param	boolean	$repeated	Insert although status is already set for this Questgroup and Character
		 */
		private function setQuestgroupStatus($questgroupId, $characterId, $status, $repeated=true)
		{
			// Check if status is already set
			if(!$repeated)
			{
				$count = $this->db->query(
					'SELECT count(*) AS c '.
					'FROM questgroups_characters '.
					'WHERE questgroup_id = ? AND character_id = ? AND status = ?',
					'iii',
					$questgroupId,
					$characterId,
					$status
				);
				if(!empty($count) && intval($count[0]['c']) > 0) {
					return;
				}
			}
			
			// Set status
			$this->db->query(
				'INSERT INTO questgroups_characters '.
				'(questgroup_id, character_id, status) '.
				'VALUES '.
				'(?, ?, ?) ',
				'iii',
				$questgroupId,
				$characterId,
				$status
			);
		}
		
	}

?>
