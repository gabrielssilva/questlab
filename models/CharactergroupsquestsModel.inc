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
	 * Model of the CharactergroupsquestsAgent to interact with
	 * Charactergroupsquests-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CharactergroupsquestsModel extends \hhu\z\Model
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('uploads');
		
		
		
		
		/**
		 * Construct a new CharactergroupsquestsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get Character groups Quests of a Character groups-groups.
		 * 
		 * @param	int	$groupsgroupId	ID of the Character groups-group
		 * @return	array			Character groups Quest data
		 */
		public function getQuestsForCharactergroupsgroup($groupsgroupId)
		{
			return $this->db->query(
				'SELECT id, questgroups_id, title, url, xps '.
				'FROM charactergroupsquests '.
				'WHERE charactergroupsgroup_id = ?',
				'i',
				$groupsgroupId
			);
		}
		
		
		/**
		 * Get a Character groups Quest by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$groupsgroupId	ID of the Character groups-group
		 * @param	string	$questUrl	URL-title of the Character groups Quest
		 * @return	array			Character groups Quest data
		 */
		public function getQuestByUrl($groupsgroupId, $questUrl)
		{
			$data = $this->db->query(
				'SELECT id, questgroups_id, title, url, description, xps, rules, won_text, lost_text, questsmedia_id '.
				'FROM charactergroupsquests '.
				'WHERE charactergroupsgroup_id = ? AND url = ?',
				'is',
				$groupsgroupId,
				$questUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Character groups Quest by its ID.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$questId	ID of the Character groups Quest
		 * @return	array			Character groups Quest data
		 */
		public function getQuestById($questId)
		{
			$data = $this->db->query(
				'SELECT id, questgroups_id, title, url, description, xps, rules, won_text, lost_text, questsmedia_id '.
				'FROM charactergroupsquests '.
				'WHERE id = ?',
				'i',
				$questId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get Character groups Quests for a Character group.
		 * 
		 * @param	int	$groupId	ID of the Character group
		 * @return	array			Character groups Quests
		 */
		public function getQuestsForGroup($groupId)
		{
			$quests = $this->db->query(
				'SELECT charactergroupsquests.id, charactergroupsquests_groups.created, charactergroupsquests.title, charactergroupsquests.url, charactergroupsquests.xps, charactergroupsquests_groups.xps_factor '.
				'FROM charactergroupsquests_groups '.
				'LEFT JOIN charactergroupsquests ON charactergroupsquests.id = charactergroupsquests_groups.charactergroupsquest_id '.
				'WHERE charactergroupsquests_groups.charactergroup_id = ?',
				'i',
				$groupId
			);
			foreach($quests as &$quest) {
				$quest['group_xps'] = round($quest['xps'] * $quest['xps_factor'], 1);
			}
			
			
			return $quests;
		}
		
		
		/**
		 * Get XPs of a Character group for a Character groups Quest.
		 * 
		 * @param	int	$questId	ID of Character groups Quest
		 * @param	int	$groupId	ID of Character group to get XPs of
		 * @return	array			XP-record
		 */
		public function getXPsOfGroupForQuest($questId, $groupId)
		{
			$data = $this->db->query(
				'SELECT charactergroupsquests_groups.created, charactergroupsquests_groups.xps_factor, charactergroupsquests.xps '.
				'FROM charactergroupsquests_groups '.
				'LEFT JOIN charactergroupsquests ON charactergroupsquests.id = charactergroupsquests_groups.charactergroupsquest_id '.
				'WHERE charactergroupsquests_groups.charactergroupsquest_id = ? AND charactergroupsquests_groups.charactergroup_id = ?',
				'ii',
				$questId,
				$groupId
			);
			if(empty($data)) {
				return null;
			}
			
			$data = $data[0];
			$data['xps'] = round($data['xps'] * $data['xps_factor'], 1);
			
			
			return $data;
		} 
		
		
		/**
		 * Set XPs of a Character group for a Character groups Quest.
		 * 
		 * @param	int	$questId	ID of Character groups Quest
		 * @param	int	$groupId	ID of Character group to set XPs of
		 * @param	float	$xpsFactor	XPs-factor
		 */
		public function setXPsOfGroupForQuest($questId, $groupId, $xpsFactor)
		{
			$this->db->query(
				'INSERT INTO charactergroupsquests_groups '.
				'(charactergroupsquest_id, charactergroup_id, xps_factor) '.
				'VALUES '.
				'(?, ?, ?) '.
				'ON DUPLICATE KEY UPDATE '.
				'xps_factor = ?',
				'iidd',
				$questId,
				$groupId,
				$xpsFactor,
				$xpsFactor
			);
		}
		
		
		/**
		 * Remove a Character group from a Character groups Quest.
		 * 
		 * @param	int	$questId	ID of Character groups Quest
		 * @param	int	$groupId	ID of Character group to remove
		 */
		public function deleteGroupForQuest($questId, $groupId)
		{
			$this->db->query(
				'DELETE FROM charactergroupsquests_groups '.
				'WHERE charactergroupsquest_id = ? AND charactergroup_id = ?',
				'ii',
				$questId, $groupId
			);
		}
		
		
		/**
		 * Check if a Character groups Quest title already exists.
		 * 
		 * @param	string	$name		Character groups Quest title to check
		 * @param	int	$questId	Do not check this ID (for editing)
		 * @return	boolean			Whether Character groups Quest title exists or not
		 */
		public function characterGroupsQuestTitleExists($title, $questId=null)
		{
			$data = $this->db->query(
				'SELECT id '.
				'FROM charactergroupsquests '.
				'WHERE title = ? OR url = ?',
				'ss',
				$title,
				\nre\core\Linker::createLinkParam($title)
			);
			
			return (!empty($data) && (is_null($questId) || $questId != $data[0]['id']));
		}
		
		
		/**
		 * Set the media for a Character groups Quest.
		 * 
		 * @param	int	$questId	ID of Quest to upload media for
		 * @param	int	$mediaId	ID of Quests media
		 */
		public function setMediaForQuest($questId, $mediaId)
		{
			$this->db->query(
				'UPDATE charactergroupsquests '.
				'SET questsmedia_id = ? '.
				'WHERE id = ?',
				'ii',
				$mediaId,
				$questId
			);
		}
		
		
		/**
		 * Upload a media for a Character groups Quest.
		 * 
		 * @param	int	$userId		ID of user that does the upload
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	int	$questId	ID of Quest to upload media for
		 * @param	array	$file		File-array of file to upload
		 * @param	string	$filename	Filename for media
		 * @return	boolean			Whether upload succeeded or not
		 */
		public function uploadMediaForQuest($userId, $seminaryId, $questId, $file, $filename)
		{
			// Save file on harddrive
			$uploadId = $this->Uploads->uploadSeminaryFile($userId, $seminaryId, $file['name'], $filename, $file['tmp_name'], $file['type']);
			if($uploadId === false) {
				return false;
			}
			
			// Create database record
			$this->db->query(
				'INSERT INTO charactergroupsquests_seminaryuploads '.
				'(seminaryupload_id, charactergroupsquest_id, created_user_id) '.
				'VALUES '.
				'(?, ?, ?) ',
				'iii',
				$uploadId, $questId, $userId
			);
			
			
			return true;
		}
		
		
		/**
		 * Get uploaded Medai for a Character groups Quest.
		 * 
		 * @param	int	$questId	ID of Quest to get media for
		 * @return	array			Seminary uploads
		 */
		public function getMediaForQuest($questId)
		{
			return $this->db->query(
				'SELECT seminaryupload_id, created, created_user_id '.
				'FROM charactergroupsquests_seminaryuploads '.
				'WHERE charactergroupsquest_id = ?',
				'i',
				$questId
			);
		}
		
		
		/**
		 * Create a new Character groups Quest.
		 * 
		 * @param	int	$userId		ID of user
		 * @param	int	$groupsgroupId	ID of Character groups-group
		 * @param	int	$questgroupId	ID of Quest group
		 * @param	string	$title		Title of new Quest
		 * @param	string	$description	Description of new Quset
		 * @param	int	$xps		Amount of XPs for new Quest
		 * @param	string	$rules		Rules of new Quest
		 * @param	string	$wonText	Won-text of new Quset
		 * @param	string	$lostText	Lost-text of new Quest
		 * @return	int			ID of newly created Quest
		 */
		public function createQuest($userId, $groupsgroupId, $questgroupId, $title, $description, $xps, $rules, $wonText, $lostText)
		{
			$this->db->query(
				'INSERT INTO charactergroupsquests '.
				'(created_user_id, charactergroupsgroup_id, questgroups_id, title, url, description, xps, rules, won_text, lost_text) '.
				'VALUES '.
				'(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)',
				'iiisssdsss',
				$userId,
				$groupsgroupId,
				$questgroupId,
				$title,
				\nre\core\Linker::createLinkParam($title),
				$description,
				$xps,
				$rules,
				$wonText,
				$lostText
			);
			
			
			return $this->db->getInsertId();
		}
		
		
		/**
		 * Edit a Character groups Quest.
		 * 
		 * @param	int	$questId	ID of Character groups Quest to edit
		 * @param	int	$groupsgroupId	ID of Character groups-group
		 * @param	int	$questgroupId	ID of Quest group
		 * @param	string	$title		Title of new Quest
		 * @param	string	$description	Description of new Quset
		 * @param	int	$xps		Amount of XPs for new Quest
		 * @param	string	$rules		Rules of new Quest
		 * @param	string	$wonText	Won-text of new Quset
		 * @param	string	$lostText	Lost-text of new Quest
		 */
		public function editQuest($questId, $groupsgroupId, $questgroupId, $title, $description, $xps, $rules, $wonText, $lostText)
		{
			$this->db->query(
				'UPDATE charactergroupsquests '.
				'SET charactergroupsgroup_id = ?, questgroups_id = ?, title = ?, url = ?, description = ?, xps = ?, rules = ?, won_text = ?, lost_text= ? '.
				'WHERE id = ?',
				'iisssdsssi',
				$groupsgroupId,
				$questgroupId,
				$title,
				\nre\core\Linker::createLinkParam($title),
				$description,
				$xps,
				$rules,
				$wonText,
				$lostText,
				$questId
			);
		}
		
		
		/**
		 * Delete a Character groups Quest.
		 * 
		 * @param	int	$questId	ID of Character groups Quest to delete
		 */
		public function deleteQuest($questId)
		{
			$this->db->query('DELETE FROM charactergroupsquests WHERE id = ?', 'i', $questId);
		}
		
		
	}

?>
