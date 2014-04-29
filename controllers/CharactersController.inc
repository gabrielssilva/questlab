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
	 * Controller of the Agent to list registered users and their data.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactersController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'characters', 'users', 'charactergroups', 'charactertypes', 'seminarycharacterfields', 'avatars', 'media', 'quests', 'questgroups', 'questtopics');
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
			'index' => array('admin', 'moderator', 'user'),
			'character' => array('admin', 'moderator', 'user'),
			'register' => array('admin', 'moderator', 'user'),
			'manage' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index' => array('admin', 'moderator'),
			'character' => array('admin', 'moderator', 'user'),
			'manage' => array('admin', 'moderator')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * List registered Characters for a Seminary
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 */
		public function index($seminaryUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Seminarycharacterfields
			$characterfields = $this->Seminarycharacterfields->getFieldsForSeminary($seminary['id']);
			
			// Get registered Characters
			$characters = $this->Characters->getCharactersForSeminary($seminary['id']);
			foreach($characters as &$character)
			{
				$character['xplevel'] = $this->Characters->getXPLevelOfCharacters($character['id']);
				$character['user'] = $this->Users->getUserById($character['user_id']);
				$character['characterroles'] = array_map(function($r) { return $r['name']; }, $this->Characterroles->getCharacterrolesForCharacterById($character['id']));
				$character['characterfields'] = array();
				foreach($this->Seminarycharacterfields->getFieldsForCharacter($character['id']) as &$value) {
					$character['characterfields'][$value['url']] = $value;
				}
			}
			
			// Sort Characters
			global $sortorder;
			$sortorder = ($this->request->getRequestMethod() == 'GET') ? $this->request->getGetParam('sortorder') : null;
			$sortorder = (!is_null($sortorder)) ? $sortorder : 'xps';
			$sortMethod = 'sortCharactersBy'.ucfirst(strtolower($sortorder));
			if(method_exists($this, $sortMethod)) {
				usort($characters, array($this, $sortMethod));
			}
			elseif(in_array($sortorder, array_map(function($f) { return $f['title']; }, $characterfields))) {
				usort($characters, function($a, $b) {
					global $sortorder;
					return $this->sortCharactersByField($a, $b, $sortorder);
				});
			}
			else {
				throw new \nre\exceptions\ParamsNotValidException($sortorder);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('characters', $characters);
			$this->set('characterfields', $characterfields);
			$this->set('sortorder', $sortorder);
		}
		
		
		/**
		 * Action: character.
		 * 
		 * Show a Charater and its details.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 * @param	string	$characterUrl	URL-name of a Charater
		 */
		public function character($seminaryUrl, $characterUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			$seminary['achievable_xps'] = $this->Seminaries->getTotalXPs($seminary['id']);
			
			// Get Character
			$character = $this->Characters->getCharacterByUrl($seminary['id'], $characterUrl);
			$character['quest_xps'] = $this->Characters->getQuestXPsOfCharacter($character['id']);
			$character['xplevel'] = $this->Characters->getXPLevelOfCharacters($character['id']);
			$character['rank'] = $this->Characters->getXPRank($seminary['id'], $character['xps']);
			
			// Get User
			$user = $this->Users->getUserById($character['user_id']);
			
			// Get Character groups
			$groups = $this->Charactergroups->getGroupsForCharacter($character['id']);
			foreach($groups as &$group) {
				$group['groupsgroup'] = $this->Charactergroups->getGroupsgroupById($group['charactergroupsgroup_id']);
			}
			
			// Get Achievements
			$achievements = $this->Achievements->getAchievedAchievementsForCharacter($character['id']);
			
			// Get Achievements with deadline (milestones)
			$milestones = $this->Achievements->getDeadlineAchievements($seminary['id']);
			foreach($milestones as &$milestone) {
				$milestone['achieved'] = $this->Achievements->hasCharacterAchievedAchievement($milestone['id'], $character['id']);
			}
			
			// Get ranking
			$ranking = array(
				'superior' => $this->Characters->getSuperiorCharacters($seminary['id'], $character['xps'], \nre\configs\AppConfig::$misc['ranking_range']),
				'inferior' => $this->Characters->getInferiorCharacters($seminary['id'], $character['id'], $character['xps'], \nre\configs\AppConfig::$misc['ranking_range'])
			);
			
			// Get Quest topics
			$questtopics = $this->Questtopics->getQuesttopicsForSeminary($seminary['id']);
			foreach($questtopics as &$questtopic)
			{
				$questtopic['questcount'] = $this->Questtopics->getQuestCountForQuesttopic($questtopic['id']);
				$questtopic['characterQuestcount'] = $this->Questtopics->getCharacterQuestCountForQuesttopic($questtopic['id'], $character['id']);
			}
			
			// Get “last” Quest
			$lastQuest = null;
			if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0)
			{
				$lastQuest = $this->Quests->getLastQuestForCharacter($character['id']);
				if(!is_null($lastQuest)) {
					$lastQuest['questgroup'] = $this->Questgroups->getQuestgroupById($lastQuest['questgroup_id']);
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('character', $character);
			$this->set('user', $user);
			$this->set('groups', $groups);
			$this->set('achievements', $achievements);
			$this->set('milestones', $milestones);
			$this->set('ranking', $ranking);
			$this->set('questtopics', $questtopics);
			$this->set('lastQuest', $lastQuest);
		}
		
		
		/**
		 * Acton: register.
		 * 
		 * Register a new character for a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @throws	ParamsNotValidException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 */
		public function register($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Check for already existing Character
			try {
				$this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
				throw new \nre\exceptions\AccessDeniedException();
			}
			catch(\nre\exceptions\IdNotFoundException $e) {
				// The should be the case
			}
				
			
			// Character types
			$types = $this->Charactertypes->getCharacterTypesForSeminary($seminary['id']);
			
			// Character fields
			$fields = $this->Seminarycharacterfields->getFieldsForSeminary($seminary['id']);
			
			// Register Character
			$charactername = '';
			$validation = true;
			$fieldsValidation = true;
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// Validate Character properties
				$validation = $this->Validation->validateParams($this->request->getPostParams(), array('charactername'));
				$charactername = $this->request->getPostParam('charactername');
				if($this->Characters->characterNameExists($charactername)) {
					$validation = $this->Validation->addValidationResult($validation, 'charactername', 'exist', true);
				}
				
				// Validate type
				$typeIndex = null;
				foreach($types as $index => &$type)
				{
					$type['selected'] = ($type['url'] == $this->request->getPostParam('type'));
					if($type['selected']) {
						$typeIndex = $index;
					}
				}
				if(is_null($typeIndex)) {
					throw new \nre\exceptions\ParamsNotValidException($typeIndex);
				}
				
				// Validate fields
				$fieldsValues = $this->request->getPostParam('fields');
				foreach($fields as &$field)
				{
					if(!array_key_exists($field['url'], $fieldsValues)) {
						throw new \nre\exceptions\ParamsNotValidException($index);
					}
					$field['uservalue'] = $fieldsValues[$field['url']];
					if($field['required'])
					{
						$fieldValidation = $this->Validation->validate($fieldsValues[$field['url']], array('regex'=>$field['regex']));
						if($fieldValidation !== true)
						{
							if(!is_array($fieldsValidation)) {
								$fieldsValidation = array();
							}
							$fieldsValidation[$field['url']] = $fieldValidation;
						}
					}
				}
				
				// Register
				if($validation === true && $fieldsValidation === true)
				{
					$characterId = $this->Characters->createCharacter($this->Auth->getUserId(), $types[$typeIndex]['id'], $charactername);
					
					// Add Seminary fields
					foreach($fields as &$field) {
						if(!empty($fieldsValues[$field['url']])) {
							$this->Characters->setSeminaryFieldOfCharacter($characterId, $field['id'], $fieldsValues[$field['url']]);
						}
					}
					
					// Send mail
					$this->sendRegistrationMail($charactername);
					
					// Redirect
					$this->redirect($this->linker->link(array('seminaries')));
				}
			}
			
			// Get XP-levels
			$xplevels = $this->Characters->getXPLevelsForSeminary($seminary['id']);
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('types', $types);
			$this->set('fields', $fields);
			$this->set('charactername', $charactername);
			$this->set('validation', $validation);
			$this->set('fieldsValidation', $fieldsValidation);
			$this->set('xplevels', $xplevels);
		}
		
		
		/**
		 * Action: manage.
		 * 
		 * Manage Characters.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 */
		public function manage($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Set default properties to show
			$properties = array(
				'username',
				'xps',
				'roles'
			);
			
			$selectedCharacters = array();
			global $sortorder;
			if($this->request->getRequestMethod() == 'POST')
			{
				// Set sortorder
				$sortorder = $this->request->getPostParam('sortorder');
				
				// Do action
				$selectedCharacters = $this->request->getPostParam('characters');
				if(!is_array($selectedCharacters)) {
					$selectedCharacters = array();
				}
				if(!is_null($this->request->getPostParam('actions')) && count($this->request->getPostParam('actions')) > 0 && !is_null($this->request->getPostParam('characters')) && count($this->request->getPostParam('characters')) > 0)
				{
					$actions = $this->request->getPostParam('actions');
					$action = array_keys($actions)[0];
				
					switch($action)
					{
						// Add/remove role to/from Characters
						case 'addrole':
						case 'removerole':
							// Determine role and check permissions
							$role = null;
							switch($actions[$action])
							{
								case _('Admin'):
									if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) <= 0 && !in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) {
										throw new \nre\exceptions\AccessDeniedException();
									}
									$role = 'admin';
								break;
								case _('Moderator'):
									if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) <= 0 && !in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) {
										throw new \nre\exceptions\AccessDeniedException();
									}
									$role = 'moderator';
								break;
								case _('User'):
									if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) <= 0 && count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) <= 0) {
										throw new \nre\exceptions\AccessDeniedException();
									}
									$role = 'user';
								break;
							}
						
							// Add role
							if($action == 'addrole') {
								foreach($selectedCharacters as &$characterId) {
									$this->Characterroles->addCharacterroleToCharacter($characterId, $role);
								}
							}
							// Remove role
							else {
								foreach($selectedCharacters as &$characterId) {
									$this->Characterroles->removeCharacterroleFromCharacter($characterId, $role);
								}
							}
						break;
					}
				}
			}
			
			// Get Seminarycharacterfields
			$characterfields = $this->Seminarycharacterfields->getFieldsForSeminary($seminary['id']);
			
			// Get registered Characters
			$characters = $this->Characters->getCharactersForSeminary($seminary['id']);
			foreach($characters as &$character)
			{
				$character['xplevel'] = $this->Characters->getXPLevelOfCharacters($character['id']);
				$character['user'] = $this->Users->getUserById($character['user_id']);
				$character['characterroles'] = array_map(function($r) { return $r['name']; }, $this->Characterroles->getCharacterrolesForCharacterById($character['id']));
				$character['characterfields'] = array();
				foreach($this->Seminarycharacterfields->getFieldsForCharacter($character['id']) as &$value) {
					$character['characterfields'][$value['url']] = $value;
				}
			}
			
			// Sort Characters
			$sortorder = (!is_null($sortorder)) ? $sortorder : 'xps';
			$sortMethod = 'sortCharactersBy'.ucfirst(strtolower($sortorder));
			if(method_exists($this, $sortMethod)) {
				usort($characters, array($this, $sortMethod));
			}
			elseif(in_array($sortorder, array_map(function($f) { return $f['title']; }, $characterfields))) {
				usort($characters, function($a, $b) {
					global $sortorder;
					return $this->sortCharactersByField($a, $b, $sortorder);
				});
			}
			else {
				throw new \nre\exceptions\ParamsNotValidException($sortorder);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('characters', $characters);
			$this->set('characterfields', $characterfields);
			$this->set('selectedCharacters', $selectedCharacters);
			$this->set('sortorder', $sortorder);
		}
		
		
		
		
		/**
		 * Send mail for new Character registration.
		 * 
		 * @param	string	$charactername	Name of newly registered Character
		 */
		private function sendRegistrationMail($charactername)
		{
			$sender = \nre\configs\AppConfig::$app['mailsender'];
			if(empty($sender)) {
				return;
			}
			
			// Send notification mail to system moderators
			$subject = sprintf('new Character registration: %s', $charactername);
			$message = sprintf('User “%s” <%s> has registered a new Character “%s” for the Seminary “%s”', self::$user['username'], self::$user['email'], $charactername, self::$seminary['title']);
			$characters = $this->Characters->getCharactersWithCharacterRole(self::$seminary['id'], 'moderator');
			foreach($characters as &$character)
			{
				$moderator = $this->Users->getUserById($character['user_id']);
				\hhu\z\Utils::sendMail($sender, $moderator['email'], $subject, $message);
			}
		}
		
		
		/**
		 * Compare two Characters by their name.
		 * 
		 * @param	array	$a	Character a
		 * @param	array	$b	Character b
		 * @return	int		Result of comparison
		 */
		private function sortCharactersByCharactername($a, $b)
		{
			if($a['name'] == $b['name']) {
				return 0;
			}
			
			
			return ($a['name'] < $b['name']) ? -1 : 1;
		}
		
		
		/**
		 * Compare two Characters by their XPs.
		 * 
		 * @param	array	$a	Character a
		 * @param	array	$b	Character b
		 * @return	int		Result of comparison
		 */
		private function sortCharactersByXps($a, $b)
		{
			if($a['xps'] == $b['xps']) {
				return 0;
			}
			
			
			return ($a['xps'] > $b['xps']) ? -1 : 1;
		}
		
		
		/**
		 * Compare two Characters by their Character roles.
		 * 
		 * @param	array	$a	Character a
		 * @param	array	$b	Character b
		 * @return	int		Result of comparison
		 */
		private function sortCharactersByRole($a, $b)
		{
			$roles = array('admin', 'moderator', 'user', 'guest');
			
			if(in_array('admin', $a['characterroles']))
			{
				if(in_array('admin', $b['characterroles'])) {
					return 0;
				}
				return -1;
			}
			if(in_array('moderator', $a['characterroles']))
			{
				if(in_array('admin', $b['characterroles'])) {
					return 1;
				}
				if(in_array('moderator', $b['characterroles'])) {
					return 0;
				}
				return -1;
			}
			if(in_array('user', $a['characterroles']))
			{
				if(in_array('admin', $b['characterroles']) || in_array('moderator', $b['characterroles'])) {
					return 1;
				}
				if(in_array('user', $b['characterroles'])) {
					return 0;
				}
				return -1;
			}
			if(in_array('guest', $a['characterroles']))
			{
				if(in_array('admin', $b['characterroles']) || in_array('moderator', $b['characterroles'])  || in_array('user', $b['characterroles'])) {
					return 1;
				}
				if(in_array('guest', $b['characterroles'])) {
					return 0;
				}
				return -1;
			}
			
			
			return 1;
		}
		
		
		/**
		 * Compare two Characters by one of their Seminary fields.
		 * 
		 * @param	array	$a	Character a
		 * @param	array	$b	Character b
		 * @param	string	$field	Field to compare
		 * @return	int		Result of comparison
		 */
		private function sortCharactersByField($a, $b, $field)
		{
			if($a['characterfields'][$field] == $b['characterfields'][$field]) {
				return 0;
			}
			
			
			return ($a['characterfields'][$field] < $b['characterfields'][$field]) ? -1 : 1;
		}
		
	}

?>
