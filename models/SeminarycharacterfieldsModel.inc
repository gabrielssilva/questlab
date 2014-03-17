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
	 * Model to interact with the Seminarycharacterfields-tables.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class SeminarycharacterfieldsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new SeminarycharacterfieldsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get Seminary Character fields of a Character.
		 * 
		 * @param	int	$characterId	ID of the Character
		 * @return	array			Seminary Character fields
		 */
		public function getFieldsForCharacter($characterId)
		{
			return $this->db->query(
				'SELECT seminarycharacterfields.title, characters_seminarycharacterfields.value '.
				'FROM characters_seminarycharacterfields '.
				'LEFT JOIN seminarycharacterfields ON seminarycharacterfields.id = characters_seminarycharacterfields.seminarycharacterfield_id '.
				'LEFT JOIN seminarycharacterfieldtypes ON seminarycharacterfieldtypes.id = seminarycharacterfields.seminarycharacterfieldtype_id '.
				'WHERE characters_seminarycharacterfields.character_id = ?',
				'i',
				$characterId
			);
		}
		
	}

?>
