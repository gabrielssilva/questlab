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
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
					'seminaries.id AS seminary_id, seminaries.url AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
				'FROM characters '.
				'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
				'WHERE characters.user_id = ?',
				'i',
				$userId
			);
		}
		
		
		/**
		 * Get count of Characters for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of the Seminary
		 * @param	string	$charactername	Only get Characters with the given name (optional)
		 * @return	int			Count of Characters
		 */
		public function getCharactersForSeminaryCount($seminaryId, $charactername=null)
		{
			$data = $this->db->query(
				'SELECT count(DISTINCT characters.id) AS c '.
				'FROM characters '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
				'WHERE seminaries.id = ? '.
				(!is_null($charactername) ? sprintf('AND characters.name LIKE \'%%%s%%\'', $charactername) : null),
				'i',
				$seminaryId
			);
			if(!empty($data)) {
				return $data[0]['c'];
			}
			
			
			return 0;
		}
		
		
		/**
		 * Get Characters for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of the Seminary
		 * @return	array			Characters
		 */
		public function getCharactersForSeminary($seminaryId, $onlyWithRole=false)
		{
			return $this->db->query(
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
					'seminaries.id AS seminary_id, seminaries.url AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
				'FROM characters '.
				'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
				'WHERE seminaries.id = ?'.
				($onlyWithRole ? ' AND EXISTS (SELECT character_id FROM characters_characterroles WHERE character_id = characters.id)' : null),
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get Characters for a Seminary sorted and optionally limited.
		 * 
		 * @param	int	$seminaryId	ID of the Seminary
		 * @param	string	$sort		Field to sort by
		 * @param	string	$charactername	Only get Characters with the given name (optional)
		 * @param	int	$limit		Limit amount of Characters (optional)
		 * @param	int	$offset		Offset (optional)
		 * @return	array			Characters
		 */
		public function getCharactersForSeminarySorted($seminaryId, $sort, $charactername='', $limit=null, $offset=0)
		{
			switch($sort)
			{
				case 'name':
				case 'created':
				case 'xps':
					$orders = array(
						'name'		=> 'ASC',
						'created'	=> 'DESC',
						'xps'		=> 'DESC'
					);
					
					return $this->db->query(
						'SELECT '.
							'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
							'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
							'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
							'seminaries.id AS seminary_id, seminaries.url AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
						'FROM characters '.
						'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
						'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
						'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
						'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
						'WHERE seminaries.id = ? '.
						(!is_null($charactername) ? sprintf(' AND characters.name LIKE \'%%%s%%\' ', $charactername) : null).
						sprintf(
							'ORDER BY %s.%s %s ',
							($sort == 'xps' ? 'cache_characters' : 'characters'),
							$sort,
							$orders[$sort]
						).
						(!empty($limit) ? sprintf('LIMIT %d, %d', $offset, $limit) : null),
						'i',
						$seminaryId
					);
				break;
				case 'role':
					return $this->db->query(
						'SELECT '.
							'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
							'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
							'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
							'seminaries.id AS seminary_id, seminaries.url AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
						'FROM characters '.
						'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
						'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
						'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
						'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
						'LEFT JOIN characters_characterroles ON characters_characterroles.character_id = characters.id '.
						'LEFT JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id '.
						'WHERE seminaries.id = ? '.
						(!is_null($charactername) ? sprintf(' AND characters.name LIKE \'%%%s%%\' ', $charactername) : null).
						'ORDER BY characterroles.id IS NULL, characterroles.id ASC '.
						(!empty($limit) ? sprintf('LIMIT %d, %d', $offset, $limit) : null),
						'i',
						$seminaryId
					);
				break;
				default:
					return $this->db->query(
						'SELECT '.
							'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
							'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
							'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
							'seminaries.id AS seminary_id, seminaries.url AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
						'FROM characters '.
						'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
						'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
						'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
						'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
						'LEFT JOIN characters_seminarycharacterfields ON characters_seminarycharacterfields.character_id = characters.id '.
						'LEFT JOIN seminarycharacterfields ON seminarycharacterfields.id = characters_seminarycharacterfields.seminarycharacterfield_id AND seminarycharacterfields.url = ? '.
						'WHERE seminaries.id = ? '.
						(!is_null($charactername) ? sprintf(' AND characters.name LIKE \'%%%s%%\' ', $charactername) : null).
						'ORDER BY characters_seminarycharacterfields.value ASC '.
						(!empty($limit) ? sprintf('LIMIT %d, %d', $offset, $limit) : null),
						'si',
						$sort,
						$seminaryId
					);
				break;
			}
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
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel '.
				'FROM characters '.
				'LEFT JOIN characters_charactergroups ON characters_charactergroups.character_id = characters.id '.
				'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'WHERE characters_charactergroups.charactergroup_id = ? '.
				'ORDER BY cache_characters.xps DESC',
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
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel '.
				'FROM characters '.
				'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
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
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel '.
				'FROM characters '.
				'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
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
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps,cache_characters.quest_xps,  cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel '.
				'FROM characters '.
				'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
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
		 * Get Characters with the given Character role.
		 * 
		 * @param	string	$characterrole	Character role
		 * @return	array			List of Characters
		 */
		public function getCharactersWithRole($characterrole)
		{
			return $this->db->query(
				'SELECT characters.id, characters.created, characters.user_id, characters.name, characters.url '.
				'FROM characters '.
				'LEFT JOIN characters_characterroles ON characters_characterroles.character_id = characters.id '.
				'LEFT JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id '.
				'WHERE characterroles.name = ? '.
				'ORDER BY name ASC',
				's',
				$characterrole
			);
		}
		
		
		/**
		 * Get Characters with the most amount of Achievements.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$conut		Amount of Characters to retrieve
		 * @return	array			List of Characters
		 */
		public function getCharactersWithMostAchievements($seminaryId, $count, $alsoWithDeadline=true)
		{
			return $this->db->query(
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
					'count(DISTINCT achievement_id) AS c '.
				'FROM achievements_characters '.
				'INNER JOIN achievements ON achievements.id = achievements_characters.achievement_id '.
				'INNER JOIN characters ON characters.id = achievements_characters.character_id '.
				'INNER JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'INNER JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'INNER JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'INNER JOIN characters_characterroles ON characters_characterroles.character_id = characters.id '.
				'INNER JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id AND characterroles.name = ? '.
				'WHERE achievements.seminary_id = ? AND deadline IS NULL '.
				(!$alsoWithDeadline ? 'AND achievements.deadline IS NULL ' : null).
				'GROUP BY achievements_characters.character_id '.
				'ORDER BY count(DISTINCT achievements_characters.achievement_id) DESC '.
				'LIMIT ?',
				'sii',
				'user',
				$seminaryId,
				$count
			);
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
				'SELECT count(characters.id) AS c '.
				'FROM charactertypes '.
				'INNER JOIN characters ON characters.charactertype_id = charactertypes.id '.
				'INNER JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'INNER JOIN characters_characterroles ON characters_characterroles.character_id = characters.id '.
				'INNER JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id AND characterroles.name = ? '.
				'WHERE seminary_id = ? AND cache_characters.xps > ?',
				'sid',
				'user',
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
			$data = $this->db->query(
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps,cache_characters.quest_xps,  cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel '.
				'FROM characters '.
				'INNER JOIN characters_characterroles ON characters_characterroles.character_id = characters.id '.
				'INNER JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id AND characterroles.name = ? '.
				'INNER JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'INNER JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'INNER JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'WHERE charactertypes.seminary_id = ? AND cache_characters.xps > ? '.
				'ORDER BY cache_characters.xps ASC, RAND() '.
				'LIMIT ?',
				'sidd',
				'user',
				$seminaryId, $xps, $count
			);
			$data = array_reverse($data);
			
			
			return $data;
		}
		
		
		/**
		 * Get the inferior $count Characters in the ranking.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$xps		XP-value of Character
		 * @param	int	$count		Count of Characters to determine
		 * @return	array			List of inferior Characters
		 */
		public function getInferiorCharacters($seminaryId, $characterId, $xps, $count)
		{
			return $this->db->query(
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps,cache_characters.quest_xps,  cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel '.
				'FROM characters '.
				'INNER JOIN characters_characterroles ON characters_characterroles.character_id = characters.id '.
				'INNER JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id AND characterroles.name = ? '.
				'INNER JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'INNER JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'INNER JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'WHERE charactertypes.seminary_id = ? AND cache_characters.xps <= ? AND characters.id <> ? '.
				'ORDER BY cache_characters.xps DESC, RAND() '.
				'LIMIT ?',
				'sidid',
				'user',
				$seminaryId, $xps, $characterId, $count
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
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps,cache_characters.quest_xps,  cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
					'quests_characters.created AS submission_created '.
				'FROM quests_characters '.
				'INNER JOIN characters ON characters.id = quests_characters.character_id '.
				'INNER JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'INNER JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'INNER JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'WHERE quests_characters.quest_id = ? AND quests_characters.status = ? AND NOT EXISTS ('.
					'SELECT id '.
					'FROM quests_characters AS qc '.
					'WHERE qc.quest_id = quests_characters.quest_id AND qc.character_id = quests_characters.character_id AND qc.created > quests_characters.created'.
				') '.
				'ORDER BY quests_characters.created ASC',
				'ii',
				$questId, QuestsModel::QUEST_STATUS_SOLVED
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
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps,cache_characters.quest_xps,  cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
					'quests_characters.created AS submission_created '.
				'FROM quests_characters '.
				'INNER JOIN characters ON characters.id = quests_characters.character_id '.
				'INNER JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'INNER JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'INNER JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'WHERE quests_characters.quest_id = ? AND quests_characters.status = ? AND NOT EXISTS ('.
					'SELECT id '.
					'FROM quests_characters AS qc '.
					'WHERE qc.quest_id = quests_characters.quest_id AND qc.character_id = quests_characters.character_id AND qc.created > quests_characters.created'.
				') '.
				'ORDER BY quests_characters.created ASC',
				'ii',
				$questId, QuestsModel::QUEST_STATUS_UNSOLVED
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
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps,cache_characters.quest_xps,  cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
					'quests_characters.created AS submission_created '.
				'FROM quests_characters '.
				'INNER JOIN characters ON characters.id = quests_characters.character_id '.
				'INNER JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'INNER JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'INNER JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'WHERE quests_characters.quest_id = ? AND quests_characters.status = ? AND NOT EXISTS ('.
					'SELECT id '.
					'FROM quests_characters AS qc '.
					'WHERE qc.quest_id = quests_characters.quest_id AND qc.character_id = quests_characters.character_id AND qc.created > quests_characters.created'.
				') '.
				'ORDER BY quests_characters.created ASC',
				'ii',
				$questId, QuestsModel::QUEST_STATUS_SUBMITTED
			);
		}
		
		
		/**
		 * Get all XP-levels for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			List of XP-levels
		 */
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
		 * Get Characters with the given Character role.
		 * 
		 * @param	int	$seminaryId		ID of Seminary
		 * @param	string	$characterrole		Character role
		 * @return	array				List of users
		 */
		public function getCharactersWithCharacterRole($seminaryId, $characterrole)
		{
			return $this->db->query(
				'SELECT '.
					'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
					'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
					'xplevels.id AS xplevel_id, xplevels.level AS xplevel, '.
					'seminaries.id AS seminary_id, seminaries.url AS seminary_url, seminaries.title AS seminary_title, seminaries.url AS seminary_url '.
				'FROM characters '.
				'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
				'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
				'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				'LEFT JOIN seminaries ON seminaries.id = charactertypes.seminary_id '.
				'LEFT JOIN characters_characterroles ON characters_characterroles.character_id = characters.id '.
				'LEFT JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id '.
				'WHERE seminaries.id = ? AND characterroles.name = ?',
				'is',
				$seminaryId, $characterrole
			);
		}
		
		
		/**
		 * Check if a Character name already exists.
		 * 
		 * @param	string	$name		Character name to check
		 * @param	int	$characterId	Do not check this ID (for editing)
		 * @return	boolean			Whether Character name exists or not
		 */
		public function characterNameExists($name, $characterId=null)
		{
			$data = $this->db->query(
				'SELECT id '.
				'FROM characters '.
				'WHERE name = ? OR url = ?',
				'ss',
				$name,
				\nre\core\Linker::createLinkParam($name)
			);
			
			
			return (!empty($data) && (is_null($characterId) || $characterId != $data[0]['id']));
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
		 * Edit a new Character.
		 * 
		 * @param	int	$characterId		ID of the Character to edit
		 * @param	int	$charactertypeId	ID of new type of Character
		 * @param	string	$characterName		New name for Character
		 */
		public function  editCharacter($characterId, $charactertypeId, $characterName)
		{
			$this->db->query(
				'UPDATE characters '.
				'SET charactertype_id = ?, name = ?, url = ? '.
				'WHERE id = ?',
				'issi',
				$charactertypeId,
				$characterName,
				\nre\core\Linker::createLinkParam($characterName),
				$characterId
			);
		}
		
		
		/**
		 * Delete a Character.
		 * 
		 * @param	int	$characterId	ID of the Character to delete
		 */
		public function deleteCharacter($characterId)
		{
			$this->db->query('DELETE FROM characters WHERE id = ?', 'i', $characterId);
		}
		
	}

?>
