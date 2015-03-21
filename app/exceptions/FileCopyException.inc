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
	 * Exception: File copy went wrong
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class FileCopyException extends \nre\core\Exception
	{
		/**
		 * Error code
		 * 
		 * @var int
		 */
		const CODE	=	204;
		/**
		 * Error message
		 * 
		 * @var string
		 */
		const MESSAGE	=	'File copy went wrong';
		
		/**
		 * Nested error
		 * 
		 * @var array
		 */
		private $nestedError;
		
		
		
		
		/**
		 * Construct a new exception.
		 * 
		 * @param   array   $nestedError    Nested error
		 * @param   string  $message        Error message
		 * @param   int     $code           Error code
		 */
		function __construct($nestedError, $message=self::MESSAGE, $code=self::CODE)
		{
			parent::__construct(
				$message,
                $code,
                $nestedError['message']
			);
			
			// Store values
			$this->nestedError = $nestedError;
		}
		
		
		
		
		/**
		 * Get nested error.
		 * 
		 * @return	Nested error
		 */
		public function getNestedError()
		{
			return $this->nestedError;
		}
		
	}

?>
