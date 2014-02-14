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
	 * Model to interact with Questgroups-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgroupsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new QuestgroupsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all Questgroups for a Questgroup hierarchy.
		 * 
		 * @param	int	$hierarchyId		ID of the Questgroup hierarchy to get Questgroups for
		 * @param	int	$parentQuestgroupId	ID of the parent Questgroup hierarchy
		 * @return	array				Questgroups for the given hierarchy
		 */
		public function getQuestgroupsForHierarchy($hierarchyId, $parentQuestgroupId=null)
		{
			if(is_null($parentQuestgroupId))
			{
				return $this->db->query(
					'SELECT id, questgroupshierarchy_id, pos, title, url '.
					'FROM questgroups '.
					'WHERE questgroups.questgroupshierarchy_id = ? AND parent_questgroup_id IS NULL '.
					'ORDER BY questgroups.pos ASC',
					'i',
					$hierarchyId
				);
			}
			else
			{
				return $this->db->query(
					'SELECT id, questgroupshierarchy_id, pos, title, url '.
					'FROM questgroups '.
					'WHERE questgroups.questgroupshierarchy_id = ? AND parent_questgroup_id = ? '.
					'ORDER BY questgroups.pos ASC',
					'ii',
					$hierarchyId, $parentQuestgroupId
				);
			}
		}
		
		
		/**
		 * Get a Questgroup by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	array			Questgroup data
		 */
		public function getQuestgroupById($questgroupId)
		{
			$data = $this->db->query(
				'SELECT id, questgroupshierarchy_id, parent_questgroup_id, pos, title, url, questgroupspicture_id '.
				'FROM questgroups '.
				'WHERE questgroups.id = ?',
				'i',
				$questgroupId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questgroupId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Questgroup by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$seminaryId	ID of the corresponding seminary
		 * @param	string	$questgroupURL	URL-title of a Questgroup
		 * @return	array			Questgroup data
		 */
		public function getQuestgroupByUrl($seminaryId, $questgroupUrl)
		{
			$data = $this->db->query(
				'SELECT questgroups.id, questgroups.questgroupshierarchy_id, questgroups.parent_questgroup_id, questgroups.pos, questgroups.title, questgroups.url, questgroups.questgroupspicture_id '.
				'FROM questgroups '.
				'LEFT JOIN questgroupshierarchy ON questgroupshierarchy.id = questgroups.questgroupshierarchy_id '.
				'WHERE questgroupshierarchy.seminary_id = ? AND questgroups.url = ?',
				'is',
				$seminaryId, $questgroupUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questgroupUrl);
			}
			
			
			return $data[0];
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
				'SELECT id, pos, text '.
				'FROM questgrouptexts '.
				'WHERE questgroup_id = ? '.
				'ORDER BY pos ASC',
				'i',
				$questgroupId
			);
		}
		
	}

?>
