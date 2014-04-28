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
	 * Model of the ChoiceinputQuesttypeAgent for choosing between
	 * predefined input values.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class ChoiceinputQuesttypeModel extends \hhu\z\QuesttypeModel
	{
		
		
		
		
		/**
		 * Get choiceinput-text for a Quest.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Choiceinput-text
		 */
		public function getChoiceinputQuest($questId)
		{
			$data = $this->db->query(
				'SELECT text '.
				'FROM questtypes_choiceinput '.
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
		 * Get all lists of input values for a choiceinput-text.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			List
		 */
		public function getChoiceinputLists($questId)
		{
			return $this->db->query(
				'SELECT id, number, questtypes_choiceinput_choice_id '.
				'FROM questtypes_choiceinput_lists '.
				'WHERE questtypes_choiceinput_quest_id = ? '.
				'ORDER BY number ASC',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Get the list of values for a choiceinput-list.
		 * 
		 * @param	int	$listId	ID of list
		 * @return	array		Input values
		 */
		public function getChoiceinputChoices($listId)
		{
			return $this->db->query(
				'SELECT id, pos, text '.
				'FROM questtypes_choiceinput_choices '.
				'WHERE questtypes_choiceinput_list_id = ? '.
				'ORDER BY pos ASC',
				'i',
				$listId
			);
		}
		
		
		/**
		 * Save Character’s submitted answer for one choiceinput-list.
		 * 
		 * @param	int	$regexId	ID of list
		 * @param	int	$characterId	ID of Character
		 * @param	string	$answer		Submitted answer for this list
		 */
		public function setCharacterSubmission($listId, $characterId, $answer)
		{
			if(is_null($answer))
			{
				$this->db->query(
					'INSERT INTO questtypes_choiceinput_lists_characters '.
					'(questtypes_choiceinput_list_id, character_id, questtypes_choiceinput_choice_id) '.
					'VALUES '.
					'(?, ?, NULL) '.
					'ON DUPLICATE KEY UPDATE '.
					'questtypes_choiceinput_choice_id = NULL',
					'ii',
					$listId, $characterId
				);
			}
			else
			{
				$this->db->query(
					'INSERT INTO questtypes_choiceinput_lists_characters '.
					'(questtypes_choiceinput_list_id, character_id, questtypes_choiceinput_choice_id) '.
					'VALUES '.
					'(?, ?, ?) '.
					'ON DUPLICATE KEY UPDATE '.
					'questtypes_choiceinput_choice_id = ?',
					'iiii',
					$listId, $characterId, $answer, $answer
				);
			}
		}
		
		
		/**
		 * Get answer of one choiceinput-list submitted by Character.
		 * 
		 * @param	int	$regexId	ID of list
		 * @param	int	$characterId	ID of Character
		 * @return	int			Submitted answer for this list or null
		 */
		public function getCharacterSubmission($listId, $characterId)
		{
			$data = $this->db->query(
				'SELECT questtypes_choiceinput_choice_id '.
				'FROM questtypes_choiceinput_lists_characters '.
				'WHERE questtypes_choiceinput_list_id = ? AND character_id = ? ',
				'ii',
				$listId, $characterId
			);
			if(!empty($data)) {
				return $data[0]['questtypes_choiceinput_choice_id'];
			}
			
			
			return null;
		}
		
	}

?>
