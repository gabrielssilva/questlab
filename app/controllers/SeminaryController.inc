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
	abstract class SeminaryController extends \hhu\z\controllers\IntermediateController
	{
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('achievement', 'auth', 'notification');
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'characters', 'characterroles', 'xplevels', 'avatars', 'achievements');
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
		 * Construct a new Seminary Controller.
		 * 
		 * @throws	\nre\exceptions\DriverNotFoundException
		 * @throws	\nre\exceptions\DriverNotValidException
		 * @throws	\nre\exceptions\ModelNotValidException
		 * @throws	\nre\exceptions\ModelNotFoundException
		 * @throws	\nre\exceptions\ViewNotFoundException
		 * @param	string		$layoutName	Name of the current Layout
		 * @param	string		$action		Current Action
		 * @param	\nre\core\Agent	$agent		Corresponding Agent
		 */
		public function __construct($layoutName, $action, $agent)
		{
			parent::__construct($layoutName, $action, $agent);
		}
		
		
		
		/**
		 * Prefilter that is executed before running the Controller.
		 * 
		 * @param	\nre\core\Request	$request	Current request
		 * @param	\nre\core\Response	$response	Current response
		 */
		public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::preFilter($request, $response);
			
			// Get Seminary and Character data
			try {
				self::$seminary = $this->Seminaries->getSeminaryByUrl($this->request->getParam(3));
				if(!is_null(self::$user))
				{
					self::$character = $this->Characters->getCharacterForUserAndSeminary(self::$user['id'], self::$seminary['id']);
					self::$character['characterroles'] = array_map(function($r) { return $r['name']; }, $this->Characterroles->getCharacterrolesForCharacterById(self::$character['id']));
					try {
						self::$character['xplevel'] = $this->Xplevels->getXPLevelById(self::$character['xplevel_id']);
						self::$character['avatar'] = $this->Avatars->getAvatarByTypeAndLevel(self::$seminary['id'], self::$character['charactertype_url'], self::$character['xplevel']['level']);
					}
					catch(\nre\exceptions\IdNotFoundException $e) {
						// No Avatar available
					}
				}
			}
			catch(\nre\exceptions\IdNotFoundException $e) {
			}
			
			// Check permissions
			$this->checkPermission($request, $response);
			
			// Check achievements
			$this->checkAchievements($request, $response, 'date');
			$this->checkAchievements($request, $response, 'achievement');
			
			// Set Seminary and Character data
			$this->set('loggedSeminary', self::$seminary);
			$this->set('loggedCharacter', self::$character);
		}
		
		
		/**
		 * Postfilter that is executed after running the Controller.
		 * 
		 * @param	\nre\core\Request	$request	Current request
		 * @param	\nre\core\Response	$response	Current response
		 */
		public function postFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::postFilter($request, $response);
		}
		
		
		
		/**
		 * Check user permissions.
		 * 
		 * @throws AccessDeniedException
		 * @param	\nre\core\Request	$request	Current request
		 * @param	\nre\core\Response	$response	Current response
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
			if(is_null(self::$character) || !array_key_exists('characterroles', self::$character) || count(array_intersect(self::$character['characterroles'], $permissions)) == 0) {
				throw new \nre\exceptions\AccessDeniedException();
			}
		}
		
		
		/**
		 * Check for newly achieved Achievements.
		 * 
		 * @param	\nre\core\Request	$request		Current request
		 * @param	\nre\core\Response	$response		Current response
		 * @param	array			$checkConditions	Conditions to check
		 */
		protected function checkAchievements(\nre\core\Request $request, \nre\core\Response $response, $checkConditions=null)
		{
			// Do not check MediaController
			if($this->request->getParam(0, 'toplevel') != \nre\configs\AppConfig::$defaults['toplevel']) {
				return;
			}
			
			// Check if Character is present
			if(is_null(self::$character)) {
				return;
			}
			
			// Set conditions to check
			if(!is_null($checkConditions) && !is_array($checkConditions)) {
				$checkConditions = array($checkConditions);
			}
			
			// Get unachieved Achievments
			$achievements = $this->Achievements->getUnachhievedAchievementsForCharacter(self::$seminary['id'], self::$character['id']);
			if(in_array('user', self::$character['characterroles'])) {
				$achievements = array_merge($achievements, $this->Achievements->getUnachievedOnlyOnceAchievementsForSeminary(self::$seminary['id']));
			}
			
			// Check conditions
			foreach($achievements as &$achievement)
			{
				// Check condition to test
				if(!is_null($checkConditions) && !in_array($achievement['condition'], $checkConditions)) {
					continue;
				}
				
				// Check deadline
				if(!is_null($achievement['deadline']) && $achievement['deadline'] < date('Y-m-d H:i:s')) {
					continue;
				}
				
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
				
				// Do not achieve Achievements without conditions
				if(empty($conditions)) {
					continue;
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
				
				// Achievement achieved
				if($achieved)
				{
					// Set status
					$this->Achievements->setAchievementAchieved($achievement['id'], self::$character['id']);
					
					// Add notification
					$this->Notification->addNotification(
						\hhu\z\controllers\components\NotificationComponent::TYPE_ACHIEVEMENT,
						$achievement['title'],
						$this->linker->link(array('achievements', 'index', self::$seminary['url']), 0, true, null, true, $achievement['url']),
						(!is_null($achievement['achieved_achievementsmedia_id']) ? $this->linker->link(array('media','achievement',self::$seminary['url'],$achievement['url'])) : null)
					);
				}
			}
		}
		
	}

?>
