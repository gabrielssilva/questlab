<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\exceptions;
	
	
	/**
	 * Exception: QuesttypeAgent not valid.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuesttypeAgentNotValidException extends \nre\core\Exception
	{
		/**
		 * Error code
		 * 
		 * @var int
		 */
		const CODE	=	102;
		/**
		 * Error message
		 * 
		 * @var string
		 */
		const MESSAGE	=	'QuesttypeAgent not valid';
		
		/**
		 * Name of the invalid class
		 * 
		 * @var string
		 */
		private $questtypeName;
		
		
		
		
		/**
		 * Construct a new exception.
		 * 
		 * @param	string	$questtypeName	Name of the invalid QuesttypeAgent
		 * @param	string	$message	Error message
		 * @param	int	$code		Error code
		 */
		function __construct($questtypeName, $message=self::MESSAGE, $code=self::CODE)
		{
			parent::__construct(
				$message,
				$code,
				$questtypeName
			);
			
			// Store value
			$this->questtypeName = $questtypeName;
		}
		
		
		
		
		/**
		 * Get the name of the invalid QuesttypeAgent.
		 * 
		 * @return	string	Name of the invalid QuesttypeAgent
		 */
		public function getClassName()
		{
			return $this->questtypeName;
		}
		
	}

?>
