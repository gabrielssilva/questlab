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
	class MultiplechoiceQuesttypeModel extends \hhu\z\models\QuesttypeModel
	{
		
		
		
		
		/**
		 * Get the count of multiple choice questions for a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to get count for
		 * @return	int			Conut of questions
		 */
		public function getQuestionsCountOfQuest($questId)
		{
			$data = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM questtypes_multiplechoice '.
				'WHERE quest_id = ?',
				'i',
				$questId
			);
			if(!empty($data)) {
				return $data[0]['c'];
			}
			
			
			return 0;
		}
		
		
		/**
		 * Get all multiple choice questions of a Quest.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Multiple choice questions
		 */
		public function getQuestionsOfQuest($questId)
		{
			return $this->db->query(
				'SELECT id, pos, question '.
				'FROM questtypes_multiplechoice '.
				'WHERE quest_id = ?',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Get one multiple choice question of a Quest.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @param	int	$pos		Position of question
		 * @return	array			Question data
		 */
		public function getQuestionOfQuest($questId, $pos)
		{
			$data = $this->db->query(
				'SELECT id, pos, question '.
				'FROM questtypes_multiplechoice '.
				'WHERE quest_id = ? AND pos = ?',
				'ii',
				$questId, $pos
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get all answers of a multiple choice question.
		 * 
		 * @param	int	$questionId	ID of multiple choice question
		 * @return	array			Answers of question
		 */
		public function getAnswersOfQuestion($questionId)
		{
			return $this->db->query(
				'SELECT id, pos, answer, tick '.
				'FROM questtypes_multiplechoice_answers '.
				'WHERE questtypes_multiplechoice_id = ?',
				'i',
				$questionId
			);
		}
		
		
		/**
		 * Save Character’s submitted answer for one option.
		 * 
		 * @param	int	$answerId	ID of multiple choice answer
		 * @param	int	$characterId	ID of Character
		 * @param	boolean	$answer		Submitted answer for this option
		 */
		public function setCharacterSubmission($answerId, $characterId, $answer)
		{
			$this->db->query(
				'INSERT INTO questtypes_multiplechoice_characters '.
				'(questtypes_multiplechoice_answer_id, character_id, ticked) '.
				'VALUES '.
				'(?, ?, ?) '.
				'ON DUPLICATE KEY UPDATE '.
				'ticked = ?',
				'iiii',
				$answerId, $characterId, $answer, $answer
			);
		}
		
		
		/**
		 * Get answer of one option submitted by Character.
		 * 
		 * @param	int	$answerId	ID of multiple choice answer
		 * @param	int	$characterId	ID of Character
		 * @return	boolean			Submitted answer of Character or false
		 */
		public function getCharacterSubmission($answerId, $characterId)
		{
			$data = $this->db->query(
				'SELECT ticked '.
				'FROM questtypes_multiplechoice_characters '.
				'WHERE questtypes_multiplechoice_answer_id = ? AND character_id = ? ',
				'ii',
				$answerId, $characterId
			);
			if(!empty($data)) {
				return $data[0]['ticked'];
			}
			
			
			return false;
		}
		
	}

?>
