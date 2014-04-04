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
	 * Controller of the SubmitQuesttypeAgent for a submit task.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class SubmitQuesttypeController extends \hhu\z\QuesttypeController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('quests');
		
		
		
		
		/**
		 * Save the answers of a Character for a Quest.
		 * 
		 * @throws	SubmissionNotValidException
		 * @param	array	$seminary	Current Seminary data
		 * @param	array	$questgroup	Current Questgroup data
		 * @param	array	$quest		Current Quest data
		 * @param	array	$character	Current Character data
		 * @param	array	$answers	Character answers for the Quest
		 */
		public function saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
		{
			// Get already submitted answer
			$characterSubmission = $this->Submit->getCharacterSubmission($quest['id'], $character['id']);
			
			// Save answer
			if(is_null($characterSubmission) && array_key_exists('answers', $_FILES))
			{
				$answer = $_FILES['answers'];
				
				// Check mimetype
				$mimetypes = $this->Submit->getAllowedMimetypes($seminary['id']);
				$answerMimetype = null;
				foreach($mimetypes as &$mimetype) {
					if($mimetype['mimetype'] == $answer['type']) {
						$answerMimetype = $mimetype;
						break;
					}
				}
				
				// Check file
				if(is_null($answerMimetype)) {
					throw new \hhu\z\exceptions\SubmissionNotValidException(
						new \hhu\z\exceptions\WrongFiletypeException()
					);
				}
				if($answer['size'] > $answerMimetype['size']) {
					throw new \hhu\z\exceptions\SubmissionNotValidException(
						new \hhu\z\exceptions\MaxFilesizeException()
					);
				}
				
				// Save file
				$this->Submit->setCharacterSubmission($seminary['id'], $quest['id'], $this->Auth->getUserId(), $character['id'], $answer);
			}
		}
		
		
		/**
		 * Check if answers of a Character for a Quest match the correct ones.
		 * 
		 * @param	array	$seminary	Current Seminary data
		 * @param	array	$questgroup	Current Questgroup data
		 * @param	array	$quest		Current Quest data
		 * @param	array	$character	Current Character data
		 * @param	array	$answers	Character answers for the Quest
		 * @return	boolean			True/false for a right/wrong answer or null for moderator evaluation
		 */
		public function matchAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
		{
			// A moderator has to evaluate the answer
			return null;
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Display a big textbox to let the user enter a text that has
		 * to be evaluated by a moderator.
		 * 
		 * @param	array		$seminary	Current Seminary data
		 * @param	array		$questgroup	Current Questgroup data
		 * @param	array		$quest		Current Quest data
		 * @param	array		$character	Current Character data
		 * @param	Exception	$exception	Character submission exception
		 */
		public function quest($seminary, $questgroup, $quest, $character, $exception)
		{
			// Answer (Submission)
			$characterSubmission = $this->Submit->getCharacterSubmission($quest['id'], $character['id']);
			
			// Has Character already solved Quest?
			$solved = $this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']);
			
			// Get allowed mimetypes
			$mimetypes = $this->Submit->getAllowedMimetypes($seminary['id']);
			
			
			// Pass data to view
			$this->set('submission', $characterSubmission);
			$this->set('solved', $solved);
			$this->set('mimetypes', $mimetypes);
			$this->set('exception', $exception);
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
			// Get Character submission
			$submission = $this->Submit->getCharacterSubmission($quest['id'], $character['id']);
			
			// Status
			$solved = $this->Quests->hasCharacterSolvedQuest($quest['id'], $character['id']);
			
			
			// Pass data to view
			$this->set('submission', $submission);
			$this->set('solved', $solved);
		}
		
	}

?>
