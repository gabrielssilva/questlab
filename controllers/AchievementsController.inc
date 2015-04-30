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
	class AchievementsController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('achievements', 'seminaries', 'media', 'characters', 'quests');
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('validation');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index'		=> array('admin', 'moderator', 'user'),
			'create'	=> array('admin', 'moderator', 'user'),
			'moveup'	=> array('admin', 'moderator', 'user'),
			'movedown'	=> array('admin', 'moderator', 'user'),
			'edit'		=> array('admin', 'moderator', 'user'),
			'conditions'	=> array('admin', 'moderator', 'user'),
			'delete'	=> array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index'		=> array('admin', 'moderator', 'user'),
			'create'	=> array('admin'),
			'moveup'	=> array('admin', 'moderator'),
			'movedown'	=> array('admin', 'moderator'),
			'edit'		=> array('admin', 'moderator'),
			'conditions'	=> array('admin', 'moderator'),
			'delete'	=> array('admin')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * List Achievements of a Seminary.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 */
		public function index($seminaryUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character
			$character = SeminaryController::$character;
			
			// Get seldom Achievements
			$seldomAchievements = $this->Achievements->getSeldomAchievements($seminary['id'], \nre\configs\AppConfig::$misc['achievements_range'], false);
			foreach($seldomAchievements as &$achievement) {
				$achievement['achieved'] = $this->Achievements->hasCharacterAchievedAchievement($achievement['id'], $character['id']);
			}
			
			// Get Characters with the most Achievements
			$successfulCharacters = $this->Characters->getCharactersWithMostAchievements($seminary['id'], \nre\configs\AppConfig::$misc['achievements_range'], false);
			
			// Get total count of Achievements for Seminary
			$achievementsCount = $this->Achievements->getAchievementsCountForSeminary($seminary['id'], false);
			
			// Get achieved Achievements
			$achievedAchievements = $this->Achievements->getAchievedAchievementsForCharacter($character['id']);
			
			// Get unachieved Achievements
			$unachievedAchievements = array_merge(
				$this->Achievements->getUnachhievedAchievementsForCharacter($seminary['id'], $character['id'], false, false),
				$this->Achievements->getUnachievedOnlyOnceAchievementsForSeminary($seminary['id'])
			);
			usort($unachievedAchievements, function($a, $b) {
				if($a['pos'] == $b['pos']) {
					return 0;
				}
				return ($a['pos'] > $b['pos']) ? 1 : -1;
			});
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
			
			
			// Set title
			$this->addTitleLocalized('Achievements');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('character', $character);
			$this->set('seldomAchievements', $seldomAchievements);
			$this->set('successfulCharacters', $successfulCharacters);
			$this->set('achievementsCount', $achievementsCount);
			$this->set('achievedAchievements', $achievedAchievements);
			$this->set('unachievedAchievements', $unachievedAchievements);
		}


		/**
		 * Action: manage.
		 * 
		 * Manage Achievements of a Seminary.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 */
		public function manage($seminaryUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Achievements
			$achievements = $this->Achievements->getAchievementsForSeminary($seminary['id']);


			// Set title
			$this->addTitleLocalized('Manage Achievements');
			$this->addTitle($seminary['title']);

			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('achievements', $achievements);
		}


		/**
		 * Action: create.
		 * 
		 * Create a new Achievement.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of Seminary
		 */
		public function create($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Achievements conditions
			$conditions = $this->Achievements->getAchievementsConditions();

			// Get allowed mimetypes
			$mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

			// Values
			$title = '';
			$description = '';
			$progress = 0;
			$hidden = 0;
			$onlyOnce = 0;
			$allConditions = 1;
			$deadline = '';
			$condition = $conditions[0]['condition'];
			$fields = array('title', 'deadline');
			$validation = array();

			// Create Achievement
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$title = $this->request->getPostParam('title');
				if($this->Achievements->achievementTitleExists($seminary['id'], $title)) {
					$validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
				}
				$description = $this->request->getPostParam('description');
				$progress = !is_null($this->request->getPostParam('progress'));
				$hidden = !is_null($this->request->getPostParam('hidden'));
				$onlyOnce = !is_null($this->request->getPostParam('only_once'));
				$allConditions = !is_null($this->request->getPostParam('all_conditions'));
				$deadline = $this->request->getPostParam('deadline');
				$condition = $this->request->getPostParam('condition');

				// Validate condition
				$conditionIndex = null;
				foreach($conditions as $index => &$c) {
					if($condition == $c['condition']) {
						$conditionIndex = $index;
					}
				}
				if(is_null($conditionIndex)) {
					throw new \nre\exceptions\ParamsNotValidException($condition);
				}

				// Validate images
				$images = array(
					'unachieved_image'	=> null,
					'achieved_image'	=> null
				);
				foreach($images as $key => $image)
				{
					if(!empty($_FILES) && array_key_exists($key, $_FILES) && $_FILES[$key]['error'] != UPLOAD_ERR_NO_FILE)
					{
						$images[$key] = $_FILES[$key];
						
						// Check error
						if($images[$key]['error'] !== UPLOAD_ERR_OK) {
							$validation = $this->Validation->addValidationResult($validation, 'image', 'error', $image[$key]['error']);
						}
						
						// Check mimetype
						$mediaMimetype = null;
						$images[$key]['mimetype'] = \hhu\z\Utils::getMimetype($images[$key]['tmp_name'], $images[$key]['type']);
						foreach($mimetypes as &$mimetype) {
							if($mimetype['mimetype'] == $images[$key]['mimetype']) {
								$mediaMimetype = $mimetype;
								break;
							}
						}
						if(is_null($mediaMimetype)) {
							$validation = $this->Validation->addValidationResult($validation, 'image', 'mimetype', $images[$key]['mimetype']);
						}
						elseif($images[$key]['size'] > $mediaMimetype['size']) {
							$validation = $this->Validation->addValidationResult($validation, 'image', 'size', $mediaMimetype['size']);
						}
					}
				}

				// Create Achievement
				if($validation === true)
				{
					$achievementId = $this->Achievements->createAchievement(
						$this->Auth->getUserId(),
						$seminary['id'],
						$conditions[$conditionIndex]['id'],
						$title,
						$description,
						$progress,
						$hidden,
						$onlyOnce,
						$allConditions,
						(!empty($deadline)) ? $deadline : NULL
					);
					$achievement = $this->Achievements->getAchievementById($achievementId);

					// Upload images
					foreach($images as $key => &$image)
					{
						if(!is_null($image))
						{
							$image['media_id'] = $this->Media->createAchievementMedia(
								$this->Auth->getUserId(),
								$seminary['id'],
								sprintf('achievement-%d', $achievement['id']).(substr($key, 0, 2) == 'un' ? '-locked' : NULL),
								'',
								$image['mimetype'],
								$image['tmp_name']
							);
						}
					}
					if(!is_null($images['unachieved_image']) && $images['unachieved_image']['media_id'] !== false) {
						$this->Achievements->setUnachievedMediaForAchievement($achievement['id'], $images['unachieved_image']['media_id']);
					}
					if(!is_null($images['achieved_image']) && $images['achieved_image']['media_id'] !== false) {
						$this->Achievements->setAchievedMediaForAchievement($achievement['id'], $images['achieved_image']['media_id']);
					}

					// Redirect to condition editing
					$this->redirect($this->linker->link(array('conditions', $seminary['url'], $achievement['url']), 1));
				}
			}

			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}


			// Set title
			$this->addTitleLocalized('Create Achievement');
			$this->addTitle($seminary['title']);

			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('title', $title);
			$this->set('description', $description);
			$this->set('progress', $progress);
			$this->set('hidden', $hidden);
			$this->set('onlyOnce', $onlyOnce);
			$this->set('allConditions', $allConditions);
			$this->set('deadline', $deadline);
			$this->set('condition', $condition);
			$this->set('conditions', $conditions);
			$this->set('mimetypes', $mimetypes);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}
		

		/**
		 * Action: moveup.
		 * 
		 * Move an Achievement up (decrement position).
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of Seminary
		 * @param	string	$achievementUrl	URL-title of Achievement
		 */
		public function moveup($seminaryUrl, $achievementUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Achievement
			$achievement = $this->Achievements->getAchievementByUrl($seminary['id'], $achievementUrl);
			
			// Set position
			$this->Achievements->moveAchievement($achievement, true);
			
			
			// Redirect
			$this->redirect($this->linker->link(array('manage', $seminary['url']), 1, true, null, false, $achievement['url']));
		}


		/**
		 * Action: movedown.
		 * 
		 * Move an Achievement down (increment position).
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of Seminary
		 * @param	string	$achievementUrl	URL-title of Achievement
		 */
		public function movedown($seminaryUrl, $achievementUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Achievement
			$achievement = $this->Achievements->getAchievementByUrl($seminary['id'], $achievementUrl);
			
			// Set position
			$this->Achievements->moveAchievement($achievement, false);
			
			
			// Redirect
			$this->redirect($this->linker->link(array('manage', $seminary['url']), 1, true, null, false, $achievement['url']));
		}


		/**
		 * Action: edit.
		 * 
		 * Edit an Achievement.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of Seminary
		 * @param	string	$achievementUrl	URL-title of Achievement to edit
		 */
		public function edit($seminaryUrl, $achievementUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Achievement
			$achievement = $this->Achievements->getAchievementByUrl($seminary['id'], $achievementUrl);

			// Get Achievements conditions
			$conditions = $this->Achievements->getAchievementsConditions();

			// Get allowed mimetypes
			$mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

			// Values
			$title = $achievement['title']; 
			$description = $achievement['description'];
			$progress = $achievement['progress']; 
			$hidden = $achievement['hidden']; 
			$onlyOnce = $achievement['only_once']; 
			$allConditions = $achievement['all_conditions']; 
			$deadline = $achievement['deadline']; 
			$condition = $achievement['condition'];
			$fields = array('title', 'deadline');
			$validation = array();

			// Edit Achievement
			if($this->request->getRequestMethod() == 'POST' && (!is_null($this->request->getPostParam('edit')) || !is_null($this->request->getPostParam('edit-conditions'))))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$title = $this->request->getPostParam('title');
				if($this->Achievements->achievementTitleExists($seminary['id'], $title, $achievement['id'])) {
					$validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
				}
				$description = $this->request->getPostParam('description');
				$progress = !is_null($this->request->getPostParam('progress'));
				$hidden = !is_null($this->request->getPostParam('hidden'));
				$onlyOnce = !is_null($this->request->getPostParam('only_once'));
				$allConditions = !is_null($this->request->getPostParam('all_conditions'));
				$deadline = $this->request->getPostParam('deadline');
				$condition = $this->request->getPostParam('condition');

				// Validate condition
				$conditionIndex = null;
				foreach($conditions as $index => &$c) {
					if($condition == $c['condition']) {
						$conditionIndex = $index;
					}
				}
				if(is_null($conditionIndex)) {
					throw new \nre\exceptions\ParamsNotValidException($condition);
				}

				// Validate images
				$images = array(
					'unachieved_image'	=> null,
					'achieved_image'	=> null
				);
				foreach($images as $key => $image)
				{
					if(!empty($_FILES) && array_key_exists($key, $_FILES) && $_FILES[$key]['error'] != UPLOAD_ERR_NO_FILE)
					{
						$images[$key] = $_FILES[$key];
						
						// Check error
						if($images[$key]['error'] !== UPLOAD_ERR_OK) {
							$validation = $this->Validation->addValidationResult($validation, 'image', 'error', $image[$key]['error']);
						}
						
						// Check mimetype
						$mediaMimetype = null;
						$images[$key]['mimetype'] = \hhu\z\Utils::getMimetype($images[$key]['tmp_name'], $images[$key]['type']);
						foreach($mimetypes as &$mimetype) {
							if($mimetype['mimetype'] == $images[$key]['mimetype']) {
								$mediaMimetype = $mimetype;
								break;
							}
						}
						if(is_null($mediaMimetype)) {
							$validation = $this->Validation->addValidationResult($validation, 'image', 'mimetype', $images[$key]['mimetype']);
						}
						elseif($images[$key]['size'] > $mediaMimetype['size']) {
							$validation = $this->Validation->addValidationResult($validation, 'image', 'size', $mediaMimetype['size']);
						}
					}
				}

				// Edit Achievement
				if($validation === true)
				{
					$this->Achievements->editAchievement(
						$achievement['id'],
						$conditions[$conditionIndex]['id'],
						$title,
						$description,
						$progress,
						$hidden,
						$onlyOnce,
						$allConditions,
						(!empty($deadline)) ? $deadline : NULL
					);

					// Remove old conditions
					if($conditions[$conditionIndex]['condition'] != $achievement['condition'])
					{
						var_dump("remove");
						switch($achievement['condition'])
						{
							// Date conditions
							case 'date':
								foreach($this->Achievements->getAchievementConditionsDate($achievement['id']) as $c) {
									$this->Achievements->deleteAchievementConditionDate($c['id']);
								}
							break;
							// Character conditions
							case 'character':
								foreach($this->Achievements->getAchievementConditionsCharacter($achievement['id']) as $c) {
									$this->Achievements->deleteAchievementConditionCharacter($c['id']);
								}
							break;
							// Quest conditions
							case 'quest':
								foreach($this->Achievements->getAchievementConditionsQuest($achievement['id']) as $c) {
									$this->Achievements->deleteAchievementConditionQuest($c['id']);
								}
							break;
							// Achievement conditions
							case 'achievement':
								foreach($this->Achievements->getAchievementConditionsAchievement($achievement['id']) as $c) {
									$this->Achievements->deleteAchievementConditionAchievement($c['id']);
								}
							break;
						}
					}

					// Upload images
					foreach($images as $key => &$image)
					{
						if(!is_null($image))
						{
							$image['media_id'] = $this->Media->createAchievementMedia(
								$this->Auth->getUserId(),
								$seminary['id'],
								sprintf('achievement-%d', $achievement['id']).(substr($key, 0, 2) == 'un' ? '-locked' : NULL),
								'',
								$image['mimetype'],
								$image['tmp_name']
							);
						}
					}
					if(!is_null($images['unachieved_image']) && $images['unachieved_image']['media_id'] !== false) {
						$this->Achievements->setUnachievedMediaForAchievement($achievement['id'], $images['unachieved_image']['media_id']);
					}
					if(!is_null($images['achieved_image']) && $images['achieved_image']['media_id'] !== false) {
						$this->Achievements->setAchievedMediaForAchievement($achievement['id'], $images['achieved_image']['media_id']);
					}

					// Redirect
					if(!is_null($this->request->getPostParam('edit-conditions'))) {
						// To condition editing
						$this->redirect($this->linker->link(array('conditions', $seminary['url'], $achievement['url']), 1));
					}
					else {
						// To overview
						$this->redirect($this->linker->link(array('manage', $seminary['url']), 1, true, null, false, $achievement['url']));
					}
				}
			}

			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}


			// Set title
			$this->addTitleLocalized('Edit Achievement');
			$this->addTitle($seminary['title']);

			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('achievement', $achievement);
			$this->set('title', $title);
			$this->set('description', $description);
			$this->set('progress', $progress);
			$this->set('hidden', $hidden);
			$this->set('onlyOnce', $onlyOnce);
			$this->set('allConditions', $allConditions);
			$this->set('deadline', $deadline);
			$this->set('condition', $condition);
			$this->set('conditions', $conditions);
			$this->set('mimetypes', $mimetypes);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}


		/**
		 * Action: conditions.
		 * 
		 * Edit conditions of an Achievement.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of Seminary
		 * @param	string	$achievementUrl	URL-title of Achievement to edit
		 */
		public function conditions($seminaryUrl, $achievementUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Achievement
			$achievement = $this->Achievements->getAchievementByUrl($seminary['id'], $achievementUrl);

			// Get conditions
			$conditions = array();
			switch($achievement['condition'])
			{
				// Date conditions
				case 'date':
					$conditions = $this->Achievements->getAchievementConditionsDate($achievement['id']);
				break;
				// Character conditions
				case 'character':
					$conditions = $this->Achievements->getAchievementConditionsCharacter($achievement['id']);
				break;
				// Quest conditions
				case 'quest':
					$conditions = $this->Achievements->getAchievementConditionsQuest($achievement['id']);
				break;
				// Achievement conditions
				case 'achievement':
					$conditions = $this->Achievements->getAchievementConditionsAchievement($achievement['id']);
				break;
			}

			// Values
			$characterFields = array(
				'id', 'created', 'user_id', 'name', 'url', 'xps', 'quest_xps', 'avatar_id',
				'charactertype_id', 'charactertype_name', 'charactertype_url',
				'xplevel_id', 'xplevel'
			);
			$questFields = array(
				'id', 'quest_id', 'character_id', 'created', 'status'
			);
			$achievementFields = array(
				'achievement_id', 'character_id', 'created'
			);
			$quests = $this->Quests->getQuestsForSeminary($seminary['id']);
			$achievements = $this->Achievements->getAchievementsForSeminary($seminary['id']);
			$deletes = array();

			// Save conditions
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
			{
				// Get entered conditions
				$selectedConditions = $this->request->getPostParam('conditions');
				$deletes = $this->request->getPostParam('deletes');
				if(!is_array($deletes)) {
					$deletes = array();
				}

				// Edit or delete conditions
				foreach($conditions as &$condition)
				{
					$selectedCondition = $selectedConditions[$condition['id']];
					switch($achievement['condition'])
					{
						// Date conditions
						case 'date':
							if(array_key_exists($condition['id'], $deletes)) {
								$this->Achievements->deleteAchievementConditionDate($condition['id']);
							}
							else {
								$this->Achievements->editAchievementConditionDate(
									$condition['id'],
									$selectedCondition['select']
								);
							}
						break;
						// Character conditions
						case 'character':
							if(array_key_exists($condition['id'], $deletes)) {
								$this->Achievements->deleteAchievementConditionCharacter($condition['id']);
							}
							else {
								$this->Achievements->editAchievementConditionCharacter(
									$condition['id'],
									$selectedCondition['field'],
									$selectedCondition['value']
								);
							}
						break;
						// Quest conditions
						case 'quest':
							if(array_key_exists($condition['id'], $deletes)) {
								$this->Achievements->deleteAchievementConditionQuest($condition['id']);
							}
							else
							{
								// Get selected Quest
								$questIndex = null;
								if(!empty($selectedCondition['quest'])) {
									foreach($quests as $index => &$quest) {
										if($quest['url'] == $selectedCondition['quest']) {
											$questIndex = $index;
										}
									}
								}

								// Edit condition
								$this->Achievements->editAchievementConditionQuest(
									$condition['id'],
									$selectedCondition['field'],
									array_key_exists('count', $selectedCondition),
									$selectedCondition['value'],
									(!is_null($questIndex)) ? $quests[$questIndex]['id'] : null,
									($selectedCondition['status'] != '') ? $selectedCondition['status'] : null,
									(!empty($selectedCondition['groupby'])) ? $selectedCondition['groupby'] : null
								);
							}
						break;
						// Achievement conditions
						case 'achievement':
							if(array_key_exists($condition['id'], $deletes)) {
								$this->Achievements->deleteAchievementConditionAchievement($condition['id']);
							}
							else
							{
								// Get selected Achievement
								$achievmentIndex = null;
								if(!empty($selectedCondition['achievement'])) {
									foreach($achievements as $index => &$a) {
										if($a['url'] == $selectedCondition['achievement']) {
											$achievementIndex = $index;
										}
									}
								}

								// Edit condition
								$this->Achievements->editAchievementConditionAchievement(
									$condition['id'],
									$selectedCondition['field'],
									array_key_exists('count', $selectedCondition),
									$selectedCondition['value'],
									(!is_null($achievementIndex)) ? $achievements[$achievementIndex]['id'] : null,
									(!empty($selectedCondition['groupby'])) ? $selectedCondition['groupby'] : null
								);
							}
						break;
					}
				}

				// Add new condition
				if(array_key_exists('new', $selectedConditions))
				{
					$condition = $selectedConditions['new'];
					switch($achievement['condition'])
					{
						// Date conditions
						case 'date':
							if(!empty($condition['select'])) {
								$this->Achievements->addAchievementConditionDate(
									$this->Auth->getUserId(),
									$achievement['id'],
									$condition['select']
								);
							}
						break;
						// Character conditions
						case 'character':
							if(!empty($condition['value'])) {
								$this->Achievements->addAchievementConditionCharacter(
									$this->Auth->getUserId(),
									$achievement['id'],
									$condition['field'],
									$condition['value']
								);
							}
						break;
						// Quest conditions
						case 'quest':
							if(!empty($condition['value']))
							{
								// Get selected Quest
								$questIndex = null;
								if(!empty($condition['quest'])) {
									foreach($quests as $index => &$quest) {
										if($quest['url'] == $condition['quest']) {
											$questIndex = $index;
										}
									}
								}

								// Edit condition
								$this->Achievements->addAchievementConditionQuest(
									$this->Auth->getUserId(),
									$achievement['id'],
									$condition['field'],
									array_key_exists('count', $condition),
									$condition['value'],
									(!is_null($questIndex)) ? $quests[$questIndex]['id'] : null,
									($condition['status'] != '') ? $condition['status'] : null,
									(!empty($condition['groupby'])) ? $condition['groupby'] : null
								);
							}
						break;
						// Achievement conditions
						case 'achievement':
							if(!empty($condition['value']))
							{
								// Get selected Achievement
								$achievmentIndex = null;
								if(!empty($selectedCondition['achievement'])) {
									foreach($achievements as $index => &$a) {
										if($a['url'] == $selectedCondition['achievement']) {
											$achievementIndex = $index;
										}
									}
								}

								// Edit condition
								$this->Achievements->addAchievementConditionAchievement(
									$this->Auth->getUserId(),
									$achievement['id'],
									$condition['field'],
									array_key_exists('count', $condition),
									$condition['value'],
									(!is_null($achievementIndex)) ? $achievements[$achievementIndex]['id'] : null,
									(!empty($condition['groupby'])) ? $condition['groupby'] : null
								);
							}
						break;
					}
				}

				// Redirect to overview
				$this->redirect($this->linker->link(array('manage', $seminary['url']), 1, true, null, false, $achievement['url']));
			}


			// Set title
			$this->addTitleLocalized('Edit Achievement conditions');
			$this->addTitle($seminary['title']);

			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('achievement', $achievement);
			$this->set('conditions', $conditions);
			$this->set('characterFields', $characterFields);
			$this->set('questFields', $questFields);
			$this->set('quests', $quests);
			$this->set('achievementFields', $achievementFields);
			$this->set('achievements', $achievements);
			$this->set('deletes', $deletes);
		}


		/**
		 * Action: delete.
		 * 
		 * Delete an Achievement.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of Seminary
		 * @param	string	$achievementUrl	URL-title of Achievement
		 */
		public function delete($seminaryUrl, $achievementUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Achievement
			$achievement = $this->Achievements->getAchievementByUrl($seminary['id'], $achievementUrl);
			
			// Check request method
			if($this->request->getRequestMethod() == 'POST')
			{
				// Check confirmation
				if(!is_null($this->request->getPostParam('delete')))
				{
					// Delete seminary
					$this->Achievements->deleteAchievement($achievement);
				}
				
				// Redirect to entry
				$this->redirect($this->linker->link(array('manage', $seminary['url']), 1));
			}
			
			
			// Set titile
			$this->addTitleLocalized('Delete seminary');
			
			// Show confirmation
			$this->set('seminary', $seminary);
			$this->set('achievement', $achievement);
		}
	}

?>