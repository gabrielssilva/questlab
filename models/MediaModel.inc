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
	 * Model to interact with the Media-tables.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MediaModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new MediaModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get a medium by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$mediaURL	URL-name of the Medium
		 * @return	array			Medium data
		 */
		public function getMediaByUrl($mediaUrl)
		{
			$data = $this->db->query(
				'SELECT id, name, url, description, mimetype '.
				'FROM media '.
				'WHERE url = ?',
				's',
				$mediaUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($mediaUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a medium by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$mediaId	ID of the Medium
		 * @return	array			Medium data
		 */
		public function getMediaById($mediaId)
		{
			$data = $this->db->query(
				'SELECT id, name, url, description, mimetype '.
				'FROM media '.
				'WHERE id = ?',
				'i',
				$mediaId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($mediaId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Seminary medium by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$seminaryId		ID of the seminary
		 * @param	string	$seminaryMediaUrl	URL-name of the Seminary medium
		 * @return	array				Seminary medium data
		 */
		public function getSeminaryMediaByUrl($seminaryId, $seminaryMediaUrl)
		{
			$data = $this->db->query(
				'SELECT id, name, url, description, mimetype '.
				'FROM seminarymedia '.
				'WHERE url = ?',
				's',
				$seminaryMediaUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($seminaryMediaUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Seminary medium by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$seminaryMediaId	ID of the Seminary medium
		 * @return	array				Seminary medium data
		 */
		public function getSeminaryMediaById($mediaId)
		{
			$data = $this->db->query(
				'SELECT id, name, url, description, mimetype '.
				'FROM seminarymedia '.
				'WHERE id = ?',
				'i',
				$mediaId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($mediaId);
			}
			
			
			return $data[0];
		}
		
	}

?>
