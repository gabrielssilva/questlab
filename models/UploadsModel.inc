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
	 * Model to handle files to upload.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class UploadsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new UploadsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Upload a file and create a database record.
		 * 
		 * @param	int	$userId		ID of user that uploads the file
		 * @param	string	$filename	Name of file to upload
		 * @param	string	$tmpFilename	Name of temporary uploaded file
		 * @param	string	$mimetype	Mimetype of file to upload
		 * @param	int	$seminaryId	Optional ID of Seminary if the upload is in the context of one
		 * @return	mixed			ID of database record or false
		 */
		public function uploadFile($userId, $filename, $tmpFilename, $mimetype, $seminaryId=null)
		{
			$uploadId = false;
			$this->db->setAutocommit(false);
			
			try {
				// Create database record
				if(is_null($seminaryId))
				{
					$this->db->query(
						'INSERT INTO uploads '.
						'(created_user_id, name, url, mimetype) '.
						'VALUES '.
						'(?, ? ,? ,?)',
						'isss',
						$userId, $filename, \nre\core\Linker::createLinkParam($filename), $mimetype
					);
				}
				else
				{
					$this->db->query(
						'INSERT INTO uploads '.
						'(created_user_id, seminary_id, name, url, mimetype) '.
						'VALUES '.
						'(?, ?, ? ,? ,?)',
						'iisss',
						$userId, $seminaryId, $filename, \nre\core\Linker::createLinkParam($filename), $mimetype
					);
				}
				$uploadId = $this->db->getInsertId();
			
				// Create filename
				$filename = ROOT.DS.\nre\configs\AppConfig::$dirs['uploads'].DS.$uploadId;
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
		 * Get an upload by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$uploadId	ID of the uploaded file
		 * @return	array			Upload data
		 */
		public function getUploadById($uploadId)
		{
			$data = $this->db->query(
				'SELECT id, created, created_user_id, seminary_id, name, url, mimetype, public '.
				'FROM uploads '.
				'WHERE id = ?',
				'i',
				$uploadId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($uploadId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get an upload by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$uploadId	ID of the uploaded file
		 * @return	array			Upload data
		 */
		public function getUploadByUrl($uploadUrl)
		{
			$data = $this->db->query(
				'SELECT id, created, created_user_id, seminary_id, name, url, mimetype, public '.
				'FROM uploads '.
				'WHERE url = ?',
				's',
				$uploadUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($uploadUrl);
			}
			
			
			return $data[0];
		}
		
	}

?>
