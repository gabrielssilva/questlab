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
	 * Controller of the CrosswordQuesttypeAgent for solving a crossword.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CrosswordQuesttypeController extends \hhu\z\QuesttypeController
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
			// Get words
			$words = $this->Crossword->getWordsForQuest($quest['id']);
			
			// Iterate words
			foreach($words as &$word)
			{
				// Assemble answer for word
				$answer = '';
				if($word['vertical'])
				{
					$x = $word['pos_x'];
					$startY = $word['pos_y'];
					$endY = $startY + mb_strlen($word['word'], 'UTF-8') - 1;
					
					foreach(range($startY, $endY) as $y)
					{
						if(array_key_exists($x, $answers) && array_key_exists($y, $answers[$x]) && !empty($answers[$x][$y])) {
							$answer .= $answers[$x][$y];
						}
						else {
							$answer .= ' ';
						}
					}
				}
				else
				{
					$startX = $word['pos_x'];
					$endX = $startX + mb_strlen($word['word'], 'UTF-8') - 1;
					$y = $word['pos_y'];
					
					foreach(range($startX, $endX) as $x)
					{
						if(array_key_exists($x, $answers) && array_key_exists($y, $answers[$x]) && !empty($answers[$x][$y])) {
							$answer .= $answers[$x][$y];
						}
						else {
							$answer .= ' ';
						}
					}
				}
				
				// Save answer
				$this->Crossword->setCharacterSubmission($word['id'], $character['id'], $answer);
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
			// Get words
			$words = $this->Crossword->getWordsForQuest($quest['id']);
			
			// Iterate words
			foreach($words as &$word)
			{
				// Assemble answer for word
				$answer = '';
				if($word['vertical'])
				{
					$x = $word['pos_x'];
					$startY = $word['pos_y'];
					$endY = $startY + mb_strlen($word['word'], 'UTF-8') - 1;
					
					foreach(range($startY, $endY) as $y)
					{
						if(array_key_exists($x, $answers) && array_key_exists($y, $answers[$x]) && !empty($answers[$x][$y])) {
							$answer .= $answers[$x][$y];
						}
						else {
							$answer .= ' ';
						}
					}
				}
				else
				{
					$startX = $word['pos_x'];
					$endX = $startX + mb_strlen($word['word'], 'UTF-8') - 1;
					$y = $word['pos_y'];
					
					foreach(range($startX, $endX) as $x)
					{
						if(array_key_exists($x, $answers) && array_key_exists($y, $answers[$x]) && !empty($answers[$x][$y])) {
							$answer .= $answers[$x][$y];
						}
						else {
							$answer .= ' ';
						}
					}
				}
				
				// Check answer
				if(mb_strtolower($word['word'], 'UTF-8') != mb_strtolower($answer, 'UTF-8')) {
					return false;
				}
			}
			
			
			// All answer right
			return true;
		}
		
		
		/**
		 * Action: quest.
		 * 
		 * Display a text with lists with predefined values.
		 * 
		 * @param	array		$seminary	Current Seminary data
		 * @param	array		$questgroup	Current Questgroup data
		 * @param	array		$quest		Current Quest data
		 * @param	array		$character	Current Character data
		 * @param	Exception	$exception	Character submission exception
		 */
		public function quest($seminary, $questgroup, $quest, $character, $exception)
		{
			// Get words
			$words = $this->Crossword->getWordsForQuest($quest['id']);
			
			// Create 2D-matrix
			$matrix = array();
			$maxX = 0;
			$maxY = 0;
			foreach($words as $index => &$word)
			{
				if($this->request->getGetParam('show-answer') == 'true') {
					$word['answer'] = $this->Crossword->getCharacterSubmission($word['id'], $character['id']);
				}
				// Insert word
				if($word['vertical'])
				{
					$x = $word['pos_x'];
					$startY = $word['pos_y'];
					$endY = $startY + mb_strlen($word['word'], 'UTF-8') - 1;
					
					$matrix = array_pad($matrix, $x+1, array());
					$matrix[$x] = array_pad($matrix[$x], $endY+1, null);
					$maxX = max($maxX, $x);
					$maxY = max($maxY, $endY);
					
					foreach(range($startY, $endY) as $y)
					{
						$oldValue = (array_key_exists($x, $matrix) && array_key_exists($y, $matrix[$x]) && !is_null($matrix[$x][$y])) ? $matrix[$x][$y] : null;
						$matrix[$x][$y] = array(
							'char'		=> mb_substr($word['word'], $y-$startY, 1, 'UTF-8'),
							'indices'	=> array($index),
							'answer' 	=> null
						);
						if(!is_null($oldValue)) {
							$matrix[$x][$y]['indices'] = array_merge($matrix[$x][$y]['indices'], $oldValue['indices']);
						}
						if(array_key_exists('answer', $word))
						{
							$answer = mb_substr($word['answer'], $y-$startY, 1, 'UTF-8');
							if($answer != ' ') {
								$matrix[$x][$y]['answer'] = $answer;
							}
						}
					}
				}
				else
				{
					$startX = $word['pos_x'];
					$endX = $startX + mb_strlen($word['word'], 'UTF-8') - 1;
					$y = $word['pos_y'];
					
					$matrix = array_pad($matrix, $endX+1, array());
					$maxX = max($maxX, $endX);
					$maxY = max($maxY, $y);
					
					foreach(range($startX, $endX) as $x)
					{
						$matrix[$x] = array_pad($matrix[$x], $y+1, null);
						
						$oldValue = (array_key_exists($x, $matrix) && array_key_exists($y, $matrix[$x]) && !is_null($matrix[$x][$y])) ? $matrix[$x][$y] : null;
						$matrix[$x][$y] = array(
							'char'		=> mb_substr($word['word'], $x-$startX, 1, 'UTF-8'),
							'indices'	=> array($index),
							'answer'	=> null
						);
						if(!is_null($oldValue)) {
							$matrix[$x][$y]['indices'] = array_merge($matrix[$x][$y]['indices'], $oldValue['indices']);
						}
						if(array_key_exists('answer', $word))
						{
							$answer = mb_substr($word['answer'], $x-$startX, 1, 'UTF-8');
							if($answer != ' ') {
								$matrix[$x][$y]['answer'] = $answer;
							}
						}
					}
				}
			}
			
			
			// Pass data to view
			$this->set('words', $words);
			$this->set('maxX', $maxX);
			$this->set('maxY', $maxY);
			$this->set('matrix', $matrix);
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
			// Get words
			$words = $this->Crossword->getWordsForQuest($quest['id']);
			
			// Create 2D-matrix
			$matrix = array();
			$maxX = 0;
			$maxY = 0;
			foreach($words as $index => &$word)
			{
				// Character answer
				$word['answer'] = $this->Crossword->getCharacterSubmission($word['id'], $character['id']);
				
				// Insert word
				if($word['vertical'])
				{
					$x = $word['pos_x'];
					$startY = $word['pos_y'];
					$endY = $startY + mb_strlen($word['word'], 'UTF-8') - 1;
					
					$matrix = array_pad($matrix, $x+1, array());
					$matrix[$x] = array_pad($matrix[$x], $endY+1, null);
					$maxX = max($maxX, $x);
					$maxY = max($maxY, $endY);
					
					foreach(range($startY, $endY) as $y)
					{
						$oldValue = (array_key_exists($x, $matrix) && array_key_exists($y, $matrix[$x]) && !is_null($matrix[$x][$y])) ? $matrix[$x][$y] : null;
						$matrix[$x][$y] = array(
							'char'		=> mb_substr($word['word'], $y-$startY, 1, 'UTF-8'),
							'indices'	=> array($index),
							'answer'	=> null,
							'right'		=> false
						);
						if(!is_null($oldValue)) {
							$matrix[$x][$y]['indices'] = array_merge($matrix[$x][$y]['indices'], $oldValue['indices']);
						}
						
						if(!is_null($word['answer']))
						{
							$answer = mb_substr($word['answer'], $y-$startY, 1, 'UTF-8');
							if($answer != ' ')
							{
								$matrix[$x][$y]['answer'] = $answer;
								$matrix[$x][$y]['right'] = (mb_strtolower($matrix[$x][$y]['char'], 'UTF-8') == mb_strtolower($answer, 'UTF-8'));
							}
						}
					}
				}
				else
				{
					$startX = $word['pos_x'];
					$endX = $startX + mb_strlen($word['word'], 'UTF-8') - 1;
					$y = $word['pos_y'];
					
					$matrix = array_pad($matrix, $endX+1, array());
					$maxX = max($maxX, $endX);
					$maxY = max($maxY, $y);
					
					foreach(range($startX, $endX) as $x)
					{
						$matrix[$x] = array_pad($matrix[$x], $y+1, null);
						
						$oldValue = (array_key_exists($x, $matrix) && array_key_exists($y, $matrix[$x]) && !is_null($matrix[$x][$y])) ? $matrix[$x][$y] : null;
						$matrix[$x][$y] = array(
							'char'		=> mb_substr($word['word'], $x-$startX, 1, 'UTF-8'),
							'indices'	=> array($index),
							'answer'	=> null,
							'right'		=> false
						);
						if(!is_null($oldValue)) {
							$matrix[$x][$y]['indices'] = array_merge($matrix[$x][$y]['indices'], $oldValue['indices']);
						}
						if(!is_null($word['answer']))
						{
							$answer = mb_substr($word['answer'], $x-$startX, 1, 'UTF-8');
							if($answer != ' ')
							{
								$matrix[$x][$y]['answer'] = $answer;
								$matrix[$x][$y]['right'] = (mb_strtolower($matrix[$x][$y]['char'], 'UTF-8') == mb_strtolower($answer, 'UTF-8'));
							}
						}
					}
				}
			}
			
			
			// Pass data to view
			$this->set('words', $words);
			$this->set('maxX', $maxX);
			$this->set('maxY', $maxY);
			$this->set('matrix', $matrix);
		}
		
	}

?>
