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
	class QuestgroupsController extends \hhu\z\controllers\SeminaryRoleController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'questgroupshierarchy', 'questgroups', 'quests');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'questgroup' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'questgroup' => array('admin', 'moderator', 'user')
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
			$questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyById($questgroup['questgroupshierarchy_id']);
			
			// Get child Questgroupshierarchy
			$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupshierarchy['id']);
			foreach($childQuestgroupshierarchy as &$hierarchy) {
				$hierarchy['questgroups'] = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id'], $questgroup['id']);
			}
			
			// Get texts
			$questgroupTexts = $this->Questgroups->getQuestgroupTexts($questgroup['id']);
			
			// Get Quests
			$quests = null;
			if(count($childQuestgroupshierarchy) == 0) {
				$quests = $this->Quests->getQuestsForQuestgroup($questgroup['id']);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('questgroupshierarchy', $questgroupshierarchy);
			$this->set('childquestgroupshierarchy', $childQuestgroupshierarchy);
			$this->set('texts', $questgroupTexts);
			$this->set('quests', $quests);
		}
		
	}

?>
