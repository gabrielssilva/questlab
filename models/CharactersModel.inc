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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.xps, characters.xplevel, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url, seminaries.id AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url, seminaries.id AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url, media.url AS avatar_url, media.description AS avatar_description '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN avatars ON avatars.id = characters.avatar_id '.
				'LEFT JOIN avatarpictures ON avatarpictures.media_id = avatars.avatarpicture_id '.
				'LEFT JOIN media ON media.id = avatarpictures.media_id '.
				'WHERE charactertypes.seminary_id = ? AND characters.url = ?',
				'is',
				$seminaryId, $characterUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($characterUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Character by its Id.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$characterId	ID of the Character
		 * @return	array			Character data
		 */
		public function getCharacterById($characterId)
		{
			$data = $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, charactertypes.name AS charactertype_name, charactertypes.url AS charactertypes_url, media.url AS avatar_url, media.description AS avatar_description '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN avatars ON avatars.id = characters.avatar_id '.
				'LEFT JOIN avatarpictures ON avatarpictures.media_id = avatars.avatarpicture_id '.
				'LEFT JOIN media ON media.id = avatarpictures.media_id '.
				'WHERE characters.id = ?',
				'i',
				$characterId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($characterUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Calculate only XPs for a Character achieved through Quests.
		 * 
		 * @param	int	$characterId	ID of Character
		 * @return	int			Quest-XPs for Character
		 */
		public function getQuestXPsOfCharacter($characterId)
		{
			$data = $this->db->query(
				'SELECT quest_xps '.
				'FROM v_charactersxps '.
				'WHERE character_id = ?',
				'i',
				$characterId
			);
			if(!empty($data)) {
				return $data[0]['quest_xps'];
			}
			
			
			return 0;
		}
		
		
		/**
		 * Get the XP-level of a Character.
		 * 
		 * @param	string	$characterId	ID of the Character
		 * @return	array			XP-level of Character
		 */
		public function getXPLevelOfCharacters($characterId)
		{
			$data = $this->db->query(
				'SELECT xplevels.xps, xplevels.level, xplevels.name '.
				'FROM v_charactersxplevels '.
				'INNER JOIN xplevels ON xplevels.id = v_charactersxplevels.xplevel_id '.
				'WHERE v_charactersxplevels.character_id = ?',
				'i',
				$characterId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get the rank of a XP-value of a Character.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$xps		XP-value to get rank for
		 * @return	int			Rank of XP-value
		 */
		public function getXPRank($seminaryId, $xps)
		{
			$data = $this->db->query(
				'SELECT count(v_characters.id) AS c '.
				'FROM charactertypes '.
				'INNER JOIN v_characters ON v_characters.charactertype_id = charactertypes.id '.
				'WHERE seminary_id = ? AND v_characters.xps > ?',
				'id',
				$seminaryId, $xps
			);
			if(!empty($data)) {
				return $data[0]['c'] + 1;
			}
			
			
			return 1;
		}
		
	}

?>
