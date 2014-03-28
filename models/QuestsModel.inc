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
		 * Construct a new QuestsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all Quests for the given Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	array			Quests of the given Questgroup
		 */
		public function getQuestsForQuestgroup($questgroupId)
		{
			$quests = array();
			
			// Get first Quest
			$quest = $this->db->query(
				'SELECT id, questtype_id, title, url, xps, task '.
				'FROM quests '.
				'LEFT JOIN quests_previousquests ON quests_previousquests.quest_id = quests.id '.
				'WHERE questgroup_id = ? AND quests_previousquests.previous_quest_id IS NULL',
				'i',
				$questgroupId
			);
			if(empty($quest)) {
				return $quests;
			}
			$quest = $quest[0];
			array_push($quests, $quest);
			
			// Get next Quests
			// TODO Multiple next Quests
			while(($nextQuests = $this->getNextQuests($quest['id'])) != null)
			{
				$quest = $nextQuests[0];
				array_push($quests, $quest);
			}
			
			
			// Return Quests
			return $quests;
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
		 * Mark a Quest as solved for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark as solved
		 * @param	int	$characterId	ID of Character that solved the Quest
		 */
		public function setQuestSolved($questId, $characterId)
		{
			$this->db->query(
				'INSERT INTO quests_characters '.
				'(quest_id, character_id, status) '.
				'VALUES '.
				'(?, ?, ?)',
				'iii',
				$questId,
				$characterId,
				0
			);
		}
		
		
		/**
		 * Mark a Quest as unsolved for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark as unsolved
		 * @param	int	$characterId	ID of Character that unsolved the Quest
		 */
		public function setQuestUnsolved($questId, $characterId)
		{
			$this->db->query(
				'INSERT INTO quests_characters '.
				'(quest_id, character_id, status) '.
				'VALUES '.
				'(?, ?, ?)',
				'iii',
				$questId,
				$characterId,
				-1
			);
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
				'WHERE quest_id = ? AND character_id = ? AND status IN (-1,0)',
				'ii',
				$questId,
				$characterId
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
				'WHERE quest_id = ? AND character_id = ? AND status = 0',
				'ii',
				$questId,
				$characterId
			);
			
			
			return (!empty($count) && intval($count[0]['c']) > 0);
		}
		
		
		/**
		 * Get Characters that solved a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to get Characters for
		 * @return	array			Characters data
		 */
		public function getCharactersSolvedQuest($questId)
		{
			return $data = $this->db->query(
				'SELECT character_id, created, text '.
				'FROM questtypes_submit_characters '.
				'WHERE quest_id = ? AND EXISTS ('.
					'SELECT character_id FROM quests_characters WHERE quest_id = questtypes_submit_characters.quest_id AND status = 0'.
				')',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Get Characters that did not solved a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to get Characters for
		 * @return	array			Characters data
		 */
		public function getCharactersUnsolvedQuest($questId)
		{
			return $data = $this->db->query(
				'SELECT character_id, created, text '.
				'FROM questtypes_submit_characters '.
				'WHERE quest_id = ? AND NOT EXISTS ('.
					'SELECT character_id FROM quests_characters WHERE quest_id = questtypes_submit_characters.quest_id AND status = 0'.
				')',
				'i',
				$questId
			);
		}
		
	}

?>
