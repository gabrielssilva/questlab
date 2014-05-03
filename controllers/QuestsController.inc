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
		public $models = array('seminaries', 'questgroups', 'quests', 'questtexts', 'media', 'questtypes', 'questgroupshierarchy');
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
			'create'	=> array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index'		=> array('admin', 'moderator', 'user'),
			'quest'		=> array('admin', 'moderator', 'user'),
			'submissions'	=> array('admin', 'moderator'),
			'submission'	=> array('admin', 'moderator'),
			'create'	=> array('admin', 'moderator')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * List all Quests for a Seminary.
		 * 
		 * @param	string	$seminaryUrl	URL-Title of Seminary
		 */
		public function index($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Prepare filters
			$filters = array(	
				'questgroups'	=> array(),
				'questtypes'	=> array()
			);
			
			// Get selected filters
			$selectedFilters = array(
				'questgroup'	=> "0",
				'questtype'	=> ""
			);
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('filters'))) {
				$selectedFilters = $this->request->getPostParam('filters');
			}
			
			// Get Quests
			$quests = array();
			foreach($this->Quests->getQuestsForSeminary($seminary['id']) as $quest)
			{
				// Get Questgroup
				$quest['questgroup'] = $this->Questgroups->getQuestgroupById($quest['questgroup_id']);
				if($selectedFilters['questgroup'] != "0" && $selectedFilters['questgroup'] != $quest['questgroup']['id']) {
					continue;
				}
				
				// Get Questtype
				$quest['questtype'] = $this->Questtypes->getQuesttypeById($quest['questtype_id']);
				if($selectedFilters['questtype'] != "" && $selectedFilters['questtype'] != $quest['questtype']['classname']) {
					continue;
				}
				
				// Add filter values
				$filters['questgroups'][$quest['questgroup']['id']] = $quest['questgroup'];
				$filters['questtypes'][$quest['questtype']['classname']] = $quest['questtype'];
				
				// Add open submissions count
				$quest['opensubmissionscount'] = count($this->Characters->getCharactersSubmittedQuest($quest['id']));
				
				$quests[] = $quest;
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('quests', $quests);
			$this->set('filters', $filters);
			$this->set('selectedFilters', $selectedFilters);
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
					// following Quests of ones has to be tried
					$solved = false;
					$tried = false;
					foreach($previousQuests as &$previousQuest)
					{
						// // Check previous Quest
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
									$tried = true;
									break;
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
			
			// Get (related) Questtext
			$relatedQuesttext = $this->Questtexts->getRelatedQuesttextForQuestgroup($questgroup['id']);
			if(!empty($relatedQuesttext)) {
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
		 */
		public function create($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Quest groups
			$questgroups = $this->Questgroups->getQuestgroupsForSeminary($seminary['id']);
			
			// Quest types
			$questtypes = $this->Questtypes->getQuesttypes();
			
			// Create Quest
			$validation = true;
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// TODO Validation
				$name = $this->request->getPostParam('name');
				$xps = $this->request->getPostParam('xps');
				$prolog = $this->request->getPostParam('prolog');
				$entrytext = $this->request->getPostParam('entrytext');
				$wrongtext = $this->request->getPostParam('wrongtext');
				$task = $this->request->getPostParam('task');
				
				// Validate Questgroup
				$questgroupIndex = null;
				foreach($questgroups as $index => &$questgroup)
				{
					$questgroup['selected'] = ($questgroup['url'] == $this->request->getPostParam('questgroup'));
					if($questgroup['selected']) {
						$questgroupIndex = $index;
					}
				}
				if(is_null($questgroupIndex)) {
					throw new \nre\exceptions\ParamsNotValidException($questgroup);
				}
				
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
				
				// Questmedia
				$questmedia = null;
				if(array_key_exists('questmedia', $_FILES) && !empty($_FILES['questmedia']) && $_FILES['questmedia']['error'] == 0) {
					$questmedia = $_FILES['questmedia'];
				}
				
				// Process Prolog
				if(!empty($prolog)) {
					$prolog = preg_split('/\s*(_|=){5,}\s*/', $prolog, -1, PREG_SPLIT_NO_EMPTY);
				}
				
				// Create new Quest
				if($validation === true)
				{
					$questId = $this->Quests->createQuest(
						$this->Auth->getUserId(),
						$name,
						$questgroups[$questgroupIndex]['id'],
						$questtypes[$questtypeIndex]['id'],
						$xps,
						$entrytext,
						$wrongtext,
						$task
					);
					
					// Create Questmedia
					if(!is_null($questmedia))
					{
						$questsmediaId = $this->Media->createQuestMedia(
							$this->Auth->getUserId(),
							$seminary['id'],
							$questmedia['name'],
							$name,
							$questmedia['type'],
							$questmedia['tmp_name']
						);
						if($questsmediaId > 0) {
							$this->Quests->setQuestmedia($questId, $questsmediaId);
						}
					}
					
					// Add Prolog-texts
					if(!empty($prolog)) {
						$this->Questtexts->addQuesttextsToQuest($this->Auth->getUserId(), $questId, 'Prolog', $prolog);
					}
					
					
					// Redirect
					$this->redirect($this->linker->link(array('quests', 'index', $seminary['url'])));
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroups', $questgroups);
			$this->set('questtypes', $questtypes);
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
							$newXPLevel = $this->Characters->getXPLevelOfCharacters($character['id']);
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
			\hhu\z\QuesttypeAgent::load($questtypeClassname);
			
			
			// Construct and return Agent
			return \hhu\z\QuesttypeAgent::factory($questtypeClassname, $request, $response);
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
		
	}

?>
