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
		
		
		/**
		 * Check if a Charactertype name already exists.
		 * 
		 * @param	int	$seminaryId		ID of Seminary
		 * @param	string	$name			Charactertype name to check
		 * @param	int	$charactertypeId	Do not check this ID (for editing)
		 * @return	boolean				Whether Charactertype name exists or not
		 */
		public function charactertypeNameExists($seminaryId, $name, $charactertypeId=null)
		{
			$data = $this->db->query(
				'SELECT id '.
				'FROM charactertypes '.
				'WHERE seminary_id = ? AND (name = ? OR url = ?)',
				'iss',
				$seminaryId,
				$name,
				\nre\core\Linker::createLinkParam($name)
			);
			
			return (!empty($data) && (is_null($charactertypeId) || $charactertypeId != $data[0]['id']));
		}
		
		
		/**
		 * Create a new Charactertype for a Seminary.
		 * 
		 * @param	int	$userId		ID of creating user
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	string	$name		Name for new Charactertype
		 * @return	int			ID of newly created Charactertype
		 */
		public function createCharactertype($userId, $seminaryId, $name)
		{
			$this->db->query(
				'INSERT INTO charactertypes '.
				'(created_user_id, seminary_id, name, url) '.
				'VALUES '.
				'(?, ?, ?, ?) ',
				'iiss',
				$userId,
				$seminaryId,
				$name,
				\nre\core\Linker::createLinkParam($name)
			);
			
			return $this->db->getInsertId();
		}
		
		
		/**
		 * Edit a Charactertype.
		 * 
		 * @param	int	$charactertypeId	ID of Charactertype to edit
		 * @param	string	$name			New name of Charactertype
		 */
		public function editCharactertype($charactertypeId, $name)
		{
			$this->db->query(
				'UPDATE charactertypes '.
				'SET name = ?, url = ? '.
				'WHERE id = ?',
				'ssi',
				$name,
				\nre\core\Linker::createLinkParam($name),
				$charactertypeId
			);
		}
		
		
		/**
		 * Delete a Charactertype.
		 * 
		 * @param	int	$charactertypeId	ID of Charactertype to delete
		 */
		public function deleteCharactertype($charactertypeId)
		{
			$this->db->query('DELETE FROM charactertypes WHERE id = ?', 'i', $charactertypeId);
		}
		
	}

?>
