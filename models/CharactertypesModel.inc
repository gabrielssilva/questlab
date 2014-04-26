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
	 * Model to interact with Charactertypes-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactertypesModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new CharactertypesModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all Character types of a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of Seminary to get types of
		 * @return	array			Character types
		 */
		public function getCharacterTypesForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT id, name, url '.
				'FROM charactertypes '.
				'WHERE seminary_id = ? '.
				'ORDER BY name ASC',
				'i',
				$seminaryId
			);
		}
		
	}

?>
