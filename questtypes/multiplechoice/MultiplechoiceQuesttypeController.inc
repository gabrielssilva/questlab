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
		 * 
		 * @param	int	$questId	ID of Quest to save answers for
		 * @param	int	$characterId	ID of Character to save answers of
		 * @param	array	$answers	Character answers for the Quest
		 */
		public function saveAnswersOfCharacter($questId, $characterId, $answers)
		{
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($questId);
			
			// Save answers
			foreach($questions as &$question)
			{
				$answer = (array_key_exists(intval($question['pos'])-1, $answers)) ? true : false;
				$this->Multiplechoice->setCharacterSubmission($question['id'], $characterId, $answer);
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
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($questId);
			foreach($questions as &$question) {
				$question['answer'] = $this->Multiplechoice->getCharacterSubmission($question['id'], $characterId);
			}
			
			// Has Character already solved Quest?
			$solved = $this->Quests->hasCharacterSolvedQuest($questId, $characterId);
			
			
			// Pass data to view
			$this->set('questions', $questions);
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
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($questId);
			foreach($questions as &$question) {
				$question['answer'] = $this->Multiplechoice->getCharacterSubmission($question['id'], $characterId);
			}
			
			
			// Pass data to view
			$this->set('questions', $questions);
		}
		
	}

?>
