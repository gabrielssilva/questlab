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
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('questgroupshierarchy', 'questgroups', 'quests', 'questtexts');
		
		
		
		
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
		 * Get the first text of a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	string			First text of this Questgroup or NULL
		 */
		public function getFirstQuestgroupText($questgroupId)
		{
			// Text of Questgroup itself
			$questgroupTexts = $this->getQuestgroupTexts($questgroupId);
			if(!empty($questgroupTexts)) {
				return $questgroupTexts[0]['text'];
			}
			
			// Text of first Quest
			$quest = $this->Quests->getFirstQuestOfQuestgroup($questgroupId);
			if(!is_null($quest))
			{
				$questText = $this->Questtexts->getFirstQuestText($quest['id']);
				if(!is_null($questText)) {
					return $questText;
				}
			}
			
			// Text of ChildQuestgroups
			$questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroupId);
			$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
			foreach($childQuestgroupshierarchy as &$hierarchy)
			{
				// Get Questgroups
				$questgroups = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id'], $questgroupId);
				foreach($questgroups as &$group)
				{
					$childQuestgroupText = $this->getFirstQuestgroupText($group['id']);
					if(!is_null($childQuestgroupText)) {
						return $childQuestgroupText;
					}
				}
			}
			
			
			// No text found
			return null;
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
