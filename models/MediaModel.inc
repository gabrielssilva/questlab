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
		
		
		/**
		 * Create a new Questsmedia by creating a new Seminarymedia and
		 * adding it to the list of Questsmedia.
		 * TODO Currently only temporary for easier data import.
		 */
		public function createQuestMedia($userId, $seminaryId, $filename, $description, $mimetype, $tmpFilename)
		{
			$uploadId = false;
			$this->db->setAutocommit(false);
			
			try {
				// Create database record
				$this->db->query(
					'INSERT INTO seminarymedia '.
					'(created_user_id, seminary_id, name, url, description, mimetype) '.
					'VALUES '.
					'(?, ? ,? ,?, ?, ?)',
					'iissss',
					$userId,
					$seminaryId,
					$filename,
					\nre\core\Linker::createLinkParam($filename),
					$description,
					$mimetype
				);
				$uploadId = $this->db->getInsertId();
				
				$this->db->query(
					'INSERT INTO questsmedia '.
					'(media_id, created_user_id) '.
					'VALUES '.
					'(?, ?)',
					'ii',
					$uploadId,
					$userId
				);
			
				// Create filename
				$filename = ROOT.DS.'seminarymedia'.DS.$uploadId;
				if(!move_uploaded_file($tmpFilename, $filename))
				{
					$this->db->rollback();
					$uploadId = false;
				}
			}
			catch(\nre\exceptions\DatamodelException $e) {
				$this->db->rollback();
				$this->db->setAutocommit(true);
			}
			
			
			$this->db->setAutocommit(true);
			return $uploadId;
		}
		
		
		/**
		 * Create a new Character groups media by creating a new Seminarymedia and
		 * adding it to the list of media for Character groups.
		 * 
		 * @param	int	$userId
		 * @param	int	$seminaryId
		 * @param	string	$filename
		 * @param	string	$description
		 * @param	string	$mimetype
		 * @param	string	$tmpFilename
		 * @return
		 */
		public function createCharactergroupMedia($userId, $seminaryId, $filename, $description, $mimetype, $tmpFilename)
		{
			$mediaId = false;
			$this->db->setAutocommit(false);
			
			try {
				// Check for existing database record
				$data = $this->db->query(
					'SELECT id '.
					'FROM seminarymedia '.
					'WHERE url = ?',
					's',
					\nre\core\Linker::createLinkParam($filename)
				);
				if(!empty($data)) {
					$mediaId = $data[0]['id'];
				}
				
				// Create database record
				if($mediaId === false)
				{
					$this->db->query(
						'INSERT INTO seminarymedia '.
						'(created_user_id, seminary_id, name, url, description, mimetype) '.
						'VALUES '.
						'(?, ? ,? ,?, ?, ?)',
						'iissss',
						$userId,
						$seminaryId,
						$filename,
						\nre\core\Linker::createLinkParam($filename),
						$description,
						$mimetype
					);
					$mediaId = $this->db->getInsertId();
				}
				
				// Add media to Character groups media
				$this->db->query(
					'INSERT INTO charactergroupsmedia '.
					'(seminarymedia_id, created_user_id) '.
					'VALUES '.
					'(?, ?) '.
					'ON DUPLICATE KEY UPDATE '.
					'created_user_id = ?',
					'iii',
					$mediaId,
					$userId,
					$userId
				);
			
				// Create filename
				$filename = ROOT.DS.'seminarymedia'.DS.$mediaId;
				if(!move_uploaded_file($tmpFilename, $filename))
				{
					$this->db->rollback();
					$mediaId = false;
				}
			}
			catch(\nre\exceptions\DatamodelException $e) {
				$this->db->rollback();
				$this->db->setAutocommit(true);
			}
			
			
			$this->db->setAutocommit(true);
			return $mediaId;
		}
		
	}

?>
