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
	 * Model of the CharactergroupsAgent to interact with
	 * Charactergroups-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactergroupsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new CharactergroupsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get Character groups-groups of a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of the corresponding Seminary
		 * @return	array			Character groups-groups data
		 */
		public function getGroupsroupsForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT id, name, url '.
				'FROM charactergroupsgroups '.
				'WHERE seminary_id = ?',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get a Character groups-group by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$seminaryId	ID of the corresponding Seminary
		 * @param	string	$groupsgroupUrl	URL-name of the Character groups-group
		 * @return	array			Character groups-group data
		 */
		public function getGroupsgroupByUrl($seminaryId, $groupsgroupUrl)
		{
			$data = $this->db->query(
				'SELECT id, name, url '.
				'FROM charactergroupsgroups '.
				'WHERE seminary_id = ? AND url = ?',
				'is',
				$seminaryId, $groupsgroupUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($groupsgroupUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get Character groups for a Character groups-group.
		 * 
		 * @param	int	$groupsgroupId	ID of the Character groups-group
		 * @return	array			Character groups
		 */
		public function getGroupsForGroupsgroup($groupsgroupId)
		{
			return $this->db->query(
				'SELECT id, name, url '.
				'FROM charactergroups '.
				'WHERE charactergroupsgroup_id = ?',
				'i',
				$groupsgroupId
			);
		}
		
		
		/**
		 * Get a Character group by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$groupsgroupId	ID of the Character groups-group
		 * @param	string	$groupUrl	URL-name of the Character group
		 * @return	array			Character group data
		 */
		public function getGroupByUrl($groupsgroupId, $groupUrl)
		{
			$data = $this->db->query(
				'SELECT id, name, url '.
				'FROM charactergroups '.
				'WHERE charactergroupsgroup_id = ? AND url = ?',
				'is',
				$groupsgroupId, $groupUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($groupUrl);
			}
			
			
			return $data[0];
		}
		
	}

?>
