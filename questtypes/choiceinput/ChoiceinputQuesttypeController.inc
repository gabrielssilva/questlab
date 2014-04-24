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
	 * Controller of the ChoiceinputQuesttypeAgent for choosing between
	 * predefined input values.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class ChoiceinputQuesttypeController extends \hhu\z\QuesttypeController
	{
		
		
		
		
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
			// Get lists
			$choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);
			
			// Save answers
			foreach($choiceLists as &$list)
			{
				$pos = intval($list['number']) - 1;
				$answer = (array_key_exists($pos, $answers)) ? $answers[$pos] : null;
				$this->Choiceinput->setCharacterSubmission($list['id'], $character['id'], $answer);
			}
		}
		
		
		/**
		 * Save additional data for the answers of a Character for a Quest.
		 * 
		 * @param	array	$seminary	Current Seminary data
		 * @param	array	$questgroup	Current Questgroup data
		 * @param	array	$quest		Current Quest data
		 * @param	array	$character	Current Character data
		 * @param	array	$data		Additional (POST-) data
		 */
		public function saveDataForCharacterAnswers($seminary, $questgroup, $quest, $character, $data)
		{
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
			// Get lists
			$choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);
			
			// Match lists with user answers
			foreach($choiceLists as $i => &$list)
			{
				if(!array_key_exists($i, $answers)) {
					return false;
				}
				if($list['questtypes_choiceinput_choice_id'] != $answers[$i]) {
					return false;
				}
			}
			
			
			// All answer right
			return true;
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Display a text with lists with predefined values.
		 * 
		 * @param	array		$seminary	Current Seminary data
		 * @param	array		$questgroup	Current Questgroup data
		 * @param	array		$quest		Current Quest data
		 * @param	array		$character	Current Character data
		 * @param	Exception	$exception	Character submission exception
		 */
		public function quest($seminary, $questgroup, $quest, $character, $exception)
		{
			// Get Task
			$task = $this->Choiceinput->getChoiceinputQuest($quest['id']);
			
			// Process text
			$textParts = preg_split('/(\$\$)/', ' '.$task['text'].' ');
			
			// Get lists
			$choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);
			foreach($choiceLists as &$list) {
				$list['values'] = $this->Choiceinput->getChoiceinputChoices($list['id']);
			}
			
			// Get Character answers
			if($this->request->getGetParam('show-answer') == 'true' || !$this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']))
			{
				foreach($choiceLists as &$list) {
					$list['answer'] = $this->Choiceinput->getCharacterSubmission($list['id'], $character['id']);
				}
			}
			
			
			// Pass data to view
			$this->set('texts', $textParts);
			$this->set('choiceLists', $choiceLists);
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
			// Get Task
			$task = $this->Choiceinput->getChoiceinputQuest($quest['id']);
			
			// Process text
			$textParts = preg_split('/(\$\$)/', ' '.$task['text'].' ');
			
			// Get lists
			$choiceLists = $this->Choiceinput->getChoiceinputLists($quest['id']);
			foreach($choiceLists as &$list)
			{
				$list['values'] = $this->Choiceinput->getChoiceinputChoices($list['id']);
				$list['answer'] = $this->Choiceinput->getCharacterSubmission($list['id'], $character['id']);
				$list['right'] = ($list['questtypes_choiceinput_choice_id'] == $list['answer']);
			}
			
			
			// Pass data to view
			$this->set('texts', $textParts);
			$this->set('choiceLists', $choiceLists);
		}
		
	}

?>
