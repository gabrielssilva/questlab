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
	 * Model to interact with Achievements-tables.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class AchievementsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new AchievementsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get an Achievement by its URL.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	string	$achievementUrl	URL-title of Achievement
		 * @return	array			Achievement data
		 */
		public function getAchievementByUrl($seminaryId, $achievementUrl)
		{
			$data = $this->db->query(
				'SELECT achievements.id, achievementconditions.condition, seminary_id, pos, title, url, description, progress, hidden, only_once, all_conditions, deadline, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'LEFT JOIN achievementconditions ON achievementconditions.id = achievements.achievementcondition_id '.
				'WHERE seminary_id = ? AND url = ?',
				'is',
				$seminaryId, $achievementUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($achievementUrl);
			}
			
			
			return $data[0];
		}


		/**
		 * Get an Achievement by its ID.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @return	array			Achievement data
		 */
		public function getAchievementById($achievementId)
		{
			$data = $this->db->query(
				'SELECT achievements.id, achievementconditions.condition, seminary_id, pos, title, url, description, progress, hidden, only_once, all_conditions, deadline, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'LEFT JOIN achievementconditions ON achievementconditions.id = achievements.achievementcondition_id '.
				'WHERE achievements.id = ?',
				'i',
				$achievementId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($achievementId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get all not yet achieved Achievements for a Seminary that can
		 * only be achieved once (only by one Character).
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			Achievements data
		 */
		public function getUnachievedOnlyOnceAchievementsForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT achievements.id, achievements.pos, achievementconditions.condition, title, url, description, progress, hidden, only_once, all_conditions, deadline, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'LEFT JOIN achievementconditions ON achievementconditions.id = achievements.achievementcondition_id '.
				'WHERE achievements.seminary_id = ? AND only_once = 1 AND NOT EXISTS ('.
					'SELECT character_id '.
					'FROM achievements_characters '.
					'WHERE achievements_characters.achievement_id = achievements.id'.
				')',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get all Achievements that have a deadline.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			Achievements data
		 */
		public function getDeadlineAchievements($seminaryId)
		{
			return $this->db->query(
				'SELECT achievements.id, achievements.pos, achievementconditions.condition, title, url, description, progress, hidden, only_once, all_conditions, deadline, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'LEFT JOIN achievementconditions ON achievementconditions.id = achievements.achievementcondition_id '.
				'WHERE achievements.seminary_id = ? AND deadline IS NOT NULL '.
				'ORDER BY deadline ASC',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get seldom Achievements.
		 * 
		 * @param	int	$seminaryId		ID of Seminary
		 * @param	int	$count			Number of Achievements to retrieve
		 * @param	bool	$alsoWithDeadline	Include Achievements with deadline (optional)
		 * @return	array				List of seldom Achievements
		 */
		public function getSeldomAchievements($seminaryId, $count, $alsoWithDeadline=true)
		{
			return $this->db->query(
				'SELECT achievements.id, achievements.pos, achievements.title, achievements.url, achievements.description, achievements.progress, achievements.hidden, achievements.unachieved_achievementsmedia_id, achievements.achieved_achievementsmedia_id, count(DISTINCT achievements_characters.character_id) AS c '.
				'FROM achievements_characters '.
				'INNER JOIN characters_characterroles ON characters_characterroles.character_id = achievements_characters.character_id '.
				'INNER JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id AND characterroles.name = ? '. 
				'LEFT JOIN achievements ON achievements.id = achievements_characters.achievement_id '.
				'WHERE achievements.seminary_id = ? AND achievements.only_once = 0 '.
				(!$alsoWithDeadline ? 'AND achievements.deadline IS NULL ' : null).
				'GROUP BY achievements_characters.achievement_id '.
				'ORDER BY count(DISTINCT achievements_characters.character_id) ASC '.
				'LIMIT ?',
				'sii',
				'user',
				$seminaryId,
				$count
			);
		}
		
		
		/**
		 * Get all achieved Achievements for a Character.
		 * 
		 * @param	int	$characterId	ID of Character
		 * @param	bool	$alsoWithDeadline	Include Achievements with deadline (optional)
		 * @return	array			Achievements data
		 */
		public function getAchievedAchievementsForCharacter($characterId, $alsoWithDeadline=true)
		{
			return $this->db->query(
				'SELECT achievements.id, achievements.pos, achievements_characters.created, achievements.title, achievements.url, achievements.description, achievements.progress, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'INNER JOIN achievements_characters ON achievements_characters.achievement_id = achievements.id '.
				'WHERE achievements_characters.character_id = ? '.
				(!$alsoWithDeadline ? 'AND achievements.deadline IS NULL ' : null).
				'ORDER BY achievements_characters.created DESC',
				'i',
				$characterId
			);
		}
		
		
		/**
		 * Get all not yet achieved Achievements for a Character.
		 * 
		 * @param	int	$seminaryId		ID of Seminary
		 * @param	int	$characterId		ID of Character
		 * @param	boolean	$includeOnlyOnce	Include Achievements that can only be achieved by one Character
		 * @param	boolean	$alsoWithDeadline	Include milestone Achievements
		 * @return	array				Achievements data
		 */
		public function getUnachhievedAchievementsForCharacter($seminaryId, $characterId, $includeOnlyOnce=false, $alsoWithDeadline=true)
		{
			return $this->db->query(
				'SELECT achievements.id, achievements.pos, achievementconditions.condition, title, url, description, progress, hidden, only_once, all_conditions, deadline, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'LEFT JOIN achievementconditions ON achievementconditions.id = achievements.achievementcondition_id '.
				'WHERE achievements.seminary_id = ? AND only_once <= ? AND NOT EXISTS ('.
					'SELECT character_id '.
					'FROM achievements_characters '.
					'WHERE '.
						'achievements_characters.achievement_id = achievements.id AND '.
						'achievements_characters.character_id = ?'.
				') '.
				(!$alsoWithDeadline ? 'AND achievements.deadline IS NULL ' : null).
				'ORDER BY achievements.pos ASC',
				'iii',
				$seminaryId,
				$includeOnlyOnce,
				$characterId
			);
		}
		
		
		/**
		 * Get the amount of Achievement for a Seminary.
		 * 
		 * @param	int	$seminaryId		ID of Seminary
		 * @param	boolean	$includeOnlyOnce	Include Achievements that can only be achieved by one Character
		 * @param	boolean	$alsoWithDeadline	Include milestone Achievements
		 * @return	int				Count of Achievements
		 */
		public function getAchievementsCountForSeminary($seminaryId, $includeOnlyOnce=false, $alsoWithDeadline=true)
		{
			$data = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM achievements '.
				'WHERE seminary_id = ? AND only_once <= ?'.
				(!$alsoWithDeadline ? ' AND achievements.deadline IS NULL ' : null),
				'ii',
				$seminaryId,
				$includeOnlyOnce
			);
			if(!empty($data)) {
				return $data[0]['c'];
			}
			
			
			return 0;
		}


		/**
		 * Get all Achievements for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			List of Achievements
		 */
		public function getAchievementsForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT id, created, created_user_id, achievementcondition_id, pos, title, url, description, progress, hidden, only_once, all_conditions, deadline, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'WHERE seminary_id = ? '.
				'ORDER BY pos ASC',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get the rank for the number of achieved Achievements.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$xps		Amount of achieved Achievements
		 * @return	int			Rank of Achievements count
		 */
		public function getCountRank($seminaryId, $count)
		{
			$data = $this->db->query(
				'SELECT count(*) AS c '.
				'FROM ('.
					'SELECT count(DISTINCT achievement_id) '.
					'FROM achievements_characters '.
					'LEFT JOIN achievements ON achievements.id = achievements_characters.achievement_id '.
					'WHERE achievements.seminary_id = ? '.
					'GROUP BY character_id '.
					'HAVING count(DISTINCT achievement_id) > ?'.
				') AS ranking',
				'ii',
				$seminaryId,
				$count
			);
			if(!empty($data)) {
				return $data[0]['c'] + 1;
			}
			
			
			return 1;
		}
		
		
		/**
		 * Get all date conditions for an Achievement.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @return	array			Date conditions
		 */
		public function getAchievementConditionsDate($achievementId)
		{
			return $this->db->query(
				'SELECT id, `select` '.
				'FROM achievementconditions_date '.
				'WHERE achievement_id = ?',
				'i',
				$achievementId
			);
		}
		
		
		/**
		 * Check a date condition.
		 * 
		 * @param	string	$select	SELECT-string with date-functions
		 * @return	boolean		Result
		 */
		public function checkAchievementConditionDate($select)
		{
			$data = $this->db->query(
				'SELECT ('.$select.') AS got '
			);
			if(!empty($data)) {
				return ($data[0]['got'] == 1);
			}
			
			
			return false;
		}


		/**
		 * Add a new date condition.
		 * 
		 * @param	int	$userId		ID of creating user
		 * @param	int	$achievementId	ID of Achievement to add condition to
		 * @param	string	$select		SELECT-string for condition
		 */
		public function addAchievementConditionDate($userId, $achievementId, $select)
		{
			$this->db->query(
				'INSERT INTO achievementconditions_date '.
				'(created_user_id, achievement_id, `select`) '.
				'VALUES '.
				'(?, ?, ?)',
				'iis',
				$userId,
				$achievementId,
				$select
			);

		}


		/**
		 * Edit a date condition.
		 * 
		 * @param	int	$conditionId	ID of condition to edit
		 * @param	string	$select		New SELECT-string for condition
		 */
		public function editAchievementConditionDate($conditionId, $select)
		{
			$this->db->query(
				'UPDATE achievementconditions_date '.
				'SET `select` = ? '.
				'WHERE id = ?',
				'si',
				$select,
				$conditionId
			);
		}


		/**
		 * Delete a date condition.
		 * 
		 * @param	int	$conditionId	ID of condition to delete
		 */
		public function deleteAchievementConditionDate($conditionId)
		{
			$this->db->query('DELETE FROM achievementconditions_date WHERE id = ?', 'i', $conditionId);
		}
		
		
		/**
		 * Get all Character conditions for an Achievement.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @return	array			Character conditions
		 */
		public function getAchievementConditionsCharacter($achievementId)
		{
			return $this->db->query(
				'SELECT id, field, value '.
				'FROM achievementconditions_character '.
				'WHERE achievement_id = ?',
				'i',
				$achievementId
			);
		}
		
		
		/**
		 * Check a Character condition.
		 * 
		 * @param	string	$field		Field to check
		 * @param	int	$value		The value the field has to match
		 * @param	int	$characterId	ID of Character
		 * @return	boolean			Result
		 */
		public function checkAchievementConditionCharacter($field, $value, $characterId)
		{
			$data = $this->db->query(
				"SELECT ($field >= $value) AS got ".
				'FROM ('.
					'SELECT '.
						'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
						'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
						'xplevels.id AS xplevel_id, xplevels.level AS xplevel '.
					'FROM characters '.
					'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
					'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
					'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				') AS c '.
				'WHERE c.id = ?',
				'i',
				$characterId
			);
			if(!empty($data)) {
				return ($data[0]['got'] == 1);
			}
			
			
			
			
			
			return false;
		}
		
		
		/**
		 * Get the progress for a Character condition.
		 * 
		 * @param	string	$field		Field to check
		 * @param	int	$value		The value the field has to match
		 * @param	int	$characterId	ID of Character
		 * @return	float			Percentage progress
		 */
		public function getAchievementConditionCharacterProgress($field, $value, $characterId)
		{
			$data = $this->db->query(
				"SELECT $field AS field ".
				'FROM ('.
					'SELECT '.
						'characters.id, characters.created, characters.user_id, characters.name, characters.url, cache_characters.xps, cache_characters.quest_xps, cache_characters.avatar_id, '.
						'charactertypes.id AS charactertype_id, charactertypes.name AS charactertype_name, charactertypes.url AS charactertype_url, '.
						'xplevels.id AS xplevel_id, xplevels.level AS xplevel '.
					'FROM characters '.
					'LEFT JOIN cache_characters ON cache_characters.character_id = characters.id '.
					'LEFT JOIN charactertypes ON charactertypes.id = characters.charactertype_id '.
					'LEFT JOIN xplevels ON xplevels.id = cache_characters.xplevel_id '.
				') AS c '.
				'WHERE c.id = ?',
				'i',
				$characterId
			);
			if(!empty($data)) {
				return $data[0]['field'] / $value;
			}
			
			
			return 0;
		}


		/**
		 * Add a new Character condition.
		 * 
		 * @param	int	$userId		ID of creating user
		 * @param	int	$achievementId	ID of Achievement to add condition to
		 * @param	string	$field		Field to match
		 * @param	string	$value		Value to match
		 */
		public function addAchievementConditionCharacter($userId, $achievementId, $field, $value)
		{
			$this->db->query(
				'INSERT INTO achievementconditions_character '.
				'(created_user_id, achievement_id, field, value) '.
				'VALUES '.
				'(?, ?, ?, ?)',
				'iiss',
				$userId,
				$achievementId,
				$field,
				$value
			);

		}


		/**
		 * Edit a Character condition.
		 * 
		 * @param	int	$conditionId	ID of condition to edit
		 * @param	string	$field		Field to match
		 * @param	string	$value		Value to match
		 */
		public function editAchievementConditionCharacter($conditionId, $field, $value)
		{
			$this->db->query(
				'UPDATE achievementconditions_character '.
				'SET field = ?, value = ? '.
				'WHERE id = ?',
				'ssi',
				$field,
				$value,
				$conditionId
			);
		}


		/**
		 * Delete a Character condition.
		 * 
		 * @param	int	$conditionId	ID of condition to delete
		 */
		public function deleteAchievementConditionCharacter($conditionId)
		{
			$this->db->query('DELETE FROM achievementconditions_character WHERE id = ?', 'i', $conditionId);
		}
		
		
		/**
		 * Get all Quest conditions for an Achievement.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @return	array			Quest conditions
		 */
		public function getAchievementConditionsQuest($achievementId)
		{
			return $this->db->query(
				'SELECT id, field, `count`, value, quest_id, status, groupby '.
				'FROM achievementconditions_quest '.
				'WHERE achievement_id = ?',
				'i',
				$achievementId
			);
		}
		
		
		/**
		 * Check a Quest condition.
		 * 
		 * @param	string	$field		Field to check
		 * @param	boolean	$count		Conut field-value
		 * @param	int	$value		The value the field has to match
		 * @param	int	$status		Status of Quest or NULL
		 * @param	string	$groupby	Field to group or NULL
		 * @param	int	$questId	ID of related Quest or NULL
		 * @param	int	$characterId	ID of Character
		 * @return	boolean			Result
		 */
		public function checkAchievementConditionQuest($field, $count, $value, $status, $groupby, $questId, $characterId)
		{
			$data = $this->db->query(
				'SELECT ('.(
					$count
					? "count($field) >= $value"
					: "$field = $value"
				). ') AS got '.
				'FROM quests_characters '.
				'WHERE '.
					'character_id = ?'.
					(!is_null($questId) ? " AND quest_id = $questId" : '').
					(!is_null($status) ? " AND status = $status" : '').
				(!is_null($groupby) ? " GROUP BY $groupby" : ''),
				'i',
				$characterId
			);
			if(!empty($data)) {
				foreach($data as &$datum) {
					if($datum['got'] == 1) {
						return true;
					}
				}
			}
			
			
			return false;
		}
		
		
		/**
		 * Get the progress for a Quest condition.
		 * 
		 * @param	string	$field		Field to check
		 * @param	boolean	$count		Conut field-value
		 * @param	int	$value		The value the field has to match
		 * @param	int	$status		Status of Quest or NULL
		 * @param	string	$groupby	Field to group or NULL
		 * @param	int	$questId	ID of related Quest or NULL
		 * @param	int	$characterId	ID of Character
		 * @return	float			Percentage progress
		 */
		public function getAchievementConditionQuestProgress($field, $count, $value, $status, $groupby, $questId, $characterId)
		{
			$data = $this->db->query(
				'SELECT '.(
					$count
					? "count($field)"
					: "$field"
				). ' AS field '.
				'FROM quests_characters '.
				'WHERE '.
					'character_id = ?'.
					(!is_null($questId) ? " AND quest_id = $questId" : '').
					(!is_null($status) ? " AND status = $status" : '').
				(!is_null($groupby) ? " GROUP BY $groupby" : ''),
				'i',
				$characterId
			);
			if(!empty($data))
			{
				$maxField = 0;
				foreach($data as &$datum) {
					$maxField = max($maxField, intval($datum['field']));
				}
				
				return $maxField / $value;
			}
			
			
			return 0;
		}


		/**
		 * Add a new Quest condition.
		 * 
		 * @param	int	$userId		ID of creating user
		 * @param	int	$achievementId	ID of Achievement to add condition to
		 * @param	string	$field		Field to match
		 * @param	boolean	$count		Count the value
		 * @param	string	$value		Value to match
		 * @param	int	$questId	ID of Quest (optional)
		 * @param	int	$status		Quest status (optional)
		 * @param	string	$groupby	Field to group by (optional)
		 */
		public function addAchievementConditionQuest($userId, $achievementId, $field, $count, $value, $questId=null, $status=null, $groupby=null)
		{
			$this->db->query(
				'INSERT INTO achievementconditions_quest '.
				'(created_user_id, achievement_id, field, count, value, quest_id, status, groupby) '.
				'VALUES '.
				'(?, ?, ?, ?, ?, ?, ?, ?)',
				'iisisiis',
				$userId,
				$achievementId,
				$field,
				$count,
				$value,
				$questId,
				$status,
				$groupby
			);

		}


		/**
		 * Edit a Quest condition.
		 * 
		 * @param	int	$conditionId	ID of condition to edit
		 * @param	string	$field		Field to match
		 * @param	boolean	$count		Count the value
		 * @param	string	$value		Value to match
		 * @param	int	$questId	ID of Quest (optional)
		 * @param	int	$status		Quest status (optional)
		 * @param	string	$groupby	Field to group by (optional)
		 */
		public function editAchievementConditionQuest($conditionId, $field, $count, $value, $questId=null, $status=null, $groupby=null)
		{
			$this->db->query(
				'UPDATE achievementconditions_quest '.
				'SET field = ?, count = ?, value = ?, quest_id = ?, status = ?, groupby = ? '.
				'WHERE id = ?',
				'sisiisi',
				$field,
				$count,
				$value,
				$questId,
				$status,
				$groupby,
				$conditionId
			);
		}


		/**
		 * Delete a Quest condition.
		 * 
		 * @param	int	$conditionId	ID of condition to delete
		 */
		public function deleteAchievementConditionQuest($conditionId)
		{
			$this->db->query('DELETE FROM achievementconditions_quest WHERE id = ?', 'i', $conditionId);
		}
		
		
		/**
		 * Get all Metaachievement conditions for an Achievement.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @return	array			Metaachievement conditions
		 */
		public function getAchievementConditionsAchievement($achievementId)
		{
			return $this->db->query(
				'SELECT id, field, `count`, value, meta_achievement_id, groupby '.
				'FROM achievementconditions_achievement '.
				'WHERE achievement_id = ?',
				'i',
				$achievementId
			);
		}
		
		
		/**
		 * Check a Metaachievement condition.
		 * 
		 * @param	string	$field			Field to check
		 * @param	boolean	$count			Conut field-value
		 * @param	int	$value			The value the field has to match
		 * @param	string	$groupby		Field to group or NULL
		 * @param	int	$metaAchievementId	ID of related Achievement or NULL
		 * @param	int	$characterId		ID of Character
		 * @return	boolean				Result
		 */
		public function checkAchievementConditionAchievement($field, $count, $value, $groupby, $metaAchievementId, $characterId)
		{
			$data = $this->db->query(
				'SELECT ('.(
					$count
					? "count($field) >= $value"
					: "$field = $value"
				). ') AS got '.
				'FROM achievements_characters '.
				'WHERE '.
					'character_id = ?'.
					(!is_null($metaAchievementId) ? " AND achievement_id = $metaAchievementId" : '').
				(!is_null($groupby) ? " GROUP BY $groupby" : ''),
				'i',
				$characterId
			);
			if(!empty($data)) {
				foreach($data as &$datum) {
					if($datum['got'] == 1) {
						return true;
					}
				}
			}
			
			
			return false;
		}
		
		
		/**
		 * Get the progress for a Metaachievement condition.
		 * 
		 * @param	string	$field			Field to check
		 * @param	boolean	$count			Conut field-value
		 * @param	int	$value			The value the field has to match
		 * @param	string	$groupby		Field to group or NULL
		 * @param	int	$metaAchievementId	ID of related Achievement or NULL
		 * @param	int	$characterId		ID of Character
		 * @return	float				Percentage progress
		 */
		public function getAchievementConditionAchievementProgress($field, $count, $value, $groupby, $metaAchievementId, $characterId)
		{
			$data = $this->db->query(
				'SELECT '.(
					$count
					? "count($field)"
					: "$field"
				). ' AS field '.
				'FROM achievements_characters '.
				'WHERE '.
					'character_id = ?'.
					(!is_null($metaAchievementId) ? " AND achievement_id = $metaAchievementId" : '').
				(!is_null($groupby) ? " GROUP BY $groupby" : ''),
				'i',
				$characterId
			);
			if(!empty($data))
			{
				$maxField = 0;
				foreach($data as &$datum) {
					$maxField = max($maxField, intval($datum['field']));
				}
				
				return $maxField / $value;
			}
			
			
			return 0;
		}


		/**
		 * Add a new Achievement condition.
		 * 
		 * @param	int	$userId			ID of creating user
		 * @param	int	$achievementId		ID of Achievement to add condition to
		 * @param	string	$field			Field to match
		 * @param	boolean	$count			Count the value
		 * @param	string	$value			Value to match
		 * @param	int	$metaAchievementId	ID of Meta-Achievement (optional)
		 * @param	string	$groupby		Field to group by (optional)
		 */
		public function addAchievementConditionAchievement($userId, $achievementId, $field, $count, $value, $metaAchievementId=null, $groupby=null)
		{
			$this->db->query(
				'INSERT INTO achievementconditions_achievement '.
				'(created_user_id, achievement_id, field, count, value, meta_achievement_id, groupby) '.
				'VALUES '.
				'(?, ?, ?, ?, ?, ?, ?)',
				'iisisis',
				$userId,
				$achievementId,
				$field,
				$count,
				$value,
				$metaAchievementId,
				$groupby
			);

		}


		/**
		 * Edit a Achievement condition.
		 * 
		 * @param	int	$conditionId		ID of condition to edit
		 * @param	string	$field			Field to match
		 * @param	boolean	$count			Count the value
		 * @param	string	$value			Value to match
		 * @param	int	$metaAchievementId	ID of Achievement (optional)
		 * @param	string	$groupby		Field to group by (optional)
		 */
		public function editAchievementConditionAchievement($conditionId, $field, $count, $value, $metaAchievementId=null, $groupby=null)
		{
			$this->db->query(
				'UPDATE achievementconditions_achievement '.
				'SET field = ?, count = ?, value = ?, meta_achievement_id = ?, groupby = ? '.
				'WHERE id = ?',
				'sisisi',
				$field,
				$count,
				$value,
				$metaAchievementId,
				$groupby,
				$conditionId
			);
		}


		/**
		 * Delete a Achievement condition.
		 * 
		 * @param	int	$conditionId	ID of condition to delete
		 */
		public function deleteAchievementConditionAchievement($conditionId)
		{
			$this->db->query('DELETE FROM achievementconditions_achievement WHERE id = ?', 'i', $conditionId);
		}
		
		
		/**
		 * Set an Achievement as achieved for a Character.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @param	int	$characterId	ID of Character
		 */
		public function setAchievementAchieved($achievementId, $characterId)
		{
			$this->db->query(
				'INSERT INTO achievements_characters '.
				'(achievement_id, character_id) '.
				'VALUES '.
				'(?, ?)',
				'ii',
				$achievementId, $characterId
			);
		}
		
		
		/**
		 * Check if a Character has achieved an Achievement.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @param	int	$characterId	ID of Character
		 * @return	boolean			Whether Character has achieved the Achievement or not
		 */
		public function hasCharacterAchievedAchievement($achievementId, $characterId)
		{
			$data = $this->db->query(
				'SELECT achievement_id, character_id, created '.
				'FROM achievements_characters '.
				'WHERE achievement_id = ? AND character_id = ?',
				'ii',
				$achievementId, $characterId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return false;
		}


		/**
		 * Get all existing Achievements conditions.
		 * 
		 * @return	array	List of Achievements conditions
		 */
		public function getAchievementsConditions()
		{
			return $this->db->query(
				'SELECT id, created, `condition` '.
				'FROM achievementconditions'
			);
		}


		/**
		 * Check if an Achievement title already exists.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	string	$title		Achievement title to check
		 * @param	int	$characterId	Do not check this ID (for editing)
		 * @return	boolean			Whether Achievement title exists or not
		 */
		public function achievementTitleExists($seminaryId, $title, $achievementId=null)
		{
			$data = $this->db->query(
				'SELECT id '.
				'FROM achievements '.
				'WHERE seminary_id = ? AND (title = ? OR url = ?)',
				'iss',
				$seminaryId,
				$title,
				\nre\core\Linker::createLinkParam($title)
			);
			
			
			return (!empty($data) && (is_null($achievementId) || $achievementId != $data[0]['id']));
		}


		/**
		 * Create a new Achievement for a Seminary.
		 * 
		 * @param	int	$userId		ID of creating user
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$conditionId	ID of Achievement condition
		 * @param	string	$title		Title of new Achievement
		 * @param	string	$description	Description of new Achievement
		 * @param	boolean	$progress	Show progress
		 * @param	boolean	$hidden		Secret Achievement
		 * @param	boolean	$onlyOnce	Only achieveable by one user
		 * @param	boolean	$allConditions	Achievement must match all conditions
		 * @param	string	$deadline	Deadline for Achievement
		 * @return	int			ID of newly created Achievement
		 */
		public function createAchievement($userId, $seminaryId, $conditionId, $title, $description, $progress, $hidden, $onlyOnce, $allConditions, $deadline)
		{
			// Get position
			$pos = $this->db->query(
				'SELECT COALESCE(MAX(pos),0)+1 AS pos '.
				'FROM achievements '.
				'WHERE seminary_id = ?',
				'i',
				$seminaryId
			);
			$pos = $pos[0]['pos'];

			// Create Achievement
			$this->db->query(
				'INSERT INTO achievements '.
				'(created_user_id, seminary_id, achievementcondition_id, pos, title, url, description, progress, hidden, only_once, all_conditions, deadline) '.
				'VALUES '.
				'(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)',
				'iiiisssiiiis',
				$userId,
				$seminaryId,
				$conditionId,
				$pos,
				$title,
				\nre\core\Linker::createLinkParam($title),
				$description,
				$progress,
				$hidden,
				$onlyOnce,
				$allConditions,
				$deadline
			);
			

			// Return ID
			return $this->db->getInsertId();
		}

		
		/**
		 * Move an Achievement up (decrement position) or down
		 * (increment position).
		 * 
		 * @param	array	$achievement	Achievement to move
		 * @param	boolean	$up		True for moving up, false for down
		 */
		public function moveAchievement($achievement, $up)
		{
			$this->db->setAutocommit(false);
			try {
				// Set temporary position
				$this->db->query(
					'UPDATE achievements '.
					'SET pos = 0 '.
					'WHERE id = ?',
					'i',
					$achievement['id']
				);
				// Switch entry
				$this->db->query(
					'UPDATE achievements '.
					'SET pos = ? '.
					'WHERE seminary_id = ? AND pos = ?',
					'iii',
					$achievement['pos'],
					$achievement['seminary_id'],
					$achievement['pos'] + ($up ? -1 : 1)
				);
				// Set new position
				$this->db->query(
					'UPDATE achievements '.
					'SET pos = ? '.
					'WHERE id = ?',
					'ii',
					$achievement['pos'] + ($up ? -1 : 1),
					$achievement['id']
				);
				
				$this->db->commit();
			}
			catch(\nre\exceptions\DatamodelException $e) {
				$this->db->rollback();
				$this->db->setAutocommit(true);
				throw $e;
			}
			$this->db->setAutocommit(true);
		}


		/**
		 * Edit an Achievement of a Seminary.
		 * 
		 * @param	int	$achievementId	ID of Achievement to edit
		 * @param	int	$conditionId	ID of Achievement condition
		 * @param	string	$title		New title of Achievement
		 * @param	string	$description	New description of Achievement
		 * @param	boolean	$progress	Show progress
		 * @param	boolean	$hidden		Secret Achievement
		 * @param	boolean	$onlyOnce	Only achieveable by one user
		 * @param	boolean	$allConditions	Achievement must match all conditions
		 * @param	string	$deadline	Deadline for Achievement
		 */
		public function editAchievement($achievementId, $conditionId, $title, $description, $progress, $hidden, $onlyOnce, $allConditions, $deadline)
		{
			$this->db->query(
				'UPDATE achievements '.
				'SET achievementcondition_id = ?, title = ?, url = ?, description = ?, progress = ?, hidden = ?, only_once = ?, all_conditions = ?, deadline = ? '.
				'WHERE id = ?',
				'isssiiiisi',
				$conditionId,
				$title,
				\nre\core\Linker::createLinkParam($title),
				$description,
				$progress,
				$hidden,
				$onlyOnce,
				$allConditions,
				$deadline,
				$achievementId
			);
		}


		/**
		 * Set unachieved media for an Achievement.
		 * 
		 * @param	int	$achievementId		ID of Achievement to set media for
		 * @param	int	$achievementsmediaId	ID of achievementsmedia to set
		 */
		public function setUnachievedMediaForAchievement($achievementId, $achievementsmediaId)
		{
			$this->db->query(
				'UPDATE achievements '.
				'SET unachieved_achievementsmedia_id = ? '.
				'WHERE id = ?',
				'ii',
				$achievementsmediaId,
				$achievementId
			);
		}


		/**
		 * Set achieved media for an Achievement.
		 * 
		 * @param	int	$achievementId		ID of Achievement to set media for
		 * @param	int	$achievementsmediaId	ID of achievementsmedia to set
		 */
		public function setAchievedMediaForAchievement($achievementId, $achievementsmediaId)
		{
			$this->db->query(
				'UPDATE achievements '.
				'SET achieved_achievementsmedia_id = ? '.
				'WHERE id = ?',
				'ii',
				$achievementsmediaId,
				$achievementId
			);
		}

		
		/**
		 * Delete an Achievement.
		 * 
		 * @param	int	$achievement	Achievement to delete
		 */
		public function deleteAchievement($achievement)
		{
			$this->db->setAutocommit(false);
			try {
				// Delete Achievement
				$this->db->query('DELETE FROM achievements WHERE id = ?', 'i', $achievementId);

				// Adjust positions
				$this->db->query(
					'UPDATE achievements '.
					'SET pos = pos - 1 '.
					'WHERE seminary_id = ? AND pos > ?',
					'ii',
					$achievement['seminary_id'],
					$achievement['pos']
				);

				$this->db->commit();
			}
			catch(\Exception $e) {
				$this->db->rollback();
				$this->db->setAutocommit(true);
				throw $e;
			}

			$this->db->setAutocommit(true);
		}
		
	}

?>
