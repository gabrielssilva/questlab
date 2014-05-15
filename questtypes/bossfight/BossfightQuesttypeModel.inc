<?php
	
	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\questtypes;
	
	
	/**
	 * Model of the BossfightQuesttypeAgent for a boss-fight.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class BossfightQuesttypeModel extends \hhu\z\models\QuesttypeModel
	{
		
		
		
		
		/**
		 * Get a Boss-Fight.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$questId	ID of Quest
		 * @return	array			Boss-Fight data
		 */
		public function getBossFight($questId)
		{
			$data = $this->db->query(
				'SELECT bossname, boss_seminarymedia_id, lives_character, lives_boss '.
				'FROM questtypes_bossfight '.
				'WHERE quest_id = ?',
				'i',
				$questId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get the first Stage to begin the Boss-Fight with.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Data of first Stage
		 */
		public function getFirstStage($questId)
		{
			$data = $this->db->query(
				'SELECT id, text, question, livedrain_character, livedrain_boss '.
				'FROM questtypes_bossfight_stages '.
				'WHERE questtypes_bossfight_quest_id = ? AND parent_stage_id IS NULL',
				'i',
				$questId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get a Stage by its ID.
		 * 
		 * @param	int	$stageId	ID of Stage
		 * @return	array			Stage data or null
		 */
		public function getStageById($stageId)
		{
			$data = $this->db->query(
				'SELECT id, text, question, livedrain_character, livedrain_boss '.
				'FROM questtypes_bossfight_stages '.
				'WHERE id = ?',
				'i',
				$stageId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get the follow-up Stages for a Stage.
		 * 
		 * @param	int	$parentStageId	ID of Stage to get follow-up Stages for
		 * @return	array			List of follow-up Stages
		 */
		public function getChildStages($parentStageId)
		{
			return $this->db->query(
				'SELECT id, text, question, livedrain_character, livedrain_boss '.
				'FROM questtypes_bossfight_stages '.
				'WHERE parent_stage_id = ?',
				'i',
				$parentStageId
			);
		}
		
		
		/**
		 * Reset all Character submissions of a Boss-Fight.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @param	int	$characterId	ID of Character
		 */
		public function clearCharacterSubmissions($questId, $characterId)
		{
			$this->db->query(
				'DELETE FROM questtypes_bossfight_stages_characters '.
				'WHERE questtypes_bossfight_stage_id IN ('.
					'SELECT id '.
					'FROM questtypes_bossfight_stages '.
					'WHERE questtypes_bossfight_quest_id = ?'.
				') AND character_id = ?',
				'ii',
				$questId,
				$characterId
			);
		}
		
		
		/**
		 * Save Character’s submitted answer for one Boss-Fight-Stage.
		 * 
		 * @param	int	$regexId	ID of list
		 * @param	int	$characterId	ID of Character
		 */
		public function setCharacterSubmission($stageId, $characterId)
		{
			$this->db->query(
				'INSERT INTO questtypes_bossfight_stages_characters '.
				'(questtypes_bossfight_stage_id, character_id) '.
				'VALUES '.
				'(?, ?) '.
				'ON DUPLICATE KEY UPDATE '.
				'questtypes_bossfight_stage_id = ?',
				'iii',
				$stageId, $characterId, $stageId
			);
		}
		
		
		/**
		 * Get answer of one Boss-Fight-Stage submitted by Character.
		 * 
		 * @param	int	$regexId	ID of list
		 * @param	int	$characterId	ID of Character
		 * @return	boolean			Stage taken
		 */
		public function getCharacterSubmission($stageId, $characterId)
		{
			$data = $this->db->query(
				'SELECT questtypes_bossfight_stage_id '.
				'FROM questtypes_bossfight_stages_characters '.
				'WHERE questtypes_bossfight_stage_id = ? AND character_id = ? ',
				'ii',
				$stageId, $characterId
			);
			
			
			return (!empty($data));
		}
		
	}

?>
