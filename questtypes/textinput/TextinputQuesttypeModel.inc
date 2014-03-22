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
	 * Model of the TextinputQuesttypeAgent for inserting text.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class TextinputQuesttypeModel extends \hhu\z\QuesttypeModel
	{
		
		
		
		
		/**
		 * Get textinput-text for a Quest.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Textinput-text
		 */
		public function getTextinputQuest($questId)
		{
			$data = $this->db->query(
				'SELECT text '.
				'FROM questtypes_textinput '.
				'WHERE quest_id = ?',
				'i',
				$questId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get regular expressions for a textinput-text.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Regexs
		 */
		public function getTextinputRegexs($questId)
		{
			return $this->db->query(
				'SELECT id, number, regex '.
				'FROM questtypes_textinput_regexs '.
				'WHERE questtypes_textinput_quest_id = ? '.
				'ORDER BY number ASC',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Save Character’s submitted answer for one textinput field.
		 * 
		 * @param	int	$regexId	ID of regex
		 * @param	int	$characterId	ID of Character
		 * @param	string	$answer		Submitted answer for this field
		 */
		public function setCharacterSubmission($regexId, $characterId, $answer)
		{
			$this->db->query(
				'INSERT INTO questtypes_textinput_regexs_characters '.
				'(questtypes_textinput_regex_id, character_id, value) '.
				'VALUES '.
				'(?, ?, ?) '.
				'ON DUPLICATE KEY UPDATE '.
				'value = ?',
				'iiss',
				$regexId, $characterId, $answer, $answer
			);
		}
		
		
		/**
		 * Get answer of one regex input field submitted by Character.
		 * 
		 * @param	int	$regexId	ID of regex
		 * @param	int	$characterId	ID of Character
		 * @return	string			Submitted answer for this field or empty string
		 */
		public function getCharacterSubmission($regexId, $characterId)
		{
			$data = $this->db->query(
				'SELECT value '.
				'FROM questtypes_textinput_regexs_characters '.
				'WHERE questtypes_textinput_regex_id = ? AND character_id = ? ',
				'ii',
				$regexId, $characterId
			);
			if(!empty($data)) {
				return $data[0]['value'];
			}
			
			
			return '';
		}
		
	}

?>
