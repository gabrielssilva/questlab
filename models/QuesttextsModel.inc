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
				'SELECT questtexts.id, questtexts.text, questtexts.out_text, questtexttypes.type '.
				'FROM questtexts '.
				'LEFT JOIN questtexttypes ON questtexttypes.id = questtexts.questtexttype_id '.
				'WHERE questtexts.quest_id = ? AnD questtexttypes.url = ? AND questtexts.pos = ?',
				'isi',
				$questId, $questtexttypeUrl, $pos
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questtexttypeUrl);
			}
			
			
			return $data = $data[0];
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
