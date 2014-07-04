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
	 * Controller of the QuestsAgent to display Quests.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestsController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'questgroups', 'quests', 'questtexts', 'media', 'questtypes', 'questgroupshierarchy', 'xplevels');
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
			'quest'		=> array('admin', 'moderator', 'user'),
			'submissions'	=> array('admin', 'moderator', 'user'),
			'submission'	=> array('admin', 'moderator', 'user'),
			'create'	=> array('admin', 'moderator', 'user'),
			'edit'		=> array('admin', 'moderator', 'user'),
			'edittexts'	=> array('admin', 'moderator', 'user'),
			'delete'	=> array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index'		=> array('admin', 'moderator'),
			'quest'		=> array('admin', 'moderator', 'user'),
			'submissions'	=> array('admin', 'moderator'),
			'submission'	=> array('admin', 'moderator'),
			'create'	=> array('admin', 'moderator'),
			'edit'		=> array('admin', 'moderator'),
			'edittexts'	=> array('admin', 'moderator'),
			'delete'	=> array('admin')
		);
		
		
		
		
		/**
		 * Prefilter that is executed before running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::preFilter($request, $response);
			
			$this->checkAchievements($request, $response, array('character', 'quest'));
			$this->checkAchievements($request, $response, 'achievement');
		}
		
		
		/**
		 * Action: index.
		 * 
		 * List all Quests for a Seminary.
		 * 
		 * @param	string	$seminaryUrl	URL-Title of Seminary
		 * @param	string	$all		Show all Quests
		 */
		public function index($seminaryUrl, $all=null)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Set filters
			$selectedQuestgroup = null;
			$selectedQuesttype = null;
			$selectedTitle = null;
			$page = 1;
			if($this->request->getRequestMethod() == 'GET')
			{
				$selectedQuestgroup = $this->request->getGetParam('questgroup');
				$selectedQuestgroup = !empty($selectedQuestgroup) ? $selectedQuestgroup : null;
				$selectedQuesttype = $this->request->getGetParam('questtype');
				$selectedQuesttype = !empty($selectedQuesttype) ? $selectedQuesttype : null;
				$selectedTitle = $this->request->getGetParam('title');
				$selectedTitle = !empty($selectedTitle) ? $selectedTitle : null;
				$page = $this->request->getGetParam('page');
				$page = !empty($page) ? intval($page) : 1;
			}
			
			// Get Quests
			$limit = ($all != 'all') ? \nre\configs\AppConfig::$misc['lists_limit'] : null;
			$offset = ($all != 'all') ? max((intval($page) - 1), 0) * $limit : 0;
			$questsCount = $this->Quests->getCountForQuestsForSeminaryByOpenSubmissions($seminary['id'], $selectedQuestgroup, $selectedQuesttype, $selectedTitle);
			$quests = $this->Quests->getQuestsForSeminaryByOpenSubmissions($seminary['id'], $selectedQuestgroup, $selectedQuesttype, $selectedTitle, $limit, $offset);
			foreach($quests as &$quest)
			{
				// Get Questtype
				$quest['questtype'] = $this->Questtypes->getQuesttypeById($quest['questtype_id']);
			}
			
			// Get filter values
			$questgroups = $this->Questgroups->getQuestgroupsForSeminary($seminary['id']);
			$questtypes = $this->Questtypes->getQuesttypes();
			
			
			// Set titile
			$this->addTitleLocalized('Quests');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroups', $questgroups);
			$this->set('questtypes', $questtypes);
			$this->set('selectedQuestgroup', $selectedQuestgroup);
			$this->set('selectedQuesttype', $selectedQuesttype);
			$this->set('selectedTitle', $selectedTitle);
			$this->set('quests', $quests);
			$this->set('questsCount', $questsCount);
			$this->set('all', $all);
			$this->set('page', $page);
			$this->set('limit', $limit);
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Show a quest and its task.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 * @param	string	$questgroupUrl		URL-Title of Questgroup
		 * @param	string	$questUrl		URL-Title of Quest
		 * @param	string	$questtexttypeUrl	URL-Title of Questtexttype
		 * @param	int	$questtextPos		Position of Questtext
		 */
		public function quest($seminaryUrl, $questgroupUrl, $questUrl, $questtexttypeUrl=null, $questtextPos=1)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			$questgroup['picture'] = null;
			if(!is_null($questgroup['questgroupspicture_id'])) {
				$questgroup['picture'] = $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']);
			}
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);
			
			// Get Character
			$character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
			
			// Check permissions
			if(count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) == 0)
			{
				$previousQuests = $this->Quests->getPreviousQuests($quest['id']);
				if(count($previousQuests) == 0)
				{
					// Previous Questgroup
					$previousQuestgroup = $this->Questgroups->getPreviousQuestgroup($questgroup['id']);
					if(!is_null($previousQuestgroup) && !$this->Questgroups->hasCharacterSolvedQuestgroup($previousQuestgroup['id'], $character['id'])) {
						throw new \nre\exceptions\AccessDeniedException();
					}
				}
				else
				{
					// Previous Quests
					// One previous Quest has to be solved and no other
					// following Quest of ones has to be tried
					// except it is also an previous Quest of the current Quest
					$solved = false;
					$tried = false;
					foreach($previousQuests as &$previousQuest)
					{
						// Check previous Quest
						if($this->Quests->hasCharacterSolvedQuest($previousQuest['id'], $character['id']))
						{
							$solved = true;
						
							// Check following Quests
							$followingQuests = $this->Quests->getNextQuests($previousQuest['id']);
							foreach($followingQuests as $followingQuest)
							{
								// Check following Quest
								if($followingQuest['id'] != $quest['id'] && $this->Quests->hasCharacterTriedQuest($followingQuest['id'], $character['id']))
								{
									$followingFollowingQuests = $this->Quests->getNextQuests($followingQuest['id']);
									if(!in_array($quest['id'], array_map(function($q) { return $q['id']; }, $followingFollowingQuests)))
									{
										$tried = true;
										break;
									}
								}
							}
						
							break;
						}
					}
					if(!$solved || $tried) {
						throw new \nre\exceptions\AccessDeniedException();
					}
				}
			}
			
			// Set status “entered”
			$this->Quests->setQuestEntered($quest['id'], $character['id']);
			
			// Has Character solved quest?
			$solved = $this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']);
			
			// Get Questtexts
			$questtexts = array();
			$questtexts['Prolog'] = $this->Questtexts->getQuesttextsOfQuest($quest['id'], 'Prolog');
			if($solved || count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) > 0) {
				$questtexts['Epilog'] = $this->Questtexts->getQuesttextsOfQuest($quest['id'], 'Epilog');
			}
			foreach($questtexts as &$questtextList)
			{
				foreach($questtextList as &$questtext)
				{
					// Questtext media
					if(!is_null($questtext['questsmedia_id'])) {
						$questtext['media'] = $this->Media->getSeminaryMediaById($questtext['questsmedia_id']);
					}
				
					// Related Questgroups
					$questtext['relatedQuestsgroups'] = $this->Questgroups->getRelatedQuestsgroupsOfQuesttext($questtext['id']);
				}
			}
			
			// Quest status
			$questStatus = $this->request->getGetParam('status');
			
			// Quest media
			$questmedia = null;
			if(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getSeminaryMediaById($quest['questsmedia_id']);
			}
			
			// Task
			$task = null;
			$questtype = $this->Questtypes->getQuesttypeById($quest['questtype_id']);
			if(!is_null($questtype['classname'])) {
				$task = $this->renderTask($questtype['classname'], $seminary, $questgroup, $quest, $character);
			}
			else
			{
				// Mark Quest as solved
				$this->Quests->setQuestSolved($quest['id'], $character['id']);
				$solved = true;
			}
			
			// Get (related) Questtexts
			$relatedQuesttexts = $this->Questtexts->getRelatedQuesttextsForQuestgroup($questgroup['id']);
			$relatedQuesttext = $this->Questtexts->pickQuesttextLastEnteredByCharacter($character['id'], $relatedQuesttexts);
			if(!is_null($relatedQuesttext)) {
				$relatedQuesttext['quest'] = $this->Quests->getQuestById($relatedQuesttext['quest_id']);
				if(!empty($relatedQuesttext['quest'])) {
					$relatedQuesttext['quest']['questgroup_url'] = $this->Questgroups->getQuestgroupById($relatedQuesttext['quest']['questgroup_id'])['url'];
				}
			}
			
			// Next Quest/Questgroup
			$nextQuests = null;
			$charactedHasChoosenNextQuest = false;
			$nextQuestgroup = null;
			if($solved || count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) > 0)
			{
				// Next Quest
				$nextQuests = $this->Quests->getNextQuests($quest['id']);
				foreach($nextQuests as &$nextQuest)
				{
					// Set entered status of Quest
					$nextQuest['entered'] = $this->Quests->hasCharacterEnteredQuest($nextQuest['id'], $character['id']);
					if($nextQuest['entered']) {
						$charactedHasChoosenNextQuest = true;
					}
				}
				
				// Next Questgroup
				if(empty($nextQuests))
				{
					if(is_null($relatedQuesttext))
					{
						$nextQuestgroup = $this->Questgroups->getNextQuestgroup($questgroup['id']);
						$nextQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($nextQuestgroup['id']);
					}
					else
					{
						// Related (Main-) Quest
						$nextQuest = $relatedQuesttext['quest'];
						$nextQuest['entered'] = true;
						$nextQuests = array($nextQuest);
					}
				}
			}
			
			
			// Set titile
			$this->addTitle($quest['title']);
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('questtexts', $questtexts);
			$this->set('quest', $quest);
			$this->set('queststatus', $questStatus);
			$this->set('relatedquesttext', $relatedQuesttext);
			$this->set('nextquests', $nextQuests);
			$this->set('charactedHasChoosenNextQuest', $charactedHasChoosenNextQuest);
			$this->set('nextquestgroup', $nextQuestgroup);
			$this->set('task', $task);
			$this->set('media', $questmedia);
			$this->set('solved', $solved);
		}
		
		
		/**
		 * List Character submissions for a Quest.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of Seminary
		 * @param	string	$questgroupUrl	URL-Title of Questgroup
		 * @param	string	$questUrl	URL-Title of Quest
		 */
		public function submissions($seminaryUrl, $questgroupUrl, $questUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			$questgroup['picture'] = null;
			if(!is_null($questgroup['questgroupspicture_id'])) {
				$questgroup['picture'] = $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']);
			}
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);
			
			// Media
			$questmedia = null;
			if(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getSeminaryMediaById($quest['questsmedia_id']);
			}
			
			// Get submitted Character submissions waiting for approval
			$submittedSubmissionCharacters = $this->Characters->getCharactersSubmittedQuest($quest['id']);
			
			// Get unsolved Character submissions
			$unsolvedSubmissionCharacters = $this->Characters->getCharactersUnsolvedQuest($quest['id']);
			
			// Get solved Character submissions
			$solvedSubmissionCharacters = $this->Characters->getCharactersSolvedQuest($quest['id']);
			
			
			// Set titile
			$this->addTitleLocalized('Submissions');
			$this->addTitle($quest['title']);
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('quest', $quest);
			$this->set('media', $questmedia);
			$this->set('submittedSubmissionCharacters', $submittedSubmissionCharacters);
			$this->set('unsolvedSubmissionCharacters', $unsolvedSubmissionCharacters);
			$this->set('solvedSubmissionCharacters', $solvedSubmissionCharacters);
		}
		
		
		/**
		 * Show and handle the submission of a Character for a Quest.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of Seminary
		 * @param	string	$questgroupUrl	URL-Title of Questgroup
		 * @param	string	$questUrl	URL-Title of Quest
		 * @param	string	$characterUrl	URL-Title of Character
		 */
		public function submission($seminaryUrl, $questgroupUrl, $questUrl, $characterUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			$questgroup['picture'] = null;
			if(!is_null($questgroup['questgroupspicture_id'])) {
				$questgroup['picture'] = $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']);
			}
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);
			
			// Character
			$character = $this->Characters->getCharacterByUrl($seminary['id'], $characterUrl);
			
			// Media
			$questmedia = null;
			if(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getSeminaryMediaById($quest['questsmedia_id']);
			}
			
			// Questtype
			$questtype = $this->Questtypes->getQuesttypeById($quest['questtype_id']);
			
			// Render Questtype output
			$output = $this->renderTaskSubmission($questtype['classname'], $seminary, $questgroup, $quest, $character);
			
			
			// Set titile
			$this->addTitleLocalized('Submission of %s', $character['name']);
			$this->addTitle($quest['title']);
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('quest', $quest);
			$this->set('character', $character);
			$this->set('media', $questmedia);
			$this->set('output', $output);
		}
		
		
		/**
		 * Action: create.
		 * 
		 * Create a new Quest.
		 * 
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 * @param	string	$questgroupUrl	URL-Title of Questgroup
		 */
		public function create($seminaryUrl, $questgroupUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			$questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			$questgroup['picture'] = (!is_null($questgroup['questgroupspicture_id'])) ?  $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']) : null;
			
			// Get Quest types
			$questtypes = $this->Questtypes->getQuesttypes();
			foreach($questtypes as &$questtype) {
				$questtype['selected'] = false;
			}

			// Get allowed mimetypes
			$mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

			// Values
			$title = '';
			$xps = 0;
			$task = '';
			$entryText = '';
			$wrongText = '';
			$fields = array('title', 'xps');
			$validation = array();
			
			// Check request method
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$title = $this->request->getPostParam('title');
				if($this->Quests->questTitleExists($title, $seminary['id'])) {
					$validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
				}
				$xps = $this->request->getPostParam('xps');
				$task = $this->request->getPostParam('task');
				$entryText = $this->request->getPostParam('entrytext');
				$wrongText = $this->request->getPostParam('wrongtext');
				
				// Validate Questtype
				$questtypeIndex = null;
				foreach($questtypes as $index => &$questtype)
				{
					$questtype['selected'] = ($questtype['url'] == $this->request->getPostParam('questtype'));
					if($questtype['selected']) {
						$questtypeIndex = $index;
					}
				}
				if(is_null($questtypeIndex)) {
					throw new \nre\exceptions\ParamsNotValidException($questtype);
				}
				
				// Validate media
				$media = null;
				if(!empty($_FILES) && array_key_exists('media', $_FILES) && $_FILES['media']['error'] != UPLOAD_ERR_NO_FILE)
				{
					$media = $_FILES['media'];
					
					// Check error
					if($media['error'] !== UPLOAD_ERR_OK) {
						$validation = $this->Validation->addValidationResult($validation, 'media', 'error', $media['error']);
					}
					
					// Check mimetype
					$mediaMimetype = null;
					$media['mimetype'] = \hhu\z\Utils::getMimetype($media['tmp_name'], $media['type']);
					foreach($mimetypes as &$mimetype) {
						if($mimetype['mimetype'] == $media['mimetype']) {
							$mediaMimetype = $mimetype;
							break;
						}
					}
					if(is_null($mediaMimetype)) {
						$validation = $this->Validation->addValidationResult($validation, 'media', 'mimetype', $media['mimetype']);
					}
					elseif($media['size'] > $mediaMimetype['size']) {
						$validation = $this->Validation->addValidationResult($validation, 'media', 'size', $mediaMimetype['size']);
					}
				}
				
				// Create new Quest
				if($validation === true)
				{
					$questId = $this->Quests->createQuest(
						$this->Auth->getUserId(),
						$questgroup['id'],
						$questtypes[$questtypeIndex]['id'],
						$title,
						$xps,
						$task,
						$entryText,
						$wrongText
					);
					$quest = $this->Quests->getQuestById($questId);
					
					// Update picture
					if(!is_null($media))
					{
						$questsmediaId = $this->Media->createQuestMedia(
							$this->Auth->getUserId(),
							$seminary['id'],
							$media['name'],
							$title,
							$media['type'],
							$media['tmp_name']
						);
						if($questsmediaId > 0) {
							$this->Quests->setQuestmedia($quest['id'], $questsmediaId);
						}
					}
					
					// Redirect
					$this->redirect($this->linker->link(array('quest', $seminary['url'], $questgroup['url'], $quest['url']), 1));
				}
			}

			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}
			
			
			// Set titile
			$this->addTitleLocalized('Create Quest');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('mimetypes', $mimetypes);
			$this->set('questtypes', $questtypes);
			$this->set('title', $title);
			$this->set('task', $task);
			$this->set('entryText', $entryText);
			$this->set('wrongText', $wrongText);
			$this->set('xps', $xps);
			$this->set('questtype_id', $questtype);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}


		/**
		 * Action: edit.
		 * 
		 * Edit a Quest of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 * @param	string	$questgroupUrl		URL-Title of Questgroup
		 * @param	string	$questUrl		URL-Title of Quest
		 */
		public function edit($seminaryUrl, $questgroupUrl, $questUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			$questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			$questgroup['picture'] = (!is_null($questgroup['questgroupspicture_id'])) ?  $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']) : null;
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);
			
			// Get Quest media
			$questmedia = null;
			if(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getSeminaryMediaById($quest['questsmedia_id']);
			}

			// Get Quest types
			$questtypes = $this->Questtypes->getQuesttypes();
			foreach($questtypes as &$questtype) {
				$questtype['selected'] = ($questtype['id'] == $quest['questtype_id']);
			}

			// Get allowed mimetypes
			$mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

			// Values
			$title = $quest['title'];
			$xps = $quest['xps'];
			$task = $quest['task'];
			$entryText = $quest['entry_text'];
			$wrongText = $quest['wrong_text'];
			$fields = array('title', 'xps');
			$validation = array();

			// Check request method
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$title = $this->request->getPostParam('title');
				if($this->Quests->questTitleExists($title, $seminary['id'], $quest['id'])) {
					$validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
				}
				$xps = $this->request->getPostParam('xps');
				$task = $this->request->getPostParam('task');
				$entryText = $this->request->getPostParam('entrytext');
				$wrongText = $this->request->getPostParam('wrongtext');

				// Validate Questtype
				$questtypeIndex = null;
				foreach($questtypes as $index => &$questtype)
				{
					$questtype['selected'] = ($questtype['url'] == $this->request->getPostParam('questtype'));
					if($questtype['selected']) {
						$questtypeIndex = $index;
					}
				}
				if(is_null($questtypeIndex)) {
					throw new \nre\exceptions\ParamsNotValidException($questtype);
				}

				// Validate media
				$media = null;
				if(!empty($_FILES) && array_key_exists('media', $_FILES) && $_FILES['media']['error'] != UPLOAD_ERR_NO_FILE)
				{
					$media = $_FILES['media'];
					
					// Check error
					if($media['error'] !== UPLOAD_ERR_OK) {
						$validation = $this->Validation->addValidationResult($validation, 'media', 'error', $media['error']);
					}
					
					// Check mimetype
					$mediaMimetype = null;
					$media['mimetype'] = \hhu\z\Utils::getMimetype($media['tmp_name'], $media['type']);
					foreach($mimetypes as &$mimetype) {
						if($mimetype['mimetype'] == $media['mimetype']) {
							$mediaMimetype = $mimetype;
							break;
						}
					}
					if(is_null($mediaMimetype)) {
						$validation = $this->Validation->addValidationResult($validation, 'media', 'mimetype', $media['mimetype']);
					}
					elseif($media['size'] > $mediaMimetype['size']) {
						$validation = $this->Validation->addValidationResult($validation, 'media', 'size', $mediaMimetype['size']);
					}
				}

				// Edit Quest
				if($validation === true)
				{
					$this->Quests->editQuest(
						$quest['id'],
						$questtypes[$questtypeIndex]['id'],
						$title,
						$xps,
						$task,
						$entryText,
						$wrongText
					);
					$quest = $this->Quests->getQuestById($quest['id']);
					
					// Update picture
					if(!is_null($media))
					{
						$questsmediaId = $this->Media->createQuestMedia(
							$this->Auth->getUserId(),
							$seminary['id'],
							$media['name'],
							$title,
							$media['type'],
							$media['tmp_name']
						);
						if($questsmediaId > 0) {
							$this->Quests->setQuestmedia($quest['id'], $questsmediaId);
						}
					}
					
					// Redirect to entry
					$this->redirect($this->linker->link(array('quest', $seminary['url'], $questgroup['url'], $quest['url']), 1));
				}
			}

			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}


			// Set titile
			$this->addTitleLocalized('Edit Quest');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('quest', $quest);
			$this->set('media', $questmedia);
			$this->set('mimetypes', $mimetypes);
			$this->set('questtypes', $questtypes);
			$this->set('title', $title);
			$this->set('task', $task);
			$this->set('entryText', $entryText);
			$this->set('wrongText', $wrongText);
			$this->set('xps', $xps);
			$this->set('questtype_id', $questtype);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}


		/**
		 * Action: edittexts.
		 * 
		 * Edit the texts of a Quest of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 * @param	string	$questgroupUrl		URL-Title of Questgroup
		 * @param	string	$questUrl		URL-Title of Quest
		 */
		public function edittexts($seminaryUrl, $questgroupUrl, $questUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			$questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			$questgroup['picture'] = (!is_null($questgroup['questgroupspicture_id'])) ?  $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']) : null;
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);

			// Get Questtexts
			$questtextTypes = $this->Questtexts->getQuesttexttypes();
			foreach($questtextTypes as &$questtextType)
			{
				$questtextType['texts'] = $this->Questtexts->getQuesttextsOfQuest($quest['id'], $questtextType['url']);
				foreach($questtextType['texts'] as &$questtext)
				{
					if(!is_null($questtext['questsmedia_id'])) {
						$questtext['media'] = $this->Media->getSeminaryMediaById($questtext['questsmedia_id']);
					}
				}
			}

			// Get allowed mimetypes
			$mimetypes = \nre\configs\AppConfig::$mimetypes['moodpics'];

			// Check request method
			$validations = array();
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
			{
				$media = $_FILES['media'];
				$texts = $this->request->getPostParam('questtexts');
				$deleteTexts = $this->request->getPostParam('deletes');
				if(!is_array($deleteTexts)) {
					$deleteTexts = array();
				}

				foreach($questtextTypes as &$type)
				{
					// Edit or delete texts
					if(!array_key_exists($type['url'], $texts)) {
						continue;
					}
					foreach($type['texts'] as &$text)
					{
						if(array_key_exists($type['url'], $deleteTexts) && array_key_exists($text['id'], $deleteTexts[$type['url']]))
						{
							// Delete text
							$this->Questtexts->deleteQuesttext($text);
							//unset($texts[$type['url']][$text['id']]);
						}
						elseif(array_key_exists($type['url'], $texts) && array_key_exists($text['id'], $texts[$type['url']]))
						{
							// Edit text
							$this->Questtexts->editQuesttext($text['id'], $texts[$type['url']][$text['id']]);

							// Validate medium
							$medium = null;
							$validation = true;
							if(!empty($media) && array_key_exists($type['url'], $media['error']) && array_key_exists($text['id'], $media['error'][$type['url']]) && $media['error'][$type['url']][$text['id']] != UPLOAD_ERR_NO_FILE)
							{
								$medium = array(
									'name'		=> $media['name'][$type['url']][$text['id']],
									'tmp_name'	=> $media['tmp_name'][$type['url']][$text['id']],
									'type'		=> $media['type'][$type['url']][$text['id']],
									'size'		=> $media['size'][$type['url']][$text['id']],
									'error'		=> $media['error'][$type['url']][$text['id']]
								);

								// Check error
								if($medium['error'] !== UPLOAD_ERR_OK) {
									$validation = $this->Validation->addValidationResult($validation, 'media', 'error', $medium);
								}
								
								// Check mimetype
								$mediaMimetype = null;
								$medium['mimetype'] = \hhu\z\Utils::getMimetype($medium['tmp_name'], $medium['type']);
								foreach($mimetypes as &$mimetype) {
									if($mimetype['mimetype'] == $medium['mimetype']) {
										$mediaMimetype = $mimetype;
										break;
									}
								}
								if(is_null($mediaMimetype)) {
									$validation = $this->Validation->addValidationResult($validation, 'media', 'mimetype', $medium['mimetype']);
								}
								elseif($medium['size'] > $mediaMimetype['size']) {
									$validation = $this->Validation->addValidationResult($validation, 'media', 'size', $mediaMimetype['size']);
								}
							}
							$validations[$type['url']][$text['id']] = $validation;

							// Upload medium
							if(!is_null($medium) && $validation === true)
							{
								$questsmediaId = $this->Media->createQuestMedia(
									$this->Auth->getUserId(),
									$seminary['id'],
									sprintf('questtext-%d-%d', $quest['id'], $text['id']),
									$medium['name'],
									$medium['type'],
									$medium['tmp_name']
								);
								if($questsmediaId > 0) {
									$this->Questtexts->setQuestmedia($text['id'], $questsmediaId);
								}
							}

							// Remove text from list
							//unset($texts[$type['url']][$text['id']]);
						}
					}

					// Add new text
					if(array_key_exists($type['url'], $texts) && array_key_exists('new', $texts[$type['url']]))
					{
						$text = $texts[$type['url']]['new'];
						if(!empty($text))
						{
							// Add text
							$questtextId = $this->Questtexts->addQuesttextToQuest(
								$this->Auth->getUserId(),
								$quest['id'],
								$type['url'],
								$text
							);

							// Validate medium
							$medium = null;
							$validation = true;
							if(!empty($media) && array_key_exists($type['url'], $media['error']) && array_key_exists('new', $media['error'][$type['url']]) && $media['error'][$type['url']]['new'] != UPLOAD_ERR_NO_FILE)
							{
								$medium = array(
									'name'		=> $media['name'][$type['url']]['new'],
									'tmp_name'	=> $media['tmp_name'][$type['url']]['new'],
									'type'		=> $media['type'][$type['url']]['new'],
									'size'		=> $media['size'][$type['url']]['new'],
									'error'		=> $media['error'][$type['url']]['new']
								);

								// Check error
								if($medium['error'] !== UPLOAD_ERR_OK) {
									$validation = $this->Validation->addValidationResult($validation, 'media', 'error', $medium);
								}
								
								// Check mimetype
								$mediaMimetype = null;
								$medium['mimetype'] = \hhu\z\Utils::getMimetype($medium['tmp_name'], $medium['type']);
								foreach($mimetypes as &$mimetype) {
									if($mimetype['mimetype'] == $medium['mimetype']) {
										$mediaMimetype = $mimetype;
										break;
									}
								}
								if(is_null($mediaMimetype)) {
									$validation = $this->Validation->addValidationResult($validation, 'media', 'mimetype', $medium['mimetype']);
								}
								elseif($medium['size'] > $mediaMimetype['size']) {
									$validation = $this->Validation->addValidationResult($validation, 'media', 'size', $mediaMimetype['size']);
								}
							}
							$validations[$type['url']]['new'] = $validation;
							
							// Upload medium
							if(!is_null($medium) && $validation === true)
							{
								$questsmediaId = $this->Media->createQuestMedia(
									$this->Auth->getUserId(),
									$seminary['id'],
									sprintf('questtext-%d-%d', $quest['id'], $questtextId),
									$medium['name'],
									$medium['type'],
									$medium['tmp_name']
								);
								if($questsmediaId > 0) {
									$this->Questtexts->setQuestmedia($questtextId, $questsmediaId);
								}
							}
						}
					}

					// Reload texts
					$type['texts'] = $this->Questtexts->getQuesttextsOfQuest($quest['id'], $type['url']);
					foreach($type['texts'] as &$questtext)
					{
						if(!is_null($questtext['questsmedia_id'])) {
							$questtext['media'] = $this->Media->getSeminaryMediaById($questtext['questsmedia_id']);
						}
					}
				}
			}


			// Set titile
			$this->addTitleLocalized('Edit Quest texts');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('quest', $quest);
			$this->set('questtexttypes', $questtextTypes);
			$this->set('mimetypes', $mimetypes);
			$this->set('validations', $validations);
		}



		/**
		 * Action: delete.
		 * 
		 * Delete a Quest of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 * @param	string	$questgroupUrl		URL-Title of Questgroup
		 * @param	string	$questUrl		URL-Title of Quest
		 */
		public function delete($seminaryUrl, $questgroupUrl, $questUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			$questgroup['picture'] = null;
			if(!is_null($questgroup['questgroupspicture_id'])) {
				$questgroup['picture'] = $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']);
			}
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);

			// Check request method
			if($this->request->getRequestMethod() == 'POST')
			{
				// Check confirmation
				if(!is_null($this->request->getPostParam('delete')))
				{
					// Delete seminary
					$this->Quests->deleteQuest($quest['id']);
					
					// Redirect to Questgroup
					$this->redirect($this->linker->link(array('questgroups', 'questgroup', $seminary['url'], $questgroup['url'])));
				}
				
				// Redirect to entry
				$this->redirect($this->linker->link(array('seminary', $seminary['url']), 1));
			}


			// Set titile
			$this->addTitleLocalized('Delete Quest');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('quest', $quest);
		}
		
		
		/**
		 * Action: createmedia.
		 * TODO only temporary for easier data import.
		 * 
		 * Display a form for creating new Seminary media.
		 * 
		 * @param	string	$seminaryUrl	URL-title of Seminary
		 */
		public function createmedia($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Create media
			$mediaId = null;
			$error = null;
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('submit')))
			{
				$file = $_FILES['file'];
				$error = $file['error'];
				if(empty($error))
				{
					$mediaId = $this->Media->createQuestMedia(
						$this->Auth->getUserId(),
						$seminary['id'],
						$file['name'],
						$this->request->getPostParam('description'),
						$file['type'],
						$file['tmp_name']
					);
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('mediaid', $mediaId);
		}
		
		
		
		
		/**
		 * Render and handle the task of a Quest.
		 * 
		 * @param	string	$questtypeClassname	Name of the class for the Questtype of a Quest
		 * @param	array	$seminary		Seminary data
		 * @param	array	$questgroup		Questgroup data
		 * @param	array	$quest			Quest data
		 * @param	array	$character		Character data
		 * @return	string				Rendered output
		 */
		private function renderTask($questtypeClassname, $seminary, $questgroup, $quest, $character)
		{
			$task = null;
			try {
				// Generate request and response
				$request = clone $this->request;
				$response = $this->createQuesttypeResponse('quest', $seminary, $questgroup, $quest, $character);
				
				// Load Questtype Agent
				$questtypeAgent = $this->loadQuesttypeAgent($questtypeClassname, $request, $response);
				
				// Solve Quest
				if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('submit')))
				{
					// Get user answers
					$answers = $this->request->getPostParam('answers');
					
					// Save answers in database
					try {
						if(!$this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id'])) {
							$questtypeAgent->saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers);
						}
					
						// Match answers with correct ones
						$status = $questtypeAgent->matchAnswersofCharacter($seminary, $questgroup, $quest, $character, $answers);
						if($status === true)
						{
							// Mark Quest as solved
							$this->Quests->setQuestSolved($quest['id'], $character['id']);
							
							// Notify of XP-level change
							$newXPLevel = $this->Xplevels->getXPLevelById($character['xplevel_id']);
							if($newXPLevel['level'] > $character['xplevel']) {
								$this->Notification->addNotification(
									\hhu\z\controllers\components\NotificationComponent::TYPE_LEVELUP,
									$newXPLevel['level'],
									$this->linker->link(array('characters', 'character', $seminary['url'], $character['url']))
								);
							}
						
							// Redirect
							$this->redirect($this->linker->link(array(), 5, true, array('status'=>'solved'), false, 'task'));
						}
						elseif($status === false)
						{
							// Mark Quest as unsolved
							$this->Quests->setQuestUnsolved($quest['id'], $character['id']);
						
							// Redirect
							$this->redirect($this->linker->link(array(), 5, true, array('status'=>'unsolved'), false, 'task'));
						}
						else {
							// Mark Quest as submitted
							$this->Quests->setQuestSubmitted($quest['id'], $character['id']);
							
							// Send notification mail
							$this->sendSubmissionMail($seminary, $questgroup, $quest, $character);
						
							// Redirect
							$this->redirect($this->linker->link(array(), 5, true, null, false, 'task'));
						}
					}
					catch(\hhu\z\exceptions\SubmissionNotValidException $e) {
						$response->addParam($e);
					}
				}
				
				// Render Task
				$task = $this->runQuesttypeAgent($questtypeAgent, $request, $response);
			}
			catch(\nre\exceptions\ViewNotFoundException $e) {
				$task = $e->getMessage();
			}
			catch(\nre\exceptions\ActionNotFoundException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeModelNotValidException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeModelNotFoundException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeControllerNotValidException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeControllerNotFoundException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeAgentNotValidException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeAgentNotFoundException $e) {
				$task = $e->getMessage();
			}
			
			
			// Return rendered output
			return $task;
		}
		
		
		/**
		 * Render and handle a Character submission for a Quest.
		 * 
		 * @param	string	$questtypeClassname	Name of the class for the Questtype of a Quest
		 * @param	array	$seminary		Seminary data
		 * @param	array	$questgroup		Questgroup data
		 * @param	array	$quest			Quest data
		 * @param	array	$character		Character data
		 * @return	string				Rendered output
		 */
		private function renderTaskSubmission($questtypeClassname, $seminary, $questgroup, $quest, $character)
		{
			$task = null;
			try {
				// Generate request and response
				$request = clone $this->request;
				$response = $this->createQuesttypeResponse('submission', $seminary, $questgroup, $quest, $character);
				
				// Load Questtype Agent
				$questtypeAgent = $this->loadQuesttypeAgent($questtypeClassname, $request, $response);
				
				// Solve Quest
				if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('submit')))
				{
					// Set status
					if($this->request->getPostParam('submit') == _('solved'))
					{
						// Mark Quest as solved
						$this->Quests->setQuestSolved($quest['id'], $character['id']);
					}
					else
					{
						// Mark Quest as unsolved
						$this->Quests->setQuestUnsolved($quest['id'], $character['id']);
					}
					
					// Save additional data for Character answers
					$questtypeAgent->controller->saveDataForCharacterAnswers($seminary, $questgroup, $quest, $character, $this->request->getPostParam('characterdata'));
					
					// Send notification
					$this->sendSubmissionApprovedMail($character, $seminary, $questgroup, $quest);
					
					// Redirect
					$this->redirect($this->linker->link(array('submissions', $seminary['url'], $questgroup['url'], $quest['url']), 1));
				}
				
				// Render task submissions
				$task = $this->runQuesttypeAgent($questtypeAgent, $request, $response);
			}
			catch(\nre\exceptions\ViewNotFoundException $e) {
				$task = $e->getMessage();
			}
			catch(\nre\exceptions\ActionNotFoundException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeModelNotValidException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeModelNotFoundException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeControllerNotValidException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeControllerNotFoundException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeAgentNotValidException $e) {
				$task = $e->getMessage();
			}
			catch(\hhu\z\exceptions\QuesttypeAgentNotFoundException $e) {
				$task = $e->getMessage();
			}
			
			
			// Return rendered output
			return $task;
		}
		
		
		/**
		 * Create a response for the Questtype rendering.
		 * 
		 * @param	string		$action	Action to run
		 * @param	mixed		$param	Additional parameters to add to the response
		 * @return	Response		Generated response
		 */
		private function createQuesttypeResponse($action, $param1)
		{
			// Clone current response
			$response = clone $this->response;
			// Clear parameters
			$response->clearParams(1);
			
			// Add Action
			$response->addParams(
				null,
				$action
			);
			
			// Add additional parameters
			foreach(array_slice(func_get_args(), 1) as $param) {
				$response->addParam($param);
			}
			
			
			// Return response
			return $response;
		}
		
		
		/**
		 * Load and construct the QuesttypeAgent for a Questtype.
		 * 
		 * @param	string		$questtypeClassname	Name of the class for the Questtype of a Quest
		 * @param	Request		$request		Request
		 * @param	Response	$response		Response
		 * @return						QuesttypeAgent
		 */
		private function loadQuesttypeAgent($questtypeClassname, $request, $response)
		{
			// Load Agent
			\hhu\z\agents\QuesttypeAgent::load($questtypeClassname);
			
			
			// Construct and return Agent
			return \hhu\z\agents\QuesttypeAgent::factory($questtypeClassname, $request, $response);
		}
		
		
		/**
		 * Run and render the Agent for a QuesttypeAgent and return ist output.
		 * 
		 * @param	Agent		$questtypeAgent		QuesttypeAgent to run and render
		 * @param	Request		$request		Request
		 * @param	Response	$response		Response
		 * @return	string					Rendered output
		 */
		private function runQuesttypeAgent($questtypeAgent, $request, $response)
		{
			// Run Agent
			$questtypeAgent->run($request, $response);
			
			
			// Render and return output
			return $questtypeAgent->render();
		}
		
		
		/**
		 * Send mail for new Character submission.
		 * 
		 * @param	array	$seminary	Seminary which the Quest belongs to
		 * @param	array	$questgroup	Questgroup of Quest
		 * @param	array	$quest		Quest the answer has been submitted for
		 * @param	array	$character	Character that send the submission
		 */
		private function sendSubmissionMail($seminary, $questgroup, $quest, $character)
		{
			// Get system moderators
			$moderators = $this->Characters->getCharactersWithRole('moderator');
			
			// Send notification mail
			try {
				foreach($moderators as &$moderator)
				{
					$user = $this->Users->getUserById($moderator['user_id']);
					if($user['mailing']) {
						\hhu\z\Utils::sendMail(
							$user['email'],
							'charactersubmission',
							true,
							array(
								$user,
								$seminary,
								$questgroup,
								$quest,
								$character
							),
							$this->linker
						);
					}
				}
			}
			catch(\hhu\z\exceptions\MailingException $e) {
				$this->log($e->getMessage());
			}
		}
		
		
		/**
		 * Send mail for approval of a Character submission.
		 * 
		 * @param	array	$character	Character of submission that has been approved
		 * @param	array	$seminary	Seminary which the Quest belongs to
		 * @param	array	$questgroup	Questgroup of Quest
		 * @param	array	$quest		Quest the submission has been approved for
		 */
		private function sendSubmissionApprovedMail($character, $seminary, $questgroup, $quest)
		{
			// Get user
			$user = $this->Users->getUserById($character['user_id']);
			if(!$user['mailing']) {
				return;
			}
			
			// Send notification mail
			try {
				\hhu\z\Utils::sendMail(
					$user['email'],
					'charactersubmissionapproved',
					true,
					array(
						$user,
						$seminary,
						$questgroup,
						$quest
					),
					$this->linker
				);
			}
			catch(\hhu\z\exceptions\MailingException $e) {
				$this->log($e->getMessage());
			}
		}
		
	}

?>
