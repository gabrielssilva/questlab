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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, seminaries.id AS seminary_id, seminaries.url AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, seminaries.id AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
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
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
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
		 * Get Characters with the most amount of Achievements.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$conut		Amount of Characters to retrieve
		 * @return	array			List of Characters
		 */
		public function getCharactersWithMostAchievements($seminaryId, $count)
		{
			return $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, count(DISTINCT achievement_id) AS c '.
				'FROM achievements_characters '.
				'LEFT JOIN achievements ON achievements.id = achievements_characters.achievement_id '.
				'LEFT JOIN v_characters AS characters ON characters.id = achievements_characters.character_id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE achievements.seminary_id = ? '.
				'GROUP BY character_id '.
				'ORDER BY count(DISTINCT achievement_id) DESC '.
				'LIMIT ?',
				'ii',
				$seminaryId,
				$count
			);
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
		
		
		/**
		 * Get the superior $count Characters in the ranking.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$xps		XP-value of Character
		 * @param	int	$count		Count of Characters to determine
		 * @return	array			List of superior Characters
		 */
		public function getSuperiorCharacters($seminaryId, $xps, $count)
		{
			return $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
				'FROM v_characters AS characters  '.
				'INNER JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE charactertypes.seminary_id = ? AND characters.xps > ? '.
				'ORDER BY characters.xps ASC '.
				'LIMIT ?',
				'idd',
				$seminaryId, $xps, $count
			);
		}
		
		
		/**
		 * Get the inferior $count Characters in the ranking.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$xps		XP-value of Character
		 * @param	int	$count		Count of Characters to determine
		 * @return	array			List of inferior Characters
		 */
		public function getInferiorCharacters($seminaryId, $xps, $count)
		{
			return $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
				'FROM v_characters AS characters  '.
				'INNER JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE charactertypes.seminary_id = ? AND characters.xps < ? '.
				'ORDER BY characters.xps DESC '.
				'LIMIT ?',
				'idd',
				$seminaryId, $xps, $count
			);
		}
		
		
		/**
		 * Get Characters that solved a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to get Characters for
		 * @return	array			Characters data
		 */
		public function getCharactersSolvedQuest($questId)
		{
			return $data = $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE EXISTS ('.
					'SELECT character_id FROM quests_characters WHERE character_id = characters.id AND quest_id = ? AND status = ?'.
				')',
				'ii',
				$questId,
				QuestsModel::QUEST_STATUS_SOLVED
			);
		}
		
		
		/**
		 * Get Characters that did not solv a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to get Characters for
		 * @return	array			Characters data
		 */
		public function getCharactersUnsolvedQuest($questId)
		{
			return $data = $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE EXISTS ('.
					'SELECT character_id FROM quests_characters WHERE character_id = characters.id AND quest_id = ? AND status = ?'.
				') AND NOT EXISTS ('.
					'SELECT character_id FROM quests_characters WHERE character_id = characters.id AND quest_id = ? AND status = ?'.
				')',
				'iiii',
				$questId, QuestsModel::QUEST_STATUS_UNSOLVED,
				$questId, QuestsModel::QUEST_STATUS_SOLVED
			);
		}
		
		
		/**
		 * Get Characters that sent a submission for a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to get Characters for
		 * @return	array			Characters data
		 */
		public function getCharactersSubmittedQuest($questId)
		{
			return $data = $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'WHERE ('.
					'SELECT status '.
					'FROM quests_characters '.
					'WHERE quest_id = ? AND character_id = characters.id '.
					'ORDER BY created DESC '.
					'LIMIT 1'.
				') = ?',
				'ii',
				$questId, QuestsModel::QUEST_STATUS_SUBMITTED
			);
		}
		
		
		public function getXPLevelsForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT id, xps, level, name '.
				'FROM xplevels '.
				'WHERE seminary_id = ? '.
				'ORDER BY level ASC',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Check if a Character name already exists.
		 * 
		 * @param	string	$name	Character name to check
		 * @return	boolean		Whether Character name exists or not
		 */
		public function characterNameExists($name)
		{
			$data = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM characters '.
				'WHERE name = ? OR url = ?',
				'ss',
				$name,
				\nre\core\Linker::createLinkParam($name)
			);
			if(!empty($data)) {
				return ($data[0]['c'] > 0);
			}
			
			
			return false;
		}
		
		
		/**
		 * Create a new Character.
		 * 
		 * @param	int	$userId			User-ID that creates the new character
		 * @param	int	$charactertypeId	ID of type of new Character
		 * @param	string	$characterName		Name for the new Character
		 * @return	int				ID of Character
		 */
		public function createCharacter($userId, $charactertypeId, $characterName)
		{
			$this->db->query(
				'INSERT INTO characters '.
				'(user_id, charactertype_id, name, url) '.
				'VALUES '.
				'(?, ?, ?, ?)',
				'iiss',
				$userId,
				$charactertypeId,
				$characterName,
				\nre\core\Linker::createLinkParam($characterName)
			);
			
			
			return $this->db->getInsertId();
		}
		
		
		/**
		 * Set the value of a Seminary field for a Character.
		 * 
		 * @param	int	$characterId			ID of Character
		 * @param	int	$seminarycharacterfieldId	ID of seminarycharacterfield to set value of
		 * @param	string	$value				Value to set
		 */
		public function setSeminaryFieldOfCharacter($characterId, $seminarycharacterfieldId, $value)
		{
			$this->db->query(
				'INSERT INTO characters_seminarycharacterfields '.
				'(character_id, seminarycharacterfield_id, value) '.
				'VALUES '.
				'(?, ?, ?) '.
				'ON DUPLICATE KEY UPDATE '.
				'value = ?',
				'iiss',
				$characterId,
				$seminarycharacterfieldId,
				$value,
				$value
			);
		}
		
		
		/**
		 * Get Characters with the given Character role.
		 * 
		 * @param	int	$seminaryId		ID of Seminary
		 * @param	string	$characterrole		Character role
		 * @return	array				List of users
		 */
		public function getCharactersWithCharacterRole($seminaryId, $characterrole)
		{
			return $this->db->query(
				'SELECT characters.id, characters.created, characters.charactertype_id, characters.name, characters.url, characters.user_id, characters.xps, characters.xplevel, characters.avatar_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, seminaries.id AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
				'FROM v_characters AS characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
				'LEFT JOIN characters_characterroles ON characters_characterroles.character_id = characters.id '.
				'LEFT JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id '.
				'WHERE seminaries.id = ? AND characterroles.name = ?',
				'is',
				$seminaryId, $characterrole
			);
		}
		
	}

?>
