<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\models;
	
	
	/**
	 * Model to interact with characterroles-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharacterrolesModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new CharacterrolesModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all characterroles for a Character referenced by its ID.
		 * 
		 * @param	int	$userId	ID of an user
		 * @return	array		Characterroles for a Character
		 */
		public function getCharacterrolesForCharacterById($characterId)
		{
			return $this->db->query(
				'SELECT characterroles.id, characterroles.created, characterroles.name '.
				'FROM characters_characterroles '.
				'LEFT JOIN characterroles ON characterroles.id = characters_characterroles.characterrole_id '.
				'WHERE characters_characterroles.character_id = ?',
				'i',
				$characterId
			);
		}
		
	}

?>
