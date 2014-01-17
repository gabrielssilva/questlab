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
	 * Model of the SeminariesAgent to list registered seminaries.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class SeminariesModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new SeminariesModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get registered seminaries.
		 * 
		 * @return	array	Seminaries
		 */
		public function getSeminaries()
		{			
			// Get seminaries
			return $this->db->query(
				'SELECT id, created, created_user_id, title, url '.
				'FROM seminaries '.
				'ORDER BY created DESC'
			);
		}
		
		
		/**
		 * Get a seminary and its data by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryId	ID of a seminary
		 * @return	array			Seminary
		 */
		public function getSeminaryById($seminaryId)
		{
			$seminary = $this->db->query(
				'SELECT id, created, created_user_id, title, url '.
				'FROM seminaries '.
				'WHERE id = ?',
				'i',
				$seminaryId
			);
			if(empty($seminary)) {
				throw new \nre\exceptions\IdNotFoundException($seminaryId);
			}
			
			
			return $seminary[0];
		}
		
		
		/**
		 * Get a seminary and its data by its URL-title.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a seminary
		 * @return	array			Seminary
		 */
		public function getSeminaryByUrl($seminaryUrl)
		{
			$seminary = $this->db->query(
				'SELECT id, created, created_user_id, title, url '.
				'FROM seminaries '.
				'WHERE url = ?',
				's',
				$seminaryUrl
			);
			if(empty($seminary)) {
				throw new \nre\exceptions\IdNotFoundException($seminaryUrl);
			}
			
			
			return $seminary[0];
		}
		
	}

?>
