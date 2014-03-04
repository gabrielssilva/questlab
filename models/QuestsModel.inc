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
			return $this->db->query(
				'SELECT id, questtype_id, title, url, xps, task '.
				'FROM quests '.
				'WHERE questgroup_id = ?',
				'i',
				$questgroupId
			);
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
				'SELECT quests.id, quests.questtype_id, quests.title, quests.url, quests.xps, quests.task, quests.right_text, quests.wrong_text, quests.questsmedia_id '.
				'FROM quests '.
				'LEFT JOIN questgroups ON questgroups.id = quests.questgroup_id '.
				'LEFT JOIN questgroupshierarchy ON questgroupshierarchy.id = questgroups.questgroupshierarchy_id '.
				'WHERE questgroupshierarchy.seminary_id = ? AND questgroups.id = ? AND quests.url = ?',
				'iis',
				$seminaryId, $questgroupId, $questUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Sidequest and its data by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$seminaryId	ID of the corresponding Seminary
		 * @param	int	$questgroupId	ID of the corresponding Questgroup
		 * @param	int	$questId	ID of the Quest
		 * @param	string	$sidequestUrl	URL-title of a Sidequest
		 * @return	array			Sidequest data
		 */
		public function getSidequestByUrl($seminaryId, $questgroupId, $questId, $sidequestUrl)
		{
			$data = $this->db->query(
				'SELECT sidequests.id, sidequests.questtype_id, sidequests.title, sidequests.url, sidequests.xps, sidequests.task, quests.right_text, quests.wrong_text, sidequests.questsmedia_id '.
				'FROM sidequests '.
				'LEFT JOIN questtexts ON questtexts.id = sidequests.questtext_id '.
				'LEFT JOIN quests ON quests.id = questtexts.quest_id '.
				'LEFT JOIN questgroups ON questgroups.id = quests.questgroup_id '.
				'LEFT JOIN questgroupshierarchy ON questgroupshierarchy.id = questgroups.questgroupshierarchy_id '.
				'LEFT JOIN seminaries ON seminaries.id = questgroupshierarchy.seminary_id '.
				'WHERE sidequests.url = ? AND quests.id = ? AND questgroups.id = ? AND seminaries.id = ?',
				'siii',
				$sidequestUrl,
				$questId,
				$questgroupId,
				$seminaryId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($sidequestUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get all sidequests for a Quest.
		 * 
		 * @param	int	$questId	ID of the quest
		 * @return	array			Sidequests for the quest
		 */
		public function getSidequestsForQuest($questId)
		{
			return $this->db->query(
				'SELECT sidequests.id, sidequests.questtext_id, sidequests.title, sidequests.url, sidequests.entry_text '.
				'FROM sidequests '.
				'LEFT JOIN questtexts ON questtexts.id = sidequests.questtext_id '.
				'WHERE questtexts.quest_id = ?',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Get all sidequests for a Questtext.
		 * 
		 * @param	int	$questtextId	ID of the questtext
		 * @return	array			Sidequests for the questtext
		 */
		public function getSidequestsForQuesttext($questtextId)
		{
			return $this->db->query(
				'SELECT id, questtext_id, title, url, entry_text '.
				'FROM sidequests '.
				'WHERE questtext_id = ?',
				'i',
				$questtextId
			);
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
				'SELECT quests.id, quests.title, quests.url, questgroups.title AS questgroup_title, questgroups.url AS questgroup_url '.
				'FROM quests_previousquests '.
				'LEFT JOIN quests ON quests.id = quests_previousquests.quest_id '.
				'LEFT JOIN questgroups ON questgroups.id = quests.questgroup_id '.
				'LEFT JOIN questgroupshierarchy ON questgroupshierarchy.id = questgroups.questgroupshierarchy_id '.
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
				'LEFT JOIN quests ON quests.id = quests_previousquests.previous_quest_id '.
				'LEFT JOIN questgroups ON questgroups.id = quests.questgroup_id '.
				'LEFT JOIN questgroupshierarchy ON questgroupshierarchy.id = questgroups.questgroupshierarchy_id '.
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
		
	}

?>
