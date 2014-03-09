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
			
			
			return $data[0];
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
				'SELECT number, regex '.
				'FROM questtypes_textinput_regexs '.
				'WHERE questtypes_textinput_quest_id = ? '.
				'ORDER BY number ASC',
				'i',
				$questId
			);
		}
		
	}

?>
