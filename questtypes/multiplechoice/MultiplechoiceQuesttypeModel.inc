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
	 * Model of the MultiplechoiceQuesttypeAgent for multiple choice.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MultiplechoiceQuesttypeModel extends \hhu\z\QuesttypeModel
	{
		
		
		
		
		/**
		 * Get all multiple choice questions of a Quest.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Multiple choice questions
		 */
		public function getQuestionsOfQuest($questId)
		{
			return $this->db->query(
				'SELECT id, pos, question, tick '.
				'FROM questtypes_multiplechoice '.
				'WHERE quest_id = ?',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Get all multiple choice questions of a Quest that should be
		 * ticked.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Multiple choice questions that should be ticked
		 */
		public function getTickQuestionsOfQuest($questId)
		{
			return $this->db->query(
				'SELECT id, question, tick, pos '.
				'FROM questtypes_multiplechoice '.
				'WHERE quest_id = ? AND tick = True',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Save Character’s submitted answer for one option.
		 * 
		 * @param	int	$multipleChoiceId	ID of multiple choice option
		 * @param	int	$characterId		ID of Character
		 * @param	boolean	$answer			Submitted answer for this option
		 */
		public function setCharacterSubmission($multipleChoiceId, $characterId, $answer)
		{
			$this->db->query(
				'INSERT INTO questtypes_multiplechoice_characters '.
				'(questtypes_multiplechoice_id, character_id, ticked) '.
				'VALUES '.
				'(?, ?, ?) '.
				'ON DUPLICATE KEY UPDATE '.
				'ticked = ?',
				'iiii',
				$multipleChoiceId, $characterId, $answer, $answer
			);
		}
		
		
		/**
		 * Get answer of one option submitted by Character.
		 * 
		 * @param	int	$multipleChoiceId	ID of multiple choice option
		 * @param	int	$characterId		ID of Character
		 * @return	boolean				Submitted answer of Character or false
		 */
		public function getCharacterSubmission($multipleChoiscId, $characterId)
		{
			$data = $this->db->query(
				'SELECT ticked '.
				'FROM questtypes_multiplechoice_characters '.
				'WHERE questtypes_multiplechoice_id = ? AND character_id = ? ',
				'ii',
				$multipleChoiscId, $characterId
			);
			if(!empty($data)) {
				return $data[0]['ticked'];
			}
			
			
			return false;
		}
		
	}

?>
