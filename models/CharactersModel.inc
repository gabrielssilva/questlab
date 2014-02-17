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
	 * Model to interact with Characters-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactersModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new CharactersModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all characters for an user.
		 * 
		 * @param	int	$userId	ID of the user
		 * @return	array		Characters
		 */
		public function getCharactersForUser($userId)
		{
			return $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.xps, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url, seminaries.id AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
				'WHERE user_id = ?',
				'i',
				$userId
			);
		}
		
		
		/**
		 * Get Characters for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of the Seminary
		 * @return	array			Characters
		 */
		public function getCharactersForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url, seminaries.id AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
				'WHERE seminaries.id = ?',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get Characters for a Character group.
		 * 
		 * @param	int	$groupId	ID of the Character group
		 * @return	array			Characters
		 */
		public function getCharactersForGroup($groupId)
		{
			return $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters_charactergroups.is_leader, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN characters_charactergroups ON characters_charactergroups.character_id = characters.id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE characters_charactergroups.charactergroup_id = ?',
				'i',
				$groupId
			);
		}
		
		
		/**
		 * Get the character of a user for a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$userId		ID of the user
		 * @param	int	$seminaryId	ID of the Seminary
		 * @return	array			Character data
		 */
		public function getCharacterForUserAndSeminary($userId, $seminaryId)
		{
			$data = $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE characters.user_id = ? AND charactertypes.seminary_id = ?',
				'ii',
				$userId, $seminaryId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($userId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Character by its Url.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$seminaryId	ID of the Seminary
		 * @param	string	$characterUrl	URL-name of the Character
		 * @return	array			Character data
		 */
		public function getCharacterByUrl($seminaryId, $characterUrl)
		{
			$data = $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE charactertypes.seminary_id = ? AND characters.url = ?',
				'is',
				$seminaryId, $characterUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($characterUrl);
			}
			
			
			return $data[0];
		}
		
	}

?>
