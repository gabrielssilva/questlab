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
				// Get right answers
				$answers = array();
				$regexs = $this->Textinput->getTextinputRegexs($questId);
				
				// Match regexs with user answers
				$allSolved = true;
				for($i=0; $i<count($regexs); $i++)
				{
					$answer = $this->request->getPostParam('answer-'.strval($i+1));
					$answers[] = $answer;
					$score = preg_match($regexs[$i]['regex'], $answer);
					if($score === 0 || $score === false) {
						$allSolved = false;
					}
				}
				
				// Store answers in session
				$_SESSION['answers'][$questId] = $answers;
				
				// Set status
				if($allSolved) {
					$this->setQuestSolved();
				}
				else {
					$this->setQuestUnsolved();
				}
			}
			
			
			// Get Task
			$task = $this->Textinput->getTextinputQuest($questId);
			
			// Process text
			$textParts = preg_split('/(\$\$)/', $task['text'], -1, PREG_SPLIT_NO_EMPTY);
			
			
			// Pass data to view
			$this->set('text', $textParts);
			$this->set('answers', $answers);
		}
		
	}

?>
