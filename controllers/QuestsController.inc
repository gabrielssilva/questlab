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
	class QuestsController extends \hhu\z\controllers\SeminaryRoleController
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
			'quest' => array('admin', 'moderator', 'user'),
			'submissions' => array('admin', 'moderator'),
			'submission' => array('admin', 'moderator')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'quest' => array('admin', 'moderator', 'user'),
			'submissions' => array('admin', 'moderator'),
			'submission' => array('admin', 'moderator')
		);
		
		
		
		
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
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);
			
			// Get Character
			$character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
			
			// Check permissions
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
				if(count($previousQuests) > 0)
				{
					$solved = false;
					foreach($previousQuests as &$previousQuest)
					{
						if($this->Quests->hasCharacterSolvedQuest($previousQuest['id'], $character['id'])) {
							$solved = true;
							break;
						}
					}
					if(!$solved) {
						throw new \nre\exceptions\AccessDeniedException();
					}
				}
			}
			
			// Get (related) Questtext (for Sidequests)
			$relatedQuesttext = null;
			if(!$quest['is_mainquest'])
			{
				$relatedQuesttext = $this->Questtexts->getQuesttextForSidequest($quest['id']);
				if(!empty($relatedQuesttext)) {
					$relatedQuesttext['quest'] = $this->Quests->getQuestById($relatedQuesttext['quest_id']);
				}
			}
			
			// Get Questtext
			$questtext = null;
			if(is_null($questtexttypeUrl)) {
				$questtexttypeUrl = 'Prolog';
			}
			$questtexttypes = $this->Questtexts->getQuesttexttypes();
			$questtexttypes = array_map(function($t) { return $t['url']; }, $questtexttypes);
			$questtextCount = $this->Questtexts->getQuesttextsCountForQuest($quest['id'], $questtexttypeUrl);
			if($questtextCount > 0 && in_array($questtexttypeUrl, $questtexttypes))
			{
				$questtextPos = max(intval($questtextPos), 1);
				$questtext = $this->Questtexts->getQuesttextByUrl($quest['id'], $questtexttypeUrl, $questtextPos);
				$questtext['count'] = $questtextCount;
				$questtext['sidequests'] = $this->Quests->getSidequestsForQuesttext($questtext['id']);
			}
			
			// Quest status
			$questStatus = $this->request->getGetParam('status');
			$questStatusText = null;
			if(!is_null($questStatus))
			{
				switch($questStatus)
				{
					case 'solved':
						$questStatusText = $quest['right_text'];
					break;
					case 'unsolved':
						$questStatusText = $quest['wrong_text'];
					break;
				}
			}
			
			// Media
			$questmedia = null;
			if(!is_null($questtext) && array_key_exists('questmedia_id', $questtext) && !empty($questtext['questsmedia_id'])) {
				$questmedia = $this->Media->getMediaById($questtext['questsmedia_id']);
			}
			elseif(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getMediaById($quest['questsmedia_id']);
			}
			
			// Task
			$task = null;
			if($questtexttypeUrl == 'Prolog')
			{
				// Questtype
				$questtype = $this->Questtypes->getQuesttypeById($quest['questtype_id']);
				
				// Render task
				$task = $this->renderTask($questtype['classname'], $seminary, $questgroup, $quest, $character);
			}
			
			// Next Quest/Questgroup
			$nextQuests = null;
			$nextQuestgroup = null;
			if($questtexttypeUrl == 'Epilog')
			{
				if($quest['is_mainquest'])
				{
					// Next Quest
					$nextQuests = $this->Quests->getNextQuests($quest['id']);
				
					// Next Questgroup
					if(empty($nextQuests))
					{
						$nextQuestgroup = $this->Questgroups->getNextQuestgroup($questgroup['id']);
						$nextQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyById($nextQuestgroup['questgroupshierarchy_id']);
					}
				}
				else {
					// Related (Main-) Quest
					$nextQuest = $relatedQuesttext['quest'];
					$nextQuest['questgroup_url'] = $questgroup['url'];
					$nextQuests = array($nextQuest);
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('questtext', $questtext);
			$this->set('quest', $quest);
			$this->set('queststatus', $questStatus);
			$this->set('queststatustext', $questStatusText);
			$this->set('relatedquesttext', $relatedQuesttext);
			$this->set('nextquests', $nextQuests);
			$this->set('nextquestgroup', $nextQuestgroup);
			$this->set('task', $task);
			$this->set('media', $questmedia);
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
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);
			
			// Get (related) Questtext (for Sidequests)
			$relatedQuesttext = null;
			if(!$quest['is_mainquest'])
			{
				$relatedQuesttext = $this->Questtexts->getQuesttextForSidequest($quest['id']);
				if(!empty($relatedQuesttext)) {
					$relatedQuesttext['quest'] = $this->Quests->getQuestById($relatedQuesttext['quest_id']);
				}
			}
			
			// Media
			$questmedia = null;
			if(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getMediaById($quest['questsmedia_id']);
			}
			
			// Get unsolved Character submissions
			$unsolvedSubmissions = $this->Quests->getCharactersUnsolvedQuest($quest['id']);
			foreach($unsolvedSubmissions as &$submission) {
				$submission['character'] = $this->Characters->getCharacterById($submission['character_id']);
			}
			
			// Get solved Character submissions
			$solvedSubmissions = $this->Quests->getCharactersSolvedQuest($quest['id']);
			foreach($solvedSubmissions as &$submission) {
				$submission['character'] = $this->Characters->getCharacterById($submission['character_id']);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('quest', $quest);
			$this->set('relatedquesttext', $relatedQuesttext);
			$this->set('media', $questmedia);
			$this->set('unsolvedsubmissions', $unsolvedSubmissions);
			$this->set('solvedsubmissions', $solvedSubmissions);
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
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);
			
			// Character
			$character = $this->Characters->getCharacterByUrl($seminary['id'], $characterUrl);
			
			// Media
			$questmedia = null;
			if(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getMediaById($quest['questsmedia_id']);
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
				$response = $this->createQuesttypeResponse('quest', $quest['id'], $character['id']);
				
				// Load Questtype Agent
				$questtypeAgent = $this->loadQuesttypeAgent($questtypeClassname, $request, $response);
				
				// Solve Quest
				if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('submit')))
				{
					// Get user answers
					$answers = $this->request->getPostParam('answers');
					
					// Store answers in session
					$_SESSION['answers'][$quest['id']] = $answers;
					
					// Save answers in database
					$questtypeAgent->saveAnswersOfCharacter($quest['id'], $character['id'], $answers);
					
					// Match answers with correct ones
					$status = $questtypeAgent->matchAnswersofCharacter($quest['id'], $character['id'], $answers);
					if($status === true)
					{
						// Mark Quest as solved
						$this->Quests->setQuestSolved($quest['id'], $character['id']);
						
						// Redirect
						$this->redirect($this->linker->link('Epilog', 5, true, array('status'=>'solved')));
					}
					elseif($status === false)
					{
						// Mark Quest as unsolved
						$this->Quests->setQuestUnsolved($quest['id'], $character['id']);
						
						// Redirect
						$this->redirect($this->linker->link('Prolog', 5, true, array('status'=>'unsolved')));
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
				$response = $this->createQuesttypeResponse('submission', $quest['id'], $character['id']);
				
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
