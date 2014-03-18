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
	 * Controller of the Dummy-QuesttypeAgent for testing basic
	 * QuesttypeAgent-functionality.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class DummyQuesttypeController extends \hhu\z\QuesttypeController
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
			// Do nothing
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
			// Set status
			return true;
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Show the task of a Quest.
		 * 
		 * @param	int	$questId	ID of Quest to show
		 * @param	int	$characterId	ID of Character
		 */
		public function quest($questId, $characterId)
		{
			// Nothing to do
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
			// Nothing to do
		}
		
	}

?>
