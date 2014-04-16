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
				'SELECT achievements.id, achievementconditions.condition, title, url, description, progress, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
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
		 * Get all not yet achieved Achievements for a Seminary that can
		 * only be achieved once (only by one Character).
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			Achievements data
		 */
		public function getUnachievedOnlyOnceAchievementsForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT achievements.id, achievementconditions.condition, title, url, description, progress, hidden, only_once, all_conditions, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
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
		 * Get seldom Achievements.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$count		Number of Achievements to retrieve
		 * @return	array			List of seldom Achievements
		 */
		public function getSeldomAchievements($seminaryId, $count)
		{
			return $this->db->query(
				'SELECT id, title, url, description, progress, hidden, unachieved_achievementsmedia_id, achieved_achievementsmedia_id, count(DISTINCT character_id) AS c '.
				'FROM achievements_characters '.
				'LEFT JOIN achievements ON achievements.id = achievements_characters.achievement_id '.
				'WHERE achievements.seminary_id = ? AND only_once = 0 '.
				'GROUP BY achievement_id '.
				'ORDER BY count(DISTINCT character_id) ASC '.
				'LIMIT ?',
				'ii',
				$seminaryId,
				$count
			);
		}
		
		
		/**
		 * Get all achieved Achievements for a Character.
		 * 
		 * @param	int	$characterId	ID of Character
		 * @return	array			Achievements data
		 */
		public function getAchievedAchievementsForCharacter($characterId)
		{
			return $this->db->query(
				'SELECT achievements.id, achievements_characters.created, achievements.title, achievements.url, achievements.description, achievements.progress, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'INNER JOIN achievements_characters ON achievements_characters.achievement_id = achievements.id '.
				'WHERE achievements_characters.character_id = ? '.
				'ORDER BY achievements_characters.created DESC',
				'i',
				$characterId
			);
		}
		
		
		/**
		 * Get all not yet achieved Achievements for a Character.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$characterId	ID of Character
		 * @return	array			Achievements data
		 */
		public function getUnachhievedAchievementsForCharacter($seminaryId, $characterId, $includeOnlyOnce=false)
		{
			return $this->db->query(
				'SELECT achievements.id, achievementconditions.condition, title, url, description, progress, hidden, only_once, all_conditions, unachieved_achievementsmedia_id, achieved_achievementsmedia_id '.
				'FROM achievements '.
				'LEFT JOIN achievementconditions ON achievementconditions.id = achievements.achievementcondition_id '.
				'WHERE achievements.seminary_id = ? AND only_once <= ? AND NOT EXISTS ('.
					'SELECT character_id '.
					'FROM achievements_characters '.
					'WHERE '.
						'achievements_characters.achievement_id = achievements.id AND '.
						'achievements_characters.character_id = ?'.
				') '.
				'ORDER BY achievements.pos ASC',
				'iii',
				$seminaryId,
				$includeOnlyOnce,
				$characterId
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
				'SELECT `select` '.
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
		 * Get all Character conditions for an Achievement.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @return	array			Character conditions
		 */
		public function getAchievementConditionsCharacter($achievementId)
		{
			return $this->db->query(
				'SELECT field, value '.
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
				'FROM v_characters '.
				'WHERE user_id = ?',
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
				'FROM v_characters '.
				'WHERE user_id = ?',
				'i',
				$characterId
			);
			if(!empty($data)) {
				return $data[0]['field'] / $value;
			}
			
			
			return 0;
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
				'SELECT field, `count`, value, quest_id, status, groupby '.
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
		 * Get all Metaachievement conditions for an Achievement.
		 * 
		 * @param	int	$achievementId	ID of Achievement
		 * @return	array			Metaachievement conditions
		 */
		public function getAchievementConditionsAchievement($achievementId)
		{
			return $this->db->query(
				'SELECT field, `count`, value, meta_achievement_id, groupby '.
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
		
	}

?>
