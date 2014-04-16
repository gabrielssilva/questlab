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
	 * Model to interact with Questtopics-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuesttopicsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new QuesttopicsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get a Questtopic by its URL.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	string	$questtopicUrl	URL-Title of Questtopic
		 * @return	array			Questtopic data
		 */
		public function getQuesttopicByUrl($seminaryId, $questtopicUrl)
		{
			$data = $this->db->query(
				'SELECT id, title, url '.
				'FROM questtopics '.
				'WHERE seminary_id = ? AND url = ?',
				'is',
				$seminaryId, $questtopicUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questtopicUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get all Questtopics for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			List of Questtopics
		 */
		public function getQuesttopicsForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT id, title, url '.
				'FROM questtopics '.
				'WHERE seminary_id = ?',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get count of Quests that are linked to a Questtopic.
		 * 
		 * @param	int	$questtopicId	ID of Questtopic
		 * @return	int			Count of Quests
		 */
		public function getQuestCountForQuesttopic($questtopicId)
		{
			$data = $this->db->query(
				'SELECT count(DISTINCT quests_questsubtopics.quest_id) AS c ' .
				'FROM questsubtopics '.
				'LEFT JOIN quests_questsubtopics ON quests_questsubtopics.questsubtopic_id = questsubtopics.id '.
				'WHERE questsubtopics.questtopic_id = ?',
				'i',
				$questtopicId
			);
			if(!empty($data)) {
				return $data[0]['c'];
			}
			
			
			return 0;
		}
		
		
		/**
		 * Get count of Quests that are linked to a Questtopic and are
		 * unlocked by a Character.
		 * 
		 * @param	int	$questtopicId	ID of Questtopic
		 * @param	int	$characterId	ID of Character
		 * @return	int			Count of Quests
		 */
		public function getCharacterQuestCountForQuesttopic($questtopicId, $characterId)
		{
			$data = $this->db->query(
				'SELECT count(DISTINCT quests_characters.quest_id) AS c '.
				'FROM questsubtopics '.
				'LEFT JOIN quests_questsubtopics ON quests_questsubtopics.questsubtopic_id = questsubtopics.id '.
				'INNER JOIN quests_characters ON quests_characters.quest_id = quests_questsubtopics.quest_id AND quests_characters.character_id = ? AND quests_characters.status = 3 '.
				'WHERE questsubtopics.questtopic_id = ?',
				'ii',
				$characterId,
				$questtopicId
			);
			if(!empty($data)) {
				return $data[0]['c'];
			}
			
			
			return 0;
		}
		
		
		/**
		 * Get all Questsubtopics for a Quest.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			List of Questsubtopics
		 */
		public function getQuestsubtopicsForQuest($questId)
		{
			return $this->db->query(
				'SELECT DISTINCT id, questtopic_id, title, url '.
				'FROM quests_questsubtopics '.
				'INNER JOIN questsubtopics ON questsubtopics.id = quests_questsubtopics.questsubtopic_id '.
				'WHERE quests_questsubtopics.quest_id = ?',
				'i',
				$questId
			);
		}
		
	}

?>
