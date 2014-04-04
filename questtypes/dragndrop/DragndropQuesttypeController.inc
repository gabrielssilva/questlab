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
	 * Controller of the DragndropQuesttypeAgent for Drag&Drop.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class DragndropQuesttypeController extends \hhu\z\QuesttypeController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('media');
		
		
		
		
		/**
		 * Save the answers of a Character for a Quest.
		 * 
		 * @param	array	$seminary	Current Seminary data
		 * @param	array	$questgroup	Current Questgroup data
		 * @param	array	$quest		Current Quest data
		 * @param	array	$character	Current Character data
		 * @param	array	$answers	Character answers for the Quest
		 */
		public function saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
		{
			// Get Drag&Drop field
			$dndField = $this->Dragndrop->getDragndrop($quest['id']);
			
			// Get Drops
			$drops = $this->Dragndrop->getDrops($dndField['quest_id']);
			
			// Save user answers
			foreach($drops as &$drop)
			{
				// Determine user answer
				$answer = null;
				if(array_key_exists($drop['id'], $answers) && !empty($answers[$drop['id']]))
				{
					$a = intval(substr($answers[$drop['id']], 4));
					if($a !== false && $a > 0) {
						$answer = $a;
					}
				}
				
				// Update database record
				$this->Dragndrop->setCharacterSubmission($drop['id'], $character['id'], $answer);
			}
		}
		
		
		/**
		 * Check if answers of a Character for a Quest match the correct ones.
		 * 
		 * @param	array	$seminary	Current Seminary data
		 * @param	array	$questgroup	Current Questgroup data
		 * @param	array	$quest		Current Quest data
		 * @param	array	$character	Current Character data
		 * @return	boolean			True/false for a right/wrong answer or null for moderator evaluation
		 */
		public function matchAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
		{
			// Get Drag&Drop field
			$dndField = $this->Dragndrop->getDragndrop($quest['id']);
			
			// Get Drops
			$drops = $this->Dragndrop->getDrops($dndField['quest_id']);
			
			// Match drops with user answers
			foreach($drops as &$drop)
			{
				if(!array_key_exists($drop['id'], $answers) || intval(substr($answers[$drop['id']], 4)) !== $drop['questtypes_dragndrop_drag_id']) {
					return false;
				}
			}
			
			
			// Set status
			return true;
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Display a text with input fields and evaluate if user input
		 * matches with stored regular expressions.
		 * 
		 * @param	array		$seminary	Current Seminary data
		 * @param	array		$questgroup	Current Questgroup data
		 * @param	array		$quest		Current Quest data
		 * @param	array		$character	Current Character data
		 * @param	Exception	$exception	Character submission exception
		 */
		public function quest($seminary, $questgroup, $quest, $character, $exception)
		{
			// Get Drag&Drop field
			$dndField = $this->Dragndrop->getDragndrop($quest['id']);
			$dndField['media'] = $this->Media->getMediaById($dndField['questmedia_id']);
			
			// Get Drags
			$drags = array();
			$dragsByIndex = $this->Dragndrop->getDrags($dndField['quest_id']);
			foreach($dragsByIndex as &$drag) {
				$drag['media'] = $this->Media->getMediaById($drag['questmedia_id']);
				$drags[$drag['id']] = $drag;
			}
			
			// Get Drops
			$drops = $this->Dragndrop->getDrops($dndField['quest_id']);
			
			// Get Character answers
			if($this->request->getGetParam('show-answer') == 'true')
			{
				foreach($drops as &$drop)
				{
					$drop['answer'] = $this->Dragndrop->getCharacterSubmission($drop['id'], $character['id']);
					if(!is_null($drop['answer']))
					{
						$drop['answer'] = $drags[$drop['answer']];
						unset($drags[$drop['answer']['id']]);
					}
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('field', $dndField);
			$this->set('drops', $drops);
			$this->set('drags', $drags);
		}
		
		
		/**
		 * Action: submission.
		 * 
		 * Show the submission of a Character for a Quest.
		 * 
		 * @param	array	$seminary	Current Seminary data
		 * @param	array	$questgroup	Current Questgroup data
		 * @param	array	$quest		Current Quest data
		 * @param	array	$character	Current Character data
		 */
		public function submission($seminary, $questgroup, $quest, $character)
		{
			// Get Drag&Drop field
			$dndField = $this->Dragndrop->getDragndrop($quest['id']);
			$dndField['media'] = $this->Media->getMediaById($dndField['questmedia_id']);
			
			// Get Drags
			$drags = array();
			$dragsByIndex = $this->Dragndrop->getDrags($dndField['quest_id']);
			foreach($dragsByIndex as &$drag) {
				$drag['media'] = $this->Media->getMediaById($drag['questmedia_id']);
				$drags[$drag['id']] = $drag;
			}
			
			// Get Drops
			$drops = $this->Dragndrop->getDrops($dndField['quest_id']);
			
			// Get Character answers
			foreach($drops as &$drop)
			{
				$drop['answer'] = $this->Dragndrop->getCharacterSubmission($drop['id'], $character['id']);
				if(!is_null($drop['answer']))
				{
					$drop['answer'] = $drags[$drop['answer']];
					unset($drags[$drop['answer']['id']]);
				}
			}
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('field', $dndField);
			$this->set('drops', $drops);
			$this->set('drags', $drags);
		}
		
	}

?>
