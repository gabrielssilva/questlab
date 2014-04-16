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
	 * Abstract class for implementing a Controller for a Seminary and its
	 * concepts.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	abstract class SeminaryRoleController extends \hhu\z\controllers\IntermediateController
	{
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('achievement', 'auth');
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'userseminaryroles', 'characters', 'achievements');
		/**
		 * Current Seminary
		 * 
		 * var array
		 */
		public static $seminary = null;
		/**
		 * Character of current user and Seminary
		 * 
		 * @var array
		 */
		public static $character = null;
		
		
		
		
		/**
		 * Construct a new SeminaryRole Controller.
		 * 
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @throws	ModelNotValidException
		 * @throws	ModelNotFoundException
		 * @throws	ViewNotFoundException
		 * @param	string	$layoutName	Name of the current Layout
		 * @param	string	$action		Current Action
		 * @param	Agent	$agent		Corresponding Agent
		 */
		public function __construct($layoutName, $action, $agent)
		{
			parent::__construct($layoutName, $action, $agent);
		}
		
		
		
		/**
		 * Prefilter that is executed before running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::preFilter($request, $response);
			
			// Get Seminary and Character data
			try {
				self::$seminary = $this->Seminaries->getSeminaryByUrl($this->request->getParam(3));
				self::$character = $this->Characters->getCharacterForUserAndSeminary(self::$user['id'], self::$seminary['id']);
				self::$user['seminaryroles'] = array_map(function($r) { return $r['name']; }, $this->Userseminaryroles->getUserseminaryrolesForUserById(self::$user['id'], self::$seminary['id']));
			}
			catch(\nre\exceptions\IdNotFoundException $e) {
			}
			
			// Check permissions
			$this->checkPermission($request, $response);
			
			// Check achievements
			$this->checkAchievements($request, $response);
			
			// Set Seminary and Character data
			$this->set('loggedSeminary', self::$seminary);
			$this->set('loggedCharacter', self::$character);
		}
		
		
		/**
		 * Postfilter that is executed after running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function postFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::postFilter($request, $response);
		}
		
		
		
		
		/**
		 * Check user permissions.
		 * 
		 * @throws AccessDeniedException
		 */
		private function checkPermission(\nre\core\Request $request, \nre\core\Response $response)
		{
			// Do not check index page
			if(is_null($request->getParam(3))) {
				return;
			}
			
			
			// Determine permissions for current action
			$action = $this->request->getParam(2, 'action');
			if(!property_exists($this, 'seminaryPermissions')) {
				return;	// Allow if nothing is specified
			}
			if(!array_key_exists($action, $this->seminaryPermissions)) {
				return;	// Allow if Action is not specified
			}
			$permissions = $this->seminaryPermissions[$action];
			
			
			// Check permissions
			if(!array_key_exists('seminaryroles', self::$user) || count(array_intersect(self::$user['seminaryroles'], $permissions)) == 0) {
				throw new \nre\exceptions\AccessDeniedException();
			}
		}
		
		
		/**
		 * Check for newly achieved Achievements.
		 */
		private function checkAchievements(\nre\core\Request $request, \nre\core\Response $response)
		{
			// Check if Character is present
			if(is_null(self::$character)) {
				return;
			}
			
			// Get unachieved Achievments
			$achievements = $this->Achievements->getUnachhievedAchievementsForCharacter(self::$seminary['id'], self::$character['id']);
			if(in_array('user', self::$user['seminaryroles'])) {
				$achievements = array_merge($achievements, $this->Achievements->getUnachievedOnlyOnceAchievementsForSeminary(self::$seminary['id']));
			}
			
			// Check conditions
			foreach($achievements as &$achievement)
			{
				// Get conditions
				$conditions = array();
				$progress = 0;
				switch($achievement['condition'])
				{
					// Date conditions
					case 'date':
						$conditionsDate = $this->Achievements->getAchievementConditionsDate($achievement['id']);
						foreach($conditionsDate as &$condition)
						{
							$conditions[] = array(
								'func'		=> 'checkAchievementConditionDate',
								'params'	=> array(
									$condition['select']
								)
							);
						}
					break;
					// Character conditions
					case 'character':
						$conditionsCharacter = $this->Achievements->getAchievementConditionsCharacter($achievement['id']);
						foreach($conditionsCharacter as &$condition)
						{
							$conditions[] = array(
								'func'		=> 'checkAchievementConditionCharacter',
								'params'	=> array(
									$condition['field'],
									$condition['value'],
									self::$character['id']
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
								'func'		=> 'checkAchievementConditionQuest',
								'params'	=> array(
									$condition['field'],
									$condition['count'],
									$condition['value'],
									$condition['status'],
									$condition['groupby'],
									$condition['quest_id'],
									self::$character['id']
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
								'func'		=> 'checkAchievementConditionAchievement',
								'params'	=> array(
									$condition['field'],
									$condition['count'],
									$condition['value'],
									$condition['groupby'],
									$condition['meta_achievement_id'],
									self::$character['id']
								)
							);
						}
					break;
				}
				
				// Check conditions
				$achieved = ($achievement['all_conditions'] == 1);
				foreach($conditions as &$condition)
				{
					// Calculate result of condition
					$result = call_user_func_array(
						array(
							$this->Achievements,
							$condition['func']
						),
						$condition['params']
					);
					
					// The overall result and abort if possible
					if($achievement['all_conditions'])
					{
						if(!$result) {
							$achieved = false;
							break;
						}
					}
					else
					{
						if($result) {
							$achieved = true;
							break;
						}
					}
					
				}
				
				// Set status
				if($achieved) {
					$this->Achievements->setAchievementAchieved($achievement['id'], self::$character['id']);
				}
			}
		}
		
	}

?>
