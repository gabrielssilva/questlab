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
	class TextinputQuesttypeModel extends \hhu\z\models\QuesttypeModel
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
		 * Get fields for a textinput-text.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Fields
		 */
		public function getTextinputFields($questId)
		{
			return $this->db->query(
				'SELECT fields.id, fields.number, fields.regex, fieldsizes.id AS fieldsize_id, fieldsizes.size '.
				'FROM questtypes_textinput_fields AS fields '.
				'LEFT JOIN questtypes_textinput_fieldsizes AS fieldsizes ON fieldsizes.id = fields.questtypes_textinput_fieldsize_id '.
				'WHERE fields.questtypes_textinput_quest_id = ? '.
				'ORDER BY fields.number ASC',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Save Character’s submitted answer for one textinput field.
		 * 
		 * @param	int	$fieldId	ID of field
		 * @param	int	$characterId	ID of Character
		 * @param	string	$answer		Submitted answer for this field
		 */
		public function setCharacterSubmission($fieldId, $characterId, $answer)
		{
			$this->db->query(
				'INSERT INTO questtypes_textinput_fields_characters '.
				'(questtypes_textinput_field_id, character_id, value) '.
				'VALUES '.
				'(?, ?, ?) '.
				'ON DUPLICATE KEY UPDATE '.
				'value = ?',
				'iiss',
				$fieldId, $characterId, $answer, $answer
			);
		}
		
		
		/**
		 * Get answer of one input field submitted by Character.
		 * 
		 * @param	int	$fieldId	ID of field
		 * @param	int	$characterId	ID of Character
		 * @return	string			Submitted answer for this field or empty string
		 */
		public function getCharacterSubmission($fieldId, $characterId)
		{
			$data = $this->db->query(
				'SELECT value '.
				'FROM questtypes_textinput_fields_characters '.
				'WHERE questtypes_textinput_field_id = ? AND character_id = ? ',
				'ii',
				$fieldId, $characterId
			);
			if(!empty($data)) {
				return $data[0]['value'];
			}
			
			
			return '';
		}
		
	}

?>
