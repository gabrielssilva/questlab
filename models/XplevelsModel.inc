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
	 * Model for XP-levels.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class XplevelsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new XplevelsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get XP-level by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$xplevelId	ID of XP-level
		 * @return	array			XP-level data
		 */
		public function getXPLevelById($xplevelId)
		{
			$data = $this->db->query(
				'SELECT id, seminary_id, xps, level, name '.
				'FROM xplevels '.
				'WHERE id = ?',
				'i',
				$xplevelId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($xplevelId);
			}
			
			
			return $data[0];
		}
		
	}

?>
