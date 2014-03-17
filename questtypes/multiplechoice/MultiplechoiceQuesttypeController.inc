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
		 * Action: index.
		 * 
		 * Display a text with input fields and evaluate if user input
		 * matches with stored regular expressions.
		 */
		public function index($questId)
		{
			// Answers
			if(!array_key_exists('answers', $_SESSION)) {
				$_SESSION['answers'] = array();
			}
			$answers = array_key_exists($questId, $_SESSION['answers']) ? $_SESSION['answers'][$questId] : array();
			
			// Check for submission
			if($this->request->getRequestMethod() == 'POST' && !is_null($this->request->getPostParam('submit')))
			{
				// Get answers
				$answers = $this->request->getPostParam('answers');
				
				// Store answers in session
				$_SESSION['answers'][$questId] = $answers;
				
				// Get right answers
				$tickQuestions = $this->Multiplechoice->getTickQuestionsOfQuest($questId);
				
				// Match tick questions with user answers
				$allSolved = true;
				foreach($tickQuestions as &$tickQuestion)
				{
					$pos = intval($tickQuestion['pos'])-1;
					if(!array_key_exists($pos, $answers) && $answers[$pos] == 'true')
					{
						$allSolved = false;
						break;
					}
					else {
						unset($answers[$pos]);
					}
				}
				
				// Set status
				if($allSolved && count($answers) == 0) {
					$this->setQuestSolved();
				}
				else {
					$this->setQuestUnsolved();
				}
			}
			
			
			// Get questions
			$questions = $this->Multiplechoice->getQuestionsOfQuest($questId);
			
			
			// Pass data to view
			$this->set('questions', $questions);
			$this->set('answers', $answers);
		}
		
	}

?>
