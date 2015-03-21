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
	 * Model to interact with Questgroups-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgroupsModel extends \hhu\z\Model
	{
		/**
		 * Questgroup-status: Entered
		 * 
		 * @var int;
		 */
		const QUESTGROUP_STATUS_ENTERED = 0;
		
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('questgroupshierarchy', 'questgrouptexts', 'quests', 'questtexts', 'media');
		
		
		
		
		/**
		 * Construct a new QuestgroupsModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
		/**
		 * Get all Questgroups for a Questgroup hierarchy.
		 * 
		 * @param	int	$hierarchyId		ID of the Questgroup hierarchy to get Questgroups for
		 * @param	int	$parentQuestgroupId	ID of the parent Questgroup hierarchy
		 * @return	array				Questgroups for the given hierarchy
		 */
		public function getQuestgroupsForHierarchy($hierarchyId, $parentQuestgroupId=null)
		{
			// Get Questgroups
			$questgroups = array();
			if(is_null($parentQuestgroupId))
			{
				$questgroups = $this->db->query(
					'SELECT questgroups.id, questgroups_questgroupshierarchy.questgroupshierarchy_id, questgroups_questgroupshierarchy.pos, questgroups.title, questgroups.url, questgroups.questgroupspicture_id, questgroups.achievable_xps '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE questgroups_questgroupshierarchy.questgroupshierarchy_id = ? AND questgroups_questgroupshierarchy.parent_questgroup_id IS NULL '.
					'ORDER BY questgroups_questgroupshierarchy.pos ASC',
					'i',
					$hierarchyId
				);
			}
			else
			{
				$questgroups = $this->db->query(
					'SELECT questgroups.id, questgroups_questgroupshierarchy.questgroupshierarchy_id, questgroups_questgroupshierarchy.pos, questgroups.title, questgroups.url, questgroups.questgroupspicture_id, questgroups.achievable_xps '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE questgroups_questgroupshierarchy.questgroupshierarchy_id = ? AND questgroups_questgroupshierarchy.parent_questgroup_id = ? '.
					'ORDER BY questgroups_questgroupshierarchy.pos ASC',
					'ii',
					$hierarchyId, $parentQuestgroupId
				);
			}
			
			
			// Return Questgroups
			return $questgroups;
		}
		
		
		/**
		 * Get all Questgroups for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @return	array			List of Questgroups
		 */
		public function getQuestgroupsForSeminary($seminaryId)
		{
			return $this->db->query(
				'SELECT id, title, url, questgroupspicture_id, achievable_xps '.
				'FROM questgroups '.
				'WHERE seminary_id = ? '.
				'ORDER BY title ASC',
				'i',
				$seminaryId
			);
		}
		
		
		/**
		 * Get a Questgroup by its ID.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	int	$questgroupId	ID of a Questgroup
		 * @return	array			Questgroup data
		 */
		public function getQuestgroupById($questgroupId)
		{
			$data = $this->db->query(
				'SELECT id, title, url, questgroupspicture_id, achievable_xps '.
				'FROM questgroups '.
				'WHERE questgroups.id = ?',
				'i',
				$questgroupId
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questgroupId);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get a Questgroup by its URL.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	int	$seminaryId	ID of the corresponding seminary
		 * @param	string	$questgroupURL	URL-title of a Questgroup
		 * @return	array			Questgroup data
		 */
		public function getQuestgroupByUrl($seminaryId, $questgroupUrl)
		{
			$data = $this->db->query(
				'SELECT id, title, url, questgroupspicture_id, achievable_xps '.
				'FROM questgroups '.
				'WHERE seminary_id = ? AND url = ?',
				'is',
				$seminaryId, $questgroupUrl
			);
			if(empty($data)) {
				throw new \nre\exceptions\IdNotFoundException($questgroupUrl);
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get the next Questgroup.
		 * 
		 * Determine the next Questgroup. If there is no next Questgroup
		 * on the same level as the given Quest then the followed-up
		 * Questgroup from a higher hierarchy level is returned.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to get next Questgroup of
		 * @return	array			Questgroup data
		 */
		public function getNextQuestgroup($questgroupId)
		{
			$currentQuestgroup = $this->getQuestgroupById($questgroupId);
			$currentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($currentQuestgroup['id']);
			if(empty($currentQuestgroup['hierarchy'])) {
				return null;
			}
			
			$nextQuestgroup = $this->_getNextQuestgroup($currentQuestgroup['hierarchy']['parent_questgroup_id'], $currentQuestgroup['hierarchy']['questgroup_pos']);
			if(is_null($nextQuestgroup) && !is_null($currentQuestgroup['hierarchy']['parent_questgroup_id'])) {
				$nextQuestgroup = $this->getNextQuestgroup($currentQuestgroup['hierarchy']['parent_questgroup_id']);
			}
			
			
			return $nextQuestgroup;
		}
		
		
		/**
		 * Get the previous Questgroup.
		 * 
		 * Determine the previous Questgroup. If there is no previous
		 * Questgroup on the same level as the given Quest then the
		 * followed-up Questgroup from a higher hierarchy level is
		 * returned.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to get previous Questgroup of
		 * @return	array			Questgroup data
		 */
		public function getPreviousQuestgroup($questgroupId)
		{
			$currentQuestgroup = $this->getQuestgroupById($questgroupId);
			$currentQuestgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($currentQuestgroup['id']);
			if(empty($currentQuestgroup['hierarchy'])) {
				return null;
			}
			
			$previousQuestgroup = $this->_getPreviousQuestgroup($currentQuestgroup['hierarchy']['parent_questgroup_id'], $currentQuestgroup['hierarchy']['questgroup_pos']);
			if(is_null($previousQuestgroup) && !is_null($currentQuestgroup['hierarchy']['parent_questgroup_id'])) {
				$previousQuestgroup = $this->getPreviousQuestgroup($currentQuestgroup['hierarchy']['parent_questgroup_id']);
			}
			
			
			return $previousQuestgroup;
		}
		
		
		/**
		 * Mark a Questgroup as entered for a Character.
		 * 
		 * @param	int	$questId	ID of Quest to mark as entered
		 * @param	int	$characterId	ID of Character that entered the Quest
		 */
		public function setQuestgroupEntered($questgroupId, $characterId)
		{
			$this->setQuestgroupStatus($questgroupId, $characterId, self::QUESTGROUP_STATUS_ENTERED, false);
		}
		
		
		/**
		 * Determine if the given Character has entered a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to check
		 * @param	int	$characterId	ID of Character to check
		 * @result	boolean			Whether Character has entered the Questgroup or not
		 */
		public function hasCharacterEnteredQuestgroup($questgroupId, $characterId)
		{
			$count = $this->db->query(
				'SELECT count(id) AS c '.
				'FROM questgroups_characters '.
				'WHERE questgroup_id = ? AND character_id = ? AND status IN (?)',
				'iii',
				$questgroupId,
				$characterId,
				self::QUESTGROUP_STATUS_ENTERED
			);
			
			
			return (!empty($count) && intval($count[0]['c']) > 0);
		}
		
		
		/**
		 * Determine if the given Character has solved a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to check
		 * @param	int	$characterId	ID of Character to check
		 * @result	boolean			Whether Character has solved the Questgroup or not
		 */
		public function hasCharacterSolvedQuestgroup($questgroupId, $characterId)
		{
			// Get data of Questgroup
			$questgroup = $this->getQuestgroupById($questgroupId);
			$questgroup['hierarchy'] = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroup['id']);
			
			// Check last Quest(s) of this Questgroup
			$solvedLastQuest = false;
			$lastQuests = $this->Quests->getLastQuestsOfQuestgroup($questgroup['id']);
			// Check last Quest(s) of last child Questgroup
			if(empty($lastQuests) && !empty($questgroup['hierarchy']))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroup['hierarchy']['id']);
				if(!empty($childQuestgroupshierarchy))
				{
					$childQuestgroupshierarchy = array_pop($childQuestgroupshierarchy);
					$childQuestgroups = $this->getQuestgroupsForHierarchy($childQuestgroupshierarchy['id'], $questgroupId);
					if(!empty($childQuestgroups))
					{
						$childQuestgroup = array_pop($childQuestgroups);
						$lastQuests = $this->Quests->getLastQuestsOfQuestgroup($childQuestgroup['id']);
					}
				}
			}
			foreach($lastQuests as &$lastQuest)
			{
				if($this->Quests->hasCharacterSolvedQuest($lastQuest['id'], $characterId))
				{
					$solvedLastQuest = true;
					break;
				}
			}
			if(!$solvedLastQuest) {
				return false;
			}
			
			// Check all child Questgroups
			if(!empty($questgroup['hierarchy']))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroup['hierarchy']['id']);
				foreach($childQuestgroupshierarchy as &$hierarchy)
				{
					// Get Questgroups
					$questgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroup['id']);
					foreach($questgroups as &$group) {
						if(!$this->hasCharacterSolvedQuestgroup($group['id'], $characterId)) {
							return false;
						}
					}
				}
			}
			
			
			return true;
		}
		
		
		/**
		 * Get all related Questgroups of a Questtext.
		 * 
		 * @param	int	$questtextId	ID of the Questtext
		 * @return	array			Related Questgroups for the Questtext
		 */
		public function getRelatedQuestsgroupsOfQuesttext($questtextId)
		{
			return $this->db->query(
				'SELECT questgroups.id, questgroups_questtexts.questtext_id, questgroups.title, questgroups.url, questgroups_questtexts.entry_text '.
				'FROM questgroups_questtexts '.
				'INNER JOIN questgroups ON questgroups.id = questgroups_questtexts.questgroup_id '.
				'WHERE questgroups_questtexts.questtext_id = ?',
				'i',
				$questtextId
			);
		}
		
		
		/**
		 * Get all related Questgroups of a Quest.
		 * 
		 * @param	int	$questId	ID of the Quest
		 * @return	array			Related Quests for the Quest
		 */
		public function getRelatedQuestsgroupsOfQuest($questId)
		{
			return $this->db->query(
				'SELECT questgroups_questtexts.questgroup_id AS id '.
				'FROM quests '.
				'INNER JOIN questtexts ON questtexts.quest_id = quests.id '.
				'INNER JOIN questgroups_questtexts ON questgroups_questtexts.questtext_id = questtexts.id '.
				'WHERE quests.id = ?',
				'i',
				$questId
			);
			
		}
		
		
		/**
		 * Get all related Questgroups of a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of the Questgroup
		 * @return	array			Related Questgroups for the Questgroup
		 */
		public function getRelatedQuestsgroupsOfQuestgroup($questgroupId)
		{
			return $this->db->query(
				'SELECT DISTINCT questgroups_questtexts.questgroup_id AS id '.
				'FROM questgroups '.
				'INNER JOIN quests ON quests.questgroup_id = questgroups.id '.
				'INNER JOIN questtexts ON questtexts.quest_id = quests.id '.
				'INNER JOIN questgroups_questtexts ON questgroups_questtexts.questtext_id = questtexts.id '.
				'WHERE questgroups.id = ?',
				'i',
				$questgroupId
			);
		}
		
		
		/**
		 * Summarize XPs of all Quests for a Questgroup and its
		 * sub-Questgroups solved by a Character.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup
		 * @param	int	$characterId	ID of Character
		 * @return	int			Sum of XPs
		 */
		public function getAchievedXPsForQuestgroup($questgroupId, $characterId)
		{
			// Questgroup
			$xps = $this->_getAchievedXPsForQuestgroup($questgroupId, $characterId);
			
			// Related Questgroups
			foreach($this->getRelatedQuestsgroupsOfQuestgroup($questgroupId) as $relatedQuestgroup) {
				$xps += $this->getAchievedXPsForQuestgroup($relatedQuestgroup['id'], $characterId);
			}
			
			// XPs of child Questgroups
            //var_dump($this->Questgroupshierarchy);
			$questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroupId);
			if(!empty($questgroupHierarchy))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
				foreach($childQuestgroupshierarchy as &$hierarchy)
				{
					$childQuestgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroupId);
					foreach($childQuestgroups as &$childQuestgroup) {
						$xps += $this->getAchievedXPsForQuestgroup($childQuestgroup['id'], $characterId);
					}
				}
			}
			
			
			return $xps;
		}
		
		
		/**
		 * Check if a Questgroups title already exists for a Seminary.
		 * 
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	string	$title		Questgroup title to check
		 * @param	int	$questgroupId	Do not check this ID (for editing)
		 * @return	boolean			Whether Questgroup title exists or not
		 */
		public function questgroupTitleExists($seminaryId, $title, $questgroupId=null)
		{
			$data = $this->db->query(
				'SELECT id '.
				'FROM questgroups '.
				'WHERE seminary_id = ? AND (title = ? OR url = ?)',
				'iss',
				$seminaryId,
				$title,
				\nre\core\Linker::createLinkParam($title)
			);
			
			return (!empty($data) && (is_null($questgroupId) || $questgroupId != $data[0]['id']));
		}
		
		
		/**
		 * Create a new Questgroup.
		 * 
		 * @param	int	$userId		User-ID that creates the new character
		 * @param	int	$seminaryId	ID of Seminary
		 * @param	string	$title		Title for new Questgroup
		 * @return	int			ID of new Questgroup
		 */
		public function createQuestgroup($userId, $seminaryId, $title)
		{
			$this->db->query(
				'INSERT INTO questgroups '.
				'(created_user_id, seminary_id, title, url) '.
				'VALUES '.
				'(?, ?, ?, ?)',
				'iiss',
				$userId,
				$seminaryId,
				$title,
				\nre\core\Linker::createLinkParam($title)
			);
			
			
			return $this->db->getInsertId();
		}


		/**
		 * Set the moodpic for a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to set moodpic for
		 * @param	int	$mediaId	ID of moodpic media
		 */
		public function setMoodpicForQuestgroup($questgroupId, $mediaId)
		{
			$this->db->query(
				'UPDATE questgroups '.
				'SET questgroupspicture_id = ? '.
				'WHERE id = ?',
				'ii',
				$mediaId,
				$questgroupId
			);
		}


		/**
		 * Add a Questgroup to a Questgroupshierarchy.
		 * 
		 * @param	int	$questgroupId		Id of Questgroup to add
		 * @param	int	$hierarchyId		Id of Hierarchy to add Questgroup to
		 * @param	int	$parentQuestgroupId	Id of parent Questgroup
		 */
		public function addQuestgroupToHierarchy($questgroupId, $hierarchyId, $parentQuestgroupId)
		{
			// Get last position
			$pos = $this->db->query(
				'SELECT COALESCE(MAX(pos),0) AS pos '.
				'FROM questgroups_questgroupshierarchy '.
				'WHERE  questgroupshierarchy_id = ? AND '.
				'parent_questgroup_id '.(!is_null($parentQuestgroupId) ? sprintf('= %d', $parentQuestgroupId) : 'IS NULL'),
				'i',
				$hierarchyId
			);
			$pos = intval($pos[0]['pos']);
			
			// Add Questgroup to Hierarchy
			$this->db->query(
				'INSERT INTO questgroups_questgroupshierarchy '.
				'(questgroup_id, questgroupshierarchy_id, parent_questgroup_id, pos) '.
				'VALUES '.
				'(?, ?, ?, ?)',
				'iiii',
				$questgroupId,
				$hierarchyId,
				$parentQuestgroupId,
				$pos + 1
			);
		}


        /**
         * Copy Questgroupshierarchy of Questgroups from a Seminary.
         * 
         * @param   array   $questgroupshierarchyIds    Mapping of hierarchy-IDs from source Seminary to target Seminary
         * @param   array   $questgroupIds              Mapping of Questgroup-IDs from source Seminary to target Seminary
         */
        public function copyQuestgroupsHierarchy($questgroupshierarchyIds, $questgroupIds)
        {
            foreach($questgroupIds as $sourceQuestgroupId => $targetQuestgroupId)
            {
                $hierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($sourceQuestgroupId);
                if(!is_null($hierarchy))
                {
                    if(is_null($hierarchy['parent_questgroup_id']))
                    {
                        $this->db->query(
                            'INSERT INTO questgroups_questgroupshierarchy '.
                            '(questgroup_id, questgroupshierarchy_id, parent_questgroup_id, pos) '.
                            'VALUES '.
                            '(?, ?, null, ?)',
                            'iii',
                            $targetQuestgroupId,
                            $questgroupshierarchyIds[$hierarchy['id']],
                            $hierarchy['questgroup_pos']
                        );
                    }
                    else
                    {
                        $this->db->query(
                            'INSERT INTO questgroups_questgroupshierarchy '.
                            '(questgroup_id, questgroupshierarchy_id, parent_questgroup_id, pos) '.
                            'VALUES '.
                            '(?, ?, ?, ?)',
                            'iiii',
                            $targetQuestgroupId,
                            $questgroupshierarchyIds[$hierarchy['id']],
                            $questgroupIds[$hierarchy['parent_questgroup_id']],
                            $hierarchy['questgroup_pos']
                        );
                    }
                }
            }
        }


        /**
         * Copy all related Questgroups of Questtexts of a Seminary.
         * 
         * @param   array   $questgroupIds  Mapping of Questgroup-IDs from source Seminary to target Seminary
         * @param   array   $questtextIds   Mapping of Questtext-IDs from source Seminary to target Seminary
         */
        public function copyRelatedQuestgroups($questgroupIds, $questtextIds)
        {
            foreach($questgroupIds as $sourceQuestgroupId => $targetQuestgroupId)
            {
                $questtexts = $this->Questtexts->getRelatedQuesttextsForQuestgroup($sourceQuestgroupId);
                foreach($questtexts as &$questtext)
                {
                    $this->db->query(
                        'INSERT INTO questgroups_questtexts '.
                        '(questgroup_id, questtext_id, entry_text) '.
                        'SELECT ?, ?, entry_text '.
                        'FROM questgroups_questtexts '.
                        'WHERE questgroup_id = ? AND questtext_id = ?',
                        'iiii',
                        $targetQuestgroupId, $questtextIds[$questtext['id']],
                        $sourceQuestgroupId, $questtext['id']
                    );
                }
            }
        }


		/**
		 * Move a Questgroup up (decrement position) or down (increment
		 * position).
		 * 
		 * @param	array	$questgroup	Questgroup to move
		 * @param	boolean	$up		True for moving up, false for down
		 */
		public function moveQuestgroup($questgroup, $up)
		{
			$this->db->setAutocommit(false);
			try {
				// Set temporary position
				$this->db->query(
					'UPDATE questgroups_questgroupshierarchy '.
					'SET pos = 0 '.
					'WHERE questgroup_id = ?',
					'i',
					$questgroup['id']
				);
				// Switch entry
				if(is_null($questgroup['hierarchy']['parent_questgroup_id'])) {
					$this->db->query(
						'UPDATE questgroups_questgroupshierarchy '.
						'SET pos = ? '.
						'WHERE questgroupshierarchy_id = ? AND parent_questgroup_id IS NULL AND pos = ?',
						'iii',
						$questgroup['hierarchy']['questgroup_pos'],
						$questgroup['hierarchy']['id'],
						$questgroup['hierarchy']['questgroup_pos'] + ($up ? -1 : 1)
					);
				}
				else {
					$this->db->query(
						'UPDATE questgroups_questgroupshierarchy '.
						'SET pos = ? '.
						'WHERE questgroupshierarchy_id = ? AND parent_questgroup_id = ? AND pos = ?',
						'iiii',
						$questgroup['hierarchy']['questgroup_pos'],
						$questgroup['hierarchy']['id'],
						$questgroup['hierarchy']['parent_questgroup_id'],
						$questgroup['hierarchy']['questgroup_pos'] + ($up ? -1 : 1)
					);
				}
				// Set new position
				$this->db->query(
					'UPDATE questgroups_questgroupshierarchy '.
					'SET pos = ? '.
					'WHERE questgroup_id = ?',
					'ii',
					$questgroup['hierarchy']['questgroup_pos'] + ($up ? -1 : 1),
					$questgroup['id']
				);
				
				$this->db->commit();
			}
			catch(\nre\exceptions\DatamodelException $e) {
				$this->db->rollback();
				$this->db->setAutocommit(true);
				throw $e;
			}
			$this->db->setAutocommit(true);
		}


		/**
		 * Edit a Questgroup.
		 * 
		 * @throws	\nre\exceptions\DatamodelException
		 * @param	int	$questgroupId	ID of Questgroup to edit
		 * @param	string	$title		New title of Questgroup
		 */
		public function editQuestgroup($questgroupId, $title)
		{
			$this->db->query(
				'UPDATE questgroups '.
				'SET title = ?, url = ? '.
				'WHERE id = ?',
				'ssi',
				$title,
				\nre\core\Linker::createLinkParam($title),
				$questgroupId
			);
		}


		/**
		 * Copy Questgroups of Seminary.
		 * 
		 * @throws	\nre\exceptions\DatamodelException
         * @param   int     $userId                     ID of creating user
		 * @param	int	    $sourceSeminaryId	        ID of Seminary to copy Questgroups from
         * @param   int     $targetSeminaryId           ID of Seminary to copy Questgroups to
         * @param   array   $questgroupshierarchyIds    Mapping of hierarchy-IDs from source Seminary to target Seminary
         * @param   array   $seminaryMediaIds           Mapping of Seminary-media-IDs from source Seminary to target Seminary (optional)
         * @return  array                               Mapping of Questgroup-IDs from source Seminary to target Seminary
		 */
		public function copyQuestgroupsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId, $questgroupshierarchyIds, $seminaryMediaIds=null)
		{
            // Get Questgroups of source Seminary
            $questgroupIds = array();
            $questgroups = $this->getQuestgroupsForSeminary($sourceSeminaryId);
            foreach($questgroups as &$questgroup)
            {
                // Insert into target Seminary
                $this->db->query(
                    'INSERT INTO questgroups '.
                    '(created_user_id, seminary_id, title, url) '.
                    'VALUES '.
                    '(?, ?, ?, ?)',
                    'iiss',
                    $userId,
                    $targetSeminaryId,
                    $questgroup['title'],
                    $questgroup['url']
                );
                $questgroupIds[$questgroup['id']] = $this->db->getInsertId();

                // Copy media
                if(!is_null($seminaryMediaIds) && !is_null($questgroup['questgroupspicture_id']))
                {
                    $this->Media->copyQuestgroupspicture($userId, $seminaryMediaIds[$questgroup['questgroupspicture_id']]);
                    $this->db->query(
                        'UPDATE questgroups '.
                        'SET questgroupspicture_id = ? '.
                        'WHERE id = ?',
                        'ii',
                        $seminaryMediaIds[$questgroup['questgroupspicture_id']],
                        $questgroupIds[$questgroup['id']]
                    );
                }

                // Copy Questgroup texts
                $this->Questgrouptexts->copyQuestgrouptexts($userId, $questgroup['id'], $questgroupIds[$questgroup['id']]);
            }


            return $questgroupIds;
		}


		/**
		 * Delete a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to delete
		 */
		public function deleteQuestgroup($questgroupId)
		{
			$this->db->query(
				'DELETE FROM questgroups WHERE id = ?',
				'i',
				$questgroupId
			);
		}
		
		
		
		
		/**
		 * Get the next (direct) Questgroup.
		 * 
		 * @param	int	$parentQuestgroupId	ID of parent Questgroup to get next Questgroup of
		 * @param	int	$questgroupPos		Position of Questgroup to get next Questgroup of
		 * @return	array				Data of next Questgroup or NULL
		 */
		private function _getNextQuestgroup($parentQuestgroupId, $questgroupPos)
		{
			if(!is_null($parentQuestgroupId))
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE parent_questgroup_id = ? AND pos = ? + 1',
					'ii',
					$parentQuestgroupId, $questgroupPos
				);
			}
			else
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE parent_questgroup_id IS NULL AND pos = ? + 1',
					'i',
					$questgroupPos
				);
			}
			if(empty($data)) {
				return null;
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Get the previous (direct) Questgroup.
		 * 
		 * @param	int	$parentQuestgroupId	ID of parent Questgroup to get previous Questgroup of
		 * @param	int	$questgroupPos		Position of Questgroup to get previous Questgroup of
		 * @return	array				Data of previous Questgroup or NULL
		 */
		private function _getPreviousQuestgroup($parentQuestgroupId, $questgroupPos)
		{
			if(!is_null($parentQuestgroupId))
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE parent_questgroup_id = ? AND pos = ? - 1',
					'ii',
					$parentQuestgroupId, $questgroupPos
				);
			}
			else
			{
				$data = $this->db->query(
					'SELECT * '.
					'FROM questgroups_questgroupshierarchy '.
					'INNER JOIN questgroups ON questgroups.id = questgroups_questgroupshierarchy.questgroup_id '.
					'WHERE parent_questgroup_id IS NULL AND pos = ? - 1',
					'i',
					$questgroupPos
				);
			}
			if(empty($data)) {
				return null;
			}
			
			
			return $data[0];
		}
		
		
		/**
		 * Mark a Questgroup for a Character.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup to mark
		 * @param	int	$characterId	ID of Character to mark the Questgroup for
		 * @param	int	$status		Questgroup status to mark
		 * @param	boolean	$repeated	Insert although status is already set for this Questgroup and Character
		 */
		private function setQuestgroupStatus($questgroupId, $characterId, $status, $repeated=true)
		{
			// Check if status is already set
			if(!$repeated)
			{
				$count = $this->db->query(
					'SELECT count(*) AS c '.
					'FROM questgroups_characters '.
					'WHERE questgroup_id = ? AND character_id = ? AND status = ?',
					'iii',
					$questgroupId,
					$characterId,
					$status
				);
				if(!empty($count) && intval($count[0]['c']) > 0) {
					return;
				}
			}
			
			// Set status
			$this->db->query(
				'INSERT INTO questgroups_characters '.
				'(questgroup_id, character_id, status) '.
				'VALUES '.
				'(?, ?, ?) ',
				'iii',
				$questgroupId,
				$characterId,
				$status
			);
		}
		
		
		/**
		 * Calculate the total amount of achievable XPs for a
		 * Questgroup, its sub-Questgroups, related Questgroups etc. and
		 * store this value in the database.
		 * 
		 * @param	int	$questgroupId		ID of Questgroup
		 * @param	array	$calculatedQuests	Already calculated Quests
		 * @return	int				Sum of calculated XPs
		 */
		public function calculateXPsForQuestgroup($questgroupId, &$calculatedQuests=array())
		{
			$xps = 0;
			
			// Quests
			$quest = $this->Quests->getFirstQuestOfQuestgroup($questgroupId);
			if(!is_null($quest)) {
				$xps = $this->_calculateXPsForQuestgroup($quest);
			}
			
			// Child Questgroups
			$questgroupHierarchy = $this->Questgroupshierarchy->getHierarchyForQuestgroup($questgroupId);
			if(!empty($questgroupHierarchy))
			{
				$childQuestgroupshierarchy = $this->Questgroupshierarchy->getChildQuestgroupshierarchy($questgroupHierarchy['id']);
				foreach($childQuestgroupshierarchy as &$hierarchy)
				{
					$questgroups = $this->getQuestgroupsForHierarchy($hierarchy['id'], $questgroupId);
					foreach($questgroups as &$questgroup) {
						$xps += $this->calculateXPsForQuestgroup($questgroup['id'], $calculatedQuests);
					}
				}
			}
			
			// Save XPs
			$this->setXPsForQuestgroup($questgroupId, $xps);
			
			
			return $xps;
		}
		
		
		
		
		/**
		 * Get the sum of XPs of Quests for a Questgroup solved by a
		 * Character.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup
		 * @param	int	$characterId	ID of Character
		 * @return	int			Sum of XPs of Quests
		 */
		private function _getAchievedXPsForQuestgroup($questgroupId, $characterId)
		{
			$data = $this->db->query(
				'SELECT COALESCE(SUM(quests.xps),0) AS xps '.
				'FROM quests '.
				'INNER JOIN quests_characters ON quests_characters.quest_id = quests.id AND quests_characters.character_id = ? AND quests_characters.status = ? '.
				'WHERE quests.questgroup_id = ?',
				'iii',
				$characterId,
				\hhu\z\models\QuestsModel::QUEST_STATUS_SOLVED,
				$questgroupId
			);
			if(!empty($data)) {
				return $data[0]['xps'];
			}
		}
		
		
		/**
		 * Calculate the total amount of achievable XPs for a Quest and
		 * its following Quests by choosing the path with the highest
		 * amount of XPs.
		 * 
		 * @param	int	$quest			Quest data
		 * @param	array	$calculatedQuests	Already calculated Quests
		 * @return	int				Sum of calculated XPs
		 */
		private function _calculateXPsForQuestgroup($quest, &$calculatedQuests=array())
		{
			$xps = $quest['xps'];
			
			// Related Questgroups
			$relatedQuestgroups = $this->getRelatedQuestsgroupsOfQuest($quest['id']);
			foreach($relatedQuestgroups as &$relatedQuestgroup) {
				$xps += $this->calculateXPsForQuestgroup($relatedQuestgroup['id'], $calculatedQuests);
			}
			
			// Next Quests
			$nextQuests = $this->Quests->getNextQuests($quest['id']);
			$allNextXPs = array(0);
			foreach($nextQuests as &$nextQuest)
			{
				if(!array_key_exists($nextQuest['id'], $calculatedQuests)) {
					$calculatedQuests[$nextQuest['id']] = $this->_calculateXPsForQuestgroup($nextQuest, $calculatedQuests);
				}
				$allNextXPs[] = $calculatedQuests[$nextQuest['id']];
			}
			$xps += max($allNextXPs);
			
			
			return $xps;
		}
		
		
		/**
		 * Set achievable XPs for a Questgroup.
		 * 
		 * @param	int	$questgroupId	ID of Questgroup
		 * @param	int	$xps		XPs to set
		 */
		private function setXPsForQuestgroup($questgroupId, $xps)
		{
			$this->db->query(
				'UPDATE questgroups '.
				'SET achievable_xps = ? '.
				'WHERE id = ?',
				'ii',
				$xps,
				$questgroupId
			);
		}
		
	}

?>
