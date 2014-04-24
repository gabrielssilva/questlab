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
			// Save temporary user answer of last question
			$answers = (!is_array($answers)) ? array() : $answers;
			$pos = $this->Multiplechoice->getQuestionsCountOfQuest($quest['id']);
			$question = $this->Multiplechoice->getQuestionOfQuest($quest['id'], $pos);
			$this->saveUserAnswers($quest['id'], $question['id'], $answers);
			
			// Save answers
			$questions = $this->Multiplechoice->getQuestionsOfQuest($quest['id']);
			foreach($questions as &$question)
			{
				$userAnswers = $this->getUserAnswers($quest['id'], $question['id']);
				$answers = $this->Multiplechoice->getAnswersOfQuestion($question['id']);
				foreach($answers as &$answer)
				{
					$userAnswer = (array_key_exists($answer['pos']-1, $userAnswers)) ? true : false;
					$this->Multiplechoice->setCharacterSubmission($answer['id'], $character['id'], $userAnswer);
				}
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
			// Save temporary user answer of last question
			$answers = (!is_array($answers)) ? array() : $answers;
			$pos = $this->Multiplechoice->getQuestionsCountOfQuest($quest['id']);
			$question = $this->Multiplechoice->getQuestionOfQuest($quest['id'], $pos);
			$this->saveUserAnswers($quest['id'], $question['id'], $answers);
			
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($quest['id']);
			
			// Iterate questions
			foreach($questions as &$question)
			{
				// Get answers
				$userAnswers = $this->getUserAnswers($quest['id'], $question['id']);
				$answers = $this->Multiplechoice->getAnswersOfQuestion($question['id']);
				
				// Match answers with user answers
				foreach($answers as &$answer)
				{
					if(is_null($answer['tick'])) {
						continue;
					}
					if($answer['tick']) {
						if(!array_key_exists($answer['pos']-1, $userAnswers)) {
							return false;
						}
					}
					else {
						if(array_key_exists($answer['pos']-1, $userAnswers)) {
							return false;
						}
					}
				}
			}
			
			
			// All questions correct answerd
			return true;
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Display questions with a checkbox to let the user choose the
		 * right ones.
		 * 
		 * @param	array		$seminary	Current Seminary data
		 * @param	array		$questgroup	Current Questgroup data
		 * @param	array		$quest		Current Quest data
		 * @param	array		$character	Current Character data
		 * @param	Exception	$exception	Character submission exception
		 */
		public function quest($seminary, $questgroup, $quest, $character, $exception)
		{
			// Get count of questions
			$count = $this->Multiplechoice->getQuestionsCountOfQuest($quest['id']);
			
			// Get position
			$pos = 1;
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('submit-answer')))
			{	
				if(!is_null($this->request->getPostParam('question')))
				{
					// Get current position
					$pos = intval($this->request->getPostParam('question'));
					if($pos < 0 || $pos > $count) {
						throw new \nre\exceptions\ParamsNotValidException($pos);
					}
					
					// Save temporary answer of user
					$question = $this->Multiplechoice->getQuestionOfQuest($quest['id'], $pos);
					$answers = ($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('answers'))) ? $this->request->getPostParam('answers') : array();
					$this->saveUserAnswers($quest['id'], $question['id'], $answers);
					
					// Go to next position
					$pos++;
				}
				else {
					throw new \nre\exceptions\ParamsNotValidException('pos');
				}
			}
			
			// Get current question
			$question = $this->Multiplechoice->getQuestionOfQuest($quest['id'], $pos);
			
			// Get answers
			$question['answers'] = $this->Multiplechoice->getAnswersOfQuestion($question['id']);
			
			
			// Get previous user answers
			if($this->request->getGetParam('show-answer') == 'true' || !$this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']))
			{
				foreach($question['answers'] as &$answer) {
					$answer['useranswer'] = $this->Multiplechoice->getCharacterSubmission($answer['id'], $character['id']);
				}
			}
			
			
			// Pass data to view
			$this->set('question', $question);
			$this->set('pos', $pos);
			$this->set('count', $count);
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
			
			// Get answers
			foreach($questions as &$question)
			{
				$question['answers'] = $this->Multiplechoice->getAnswersOfQuestion($question['id']);
				
				// Get user answers
				foreach($question['answers'] as &$answer) {
					$answer['useranswer'] = $this->Multiplechoice->getCharacterSubmission($answer['id'], $character['id']);
				}
			}
			
			
			// Pass data to view
			$this->set('questions', $questions);
		}
		
		
		
		
		/**
		 * Save the answers of a user for a question temporary in the
		 * session.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @param	int	$questionId	ID of multiple choice question
		 * @param	array	$userAnswers	Answers of user for the question
		 */
		private function saveUserAnswers($questId, $questionId, $userAnswers)
		{
			// Ensure session structure
			if(!array_key_exists('answers', $_SESSION)) {
				$_SESSION['answers'] = array();
			}
			if(!array_key_exists($questId, $_SESSION['answers'])) {
				$_SESSION['answers'][$questId] = array();
			}
			$_SESSION['answers'][$questId][$questionId] = array();
			
			// Save answres
			foreach($userAnswers as $pos => &$answer) {
				$_SESSION['answers'][$questId][$questionId][$pos] = $answer;
			}
		}
		
		
		/**
		 * Get the temporary saved answers of a user for a question.
		 * 
		 * @param	int	$questId	ID of Quest
		 * @param	int	$questionId	ID of multiple choice question
		 * @return	array			Answers of user for the question
		 */
		private function getUserAnswers($questId, $questionId)
		{
			// Ensure session structure
			if(!array_key_exists('answers', $_SESSION)) {
				$_SESSION['answers'] = array();
			}
			if(!array_key_exists($questId, $_SESSION['answers'])) {
				$_SESSION['answers'][$questId] = array();
			}
			if(!array_key_exists($questionId, $_SESSION['answers'][$questId])) {
				$_SESSION['answers'][$questId][$questionId] = array();
			}
			
			
			// Return answers
			return $_SESSION['answers'][$questId][$questionId];
		}
		
	}

?>
