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
	 * Exception during sending of an e‑mail.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MailingException extends \nre\core\Exception
	{
		/**
		 * Error code
		 * 
		 * @var int
		 */
		const CODE	=	300;
		/**
		 * Error message
		 * 
		 * @var string
		 */
		const MESSAGE	=	'Error sending e‑mail';
		
		/**
		 * Nested error message
		 * 
		 * @var string
		 */
		private $error;
		
		
		
		
		/**
		 * Construct a new exception.
		 * 
		 * @param	int	$error		Nested error message
		 * @param	string	$message	Error message
		 * @param	int	$code		Error code
		 */
		function __construct($error, $message=self::MESSAGE, $code=self::CODE)
		{
			parent::__construct(
				$message,
				$code,
				$error
			);
			
			// Store values
			$this->error = $error;
		}
		
		
		
		
		/**
		 * Get nested error message.
		 * 
		 * @return	string	Nested error message
		 */
		public function getError()
		{
			return $this->error;
		}
		
	}

?>
