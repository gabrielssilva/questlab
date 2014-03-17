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
				'SELECT question, tick '.
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
				'SELECT question, tick, pos '.
				'FROM questtypes_multiplechoice '.
				'WHERE quest_id = ? AND tick = True',
				'i',
				$questId
			);
		}
		
	}

?>
