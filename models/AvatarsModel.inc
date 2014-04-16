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
	 * Model to interact with Avatars-tables.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class AvatarsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new AvatarsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get an Avatar by its ID
		 * 
		 * @param	int	$avatarId	ID of Avatar
		 * @return	array			Avatar data
		 */
		public function getAvatarById($avatarId)
		{
			$data = $this->db->query(
				'SELECT id, charactertype_id, xplevel_id, avatarpicture_id, small_avatarpicture_id '.
				'FROM avatars '.
				'WHERE id = ?',
				'i',
				$avatarId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get an Avatar by its Character type and XP-level.
		 * 
		 * @param	int	$seminaryId		ID of Seminary
		 * @param	string	$charactertypeUrl	URL-title of Character type
		 * @param	int	$xplevel		XP-level
		 * @return	array				Avatar data
		 */
		public function getAvatarByTypeAndLevel($seminaryId, $charactertypeUrl, $xplevel)
		{
			$data = $this->db->query(
				'SELECT avatars.id, charactertype_id, xplevel_id, avatarpicture_id, small_avatarpicture_id '.
				'FROM avatars '.
				'INNER JOIN charactertypes ON charactertypes.id = avatars.charactertype_id '.
				'INNER JOIN xplevels ON xplevels.id = avatars.xplevel_id AND xplevels.seminary_id = charactertypes.seminary_id '.
				'WHERE charactertypes.seminary_id = ? AND charactertypes.url = ? AND xplevels.level = ?',
				'isi',
				$seminaryId,
				$charactertypeUrl,
				$xplevel
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($charactertypeUrl);
			}
			
			
			return $data[0];
		}
		
	}

?>
