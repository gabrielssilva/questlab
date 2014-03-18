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
	 * Controller of the Agent to list registered seminaries.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class SeminariesController extends \hhu\z\controllers\SeminaryRoleController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'users', 'questgroupshierarchy', 'questgroups');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array('admin', 'moderator', 'user'),
			'seminary' => array('admin', 'moderator', 'user'),
			'create' => array('admin', 'moderator'),
			'edit' => array('admin', 'moderator', 'user'),
			'delete' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'seminary' => array('admin', 'moderator', 'user', 'guest'),
			'edit' => array('admin', 'moderator'),
			'delete' => array('admin', 'moderator')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * List registered seminaries.
		 */
		public function index()
		{
			// Get seminaries
			$seminaries = $this->Seminaries->getSeminaries();
			
			// Get additional data
			foreach($seminaries as &$seminary)
			{
				// Created user
				$seminary['creator'] = $this->Users->getUserById($seminary['created_user_id']);
			}
			
			
			// Pass data to view
			$this->set('seminaries', $seminaries);
		}
		
		
		/**
		 * Action: seminary.
		 * 
		 * Show a seminary and its details.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a seminary
		 */
		public function seminary($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Created user
			$seminary['creator'] = $this->Users->getUserById($seminary['created_user_id']);
			
			// Get Character
			$character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
			
			// Questgrouphierarchy and Questgroups
			$questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyForSeminary($seminary['id']);
			foreach($questgroupshierarchy as &$hierarchy)
			{
				// Get Questgroups
				$hierarchy['questgroups'] = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id']);
				
				// Get additional data
				for($i=0; $i<count($hierarchy['questgroups']); $i++)
				{
					// Get first Questgroup text
					$text = $this->Questgroups->getFirstQuestgroupText($hierarchy['questgroups'][$i]['id']);
					if(!empty($text))
					{
						$text = \hhu\z\Utils::shortenString($text['text'], 100, 120).' …';
						$hierarchy['questgroups'][$i]['text'] = $text;
					}
					
					// Check permission of Questgroups
					if($i >= 1) {
						$hierarchy['questgroups'][$i]['access'] =  $this->Questgroups->hasCharacterSolvedQuestgroup($hierarchy['questgroups'][$i-1]['id'], $character['id']);
					}
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('questgroupshierarchy', $questgroupshierarchy);
		}
		
		
		/**
		 * Action: create.
		 * 
		 * Create a new seminary.
		 */
		public function create()
		{
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// Create new seminary
				var_dump($this->Auth->getUserId());
				$seminaryId = $this->Seminaries->createSeminary(
					$this->request->getPostParam('title'),
					$this->Auth->getUserId()
				);
				
				// Redirect to seminary
				$user = $this->Seminaries->getSeminaryById($seminaryId);
				$this->redirect($this->linker->link(array($seminary['url']), 1));
			}
		}
		
		
		/**
		 * Action: edit.
		 * 
		 * Edit a seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a seminary
		 */
		public function edit($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Check request method
			if($this->request->getRequestMethod() == 'POST')
			{
				// Save changes
				if(!is_null($this->request->getPostParam('save')))
				{
					// Edit seminary
					$this->Seminaries->editSeminary(
						$seminary['id'],
						$this->request->getPostParam('title')
					);
					$seminary = $this->Seminaries->getSeminaryById($seminary['id']);
				}
				
				
				// Redirect to entry
				$this->redirect($this->linker->link(array($seminary['url']), 1));
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
		}
		
		
		/**
		 * Action: delete.
		 * 
		 * Delete a seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a seminary
		 */
		public function delete($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Check request method
			if($this->request->getRequestMethod() == 'POST')
			{
				// Check confirmation
				if(!is_null($this->request->getPostParam('delete')))
				{
					// Delete seminary
					$this->Seminaries->deleteSeminary($seminary['id']);
					
					// Redirect to overview
					$this->redirect($this->linker->link(null, 1));
				}
				
				// Redirect to entry
				$this->redirect($this->linker->link(array('seminary', $seminary['url']), 1));
			}
			
			
			// Show confirmation
			$this->set('seminary', $seminary);
		}
		
	}

?>
