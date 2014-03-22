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
	 * Model of the DragndropQuesttypeAgent for Drag&Drop.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class DragndropQuesttypeModel extends \hhu\z\QuesttypeModel
	{
		
		
		
		
		/**
		 * Get Drag&Drop-field.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Drag&Drop-field
		 */
		public function getDragndrop($questId)
		{
			$data = $this->db->query(
				'SELECT quest_id, questmedia_id, width, height '.
				'FROM questtypes_dragndrop '.
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
		 * Get Drop-items.
		 * 
		 * @param	int	$dragndropId	ID of Drag&Drop-field
		 * @return	array			Drop-items
		 */
		public function getDrops($dragndropId)
		{
			return $this->db->query(
				'SELECT id, top, `left`, width, height, questtypes_dragndrop_drag_id '.
				'FROM questtypes_dragndrop_drops '.
				'WHERE questtypes_dragndrop_id = ?',
				'i',
				$dragndropId
			);
		}
		
		
		/**
		 * Get Drag-items.
		 * 
		 * @param	int	$dragndropId	ID of Drag&Drop-field
		 * @return	array			Drag-items
		 */
		public function getDrags($dragndropId)
		{
			return $this->db->query(
				'SELECT id, questmedia_id '.
				'FROM questtypes_dragndrop_drags '.
				'WHERE questtypes_dragndrop_id = ?',
				'i',
				$dragndropId
			);
		}
		
		
		/**
		 * Save Character’s submitted answer for one Drag&Drop-field.
		 * 
		 * @param	int	$dropId		ID of Drop-field
		 * @param	int	$characterId	ID of Character
		 * @param	string	$answer		Submitted Drag-field-ID for this field
		 */
		public function setCharacterSubmission($dropId, $characterId, $answer)
		{
			$this->db->query(
				'INSERT INTO questtypes_dragndrop_drops_characters '.
				'(questtypes_dragndrop_drops_id, character_id, questtypes_dragndrop_drag_id) '.
				'VALUES '.
				'(?, ?, ?) '.
				'ON DUPLICATE KEY UPDATE '.
				'questtypes_dragndrop_drag_id = ?',
				'iiii',
				$dropId, $characterId, $answer, $answer
			);
		}
		
	}

?>
