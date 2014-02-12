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
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$questgroupUrl		URL-Title of a Questgroup
		 * @param	string	$questUrl		URL-Title of a Quest
		 * @param	string	$questtexttypeUrl	URL-Title of a Questtexttype
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
			$questtexttypes = $this->Questtexts->getQuesttexttypes();
			$questtexttypes = array_map(function($t) { return $t['url']; }, $questtexttypes);
			if(is_null($questtexttypeUrl)) {
				$questtexttypeUrl = 'Prolog';
			}
			$questtextCount = $this->Questtexts->getQuesttextsCountForQuest($quest['id'], $questtexttypeUrl);
			if($questtextCount > 0)
			{
				if(in_array($questtexttypeUrl, $questtexttypes))
				{
					$questtextPos = max(intval($questtextPos), 1);
					$questtext = $this->Questtexts->getQuesttextByUrl($quest['id'], $questtexttypeUrl, $questtextPos);
					$questtext['count'] = $questtextCount;
					$questtext['sidequests'] = $this->Quests->getSidequestsForQuesttext($questtext['id']);
				}
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
		
		/**
		 * Action: sidequest.
		 * 
		 * Show a sidequest and its task.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of a Seminary
		 * @param	string	$questgroupUrl		URL-Title of a Questgroup
		 * @param	string	$questUrl		URL-Title of a Quest
		 * @param	string	$sidequestUrl		URL-Title of a Sidequest
		 * @param	string	$questtexttypeUrl	URL-Title of a Questtexttype
		 * @param	int	$questtextPos		Position of Questtext
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
			$questtexttypes = $this->Questtexts->getQuesttexttypes();
			$questtexttypes = array_map(function($t) { return $t['url']; }, $questtexttypes);
			if(is_null($sidequesttexttypeUrl)) {
				$sidequesttexttypeUrl = 'Prolog';
			}
			$sidequesttextCount = $this->Questtexts->getQuesttextsCountForSidequest($sidequest['id'], $sidequesttexttypeUrl);
			if($sidequesttextCount > 0)
			{
				if(in_array($sidequesttexttypeUrl, $questtexttypes))
				{
					$sidequesttextPos = max(intval($sidequesttextPos), 1);
					$sidequesttext = $this->Questtexts->getSidequesttextByUrl($sidequest['id'], $sidequesttexttypeUrl, $sidequesttextPos);
					$sidequesttext['count'] = $sidequesttextCount;
				}
			}
			
			// Show task only for Prologes
			$showTask = false;
			if($sidequesttext['type'] == 'Prolog') {
				$showTask = true;
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroup', $questgroup);
			$this->set('sidequesttext', $sidequesttext);
			$this->set('quest', $quest);
			$this->set('questtext', $questtext);
			$this->set('sidequest', $sidequest);
			$this->set('showtask', $showTask);
		}
		
	}

?>
