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
	 * Model of the DragndropQuesttypeAgent for Drag&Drop.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class DragndropQuesttypeModel extends \hhu\z\models\QuesttypeModel
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('media');
		
		
		
		
        /**
         * Copy a Quest
         * 
         * @param   int $userId             ID of creating user
         * @param   int $sourceQuestId      ID of Quest to copy from
         * @param   int $targetQuestId      ID of Quest to copy to
         * @param   int $seminaryMediaIds   Mapping of SeminaryMedia-IDs from source Seminary to targetSeminary
         */
        public function copyQuest($userId, $sourceQuestId, $targetQuestId, $seminaryMediaIds)
        {
            // Check Seminary media
            if(is_null($seminaryMediaIds)) {
                return;
            }

            // Get Dragndrop
            $dragndrop = $this->getDragndrop($sourceQuestId);

            // Copy media
            $this->Media->copyQuestsmedia($userId, $seminaryMediaIds[$dragndrop['questmedia_id']]);

            // Copy dran&drop
            $this->db->query(
                'INSERT INTO questtypes_dragndrop '.
                '(quest_id, created_user_id, questmedia_id, width, height) '.
                'SELECT ?, ?, ?, width, height '.
                'FROM questtypes_dragndrop '.
                'WHERE quest_id = ?',
                'iiii',
                $targetQuestId, $userId, $seminaryMediaIds[$dragndrop['questmedia_id']],
                $sourceQuestId
            );

            // Copy drags
            $dragIds = array();
            $drags = $this->getDrags($sourceQuestId);
            foreach($drags as &$drag)
            {
                // Copy media
                $this->Media->copyQuestsmedia($userId, $seminaryMediaIds[$drag['questmedia_id']]);

                // Copy drag
                $this->db->query(
                    'INSERT INTO questtypes_dragndrop_drags '.
                    '(questtypes_dragndrop_id, questmedia_id) '.
                    'SELECT ?, ? '.
                    'FROM questtypes_dragndrop_drags '.
                    'WHERE id = ?',
                    'iii',
                    $targetQuestId, $seminaryMediaIds[$drag['questmedia_id']],
                    $drag['id']
                );
                $dragIds[$drag['id']] = $this->db->getInsertId();
            }

            // Copy drops
            $dropIds = array();
            $drops = $this->getDrops($sourceQuestId);
            foreach($drops as &$drop)
            {
                // Copy drop
                $this->db->query(
                    'INSERT INTO questtypes_dragndrop_drops '.
                    '(questtypes_dragndrop_id, top, `left`, width, height) '.
                    'SELECT ?, top, `left`, width, height '.
                    'FROM questtypes_dragndrop_drops '.
                    'WHERE id = ?',
                    'ii',
                    $targetQuestId,
                    $drop['id']
                );
                $dropIds[$drop['id']] = $this->db->getInsertId();

                // Link drags and drops
                $links = $this->db->query(
                    'SELECT questtypes_dragndrop_drag_id '.
                    'FROM questtypes_dragndrop_drops_drags '.
                    'WHERE questtypes_dragndrop_drop_id = ?',
                    'i',
                    $drop['id']
                );
                foreach($links as $link)
                {
                    $this->db->query(
                        'INSERT INTO questtypes_dragndrop_drops_drags '.
                        '(questtypes_dragndrop_drop_id, questtypes_dragndrop_drag_id, created_user_id) '.
                        'VALUES '.
                        '(?, ?, ?)',
                        'iii',
                        $dropIds[$drop['id']],
                        $dragIds[$link['questtypes_dragndrop_drag_id']],
                        $userId
                    );
                }
            }
        }



		/**
		 * Get Drag&Drop-field.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @return	array			Drag&Drop-field
		 */
		public function getDragndrop($questId)
		{
			$data = $this->db->query(
				'SELECT quest_id, questmedia_id, width, height '.
				'FROM questtypes_dragndrop '.
				'WHERE quest_id = ?',
				'i',
				$questId
			);
			if(!empty($data)) {
				return $data[0];
			}
			
			
			return null;
		}
		
		
		/**
		 * Get Drop-items.
		 * 
		 * @param	int	$dragndropId	ID of Drag&Drop-field
		 * @return	array			Drop-items
		 */
		public function getDrops($dragndropId)
		{
			return $this->db->query(
				'SELECT id, top, `left`, width, height '. //, questtypes_dragndrop_drag_id '.
				'FROM questtypes_dragndrop_drops '.
				'WHERE questtypes_dragndrop_id = ?',
				'i',
				$dragndropId
			);
		}
		
		
		/**
		 * Get Drag-items.
		 * 
		 * @param	int	$dragndropId	ID of Drag&Drop-field
		 * @param	boolean	$onlyUsed	Only Drag-items that are used for a Drop-item
		 * @return	array			Drag-items
		 */
		public function getDrags($dragndropId, $onlyUsed=false)
		{
			return $this->db->query(
				'SELECT id, questmedia_id '.
				'FROM questtypes_dragndrop_drags '.
				'WHERE questtypes_dragndrop_id = ?'.
				($onlyUsed
					? ' AND EXISTS ('.
						'SELECT questtypes_dragndrop_drag_id '.
						'FROM questtypes_dragndrop_drops_drags '.
						'WHERE questtypes_dragndrop_drag_id = questtypes_dragndrop_drags.id'.
					')'
					: null
				),
				'i',
				$dragndropId
			);
		}
		
		
		/**
		 * Check if a Drag-item mathes a Drop-item.
		 * 
		 * @param	int	$dragId	ID of Drag-field
		 * @param	int	$dropId	ID of Drop-field
		 * @return	boolean	Drag-item is valid for Drop-item
		 */
		public function dragMatchesDrop($dragId, $dropId)
		{
			$data = $this->db->query(
				'SELECT count(*) AS c '.
				'FROM questtypes_dragndrop_drops_drags '.
				'WHERE questtypes_dragndrop_drop_id = ? AND questtypes_dragndrop_drag_id = ?',
				'ii',
				$dropId, $dragId
			);
			if(!empty($data)) {
				return ($data[0]['c'] > 0);
			}
			
			
			return false;
		}
		
		
		/**
		 * Save Character’s submitted answer for one Drop-field.
		 * 
		 * @param	int	$dropId		ID of Drop-field
		 * @param	int	$characterId	ID of Character
		 * @param	string	$answer		Submitted Drag-field-ID for this field
		 */
		public function setCharacterSubmission($dropId, $characterId, $answer)
		{
			if(is_null($answer))
			{
				$this->db->query(
					'DELETE FROM questtypes_dragndrop_drops_characters '.
					'WHERE questtypes_dragndrop_drop_id = ? AND character_id = ?',
					'ii',
					$dropId, $characterId
				);
			}
			else
			{
				$this->db->query(
					'INSERT INTO questtypes_dragndrop_drops_characters '.
					'(questtypes_dragndrop_drop_id, character_id, questtypes_dragndrop_drag_id) '.
					'VALUES '.
					'(?, ?, ?) '.
					'ON DUPLICATE KEY UPDATE '.
					'questtypes_dragndrop_drag_id = ?',
					'iiii',
					$dropId, $characterId, $answer, $answer
				);
			}
		}
		
		
		/**
		 * Get Character’s saved answer for one Drop-field.
		 * 
		 * @param	int	$dropId		ID of Drop-field
		 * @param	int	$characterId	ID of Character
		 * @return	int			ID of Drag-field or null
		 */
		public function getCharacterSubmission($dropId, $characterId)
		{
			$data = $this->db->query(
				'SELECT questtypes_dragndrop_drag_id '.
				'FROM questtypes_dragndrop_drops_characters '.
				'WHERE questtypes_dragndrop_drop_id = ? AND character_id = ?',
				'ii',
				$dropId, $characterId
			);
			if(!empty($data)) {
				return $data[0]['questtypes_dragndrop_drag_id'];
			}
			
			
			return null;
		}
		
	}

?>
