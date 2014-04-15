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
	 * Controller of the Agent to list registered users and their data.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactersController extends \hhu\z\controllers\SeminaryRoleController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'characters', 'users', 'charactergroups', 'charactertypes', 'seminarycharacterfields', 'avatars', 'media', 'questtopics');
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('validation');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array('admin', 'moderator'),
			'character' => array('admin', 'moderator', 'user'),
			'register' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index' => array('admin', 'moderator'),
			'character' => array('admin', 'moderator', 'user')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * List registered Characters for a Seminary
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 */
		public function index($seminaryUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get registered Characters
			$characters = $this->Characters->getCharactersForSeminary($seminary['id']);
			
			// Additional Character information
			foreach($characters as &$character)
			{
				// Level
				$character['xplevel'] = $this->Characters->getXPLevelOfCharacters($character['id']);
				
				// Avatar
				$avatar = $this->Avatars->getAvatarById($character['avatar_id']);
				if(!is_null($avatar['small_avatarpicture_id'])) {
					$character['small_avatar'] = $this->Media->getSeminaryMediaById($avatar['small_avatarpicture_id']);
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('characters', $characters);
		}
		
		
		/**
		 * Action: character.
		 * 
		 * Show a Charater and its details.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 * @param	string	$characterUrl	URL-name of a Charater
		 */
		public function character($seminaryUrl, $characterUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			$seminary['achievable_xps'] = $this->Seminaries->getTotalXPs($seminary['id']);
			
			// Get Character
			$character = $this->Characters->getCharacterByUrl($seminary['id'], $characterUrl);
			$character['quest_xps'] = $this->Characters->getQuestXPsOfCharacter($character['id']);
			$character['xplevel'] = $this->Characters->getXPLevelOfCharacters($character['id']);
			$character['rank'] = $this->Characters->getXPRank($seminary['id'], $character['xps']);
			
			// Get Seminarycharacterfields
			$characterfields = $this->Seminarycharacterfields->getFieldsForCharacter($character['id']);
			
			// Get User
			$user = $this->Users->getUserById($character['user_id']);
			
			// Get Character groups
			$groups = $this->Charactergroups->getGroupsForCharacter($character['id']);
			
			// Get Achievements
			$achievements = $this->Achievements->getAchievedAchievementsForCharacter($character['id']);
			
			// Get Quest topics
			$questtopics = $this->Questtopics->getQuesttopicsForSeminary($seminary['id']);
			foreach($questtopics as &$questtopic)
			{
				$questtopic['questcount'] = $this->Questtopics->getQuestCountForQuesttopic($questtopic['id']);
				$questtopic['characterQuestcount'] = $this->Questtopics->getCharacterQuestCountForQuesttopic($questtopic['id'], $character['id']);
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('character', $character);
			$this->set('characterfields', $characterfields);
			$this->set('user', $user);
			$this->set('groups', $groups);
			$this->set('achievements', $achievements);
			$this->set('questtopics', $questtopics);
		}
		
		
		/**
		 * Acton: register.
		 * 
		 * Register a new character for a Seminary.
		 * 
		 * @throws	IdNotFoundException
		 * @throws	ParamsNotValidException
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 */
		public function register($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Character types
			$types = $this->Charactertypes->getCharacterTypesForSeminary($seminary['id']);
			
			// Character fields
			$fields = $this->Seminarycharacterfields->getFieldsForSeminary($seminary['id']);
			
			// Register Character
			$charactername = '';
			$validation = true;
			$fieldsValidation = true;
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('create')))
			{
				// Validate Character properties
				$validation = $this->Validation->validateParams($this->request->getPostParams(), array('charactername'));
				$charactername = $this->request->getPostParam('charactername');
				
				// Validate type
				$typeIndex = null;
				foreach($types as $index => &$type)
				{
					$type['selected'] = ($type['url'] == $this->request->getPostParam('type'));
					if($type['selected']) {
						$typeIndex = $index;
					}
				}
				if(is_null($typeIndex)) {
					throw new \nre\exceptions\ParamsNotValidException($characterType);
				}
				
				// Validate fields
				$fieldsValues = $this->request->getPostParam('fields');
				foreach($fields as &$field)
				{
					if(!array_key_exists($field['url'], $fieldsValues)) {
						throw new \nre\exceptions\ParamsNotValidException($index);
					}
					if($field['required'])
					{
						$fieldValidation = $this->Validation->validate($fieldsValues[$field['url']], array('regex'=>$field['regex']));
						if($fieldValidation !== true)
						{
							if(!is_array($fieldsValidation)) {
								$fieldsValidation = array();
							}
							$fieldsValidation[$field['url']] = $fieldValidation;
						}
					}
				}
				
				// Register
				if($validation === true && $fieldsValidation === true)
				{
					$characterId = $this->Characters->createCharacter($this->Auth->getUserId(), $types[$typeIndex]['id'], $charactername);
					
					// Add Seminary fields
					foreach($fields as &$field) {
						if(!empty($fieldsValues[$field['url']])) {
							$this->Characters->setSeminaryFieldOfCharacter($characterId, $field['id'], $fieldsValues[$field['url']]);
						}
					}
					
					// Redirect
					$this->redirect($this->linker->link(array('seminaries')));
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('types', $types);
			$this->set('fields', $fields);
			$this->set('charactername', $charactername);
			$this->set('validation', $validation);
			$this->set('fieldsValidation', $fieldsValidation);
		}
		
	}

?>
