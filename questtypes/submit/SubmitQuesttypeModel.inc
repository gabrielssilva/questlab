<?php
	
	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\questtypes;
	
	
	/**
	 * Model of the SubmitQuesttypeAgent for a submit task.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class SubmitQuesttypeModel extends \hhu\z\QuesttypeModel
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('uploads');
		
		
		
		
		/**
		 * Save Character’s submitted upload.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @param	int	$characterId	ID of Character
		 * @param	array	$file		Submitted upload
		 */
		public function setCharacterSubmission($seminaryId, $questId, $userId, $characterId, $file)
		{
			// Save file on harddrive
			$uploadId = $this->Uploads->uploadFile($userId, $file['name'], $file['tmp_name'], $file['type'], $seminaryId);
			if($uploadId === false) {
				return false;
			}
			
			// Create database record
			$this->db->query(
				'INSERT INTO questtypes_submit_characters '.
				'(quest_id, character_id, upload_id) '.
				'VALUES '.
				'(?, ?, ?) ',
				'iii',
				$questId, $characterId, $uploadId
			);
			
			
			return true;
		}
		
		
		/**
		 * Get upload submitted by Character.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @param	int	$characterId	ID of Character
		 * @return	array			Text submitted by Character or NULL
		 */
		public function getCharacterSubmission($questId, $characterId)
		{
			$data = $this->db->query(
				'SELECT upload_id '.
				'FROM questtypes_submit_characters '.
				'WHERE quest_id = ? AND character_id = ?',
				'ii',
				$questId, $characterId
			);
			if(!empty($data)) {
				return $this->Uploads->getUploadById($data[0]['upload_id']);
			}
			
			
			return null;
		}
		
		
		/**
		 * Get allowed mimetypes for uploading a file.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			Allowed mimetypes
		 */
		public function getAllowedMimetypes($seminaryId)
		{
			return $this->db->query(
				'SELECT id, mimetype, size '.
				'FROM questtypes_submit_mimetypes '.
				'WHERE seminary_id = ?',
				'i',
				$seminaryId
			);
		}
		
	}

?>
