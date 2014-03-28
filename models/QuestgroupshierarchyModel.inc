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
	 * Model to interact with Questgroupshierarchy-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgroupshierarchyModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new QuestgroupshierarchyModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get a Questgroup hierarchy by its ID.
		 * 
		 * throws	IdNotFoundException
		 * @param	int	$questgroupshierarchyId	ID of a Questgroup hierarchy
		 * @return	array				Questgroup hierarchy
		 */
		public function getHierarchyById($questgroupshierarchyId)
		{
			$data = $this->db->query(
				'SELECT id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url '.
				'FROM questgroupshierarchy '.
				'WHERE questgroupshierarchy.id = ?',
				'i',
				$questgroupshierarchyId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questgroupshierarchyId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get the toplevel hierarchy entries of a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of the seminary to get hierarchy for
		 * @return	array			Toplevel hierarchy
		 */
		public function getHierarchyOfSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url '.
				'FROM questgroupshierarchy '.
				'WHERE '.
					'questgroupshierarchy.seminary_id = ? AND '.
					'questgroupshierarchy.parent_questgroupshierarchy_id IS NULL '.
				'ORDER BY questgroupshierarchy.pos ASC',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get the Questgroup-Hierarchy for a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup
		 * @return	array			Hierarchy for Questgroup
		 */
		public function getHierarchyForQuestgroup($questgroupId)
		{
			$data = $this->db->query(
				'SELECT questgroups_questgroupshierarchy.parent_questgroup_id, questgroups_questgroupshierarchy.pos AS questgroup_pos, questgroupshierarchy.id, questgroupshierarchy.seminary_id, questgroupshierarchy.parent_questgroupshierarchy_id, questgroupshierarchy.pos, questgroupshierarchy.title_singular, questgroupshierarchy.title_plural, questgroupshierarchy.url '.
				'FROM questgroups_questgroupshierarchy '.
				'INNER JOIN questgroupshierarchy ON questgroupshierarchy.id = questgroups_questgroupshierarchy.questgroupshierarchy_id '.
				'WHERE questgroups_questgroupshierarchy.questgroup_id = ?',
				'i',
				$questgroupId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get the child hierarchy entries of a Questgroup hierarchy.
		 * 
		 * @param	int	$questgroupshierarchyId	ID of a Questgroup hierarchy
		 * @return	array				Child Questgroup hierarchy entries
		 */
		public function getChildQuestgroupshierarchy($questgroupshierarchyId)
		{
			return $this->db->query(
				'SELECT id, seminary_id, parent_questgroupshierarchy_id, pos, title_singular, title_plural, url '.
				'FROM questgroupshierarchy '.
				'WHERE questgroupshierarchy.parent_questgroupshierarchy_id = ? '.
				'ORDER BY questgroupshierarchy.pos ASC',
				'i',
				$questgroupshierarchyId
			);
		}
		
	}

?>
