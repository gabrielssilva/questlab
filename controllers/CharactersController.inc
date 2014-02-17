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
	class CharactersController extends \hhu\z\Controller
	{
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array('admin', 'moderator'),
			'character' => array('admin', 'moderator', 'user')
		);
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'characters', 'users', 'charactergroups', 'seminarycharacterfields');
		
		
		
		
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
			
			// Get Character
			$character = $this->Characters->getCharacterByUrl($seminary['id'], $characterUrl);
			
			// Get Seminarycharacterfields
			$characterfields = $this->Seminarycharacterfields->getFieldsForCharacter($character['id']);
			
			// Get User
			$user = $this->Users->getUserById($character['user_id']);
			
			// Get Character groups
			$groups = $this->Charactergroups->getGroupsForCharacter($character['id']);
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('character', $character);
			$this->set('characterfields', $characterfields);
			$this->set('user', $user);
			$this->set('groups', $groups);
		}
		
	}

?>
