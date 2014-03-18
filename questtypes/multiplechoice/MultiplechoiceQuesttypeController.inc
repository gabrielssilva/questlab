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
	 * Controller of the MultiplechoiceQuesttypeAgent multiple choice.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MultiplechoiceQuesttypeController extends \hhu\z\QuesttypeController
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
			$tickQuestions = $this->Multiplechoice->getTickQuestionsOfQuest($questId);
			
			// Match tick questions with user answers
			$allSolved = true;
			foreach($tickQuestions as &$tickQuestion)
			{
				$pos = intval($tickQuestion['pos'])-1;
				if(!array_key_exists($pos, $answers) || $answers[$pos] != 'true')
				{
					$allSolved = false;
					break;
				}
				else {
					unset($answers[$pos]);
				}
			}
			
			
			// Return status
			return ($allSolved && count($answers) == 0);
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Display questions with a checkbox to let the user choose the
		 * right ones.
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
			
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($questId);
			
			
			// Pass data to view
			$this->set('questions', $questions);
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
