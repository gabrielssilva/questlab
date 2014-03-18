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
		 * TODO saveAnswersOfCharacter()
		 * 
		 * @param	int	$questId	ID of Quest to save answers for
		 * @param	int	$characterId	ID of Character to save answers of
		 * @param	array	$answers	Character answers for the Quest
		 */
		public function saveAnswersOfCharacter($questId, $characterId, $answers)
		{
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
				
				$score = preg_match($regex['regex'], $answers[$i]);
				if($score === 0 || $score === false)
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
			// Answers
			if(!array_key_exists('answers', $_SESSION)) {
				$_SESSION['answers'] = array();
			}
			$answers = array_key_exists($questId, $_SESSION['answers']) ? $_SESSION['answers'][$questId] : array();
			
			
			// Get Task
			$task = $this->Textinput->getTextinputQuest($questId);
			
			// Process text
			$textParts = preg_split('/(\$\$)/', $task['text'], -1, PREG_SPLIT_NO_EMPTY);
			
			
			// Pass data to view
			$this->set('texts', $textParts);
			$this->set('answers', $answers);
		}
		
		
		/**
		 * Action: submission.
		 * @TODO submission()
		 * 
		 * Show the submission of a Character for a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to show submission for
		 * @param	int	$characterId	ID of Character to show submission of
		 */
		public function submission($questId, $characterId)
		{
		}
		
	}

?>
