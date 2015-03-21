<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\models;
	
	
	/**
	 * Model to interact with Questgrouptexts-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgrouptextsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new QuestgrouptextsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}




		/**
		 * Get texts of a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	array			Texts of this Questgroup
		 */
		public function getQuestgroupTexts($questgroupId)
		{
			return $this->db->query(
				'SELECT id, pos, text, questgroup_id '.
				'FROM questgrouptexts '.
				'WHERE questgroup_id = ? '.
				'ORDER BY pos ASC',
				'i',
				$questgroupId
			);
		}


		/**
		 * Add a Questgroup text to a Questgroup.
		 * 
		 * @param	int	$userId		ID of user
		 * @param	int	$questgroupId	ID of Questgroup to add text to
		 * @param	string	$text		Text to add
		 */
		public function addQuestgrouptextToQuestgroup($userId, $questgroupId, $text)
		{
			// Get position
			$pos = $this->db->query(
				'SELECT COALESCE(MAX(pos),0)+1 AS pos '.
				'FROM questgrouptexts '.
				'WHERE questgroup_id = ?',
				'i',
				$questgroupId
			);
			$pos = $pos[0]['pos'];

			// Add Questgroup text
			$this->db->query(
				'INSERT INTO questgrouptexts '.
				'(created_user_id, questgroup_id, pos, text) '.
				'VALUES '.
				'(?, ?, ?, ?)',
				'iiis',
				$userId, $questgroupId, $pos, $text
			);
		}


		/**
		 * Edit a Questgroup text.
		 * 
		 * @param	int	$questgrouptextId	ID of Questgroup text to edit
		 * @param	string	$text			New text
		 */
		public function editQuestgrouptext($questgrouptextId, $text)
		{
			$this->db->query(
				'UPDATE questgrouptexts '.
				'SET text = ? '.
				'WHERE id = ?',
				'si',
				$text,
				$questgrouptextId
			);
		}


        /**
         * Copy Questgroup texts from one Questgroup to another.
         * 
         * @param   $userId             ID of copying user
         * @param   $sourceQuestgroupId ID of source Questgroup
         * @param   $targetQuestgroupId ID of target Questgroup
         */
        public function copyQuestgrouptexts($userId, $sourceQuestgroupId, $targetQuestgroupId)
        {
            $this->db->query(
                'INSERT INTO questgrouptexts '.
                '(created_user_id, questgroup_id, pos, text) '.
                'SELECT ?, ?, pos, text '.
                'FROM questgrouptexts '.
                'WHERE questgroup_id = ?',
                'iii',
                $userId, $targetQuestgroupId,
                $sourceQuestgroupId
            );
        }


		/**
		 * Delete a Questgroup text.
		 * 
		 * @param	array	$questgrouptext	Data of Questgroup text to delete
		 */
		public function deleteQuestgrouptext($questgrouptext)
		{
			// Delete Questgroup text
			$this->db->query('DELETE FROM questgrouptexts WHERE id = ?', 'i', $questgrouptext['id']);

			// Adjust positions
			$this->db->query(
				'UPDATE questgrouptexts '.
				'SET pos = pos - 1 '.
				'WHERE questgroup_id = ? AND pos > ?',
				'ii',
				$questgrouptext['questgroup_id'],
				$questgrouptext['pos']
			);
		}

	}

?>
