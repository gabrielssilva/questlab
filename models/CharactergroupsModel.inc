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
				'SELECT id, name, url, preferred '.
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
				'SELECT id, name, url, preferred '.
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
		 * Get a Character groups-group by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$groupsgroupId	ID of the Character groups-group
		 * @return	array			Character groups-group data
		 */
		public function getGroupsgroupById($groupsgroupId)
		{
			$data = $this->db->query(
				'SELECT id, name, url, preferred '.
				'FROM charactergroupsgroups '.
				'WHERE id = ?',
				'i',
				$groupsgroupId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($groupsgroupId);
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
				'SELECT id, name, url, xps, motto '.
				'FROM v_charactergroups '.
				'WHERE charactergroupsgroup_id = ?',
				'i',
				$groupsgroupId
			);
		}
		
		
		/**
		 * Get Character groups for a Character.
		 * 
		 * @param	int	$characterId	ID of the Character
		 * @return	array			Character groups
		 */
		public function getGroupsForCharacter($characterId)
		{
			return $this->db->query(
				'SELECT charactergroups.id, charactergroups.charactergroupsgroup_id, charactergroups.name, charactergroups.url, charactergroups.xps, charactergroupsgroups.id AS charactergroupsgroup_id, charactergroupsgroups.name AS charactergroupsgroup_name, charactergroupsgroups.url AS charactergroupsgroup_url '.
				'FROM characters_charactergroups '.
				'LEFT JOIN v_charactergroups AS charactergroups ON charactergroups.id = characters_charactergroups.charactergroup_id '.
				'LEFT JOIN charactergroupsgroups ON charactergroupsgroups.id = charactergroups.charactergroupsgroup_id '.
				'WHERE characters_charactergroups.character_id = ?',
				'i',
				$characterId
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
				'SELECT id, name, url, xps, motto '.
				'FROM v_charactergroups '.
				'WHERE charactergroupsgroup_id = ? AND url = ?',
				'is',
				$groupsgroupId, $groupUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($groupUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get the rank of a XP-value of a Character.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$xps		XP-value to get rank for
		 * @return	int			Rank of XP-value
		 */
		public function getXPRank($groupsgroupId, $xps)
		{
			$data = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM v_charactergroups '.
				'WHERE charactergroupsgroup_id = ? AND xps > ?',
				'id',
				$groupsgroupId, $xps
			);
			if(!empty($data)) {
				return $data[0]['c'] + 1;
			}
			
			
			return 1;
		}
		
	}

?>
