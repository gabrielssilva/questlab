<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\controllers;
	
	
	/**
	 * Controller of the Agent to list Achievements.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class AchievementsController extends \hhu\z\controllers\SeminaryRoleController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('achievements', 'seminaries', 'media', 'characters');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index' => array('admin', 'moderator', 'user')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * List Achievements of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 */
		public function index($seminaryUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character
			$character = SeminaryRoleController::$character;
			
			// Get seldom Achievements
			$seldomAchievements = $this->Achievements->getSeldomAchievements($seminary['id'], \nre\configs\AppConfig::$misc['achievements_range']);
			foreach($seldomAchievements as &$achievement) {
				$achievement['achieved'] = $this->Achievements->hasCharacterAchievedAchievement($achievement['id'], $character['id']);
			}
			
			// Get Characters with the most Achievements
			$successfulCharacters = $this->Characters->getCharactersWithMostAchievements($seminary['id'], \nre\configs\AppConfig::$misc['achievements_range']);
			
			// Get achieved Achievements
			$achievedAchievements = $this->Achievements->getAchievedAchievementsForCharacter($character['id']);
			
			// Get unachieved Achievements
			$unachievedAchievements = $this->Achievements->getUnachhievedAchievementsForCharacter($seminary['id'], $character['id'], true);
			foreach($unachievedAchievements as &$achievement)
			{
				// Get Character progress
				if($achievement['progress'])
				{
					$conditions = array();
					switch($achievement['condition'])
					{
						// Character conditions
						case 'character':
							$conditionsCharacter = $this->Achievements->getAchievementConditionsCharacter($achievement['id']);
							foreach($conditionsCharacter as &$condition)
							{
								$conditions[] = array(
									'func'		=> 'getAchievementConditionCharacterProgress',
									'params'	=> array(
										$condition['field'],
										$condition['value'],
										$character['id']
									)
								);
							}
						break;
						// Quest conditions
						case 'quest':
							$conditionsQuest = $this->Achievements->getAchievementConditionsQuest($achievement['id']);
							foreach($conditionsQuest as &$condition)
							{
								$conditions[] = array(
									'func'		=> 'getAchievementConditionQuestProgress',
									'params'	=> array(
										$condition['field'],
										$condition['count'],
										$condition['value'],
										$condition['status'],
										$condition['groupby'],
										$condition['quest_id'],
										$character['id']
									)
								);
							}
						break;
						// Achievement conditions
						case 'achievement':
							$conditionsAchievement = $this->Achievements->getAchievementConditionsAchievement($achievement['id']);
							foreach($conditionsAchievement as &$condition)
							{
								$conditions[] = array(
									'func'		=> 'getAchievementConditionAchievementProgress',
									'params'	=> array(
										$condition['field'],
										$condition['count'],
										$condition['value'],
										$condition['groupby'],
										$condition['meta_achievement_id'],
										$character['id']
									)
								);
							}
						break;
					}
					
					$characterProgresses = array();
					foreach($conditions as &$condition)
					{
						// Calculate progress of condition
						$characterProgresses[] = call_user_func_array(
							array(
								$this->Achievements,
								$condition['func']
							),
							$condition['params']
						);
					}
					
					$achievement['characterProgress'] = array_sum($characterProgresses) / count($characterProgresses);
				}
			}
			
			// Get ranking
			$character['rank'] = $this->Achievements->getCountRank($seminary['id'], count($achievedAchievements));
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('character', $character);
			$this->set('seldomAchievements', $seldomAchievements);
			$this->set('successfulCharacters', $successfulCharacters);
			$this->set('achievedAchievements', $achievedAchievements);
			$this->set('unachievedAchievements', $unachievedAchievements);
		}
		
	}

?>
