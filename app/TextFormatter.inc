<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z;
	
	
	/**
	 * Class to format text with different syntax tags.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class TextFormatter
	{
		/**
		 * Linker to create links.
		 * 
		 * @var Linker
		 */
		private $linker;
		/**
		 * Media-Model to retrieve media data
		 * 
		 * @static
		 * @var model
		 */
		private static $Media = null;
		
		
		
		
		/**
		 * Create a new text formatter.
		 * 
		 * @param	Linker $linker	Linker to create links with
		 */
		public function __construct(\nre\core\Linker $linker)
		{
			$this->linker = $linker;
		}
		
		
		
		
		/**
		 * Format a string.
		 * 
		 * @param	string	$string	String to format
		 * @return	string		Formatted string
		 */
		public function t($string)
		{
			// Remove chars and replace linefeeds
			$string = nl2br(htmlspecialchars($string));
			
			// Handle Seminarymedia
			preg_match_all('/\[seminarymedia:(\d+)\]/iu', $string, $matches, PREG_SET_ORDER | PREG_OFFSET_CAPTURE);
			foreach($matches as &$match)
			{
				// Get Seminary media
				$seminarymediaId = intval($match[1][0]);
				$htmlImage = null;
				if(!is_null(\hhu\z\controllers\SeminaryRoleController::$seminary) && $this->loadMediaModel())
				{
					try {
						$medium = self::$Media->getSeminaryMediaById($seminarymediaId);
						$htmlImage = sprintf(
							'<img src="%s" alt="%s" />',
							$this->linker->link(array('media','seminary', \hhu\z\controllers\SeminaryRoleController::$seminary['url'],$medium['url'])),
							$medium['description']
						);
					}
					catch(\nre\exceptions\IdNotFoundException $e) {
					}
				}
				
				// Replace placholder
				$startPos = mb_strlen(substr($string, 0, $match[0][1]), 'UTF-8');
				$endPos = $startPos + mb_strlen($match[0][0]);
				$string = mb_substr($string, 0, $startPos, 'UTF-8'). $htmlImage . mb_substr($string, $endPos, null, 'UTF-8');
			}
			
			
			// Return processed string
			return $string;
		}
		
		
		
		
		/**
		 * Load the Media-Model if it is not loaded
		 * 
		 * @return	boolean	Whether the Media-Model has been loaded or not
		 */
		private function loadMediaModel()
		{
			// Do not load Model if it has already been loaded
			if(!is_null(self::$Media)) {
				return true;
			}
			
			try {
				// Load class
				Model::load('media');
			
				// Construct Model
				self::$Media = Model::factory('media');
			}
			catch(\Exception $e) {
			}
			
			
			// Return whether Media-Model has been loaded or not
			return !is_null(self::$Media);
		}
		
	}

?>
