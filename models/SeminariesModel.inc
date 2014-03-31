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
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('questgroupshierarchy', 'questgroups');
		
		
		
		
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
				'SELECT id, created, created_user_id, title, url, description '.
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
				'SELECT id, created, created_user_id, title, url, description, media_id '.
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
				'SELECT id, created, created_user_id, title, url, description, media_id '.
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
		
		
		/*
		 * Calculate sum of XPs for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	int			Total sum of XPs
		 */
		public function getTotalXPs($seminaryId)
		{
			$xps = 0;
			
			// Questgroups
			$questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyOfSeminary($seminaryId);
			foreach($questgroupshierarchy as &$hierarchy)
			{
				// Get Questgroups
				$questgroups = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id']);
				foreach($questgroups as &$questgroup) {
					$xps += $this->Questgroups->getAchievableXPsForQuestgroup($questgroup['id']);
				}
			}
			
			
			return $xps;
		}
		
		
		/**
		 * Create a new seminary.
		 * 
		 * @param	string	$title		Title of seminary to create
		 * @param	int	$userId		ID of creating user
		 * @return	int			ID of the newly created seminary
		 */
		public function createSeminary($title, $userId)
		{
			$this->db->query(
				'INSERT INTO seminaries '.
				'(created_user_id, title, url) '.
				'VALUES '.
				'(?, ?, ?)',
				'iss',
				$userId,
				$title,
				\nre\core\Linker::createLinkParam($title)
			);
			
			
			return $this->db->getInsertId();
		}
		
		
		/**
		 * Edit a seminary.
		 * 
		 * @throws	DatamodelException
		 * @param	int	$seminaryId	ID of the seminary to delete
		 * @param	string	$title		New title of seminary
		 */
		public function editSeminary($seminaryId, $title)
		{
			$this->db->query(
				'UPDATE seminaries '.
				'SET title = ?, url = ? '.
				'WHERE id = ?',
				'ssi',
				$title,
				\nre\core\Linker::createLinkParam($title),
				$seminaryId
			);
		}
		
		
		/**
		 * Delete a seminary.
		 * 
		 * @param	int	$seminaryId	ID of the seminary to delete
		 */
		public function deleteSeminary($seminaryId)
		{
			$this->db->query('DELETE FROM seminaries WHERE id = ?', 'i', $seminaryId);
		}
		
	}

?>
