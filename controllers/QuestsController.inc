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
		public $models = array('seminaries', 'questgroups', 'quests', 'questtexts');
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
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 * @param	string	$questgroupUrl	URL-Title of a Questgroup
		 * @param	string	$questUrl	URL-Title of a Quest
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
			$questtexttypes = $this->Questtexts->getQuesttexttypes();
			$questtexttypes = array_map(function($t) { return $t['url']; }, $questtexttypes);
			if(is_null($questtexttypeUrl)) {
				$questtexttypeUrl = 'Prolog';
			}
			if(in_array($questtexttypeUrl, $questtexttypes))
			{
				$questtextPos = max(intval($questtextPos), 1);
				$questtext = $this->Questtexts->getQuesttextByUrl($quest['id'], $questtexttypeUrl, $questtextPos);
			}
			
			// Show task only for Prologes
			$showTask = false;
			if($questtext['type'] == 'Prolog') {
				$showTask = true;
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('questtext', $questtext);
			$this->set('quest', $quest);
			$this->set('showtask', $showTask);
		}
		
	}

?>
