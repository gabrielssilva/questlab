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
		
	}

?>
