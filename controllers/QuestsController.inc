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
		public $models = array('seminaries', 'questgroups', 'quests', 'questtexts', 'media', 'questtypes');
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
			
			// Get Questtext
			$questtext = null;
			if(is_null($questtexttypeUrl)) {
				$questtexttypeUrl = 'Prolog';
			}
			// Quest solved
			if($questtexttypeUrl == 'solved')
			{
				$questtext = array(
					'type' => 'solved',
					'text' => $quest['right_text']
				);
			}
			// Quest unsolved
			elseif($questtexttypeUrl == 'unsolved')
			{
				$questtext = array(
					'type' => 'unsolved',
					'text' => $quest['wrong_text']
				);
			}
			// Text
			else
			{
				// Text type
				$questtexttypes = $this->Questtexts->getQuesttexttypes();
				$questtexttypes = array_map(function($t) { return $t['url']; }, $questtexttypes);
				// Text count
				$questtextCount = $this->Questtexts->getQuesttextsCountForQuest($quest['id'], $questtexttypeUrl);
				// Get text
				if($questtextCount > 0 && in_array($questtexttypeUrl, $questtexttypes))
				{
					$questtextPos = max(intval($questtextPos), 1);
					$questtext = $this->Questtexts->getQuesttextByUrl($quest['id'], $questtexttypeUrl, $questtextPos);
					$questtext['count'] = $questtextCount;
					$questtext['sidequests'] = $this->Quests->getSidequestsForQuesttext($questtext['id']);
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
			if($questtext['type'] == 'Prolog')
			{
				// Questtype
				$questtype = $this->Questtypes->getQuesttypeById($quest['questtype_id']);
				
				// Task
				$task = $this->runAndRenderTask($questtype['classname']);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('questtext', $questtext);
			$this->set('quest', $quest);
			$this->set('task', $task);
			$this->set('media', $questmedia);
		}
		
		
		/**
		 * Action: sidequest.
		 * 
		 * Show a sidequest and its task.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 * @param	string	$questgroupUrl		URL-Title of Questgroup
		 * @param	string	$questUrl		URL-Title of Quest
		 * @param	string	$sidequestUrl		URL-Title of Sidequest
		 * @param	string	$sidequesttexttypeUrl	URL-Title of Sidequesttexttype
		 * @param	int	$sidequesttextPos	Position of Sidequesttext
		 */
		public function sidequest($seminaryUrl, $questgroupUrl, $questUrl, $sidequestUrl, $sidequesttexttypeUrl=null, $sidequesttextPos=1)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $questUrl);
			
			// Get Sidequest
			$sidequest = $this->Quests->getSidequestByUrl($seminary['id'], $questgroup['id'], $quest['id'], $sidequestUrl);
			
			// Get Questtext
			$questtext = $this->Questtexts->getQuesttextForSidequest($sidequest['id']);
			
			// Get Sidequesttext
			$sidequesttext = null;
			if(is_null($sidequesttexttypeUrl)) {
				$sidequesttexttypeUrl = 'Prolog';
			}
			// Quest solved
			if($sidequesttexttypeUrl == 'solved')
			{
				$sidequesttext = array(
					'type' => 'solved',
					'text' => $quest['right_text']
				);
			}
			// Quest unsolved
			elseif($sidequesttexttypeUrl == 'unsolved')
			{
				$sidequesttext = array(
					'type' => 'unsolved',
					'text' => $quest['wrong_text']
				);
			}
			// Text
			else
			{
				// Text type
				$questtexttypes = $this->Questtexts->getQuesttexttypes();
				$questtexttypes = array_map(function($t) { return $t['url']; }, $questtexttypes);
				// Text count
				$sidequesttextCount = $this->Questtexts->getQuesttextsCountForSidequest($sidequest['id'], $sidequesttexttypeUrl);
				// Get text
				if($sidequesttextCount > 0 && in_array($sidequesttexttypeUrl, $questtexttypes))
				{
					if(in_array($sidequesttexttypeUrl, $questtexttypes))
					{
						$sidequesttextPos = max(intval($sidequesttextPos), 1);
						$sidequesttext = $this->Questtexts->getSidequesttextByUrl($sidequest['id'], $sidequesttexttypeUrl, $sidequesttextPos);
						$sidequesttext['count'] = $sidequesttextCount;
					}
				}
			}
			
			// Media
			$sidequestmedia = null;
			if(!is_null($sidequesttext) && !empty($sidequesttext['questsmedia_id'])) {
				$sidequestmedia = $this->Media->getMediaById($sidequesttext['questsmedia_id']);
			}
			elseif(!is_null($sidequest['questsmedia_id'])) {
				$sidequestmedia = $this->Media->getMediaById($sidequest['questsmedia_id']);
			}
			
			// Task
			$task = null;
			if($sidequesttext['type'] == 'Prolog')
			{
				// Questtype
				$questtype = $this->Questtypes->getQuesttypeById($sidequest['questtype_id']);
				
				// Task
				$task = $this->runAndRenderTask($questtype['classname']);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('sidequesttext', $sidequesttext);
			$this->set('quest', $quest);
			$this->set('sidequest', $sidequest);
			$this->set('task', $task);
			$this->set('media', $sidequestmedia);
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
