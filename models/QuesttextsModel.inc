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
	 * Model to interact with Questtexts-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuesttextsModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new QuesttextsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all Questtexts for a Quest.
		 * 
		 * @param	int	$questId		ID of the Quest
		 * @param	string	$questtexttypeUrl	URL of the Questtexttype
		 * @return	array				All Questtexts for a Quest
		 */
		public function getQuesttextsOfQuest($questId, $questtexttypeUrl=null)
		{
			if(is_null($questtexttypeUrl))
			{
				return $this->db->query(
					'SELECT questtexts.id, questtexts.text, questtexts.pos, questtexts.out_text, questtexts.abort_text, questtexts.questsmedia_id, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
					'FROM questtexts '.
					'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
					'WHERE questtexts.quest_id = ?',
					'i',
					$questId
				);
			}
			else
			{
				return $this->db->query(
					'SELECT questtexts.id, questtexts.text, questtexts.pos, questtexts.out_text, questtexts.abort_text, questtexts.questsmedia_id, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
					'FROM questtexts '.
					'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
					'WHERE questtexts.quest_id = ? and questtexttypes.url = ?',
					'is',
					$questId,
					$questtexttypeUrl
				);
			}
		}
		
		
		/**
		 * Get count of Questtexts for a Quest.
		 * 
		 * @param	int	$questId		ID of the Quest
		 * @param	string	$questtexttypeUrl	URL of the Questtexttype
		 * @return	int				Amount of Questtexts for a Quest
		 */
		public function getQuesttextCountOfQuest($questId, $questtexttypeUrl=null)
		{
			if(is_null($questtexttypeUrl))
			{
				$data = $this->db->query(
					'SELECT count(questtexts.id) AS c '.
					'FROM questtexts '.
					'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
					'WHERE questtexts.quest_id = ?',
					'i',
					$questId
				);
			}
			else
			{
				$data = $this->db->query(
					'SELECT count(questtexts.id) AS c '.
					'FROM questtexts '.
					'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
					'WHERE questtexts.quest_id = ? and questtexttypes.url = ?',
					'is',
					$questId,
					$questtexttypeUrl
				);
			}
			if(!empty($data)) {
				return $data[0]['c'];
			}
			
			
			return 0;
		}
		
		
		/**
		 * Get corresponding Questtext for a Sidequest.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$sidequestId	ID of the Sidequest to get the Questtext for
		 * @param	array			Questtext data
		 */
		public function getRelatedQuesttextForQuestgroup($questgroupId)
		{
			$data = $this->db->query(
				'SELECT questtexts.id, questtexts.text, questtexts.pos, questtexts.quest_id, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
				'FROM questgroups_questtexts '.
				'LEFT JOIN questtexts ON questtexts.id = questgroups_questtexts.questtext_id '.
				'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
				'WHERE questgroups_questtexts.questgroup_id = ?',
				'i',
				$questgroupId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get all registered Questtexttypes.
		 * 
		 * @return	array	Registered Questtexttypes
		 */
		public function getQuesttexttypes()
		{
			return $this->db->query(
				'SELECT id, type, url '.
				'FROM questtexttypes'
			);
		}
		
		
		/**
		 * Get a Questtexttype by its URL.
		 * 
		 * @param	string	$questtexttypeUrl	URL-type of Questtexttype
		 * @return	array				Questtexttype data
		 */
		public function getQuesttexttypeByUrl($questtexttypeUrl)
		{
			$data = $this->db->query(
				'SELECT id, type, url '.
				'FROM questtexttypes '.
				'WHERE url = ?',
				's',
				$questtexttypeUrl
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Add a list of Questtexts to a Quest.
		 * 
		 * @param	int	$userId			ID of user
		 * @param	int	$questId		ID of Quest to add texts to
		 * @param	string	$questtexttypeUrl	URL-type of Questtexttype of texts
		 * @param	array	$texts			List of texts to add.
		 */
		public function addQuesttextsToQuest($userId, $questId, $questtexttypeUrl, $texts)
		{
			$questtexttype = $this->getQuesttexttypeByUrl($questtexttypeUrl);
			if(is_null($questtexttype)) {
				return;
			}
			foreach($texts as &$text)
			{
				$pos = $this->db->query(
					'SELECT COALESCE(MAX(pos),0)+1 AS pos '.
					'FROM questtexts '.
					'WHERE quest_id = ?',
					'i',
					$questId
				);
				$pos = $pos[0]['pos'];
				
				$this->db->query(
					'INSERT INTO questtexts '.
					'(created_user_id, quest_id, questtexttype_id, pos, text) '.
					'VALUES '.
					'(?, ?, ?, ?, ?)',
					'iiiis',
					$userId, $questId, $questtexttype['id'], $pos,
					$text
				);
			}
		}
		
		
		
		
	}

?>
