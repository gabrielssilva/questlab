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
		 * @param	int	$questId	ID of Quest to save answers for
		 * @param	int	$characterId	ID of Character to save answers of
		 * @param	array	$answers	Character answers for the Quest
		 */
		public function saveAnswersOfCharacter($questId, $characterId, $answers)
		{
			// Get already submitted answer
			$characterSubmission = $this->Submit->getCharacterSubmission($questId, $characterId);
			
			// Save answer
			if(is_null($characterSubmission) && array_key_exists(0, $answers)) {
				$this->Submit->setCharacterSubmission($questId, $characterId, $answers[0]);
			}
		}
		
		
		/**
		 * Check if answers of a Character for a Quest match the correct ones.
		 * 
		 * @param	int	$questId	ID of Quest to match answers for
		 * @param	int	$characterId	ID of Character to match answers of
		 * @param	array	$answers	Character answers for the Quest
		 * @return	boolean			True/false for a right/wrong answer or null for moderator evaluation
		 */
		public function matchAnswersOfCharacter($questId, $characterId, $answers)
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
		 * @param	int	$questId	ID of Quest to show
		 * @param	int	$characterId	ID of Character
		 */
		public function quest($questId, $characterId)
		{
			// Answer (Submission)
			$characterSubmission = $this->Submit->getCharacterSubmission($questId, $characterId);
			
			// Wordcount
			$wordcount = 0;
			if(!is_null($characterSubmission)) {
				$wordcount = count(preg_split('/\s+/', $characterSubmission['text']));
			}
			
			
			// Pass data to view
			$this->set('submission', $characterSubmission);
			$this->set('wordcount', $wordcount);
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
			// Get Character submission
			$submission = $this->Submit->getCharacterSubmission($questId, $characterId);
			
			// Status
			$solved = $this->Quests->hasCharacterSolvedQuest($questId, $characterId);
			
			
			// Pass data to view
			$this->set('submission', $submission);
			$this->set('solved', $solved);
		}
		
	}

?>
