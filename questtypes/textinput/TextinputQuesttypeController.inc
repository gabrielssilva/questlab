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
	 * Controller of the TextinputQuesttypeAgent for for inserting text.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class TextinputQuesttypeController extends \hhu\z\controllers\QuesttypeController
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
			// Get fields
			$fields = $this->Textinput->getTextinputFields($quest['id']);
			
			// Save answers
			foreach($fields as &$field)
			{
				$pos = intval($field['number']) - 1;
				$answer = (array_key_exists($pos, $answers)) ? $answers[$pos] : '';
				$this->Textinput->setCharacterSubmission($field['id'], $character['id'], $answer);
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
			// Get right answers
			$fields = $this->Textinput->getTextinputFields($quest['id']);
			
			// Match regexs with user answers
			foreach($fields as &$field)
			{
				$pos = intval($field['number']) - 1;
				if(!array_key_exists($pos, $answers)) {
					return false;
				}
				if(!$this->isMatching($field['regex'], $answers[$pos])) {
					return false;
				}
			}
			
			
			// All answers right
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
			// Get Task
			$task = $this->Textinput->getTextinputQuest($quest['id']);
			
			// Get fields
			$fields = $this->Textinput->getTextinputFields($quest['id']);
			
			// Has Character already solved Quest?
			$solved = $this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']);
			
			// Get Character answers
			if(!$solved || $this->request->getGetParam('show-answer') == 'true' || $this->request->getGetParam('status') == 'solved') {
				foreach($fields as &$field) {
					$field['answer'] = $this->Textinput->getCharacterSubmission($field['id'], $character['id']);
				}
			}
			
			
			// Pass data to view
			$this->set('task', $task);
			$this->set('fields', $fields);
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
			$task = $this->Textinput->getTextinputQuest($quest['id']);
			
			// Process text
			$textParts = preg_split('/(\$\$)/', ' '.$task['text'].' ');
			
			// Get fields
			$fields = $this->Textinput->getTextinputFields($quest['id']);
			
			// Get Character answers
			foreach($fields as &$field)
			{
				$field['answer'] = $this->Textinput->getCharacterSubmission($field['id'], $character['id']);
				$field['right'] = $this->isMatching($field['regex'], $field['answer']);
			}
			
			
			// Pass data to view
			$this->set('task', $task);
			$this->set('fields', $fields);
		}
		
		
		
		
		/**
		 * Check if an Character answer matches a Regex.
		 * 
		 * @param	string	$regex	Regex to match against
		 * @param	string	$answer	Character answer to match
		 * @return	boolean		Whether answer matches Regex or not
		 */
		private function isMatching($regex, $answer)
		{
			$score = preg_match($regex, trim($answer));
			
			
			return ($score !== false && $score > 0);
		}
		
	}

?>
