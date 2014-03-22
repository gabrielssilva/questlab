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
		 * @param	array	$seminary	Current Seminary data
		 * @param	array	$questgroup	Current Questgroup data
		 * @param	array	$quest		Current Quest data
		 * @param	array	$character	Current Character data
		 * @param	array	$answers	Character answers for the Quest
		 */
		public function saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
		{
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($quest['id']);
			
			// Save answers
			foreach($questions as &$question)
			{
				$answer = (array_key_exists(intval($question['pos'])-1, $answers)) ? true : false;
				$this->Multiplechoice->setCharacterSubmission($question['id'], $character['id'], $answer);
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
			// Get right answers
			$tickQuestions = $this->Multiplechoice->getTickQuestionsOfQuest($quest['id']);
			
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
		 * @param	array	$seminary	Current Seminary data
		 * @param	array	$questgroup	Current Questgroup data
		 * @param	array	$quest		Current Quest data
		 * @param	array	$character	Current Character data
		 */
		public function quest($seminary, $questgroup, $quest, $character)
		{
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($quest['id']);
			
			// Get user answers
			if($this->request->getGetParam('show-answer') == 'true')
			{
				foreach($questions as &$question) {
					$question['answer'] = $this->Multiplechoice->getCharacterSubmission($question['id'], $character['id']);
				}
			}
			
			// Has Character already solved Quest?
			$solved = $this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']);
			
			
			// Pass data to view
			$this->set('questions', $questions);
			$this->set('solved', $solved);
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
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($quest['id']);
			foreach($questions as &$question) {
				$question['answer'] = $this->Multiplechoice->getCharacterSubmission($question['id'], $character['id']);
			}
			
			
			// Pass data to view
			$this->set('questions', $questions);
		}
		
	}

?>
