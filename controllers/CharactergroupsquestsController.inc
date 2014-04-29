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
	 * Controller of the CharactergroupsquestsAgent to display Character
	 * groups Quests.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactergroupsquestsController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'charactergroups', 'charactergroupsquests', 'media', 'questgroups');
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
		 * Show a Character groups Quest for a Character groups-group
		 * of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$groupsgroupUrl		URL-Title of a Character groups-group
		 * @param	string	$questUrl		URL-Title of a Character groups Quest
		 */
		public function quest($seminaryUrl, $groupsgroupUrl, $questUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character groups-group
			$groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);
			
			// Get Character groups-group Quests
			$quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupById($quest['questgroups_id']);
			$questgroup['entered'] = $this->Questgroups->hasCharacterEnteredQuestgroup($questgroup['id'], self::$character['id']);
			
			// Get Character groups-groups
			$groups = $this->Charactergroupsquests->getGroupsForQuest($quest['id']);
			
			// Media
			$questmedia = null;
			if(!is_null($quest['questsmedia_id'])) {
				$questmedia = $this->Media->getSeminaryMediaById($quest['questsmedia_id']);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroup', $groupsgroup);
			$this->set('quest', $quest);
			$this->set('questgroup', $questgroup);
			$this->set('groups', $groups);
			$this->set('media', $questmedia);
		}
		
		
		/**
		 * Action: create.
		 * 
		 * Create a new Character groups Quest for a Character
		 * groups-group of a Seminary.
		 * 
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$groupsgroupUrl		URL-Title of a Character groups-group
		 */
		public function create($seminaryUrl, $groupsgroupUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character groups-group
			$groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);
			
			// Get Questgroups
			$questgroups = $this->Questgroups->getQuestgroupsForSeminary($seminary['id']);
			
			// Values
			$title = '';
			$xps = 0;
			$description = '';
			$rules = '';
			$wonText = '';
			$lostText = '';
			$fields = array('title', 'xps');
			$validation = array();
			
			// Create a new Character groups Quest
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$title = $this->request->getPostParam('title');
				if($this->Charactergroupsquests->characterGroupsQuestTitleExists($title)) {
					$validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
				}
				$xps = $this->request->getPostParam('xps');
				$description = $this->request->getPostParam('description');
				$rules = $this->request->getPostParam('rules');
				$wonText = $this->request->getPostParam('wonText');
				$lostText = $this->request->getPostParam('lostText');
				
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
				
				// Create groups Quest
				if($validation === true)
				{
					$questId = $this->Charactergroupsquests->createQuest(
						$this->Auth->getUserId(),
						$groupsgroup['id'],						
						$questgroups[$questgroupIndex]['id'],
						$title,
						$description,
						$xps,
						$rules,
						$wonText,
						$lostText
					);
					
					// Redirect to Quest page
					$quest = $this->Charactergroupsquests->getQuestById($questId);
					$this->redirect($this->linker->link(array('quest', $seminary['url'], $groupsgroup['url'], $quest['url']), 1));
				}
			}
			
			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroup', $groupsgroup);
			$this->set('questgroups', $questgroups);
			$this->set('title', $title);
			$this->set('xps', $xps);
			$this->set('description', $description);
			$this->set('rules', $rules);
			$this->set('wonText', $wonText);
			$this->set('lostText', $lostText);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}
		
		
		/**
		 * Action: edit.
		 * 
		 * Edit a Character groups Quest of a Character groups-group
		 * of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$groupsgroupUrl		URL-Title of a Character groups-group
		 * @param	string	$questUrl		URL-Title of a Character groups Quest
		 */
		public function edit($seminaryUrl, $groupsgroupUrl, $questUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character groups-group
			$groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);
			
			// Get Character groups-group Quests
			$quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);
			
			// Get Questgroups
			$questgroups = $this->Questgroups->getQuestgroupsForSeminary($seminary['id']);
			foreach($questgroups as $index => &$questgroup) {
				$questgroup['selected'] = ($questgroup['id'] == $quest['questgroups_id']);
			}
			
			// Values
			$title = $quest['title'];
			$xps = $quest['xps'];
			$description = $quest['description'];
			$rules = $quest['rules'];
			$wonText = $quest['won_text'];
			$lostText = $quest['lost_text'];
			$fields = array('title', 'xps');
			$validation = array();
			
			// Edit Character group
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('edit')))
			{
				// Get params and validate them
				$validation = $this->Validation->validateParams($this->request->getPostParams(), $fields);
				$title = $this->request->getPostParam('title');
				if($this->Charactergroupsquests->characterGroupsQuestTitleExists($title, $quest['id'])) {
					$validation = $this->Validation->addValidationResult($validation, 'title', 'exist', true);
				}
				$xps = $this->request->getPostParam('xps');
				$description = $this->request->getPostParam('description');
				$rules = $this->request->getPostParam('rules');
				$wonText = $this->request->getPostParam('wonText');
				$lostText = $this->request->getPostParam('lostText');
				
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
				
				// Edit groups Quest
				if($validation === true)
				{
					$this->Charactergroupsquests->editQuest(
						$quest['id'],
						$groupsgroup['id'],						
						$questgroups[$questgroupIndex]['id'],
						$title,
						$description,
						$xps,
						$rules,
						$wonText,
						$lostText
					);
					
					// Redirect to Quest page
					$quest = $this->Charactergroupsquests->getQuestById($quest['id']);
					$this->redirect($this->linker->link(array('quest', $seminary['url'], $groupsgroup['url'], $quest['url']), 1));
				}
			}
			
			// Get validation settings
			$validationSettings = array();
			foreach($fields as &$field) {
				$validationSettings[$field] = \nre\configs\AppConfig::$validation[$field];
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroup', $groupsgroup);
			$this->set('quest', $quest);
			$this->set('questgroups', $questgroups);
			$this->set('title', $title);
			$this->set('xps', $xps);
			$this->set('description', $description);
			$this->set('rules', $rules);
			$this->set('wonText', $wonText);
			$this->set('lostText', $lostText);
			$this->set('validation', $validation);
			$this->set('validationSettings', $validationSettings);
		}
		
		
		/**
		 * Action: delete.
		 * 
		 * Delete a Character groups Quest of a Character groups-group
		 * of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$groupsgroupUrl		URL-Title of a Character groups-group
		 * @param	string	$questUrl		URL-Title of a Character groups Quest
		 */
		public function delete($seminaryUrl, $groupsgroupUrl, $questUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character groups-group
			$groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);
			
			// Get Character groups-group Quests
			$quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);
			
			// Check request method
			if($this->request->getRequestMethod() == 'POST')
			{
				// Check confirmation
				if(!is_null($this->request->getPostParam('delete')))
				{
					// Delete seminary
					$this->Charactergroupsquests->deleteQuest($quest['id']);
					
					// Redirect to overview
					$this->redirect($this->linker->link(array('charactergroups', 'groupsgroup', $seminary['url'], $groupsgroup['url'])));
				}
				
				// Redirect to entry
				$this->redirect($this->linker->link(array('quest', $seminary['url'], $groupsgroup['url'], $quest['url']), 1));
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('groupsgroup', $groupsgroup);
			$this->set('quest', $quest);
		}
		
	}

?>
