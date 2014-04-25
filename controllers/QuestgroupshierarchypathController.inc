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
	 * Controller of QuestgroupshierarchypathAgent to display the
	 * Questgroups hierarchy path.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgroupshierarchypathController extends \hhu\z\Controller
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'questgroups', 'questgroupshierarchy', 'quests', 'questtexts');
		
		
		
		
		/**
		 * Action: index.
		 *
		 * Calculate and show the hierarchy path of a Questgroup.
		 * 
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 * @param	string	$questgroupUrl	URL-Title of a Questgroup
		 * @param	boolean	$showGroup	Show the current group itself
		 */
		public function index($seminaryUrl, $questgroupUrl, $showGroup=false)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			$questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			
			// Get parent Questgrouphierarchy
			$currentQuestgroup = $questgroup;
			$parentQuestgroupshierarchy = array();
			if($showGroup) {
				array_unshift($parentQuestgroupshierarchy, $currentQuestgroup);	
			}
			if(is_null($questgroup['hierarchy']))
			{
				// Get related Questgroup
				$questtext = $this->Questtexts->getRelatedQuesttextForQuestgroup($currentQuestgroup['id']);
				$quest = $this->Quests->getQuestById($questtext['quest_id']);
				$currentQuestgroup = $this->Questgroups->getQuestgroupById($quest['questgroup_id']);
				$currentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($currentQuestgroup['id']);
				$quest['questgroup'] = $currentQuestgroup;
				
				// Use Hierarchy name for optional Questgroup
				if(!empty($parentQuestgroupshierarchy)) {
					$parentQuestgroupshierarchy[0]['hierarchy'] = $currentQuestgroup['hierarchy'];
					unset($parentQuestgroupshierarchy[0]['hierarchy']['questgroup_pos']);
				}
				
				array_unshift($parentQuestgroupshierarchy, $quest);
				array_unshift($parentQuestgroupshierarchy, $currentQuestgroup);
			}
			while(!empty($currentQuestgroup['hierarchy']) && !is_null($currentQuestgroup['hierarchy']['parent_questgroup_id']))
			{
				$currentQuestgroup = $this->Questgroups->GetQuestgroupById($currentQuestgroup['hierarchy']['parent_questgroup_id']);
				$currentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($currentQuestgroup['id']);
				array_unshift($parentQuestgroupshierarchy, $currentQuestgroup);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('parentquestgroupshierarchy', $parentQuestgroupshierarchy);
		}
		
	}

?>
