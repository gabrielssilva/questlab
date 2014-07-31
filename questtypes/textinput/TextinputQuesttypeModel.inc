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


		/**
		 * Set the text for a Quest and correct fields count.
		 * 
		 * @param	int	$userId		ID of user setting text
		 * @param	int	$questId	ID of Quest to set text for
		 * @param	string	$text		Text for Quset
		 */
		public function setTextForQuest($userId, $questId, $text)
		{
			$this->db->setAutocommit(false);
			try {
				// Set text
				$this->db->query(
					'INSERT INTO questtypes_textinput '.
					'(quest_id, created_user_id, text) '.
					'VALUES '.
					'(?, ?, ?) '.
					'ON DUPLICATE KEY UPDATE '.
					'text = ?',
					'iiss',
					$questId,
					$userId,
					$text,
					$text
				);

				// Count fields
				$fieldCount = substr_count($text, '[textinput]');

				// Remove fields
				$this->db->query(
					'DELETE FROM questtypes_textinput_fields '.
					'WHERE questtypes_textinput_quest_id = ? AND number > ?',
					'ii',
					$questId,
					$fieldCount
				);

				// Add fields
				for($i=1; $i<=$fieldCount; $i++)
				{
					$this->db->query(
						'INSERT IGNORE INTO questtypes_textinput_fields '.
						'(questtypes_textinput_quest_id, number, regex) '.
						'VALUES '.
						'(?, ?, ?) ',
						'iis',
						$questId,
						$i,
						''
					);
				}

				$this->db->commit();
			}
			catch(\Exception $e) {
				$this->db->rollback();
				$this->db->setAutocommit(true);
				throw $e;
			}

			$this->db->setAutocommit(true);
		}


		/**
		 * Set values for a field of a text.
		 * 
		 * @param	int	$questId	ID of Quest to set field for
		 * @param	int	$number		Field number
		 * @param	int	$sizeId		ID of field size
		 * @param	string	$regex		RegEx for field
		 */
		public function setFieldForText($questId, $number, $sizeId, $regex)
		{
			$this->db->query(
				'UPDATE questtypes_textinput_fields '.
				'SET questtypes_textinput_fieldsize_id = ?, regex = ? '.
				'WHERE questtypes_textinput_quest_id = ? AND number = ?',
				'isii',
				$sizeId,
				$regex,
				$questId,
				$number
			);
		}


		/**
		 * Get all registered field sizes.
		 * 
		 * @return	List of field sizes
		 */
		public function getFieldSizes()
		{
			return $this->db->query(
				'SELECT id, size '.
				'FROM questtypes_textinput_fieldsizes '.
				'ORDER BY size'
			);
		}
		
	}

?>
