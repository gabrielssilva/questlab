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
	 * Model of the SubmitQuesttypeAgent for a submit task.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class SubmitQuesttypeModel extends \hhu\z\QuesttypeModel
	{
		
		
		
		
		/**
		 * Save Character’s submitted text.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @param	int	$characterId	ID of Character
		 * @param	string	$text		Submitted text
		 */
		public function setCharacterSubmission($questId, $characterId, $text)
		{
			$this->db->query(
				'INSERT INTO questtypes_submit_characters '.
				'(quest_id, character_id, text) '.
				'VALUES '.
				'(?, ?, ?) ',
				'iis',
				$questId, $characterId, $text
			);
		}
		
		
		/**
		 * Get text submitted by Character.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @param	int	$characterId	ID of Character
		 * @return	array			Text submitted by Character or NULL
		 */
		public function getCharacterSubmission($questId, $characterId)
		{
			$data = $this->db->query(
				'SELECT created, text '.
				'FROM questtypes_submit_characters '.
				'WHERE quest_id = ? AND character_id = ?',
				'ii',
				$questId, $characterId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
	}

?>
