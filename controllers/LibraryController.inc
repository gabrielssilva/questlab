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
			'index' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index' => array('admin', 'moderator', 'user')
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
					// Get Questgroup
					$quest['questgroup'] = $this->Questgroups->getQuestgroupById($quest['questgroup_id']);
					
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
		
	}

?>
