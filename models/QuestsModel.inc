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
	 * Model to interact with Quests-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestsModel extends \hhu\z\Model
	{
		/**
		 * Quest-status: Entered
		 * 
		 * @var int;
		 */
		const QUEST_STATUS_ENTERED = 0;
		/**
		 * Quest-status: submitted
		 * 
		 * @var int;
		 */
		const QUEST_STATUS_SUBMITTED = 1;
		/**
		 * Quest-status: Unsolved
		 * 
		 * @var int;
		 */
		const QUEST_STATUS_UNSOLVED = 2;
		/**
		 * Quest-status: Solved
		 * 
		 * @var int;
		 */
		const QUEST_STATUS_SOLVED = 3;
		
		
		
		
		/**
		 * Construct a new QuestsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get a Quest and its data by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$seminaryId	ID of the corresponding Seminary
		 * @param	int	$questgroupId	ID of the corresponding Questgroup
		 * @param	string	$questURL	URL-title of a Quest
		 * @return	array			Quest data
		 */
		public function getQuestByUrl($seminaryId, $questgroupId, $questUrl)
		{
			$data = $this->db->query(
				'SELECT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, quests.right_text, quests.wrong_text, quests.questsmedia_id '.
				'FROM quests '.
				'LEFT JOIN questgroups ON questgroups.id = quests.questgroup_id '.
				'WHERE questgroups.seminary_id = ? AND questgroups.id = ? AND quests.url = ?',
				'iis',
				$seminaryId, $questgroupId, $questUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Quest and its data by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$questId	ID of a Quest
		 * @return	array			Quest data
		 */
		public function getQuestById($questId)
		{
			$data = $this->db->query(
				'SELECT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, quests.right_text, quests.wrong_text, quests.questsmedia_id '.
				'FROM quests '.
				'LEFT JOIN questgroups ON questgroups.id = quests.questgroup_id '.
				'WHERE quests.id = ?',
				'i',
				$questId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get the first Quest of a Qusetgroup.
		 * 
		 * @param	int	$questId	ID of Questgroup
		 * @return	array			Data of first Quest
		 */
		public function getFirstQuestOfQuestgroup($questgroupId)
		{
			$data = $this->db->query(
				'SELECT id, questtype_id, title, url, xps, task '.
				'FROM quests '.
				'LEFT JOIN quests_previousquests ON quests_previousquests.quest_id = quests.id '.
				'WHERE questgroup_id = ? AND quests_previousquests.previous_quest_id IS NULL',
				'i',
				$questgroupId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get Quests that follow-up a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to get next Quests of
		 * @return	array			Quests data
		 */
		public function getNextQuests($questId)
		{
			return $this->db->query(
				'SELECT quests.id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, questgroups.title AS questgroup_title, questgroups.url AS questgroup_url '.
				'FROM quests_previousquests '.
				'INNER JOIN quests ON quests.id = quests_previousquests.quest_id '.
				'INNER JOIN questgroups ON questgroups.id = quests.questgroup_id '.
				'WHERE quests_previousquests.previous_quest_id = ?',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Get Quests that the given Quests follows-up to.
		 * 
		 * @param	int	$questId	ID of Quest to get previous Quests of
		 * @return	array			Quests data
		 */
		public function getPreviousQuests($questId)
		{
			return $this->db->query(
				'SELECT quests.id, quests.title, quests.url, questgroups.title AS questgroup_title, questgroups.url AS questgroup_url '.
				'FROM quests_previousquests '.
				'INNER JOIN quests ON quests.id = quests_previousquests.previous_quest_id '.
				'INNER JOIN questgroups ON questgroups.id = quests.questgroup_id '.
				'WHERE quests_previousquests.quest_id = ?',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Mark a Quest as entered for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark as entered
		 * @param	int	$characterId	ID of Character that entered the Quest
		 */
		public function setQuestEntered($questId, $characterId)
		{
			$this->setQuestStatus($questId, $characterId, self::QUEST_STATUS_ENTERED, false);
		}
		
		
		/**
		 * Mark a Quest as submitted for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark as unsolved
		 * @param	int	$characterId	ID of Character that unsolved the Quest
		 */
		public function setQuestSubmitted($questId, $characterId)
		{
			$this->setQuestStatus($questId, $characterId, self::QUEST_STATUS_SUBMITTED);
		}
		
		
		/**
		 * Mark a Quest as unsolved for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark as unsolved
		 * @param	int	$characterId	ID of Character that unsolved the Quest
		 */
		public function setQuestUnsolved($questId, $characterId)
		{
			$this->setQuestStatus($questId, $characterId, self::QUEST_STATUS_UNSOLVED);
		}
		
		
		/**
		 * Mark a Quest as solved for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark as solved
		 * @param	int	$characterId	ID of Character that solved the Quest
		 */
		public function setQuestSolved($questId, $characterId)
		{
			$this->setQuestStatus($questId, $characterId, self::QUEST_STATUS_SOLVED, false);
		}
		
		
		/**
		 * Determine if the given Character has entered a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to check
		 * @param	int	$characterId	ID of Character to check
		 * @result	boolean			Whether Character has entered the Quest or not
		 */
		public function hasCharacterEnteredQuest($questId, $characterId)
		{
			$count = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM quests_characters '.
				'WHERE quest_id = ? AND character_id = ? AND status IN (?,?,?)',
				'iiiii',
				$questId,
				$characterId,
				self::QUEST_STATUS_ENTERED, self::QUEST_STATUS_SOLVED, self::QUEST_STATUS_UNSOLVED
			);
			
			
			return (!empty($count) && intval($count[0]['c']) > 0);
		}
		
		
		/**
		 * Determine if the given Character has tried to solve a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to check
		 * @param	int	$characterId	ID of Character to check
		 * @result	boolean			Whether Character has tried to solved the Quest or not
		 */
		public function hasCharacterTriedQuest($questId, $characterId)
		{
			$count = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM quests_characters '.
				'WHERE quest_id = ? AND character_id = ? AND status IN (?,?)',
				'iiii',
				$questId,
				$characterId,
				self::QUEST_STATUS_SOLVED, self::QUEST_STATUS_UNSOLVED
			);
			
			
			return (!empty($count) && intval($count[0]['c']) > 0);
		}
		
		
		/**
		 * Determine if the given Character has solved the given Quest.
		 * 
		 * @param	int	$questId	ID of Quest to check
		 * @param	int	$characterId	ID of Character to check
		 * @result	boolean			Whether Character has solved the Quest or not
		 */
		public function hasCharacterSolvedQuest($questId, $characterId)
		{
			$count = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM quests_characters '.
				'WHERE quest_id = ? AND character_id = ? AND status = ?',
				'iii',
				$questId,
				$characterId,
				self::QUEST_STATUS_SOLVED
			);
			
			
			return (!empty($count) && intval($count[0]['c']) > 0);
		}
		
		
		/**
		 * Get the last Quests for a Character.
		 * 
		 * @param	int	$characterId	ID of Character
		 * @retrun	array			Quest data
		 */
		public function getLastQuestForCharacter($characterId)
		{
			$data = $this->db->query(
				'SELECT quests.id, quests.questgroup_id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, quests.right_text, quests.wrong_text, quests.questsmedia_id '.
				'FROM quests_characters '.
				'LEFT JOIN quests ON quests.id = quests_characters.quest_id '.
				'WHERE quests_characters.character_id = ? AND quests_characters.status IN (?, ?, ?) '.
				'ORDER BY quests_characters.created desc '.
				'LIMIT 1',
				'iiii',
				$characterId,
				self::QUEST_STATUS_ENTERED, self::QUEST_STATUS_SUBMITTED, self::QUEST_STATUS_SOLVED
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		
		
		/**
		 * Mark a Quest for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark
		 * @param	int	$characterId	ID of Character to mark the Quest for
		 * @param	int	$status		Quest status to mark
		 * @param	boolean	$repeated	Insert although status is already set for this Quest and Character
		 */
		private function setQuestStatus($questId, $characterId, $status, $repeated=true)
		{
			// Check if status is already set
			if(!$repeated)
			{
				$count = $this->db->query(
					'SELECT count(*) AS c '.
					'FROM quests_characters '.
					'WHERE quest_id = ? AND character_id = ? AND status = ?',
					'iii',
					$questId,
					$characterId,
					$status
				);
				if(!empty($count) && intval($count[0]['c']) > 0) {
					return;
				}
			}
			
			// Set status
			$this->db->query(
				'INSERT INTO quests_characters '.
				'(quest_id, character_id, status) '.
				'VALUES '.
				'(?, ?, ?) ',
				'iii',
				$questId,
				$characterId,
				$status
			);
		}
		
	}

?>
