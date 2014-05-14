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
	 * Controller of the QuestgroupsAgent to display Questgroups.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgroupsController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'questgroupshierarchy', 'questgroups', 'quests', 'questtexts', 'media');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'questgroup'	=> array('admin', 'moderator', 'user'),
			'create'	=> array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'questgroup'	=> array('admin', 'moderator', 'user'),
			'create'	=> array('admin', 'moderator')
		);
		
		
		
		
		/**
		 * Action: questgroup.
		 * 
		 * Display a Questgroup and its data.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 * @param	string	$questgroupUrl	URL-Title of a Questgroup
		 */
		public function questgroup($seminaryUrl, $questgroupUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			
			// Get Questgrouphierarchy
			$questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			
			// Get Character
			$character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
			
			// Check permission
			if(count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) == 0)
			{
				$previousQuestgroup = $this->Questgroups->getPreviousQuestgroup($questgroup['id']);
				if(!is_null($previousQuestgroup)) {
					if(!$this->Questgroups->hasCharacterSolvedQuestgroup($previousQuestgroup['id'], $character['id'])) {
						throw new \nre\exceptions\AccessDeniedException();
					}
				}
			}
			
			// Set status “entered”
			$this->Questgroups->setQuestgroupEntered($questgroup['id'], $character['id']);
			
			// Get child Questgroupshierarchy
			$childQuestgroupshierarchy = null;
			if(!empty($questgroup['hierarchy']))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroup['hierarchy']['id']);
				foreach($childQuestgroupshierarchy as &$hierarchy)
				{
					// Get Questgroups
					$hierarchy['questgroups'] = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id'], $questgroup['id']);
				
					// Get additional data
					foreach($hierarchy['questgroups'] as $i => &$group)
					{
						$group['solved'] = $this->Questgroups->hasCharacterSolvedQuestgroup($group['id'], $character['id']);
						
						// Check permission of Questgroups
						if($i >= 1 && count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) == 0)
						{
							if(!$hierarchy['questgroups'][$i-1]['solved'])
							{
								$hierarchy['questgroups'] = array_slice($hierarchy['questgroups'], 0, $i);
								break;
							}
						}
						
						// Get cumulated data
						$data = $this->Questgroups->getCumulatedDataForQuestgroup($group['id'], $character['id']);
						$group['xps'] = $data['xps'];
						$group['character_xps'] = $data['character_xps'];
						
						// Attach related Questgroups
						$group['relatedQuestgroups'] = array();
						$relatedQuestgroups = $this->Questgroups->getRelatedQuestsgroupsOfQuestgroup($group['id']);
						foreach($relatedQuestgroups as &$relatedQuestgroup) {
							if($this->Questgroups->hasCharacterEnteredQuestgroup($relatedQuestgroup['id'], $character['id'])) {
								$group['relatedQuestgroups'][] = $this->Questgroups->getQuestgroupById($relatedQuestgroup['id']);
							}
						}
					}
				}
			}
			
			// Get texts
			$questgroupTexts = $this->Questgroups->getQuestgroupTexts($questgroup['id']);
			
			// Get Character XPs
			$questgroup['character_xps'] = $this->Questgroups->getAchievedXPsForQuestgroup($questgroup['id'], $character['id']);
			
			// Media
			$picture = null;
			if(!is_null($questgroup['questgroupspicture_id']))
			{
				$picture = $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']);
			}
					
			
			// Get Quests
			$quests = array();
			if(count($childQuestgroupshierarchy) == 0)
			{
				$currentQuest = null;
				do {
					// Get next Quest
					if(is_null($currentQuest)) {
						$currentQuest = $this->Quests->getFirstQuestOfQuestgroup($questgroup['id']);
					}
					else {
						$nextQuests = $this->Quests->getNextQuests($currentQuest['id']);
						$currentQuest = null;
						foreach($nextQuests as &$nextQuest) {
							if($this->Quests->hasCharacterEnteredQuest($nextQuest['id'], $character['id'])) {
								$currentQuest = $nextQuest;
								break;
							}
						}
					}
					
					// Add additional data
					if(!is_null($currentQuest))
					{
						// Set status
						$currentQuest['solved'] = $this->Quests->hasCharacterSolvedQuest($currentQuest['id'], $character['id']);
						
						// Attach related Questgroups
						$currentQuest['relatedQuestgroups'] = array();
						$relatedQuestgroups = $this->Questgroups->getRelatedQuestsgroupsOfQuest($currentQuest['id']);
						foreach($relatedQuestgroups as &$relatedQuestgroup)
						{
							if($this->Questgroups->hasCharacterEnteredQuestgroup($relatedQuestgroup['id'], $character['id'])) {
								$currentQuest['relatedQuestgroups'][] = $this->Questgroups->getQuestgroupById($relatedQuestgroup['id']);
							}
						}
						
						// Add Quest to Quests
						$quests[] = $currentQuest;
					}
				}
				while(!is_null($currentQuest) && ($currentQuest['solved'] || count(array_intersect(array('admin','moderator'), SeminaryController::$character['characterroles'])) > 0));
			}
			
			
			// Set titile
			if(!is_null($questgroup['hierarchy'])) {
				$this->addTitle(sprintf('%s %d: %s', $questgroup['hierarchy']['title_singular'], $questgroup['hierarchy']['questgroup_pos'], $questgroup['title']));
			}
			else {
				$this->addTitle($questgroup['title']);
			}
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('childquestgroupshierarchy', $childQuestgroupshierarchy);
			$this->set('texts', $questgroupTexts);
			$this->set('picture', $picture);
			$this->set('quests', $quests);
		}
		
		
		/**
		 * Action: create.
		 * 
		 * Create a new Questgroup.
		 * 
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 */
		public function create($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Create Questgroup
			$validation = true;
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// TODO Validation
				$title = $this->request->getPostParam('title');
				
				// Create new Questgroup
				if($validation === true)
				{
					$questgroupId = $this->Questgroups->createQuestgroup(
						$this->Auth->getUserId(),
						$seminary['id'],
						$title
					);
					
					// Redirect
					$this->redirect($this->linker->link(array('seminaries', 'seminary', $seminary['url'])));
				}
			}
			
			
			// Set titile
			$this->addTitleLocalized('Create Questgroup');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
		}
		
	}

?>
