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
		public $models = array('seminaries', 'questgroups', 'questgroupshierarchy');
		
		
		
		
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
			
			// Get parent Questgrouphierarchy
			$parentQuestgroupshierarchy = array();
			$currentQuestgroup = $questgroup;
			if($showGroup) {
				$currentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyById($currentQuestgroup['questgroupshierarchy_id']);
				array_unshift($parentQuestgroupshierarchy, $currentQuestgroup);
			}
			while(!is_null($currentQuestgroup['parent_questgroup_id']))
			{
				// Get Questgroup
				$currentQuestgroup = $this->Questgroups->GetQuestgroupById($currentQuestgroup['parent_questgroup_id']);
				
				// Get Questgroupshierarchy
				$currentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyById($currentQuestgroup['questgroupshierarchy_id']);
				
				array_unshift($parentQuestgroupshierarchy, $currentQuestgroup);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('parentquestgroupshierarchy', $parentQuestgroupshierarchy);
		}
		
	}

?>
