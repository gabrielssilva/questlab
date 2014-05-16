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
	 * Controller of the LibraryAgent to list Quest topics.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class LibraryController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('questtopics', 'seminaries', 'quests', 'questgroups');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index'		=> array('admin', 'moderator', 'user'),
			'topic'		=> array('admin', 'moderator', 'user'),
			'managetopic'	=> array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index' 	=> array('admin', 'moderator', 'user', 'guest'),
			'topic'		=> array('admin', 'moderator', 'user', 'guest'),
			'managetopic'	=> array('admin', 'moderator')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * List Questtopics of a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 */
		public function index($seminaryUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character
			$character = SeminaryController::$character;
			
			// Get Quest topics
			$totalQuestcount = 0;
			$totalCharacterQuestcount = 0;
			$questtopics = $this->Questtopics->getQuesttopicsForSeminary($seminary['id']);
			foreach($questtopics as &$questtopic)
			{
				// Get Quest count
				$questtopic['questcount'] = $this->Questtopics->getQuestCountForQuesttopic($questtopic['id']);
				$totalQuestcount += $questtopic['questcount'];
				
				// Get Character progress
				$questtopic['characterQuestcount'] = $this->Questtopics->getCharacterQuestCountForQuesttopic($questtopic['id'], $character['id']);
				$totalCharacterQuestcount += $questtopic['characterQuestcount'];
			}
			
			
			// Set title
			$this->addTitleLocalized('Library');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('totalQuestcount', $totalQuestcount);
			$this->set('totalCharacterQuestcount', $totalCharacterQuestcount);
			$this->set('questtopics', $questtopics);
		}
		
		
		/**
		 * Action: topic.
		 * 
		 * Show a Questtopic and its Quests with Questsubtopics.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$eminaryUrl	URL-Title of Seminary
		 * @param	string	$questtopicUrl	URL-Title of Questtopic
		 */
		public function topic($seminaryUrl, $questtopicUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Character
			$character = SeminaryController::$character;
			
			// Get Questtopic
			$questtopic = $this->Questtopics->getQuesttopicByUrl($seminary['id'], $questtopicUrl);
			$questtopic['questcount'] = $this->Questtopics->getQuestCountForQuesttopic($questtopic['id']);
			$questtopic['characterQuestcount'] = $this->Questtopics->getCharacterQuestCountForQuesttopic($questtopic['id'], $character['id']);
			
			// Get Quests
			$quests = array();
			foreach($this->Quests->getQuestsForQuesttopic($questtopic['id']) as $quest)
			{
				if($this->Quests->hasCharacterEnteredQuest($quest['id'], $character['id']) || count(array_intersect(array('admin', 'moderator'), self::$character['characterroles'])) > 0)
				{
					// Get Subtopics
					$quest['subtopics'] = $this->Questtopics->getQuestsubtopicsForQuest($quest['id']);
					
					$quests[] = $quest;
				}
			}
			
			
			// Set title
			$this->addTitle($questtopic['title']);
			$this->addTitleLocalized('Library');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questtopic', $questtopic);
			$this->set('quests', $quests);
		}
		
		
		/**
		 * Action: managetopic.
		 * 
		 * Manage a Questtopic and its Quests with Questsubtopics.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$eminaryUrl	URL-Title of Seminary
		 * @param	string	$questtopicUrl	URL-Title of Questtopic
		 */
		public function managetopic($seminaryUrl, $questtopicUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Questtopic
			$questtopic = $this->Questtopics->getQuesttopicByUrl($seminary['id'], $questtopicUrl);
			
			// Get Questsubtopics
			$questsubtopics = $this->Questtopics->getSubtopicsForQuesttopic($questtopic['id']);
			
			// Set Questsubtopics for Quests
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('questsubtopics')))
			{
				$selectedSubtopics = $this->request->getPostParam('questsubtopics');
				
				// Set subtopics of Quests
				$quests = $this->Quests->getQuestsForQuesttopic($questtopic['id']);
				foreach($quests as &$quest)
				{
					$subtopics = (array_key_exists($quest['id'], $selectedSubtopics)) ? $selectedSubtopics[$quest['id']] : array();
					$this->Questtopics->setQuestsubtopicsForQuest($quest['id'], array_keys($subtopics));
				}
				
				// Add Quest
				$addQuestId = $this->request->getPostParam('addquest');
				if(!empty($addQuestId))
				{
					$subtopics = (array_key_exists('addquest', $selectedSubtopics)) ? $selectedSubtopics['addquest'] : array();
					if(!empty($subtopics)) {
						$this->Questtopics->setQuestsubtopicsForQuest($addQuestId, array_keys($subtopics));
					}
				}
				
				// Redirect
				$this->redirect($this->linker->link(array('topic', $seminary['url'], $questtopic['url']), 1));
			}
			
			// Get Quests
			$quests = $this->Quests->getQuestsForQuesttopic($questtopic['id']);
			foreach($quests as &$quest)
			{
				// Get Subtopics
				$quest['subtopics'] = $this->Questtopics->getQuestsubtopicsForQuest($quest['id']);
				$quest['subtopics'] = array_map(function($t) { return $t['id']; }, $quest['subtopics']);
			}
			
			// Get all Quests
			$allQuests = $this->Quests->getQuestsForSeminary($seminary['id']);
			
			
			// Set title
			$this->addTitle($questtopic['title']);
			$this->addTitleLocalized('Library');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questtopic', $questtopic);
			$this->set('questsubtopics', $questsubtopics);
			$this->set('quests', $quests);
			$this->set('allQuests', $allQuests);
		}
		
	}

?>
