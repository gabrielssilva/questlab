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
	class TextinputQuesttypeController extends \hhu\z\QuesttypeController
	{
		
		
		
		
		/**
		 * Save the answers of a Character for a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to save answers for
		 * @param	int	$characterId	ID of Character to save answers of
		 * @param	array	$answers	Character answers for the Quest
		 */
		public function saveAnswersOfCharacter($questId, $characterId, $answers)
		{
			// Get regexs
			$regexs = $this->Textinput->getTextinputRegexs($questId);
			
			// Save answers
			foreach($regexs as &$regex)
			{
				$pos = intval($regex['number']) - 1;
				$answer = (array_key_exists($pos, $answers)) ? $answers[$pos] : '';
				$this->Textinput->setCharacterSubmission($regex['id'], $characterId, $answer);
			}
		}
		
		
		/**
		 * Check if answers of a Character for a Quest match the correct ones.
		 * 
		 * @param	int	$questId	ID of Quest to match answers for
		 * @param	int	$characterId	ID of Character to match answers of
		 * @return	boolean			True/false for a right/wrong answer or null for moderator evaluation
		 */
		public function matchAnswersOfCharacter($questId, $characterId, $answers)
		{
			// Get right answers
			$regexs = $this->Textinput->getTextinputRegexs($questId);
			
			// Match regexs with user answers
			$allSolved = true;
			foreach($regexs as $i => &$regex)
			{
				if(!array_key_exists($i, $answers))
				{
					$allSolved = false;
					break;
				}
				
				if(!$this->isMatching($regex['regex'], $answers[$i]))
				{
					$allSolved = false;
					break;
				}
			}
			
			
			// Set status
			return $allSolved;
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Display a text with input fields and evaluate if user input
		 * matches with stored regular expressions.
		 * 
		 * @param	int	$questId	ID of Quest to show
		 * @param	int	$characterId	ID of Character
		 */
		public function quest($questId, $characterId)
		{
			// Get Task
			$task = $this->Textinput->getTextinputQuest($questId);
			
			// Process text
			$textParts = preg_split('/(\$\$)/', $task['text'], -1, PREG_SPLIT_NO_EMPTY);
			
			// Get Character answers
			$regexs = $this->Textinput->getTextinputRegexs($questId);
			foreach($regexs as &$regex) {
				$regex['answer'] = $this->Textinput->getCharacterSubmission($regex['id'], $characterId);
			}
			
			// Has Character already solved Quest?
			$solved = $this->Quests->hasCharacterSolvedQuest($questId, $characterId);
			
			
			// Pass data to view
			$this->set('texts', $textParts);
			$this->set('regexs', $regexs);
			$this->set('solved', $solved);
		}
		
		
		/**
		 * Action: submission.
		 * 
		 * Show the submission of a Character for a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to show submission for
		 * @param	int	$characterId	ID of Character to show submission of
		 */
		public function submission($questId, $characterId)
		{
			// Get Task
			$task = $this->Textinput->getTextinputQuest($questId);
			
			// Process text
			$textParts = preg_split('/(\$\$)/', $task['text'], -1, PREG_SPLIT_NO_EMPTY);
			
			// Get Character answers
			$regexs = $this->Textinput->getTextinputRegexs($questId);
			foreach($regexs as &$regex) {
				$regex['answer'] = $this->Textinput->getCharacterSubmission($regex['id'], $characterId);
				$regex['right'] = $this->isMatching($regex['regex'], $regex['answer']);
			}
			
			
			// Pass data to view
			$this->set('texts', $textParts);
			$this->set('regexs', $regexs);
		}
		
		
		
		
		private function isMatching($regex, $answer)
		{
			$score = preg_match($regex, $answer);
			
			
			return ($score !== false && $score > 0);
		}
		
	}

?>
