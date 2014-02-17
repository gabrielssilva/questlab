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
		 * Get a Questtext for a Quest by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$questId		ID of the Quest to get text for
		 * @param	string	$questtexttypeUrl	URL of the Questtexttype
		 * @param	int	$pos			Position of Questtexttype
		 * @return	array				Questtexttype data
		 */
		public function getQuesttextByUrl($questId, $questtexttypeUrl, $pos)
		{
			$data = $this->db->query(
				'SELECT questtexts.id, questtexts.text, questtexts.pos, questtexts.out_text, questtexts.questsmedia_id, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
				'FROM questtexts '.
				'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
				'WHERE questtexts.quest_id = ? AND questtexttypes.url = ? AND questtexts.pos = ?',
				'isi',
				$questId, $questtexttypeUrl, $pos
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questtexttypeUrl);
			}
			
			
			return $data = $data[0];
		}
		
		
		/**
		 * Get a Questtext for a Sidequest by its URL.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$sidequestId		ID of the Sidequest to get text for
		 * @param	string	$questtexttypeUrl	URL of the Questtexttype
		 * @param	int	$pos			Position of Questtexttype
		 * @return	array				Questtexttype data
		 */
		public function getSidequesttextByUrl($sidequestId, $questtexttypeUrl, $pos)
		{
			$data = $this->db->query(
				'SELECT sidequesttexts.id, sidequesttexts.text, sidequesttexts.pos, sidequesttexts.out_text, sidequesttexts.abort_text, sidequesttexts.questsmedia_id, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
				'FROM sidequesttexts '.
				'LEFT JOIN questtexttypes ON questtexttypes.id = sidequesttexts.questtexttype_id '.
				'WHERE sidequesttexts.sidequest_id = ? AND questtexttypes.url = ? AND sidequesttexts.pos = ?',
				'isi',
				$sidequestId, $questtexttypeUrl, $pos
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questtexttypeUrl);
			}
			
			
			return $data = $data[0];
		}
		
		
		/**
		 * Get count of Questtexts for a Quest.
		 * 
		 * @param	int	$questId		ID of the Quest
		 * @param	string	$questtexttypeUrl	URL of the Questtexttype
		 * @return	int				Conut of Questtexts for Quest
		 */
		public function getQuesttextsCountForQuest($questId, $questtexttypUrl)
		{
			$count = 0;
			$data = $this->db->query(
				'SELECT COUNT(questtexts.id) AS c '.
				'FROM questtexts '.
				'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
				'WHERE questtexts.quest_id = ? AND questtexttypes.url = ?',
				'is',
				$questId, $questtexttypUrl
			);
			if(!empty($data)) {
				$count = $data[0]['c'];
			}
			
			
			return $count;
		}
		
		
		/**
		 * Get count of Questtexts for a Sidequest.
		 * 
		 * @param	int	$sidequestId		ID of the Sidequest
		 * @param	string	$questtexttypeUrl	URL of the Questtexttype
		 * @return	int				Conut of Questtexts for Sideuest
		 */
		public function getQuesttextsCountForSidequest($questId, $questtexttypUrl)
		{
			$count = 0;
			$data = $this->db->query(
				'SELECT COUNT(sidequesttexts.id) AS c '.
				'FROM sidequesttexts '.
				'LEFT JOIN questtexttypes ON questtexttypes.id = sidequesttexts.questtexttype_id '.
				'WHERE sidequesttexts.sidequest_id = ? AND questtexttypes.url = ?',
				'is',
				$questId, $questtexttypUrl
			);
			if(!empty($data)) {
				$count = $data[0]['c'];
			}
			
			
			return $count;
		}
		
		
		/**
		 * Get corresponding Questtext for a Sidequest.
		 * 
		 * @throws	IdNotFoundException
		 * @param	int	$sidequestId	ID of the Sidequest to get the Questtext for
		 * @param	array			Questtext data
		 */
		public function getQuesttextForSidequest($sidequestId)
		{
			$data = $this->db->query(
				'SELECT questtexts.id, questtexts.text, questtexts.pos, questtexttypes.id AS type_id, questtexttypes.type, questtexttypes.url AS type_url '.
				'FROM sidequests '.
				'LEFT JOIN questtexts ON questtexts.id = sidequests.questtext_id '.
				'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
				'WHERE sidequests.id = ?',
				'i',
				$sidequestId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException();
			}
			
			
			return $data[0];
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
