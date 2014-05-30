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
	 * Controller of the CharactertypesAgent to handle Charactertyes of a
	 * Seminary.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactertypesController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('validation');
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('charactertypes');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'manage' => array('admin', 'moderator', 'user')
		);
		
		
		
		
		/**
		 * Action: manage.
		 * 
		 * Manage Characters.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 */
		public function manage($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Check permissions
			if(
				(is_null(self::$character) && count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) == 0) ||
				(!is_null(self::$character) && count(array_intersect(array('admin', 'moderator'), self::$character['characterroles'])) == 0)
			) {
				throw new AccessDeniedException();
			}
			
			// Get Charactertypes
			$charactertypes = $this->Charactertypes->getCharacterTypesForSeminary($seminary['id']);
			
			// Values
			$charactertypesNames = array();
			foreach($charactertypes as &$charactertype) {
				$charactertypesNames[$charactertype['id']] = $charactertype['name'];
			}
			$deleteCharactertypes = null;
			$charactertypeName = '';
			$validations = array(
				'edit-charactertypes'	=> true,
				'create-charactertype'	=> true
			);
			
			// Edit
			$action = null;
			if($this->request->getRequestMethod() == 'POST')
			{
				// Edit and delete Charactertypes
				if(!is_null($this->request->getPostParam('edit-charactertypes')))
				{
					$action = 'edit-charactertypes';
					
					// Get params and validate them
					$charactertypesNames = $this->request->getPostParam('charactertypes');
					$deleteCharactertypes = $this->request->getPostParam('delete-charactertypes');
					foreach($charactertypes as &$charactertype)
					{
						if(!is_null($deleteCharactertypes) && array_key_exists($charactertype['id'], $deleteCharactertypes)) {
							continue;
						}
						
						$name = $charactertypesNames[$charactertype['id']];
						$charactertypeValidation = $this->Validation->validate($name, \nre\configs\AppConfig::$validation['charactertypename']);
						if($charactertypeValidation !== true)
						{
							if(!is_array($validations['edit-charactertypes'])) {
								$validations['edit-charactertypes'] = array();
							}
							if(!array_key_exists($charactertype['id'], $validations['edit-charactertypes']) || !is_array($validations['edit-charactertypes'][$charactertype['id']])) {
								$validations['edit-charactertypes'][$charactertype['id']] = array();
							}
							$validations['edit-charactertypes'][$charactertype['id']] = $this->Validation->addValidationResults($validations['edit-charactertypes'][$charactertype['id']], 'charactertypename', $charactertypeValidation);
						}
						if($this->Charactertypes->charactertypeNameExists($seminary['id'], $name, $charactertype['id']))
						{
							if(!is_array($validations['edit-charactertypes'])) {
								$validations['edit-charactertypes'] = array();
							}
							if(!array_key_exists($charactertype['id'], $validations['edit-charactertypes']) || !is_array($validations['edit-charactertypes'][$charactertype['id']])) {
								$validations['edit-charactertypes'][$charactertype['id']] = array();
							}
							$validations['edit-charactertypes'][$charactertype['id']] = $this->Validation->addValidationResult($validations['edit-charactertypes'][$charactertype['id']], 'charactertypename', 'exist', true);
						}
					}
					
					// Edit and delete
					if($validations['edit-charactertypes'] === true)
					{
						foreach($charactertypes as &$charactertype)
						{
							// Delete
							if(!is_null($deleteCharactertypes) && array_key_exists($charactertype['id'], $deleteCharactertypes)) {
								$this->Charactertypes->deleteCharactertype($charactertype['id']);
							}
							// Edit
							elseif(!is_null($charactertypesNames) && array_key_exists($charactertype['id'], $charactertypesNames))
							{
								$name = $charactertypesNames[$charactertype['id']];
								$this->Charactertypes->editCharactertype($charactertype['id'], $name);
							}
						}
						
						// Redirect
						//$this->redirect($this->linker->link(array('seminaries', 'index')));
						$this->redirect($this->linker->link(null, 3));
					}
				}
				
				// Create Charactertype
				if(!is_null($this->request->getPostParam('create-charactertype')))
				{
					$action = 'create-charactertype';
					
					// Get params and validate them
					$validations[$action] = $this->Validation->validateParams($this->request->getPostParams(), array('charactertypename'));
					$charactertypeName = $this->request->getPostParam('charactertypename');
					if($this->Charactertypes->charactertypeNameExists($seminary['id'], $charactertypeName)) {
						$validations[$action] = $this->Validation->addValidationResult($validations[$action], 'charactertypename', 'exist', true);
					}
					
					// Create
					if($validations[$action] === true)
					{
						$this->Charactertypes->createCharactertype(
							$this->Auth->getUserId(),
							$seminary['id'],
							$charactertypeName
						);
						$charactertypeName = '';
						
						// Redirect
						$this->redirect($this->linker->link(null, 3));
					}
				}
			}
			
			// Get validation settings
			$validationSettings = array(
				'charactertypename' => \nre\configs\AppConfig::$validation['charactertypename']
			);
			
			
			// Set titile
			$this->addTitleLocalized('Manage Charactertypes');
			$this->addTitle($seminary['title']);
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('charactertypesNames', $charactertypesNames);
			$this->set('deleteCharactertypes', $deleteCharactertypes);
			$this->set('charactertypeName', $charactertypeName);
			$this->set('action', $action);
			$this->set('validations', $validations);
			$this->set('validationSettings', $validationSettings);
		}
		
	}

?>
