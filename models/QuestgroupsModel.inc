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
					'SELECT questgroups.id, questgroups_questgroupshierarchy.questgroupshierarchy_id, questgroups_questgroupshierarchy.pos, questgroups.title, questgroups.url, questgroups.questgroupspicture_id, questgroups.achievable_xps '.
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
					'SELECT questgroups.id, questgroups_questgroupshierarchy.questgroupshierarchy_id, questgroups_questgroupshierarchy.pos, questgroups.title, questgroups.url, questgroups.questgroupspicture_id, questgroups.achievable_xps '.
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
				'SELECT id, title, url, achievable_xps '.
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
				'SELECT id, title, url, questgroupspicture_id, achievable_xps '.
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
				'SELECT id, title, url, questgroupspicture_id, achievable_xps '.
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
		 * Get the first text of a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	string			First text of this Questgroup or NULL
		 */
		public function getFirstQuestgroupText($questgroupId)
		{
			// Text of Questgroup itself
			$questgroupTexts = $this->getQuestgroupTexts($questgroupId);
			if(!empty($questgroupTexts)) {
				return $questgroupTexts[0]['text'];
			}
			
			// Text of first Quest
			$quest = $this->Quests->getFirstQuestOfQuestgroup($questgroupId);
			if(!is_null($quest))
			{
				$questText = $this->Questtexts->getFirstQuestText($quest['id']);
				if(!is_null($questText)) {
					return $questText;
				}
			}
			
			// Text of ChildQuestgroups
			$questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroupId);
			$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
			foreach($childQuestgroupshierarchy as &$hierarchy)
			{
				// Get Questgroups
				$questgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroupId);
				foreach($questgroups as &$group)
				{
					$childQuestgroupText = $this->getFirstQuestgroupText($group['id']);
					if(!is_null($childQuestgroupText)) {
						return $childQuestgroupText;
					}
				}
			}
			
			
			// No text found
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
		 * Determine if the given Character has solved a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to check
		 * @param	int	$characterId	ID of Character to check
		 * @result	boolean			Whether Character has solved the Questgroup or not
		 */
		public function hasCharacterSolvedQuestgroup($questgroupId, $characterId)
		{
			// Get data of Questgroup
			$questgroup = $this->getQuestgroupById($questgroupId);
			$questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			
			// Check last Quest(s) of this Questgroup
			$solvedLastQuest = false;
			$lastQuests = $this->Quests->getLastQuestsOfQuestgroup($questgroup['id']);
			// Check last Quest(s) of last child Questgroup
			if(empty($lastQuests) && !empty($questgroup['hierarchy']))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroup['hierarchy']['id']);
				if(!empty($childQuestgroupshierarchy))
				{
					$childQuestgroupshierarchy = array_pop($childQuestgroupshierarchy);
					$childQuestgroups = $this->getQuestgroupsForHierarchy($childQuestgroupshierarchy['id'], $questgroupId);
					if(!empty($childQuestgroups))
					{
						$childQuestgroup = array_pop($childQuestgroups);
						$lastQuests = $this->Quests->getLastQuestsOfQuestgroup($childQuestgroup['id']);
					}
				}
			}
			foreach($lastQuests as &$lastQuest)
			{
				if($this->Quests->hasCharacterSolvedQuest($lastQuest['id'], $characterId))
				{
					$solvedLastQuest = true;
					break;
				}
			}
			if(!$solvedLastQuest) {
				return false;
			}
			
			// Check all child Questgroups
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
		 * @param	int	$questtextId	ID of the Questtext
		 * @return	array			Related Questgroups for the Questtext
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
		 * @param	int	$questId	ID of the Quest
		 * @return	array			Related Quests for the Quest
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
		 * Get all related Questgroups of a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of the Questgroup
		 * @return	array			Related Questgroups for the Questgroup
		 */
		public function getRelatedQuestsgroupsOfQuestgroup($questgroupId)
		{
			return $this->db->query(
				'SELECT DISTINCT questgroups_questtexts.questgroup_id AS id '.
				'FROM questgroups '.
				'INNER JOIN quests ON quests.questgroup_id = questgroups.id '.
				'INNER JOIN questtexts ON questtexts.quest_id = quests.id '.
				'INNER JOIN questgroups_questtexts ON questgroups_questtexts.questtext_id = questtexts.id '.
				'WHERE questgroups.id = ?',
				'i',
				$questgroupId
			);
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
			// Questgroup
			$xps = $this->_getAchievedXPsForQuestgroup($questgroupId, $characterId);
			
			// Related Questgroups
			foreach($this->getRelatedQuestsgroupsOfQuestgroup($questgroupId) as $relatedQuestgroup) {
				$xps += $this->getAchievedXPsForQuestgroup($relatedQuestgroup['id'], $characterId);
			}
			
			// XPs of child Questgroups
			$questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroupId);
			if(!empty($questgroupHierarchy))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
				foreach($childQuestgroupshierarchy as &$hierarchy)
				{
					$childQuestgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroupId);
					foreach($childQuestgroups as &$childQuestgroup) {
						$xps += $this->getAchievedXPsForQuestgroup($childQuestgroup['id'], $characterId);
					}
				}
			}
			
			
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
		
		
		/**
		 * Calculate the total amount of achievable XPs for a
		 * Questgroup, its sub-Questgroups, related Questgroups etc. and
		 * store this value in the database.
		 * 
		 * @param	int	$questgroupId		ID of Questgroup
		 * @param	array	$calculatedQuests	Already calculated Quests
		 * @return	int				Sum of calculated XPs
		 */
		public function calculateXPsForQuestgroup($questgroupId, &$calculatedQuests=array())
		{
			$xps = 0;
			
			// Quests
			$quest = $this->Quests->getFirstQuestOfQuestgroup($questgroupId);
			if(!is_null($quest)) {
				$xps = $this->_calculateXPsForQuestgroup($quest);
			}
			
			// Child Questgroups
			$questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroupId);
			if(!empty($questgroupHierarchy))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
				foreach($childQuestgroupshierarchy as &$hierarchy)
				{
					$questgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroupId);
					foreach($questgroups as &$questgroup) {
						$xps += $this->calculateXPsForQuestgroup($questgroup['id'], $calculatedQuests);
					}
				}
			}
			
			// Save XPs
			$this->setXPsForQuestgroup($questgroupId, $xps);
			
			
			return $xps;
		}
		
		
		
		
		/**
		 * Get the sum of XPs of Quests for a Questgroup solved by a
		 * Character.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup
		 * @param	int	$characterId	ID of Character
		 * @return	int			Sum of XPs of Quests
		 */
		private function _getAchievedXPsForQuestgroup($questgroupId, $characterId)
		{
			$data = $this->db->query(
				'SELECT COALESCE(SUM(quests.xps),0) AS xps '.
				'FROM quests '.
				'INNER JOIN quests_characters ON quests_characters.quest_id = quests.id AND quests_characters.character_id = ? AND quests_characters.status = ? '.
				'WHERE quests.questgroup_id = ?',
				'iii',
				$characterId,
				\hhu\z\models\QuestsModel::QUEST_STATUS_SOLVED,
				$questgroupId
			);
			if(!empty($data)) {
				return $data[0]['xps'];
			}
		}
		
		
		/*
		 * Calculate the total amount of achievable XPs for a Quest and
		 * its following Quests by choosing the path with the highest
		 * amount of XPs.
		 * 
		 * @param	int	$quest			Quest data
		 * @param	array	$calculatedQuests	Already calculated Quests
		 * @return	int				Sum of calculated XPs
		 */
		private function _calculateXPsForQuestgroup($quest, &$calculatedQuests=array())
		{
			$xps = $quest['xps'];
			
			// Related Questgroups
			$relatedQuestgroups = $this->getRelatedQuestsgroupsOfQuest($quest['id']);
			foreach($relatedQuestgroups as &$relatedQuestgroup) {
				$xps += $this->calculateXPsForQuestgroup($relatedQuestgroup['id'], $calculatedQuests);
			}
			
			// Next Quests
			$nextQuests = $this->Quests->getNextQuests($quest['id']);
			$allNextXPs = array(0);
			foreach($nextQuests as &$nextQuest)
			{
				if(!array_key_exists($nextQuest['id'], $calculatedQuests)) {
					$calculatedQuests[$nextQuest['id']] = $this->_calculateXPsForQuestgroup($nextQuest, $calculatedQuests);
				}
				$allNextXPs[] = $calculatedQuests[$nextQuest['id']];
			}
			$xps += max($allNextXPs);
			
			
			return $xps;
		}
		
		
		/**
		 * Set achievable XPs for a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup
		 * @param	int	$xps		XPs to set
		 */
		private function setXPsForQuestgroup($questgroupId, $xps)
		{
			$this->db->query(
				'UPDATE questgroups '.
				'SET achievable_xps = ? '.
				'WHERE id = ?',
				'ii',
				$xps,
				$questgroupId
			);
		}
		
	}

?>
