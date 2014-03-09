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
			'quest' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'quest' => array('admin', 'moderator', 'user')
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
				
				// Task
				$task = $this->runAndRenderTask($questtype['classname']);
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
		 * Load, construct, run and render the Agent for the given
		 * classname of a Questtype and return ist output.
		 * 
		 * @param	string	$questtypeClassname	Classname of Questtype to run and render
		 * @return	string				Rendered output of Questtype-Agent
		 */
		private function runAndRenderTask($questtypeClassname)
		{
			$task = null;
			$questtypeAgent = null;
			try {
				// Load Agent
				\hhu\z\QuesttypeAgent::load($questtypeClassname);
				// Construct Agent
				$questtypeAgent = \hhu\z\QuesttypeAgent::factory($questtypeClassname, $this->request, $this->response);
				
				// Generate response
				$response = clone $this->response;
				$response->clearParams(1);
				$response->addParams(
					null,
					\nre\configs\CoreConfig::$defaults['action']
				);
				// Run Agent
				$questtypeAgent->run($this->request, $response);
			
				// Render output
				$task = $questtypeAgent->render();
			
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
		
	}

?>
