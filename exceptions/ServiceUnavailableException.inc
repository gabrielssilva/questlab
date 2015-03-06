<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	
	namespace nre\exceptions;
	
	
	/**
	 * Exception: Service is unavailable.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class ServiceUnavailableException extends \nre\core\Exception
	{
		/**
		 * Error code
		 * 
		 * @var int
		 */
		const CODE	=	84;
		/**
		 * Error message
		 * 
		 * @var string
		 */
		const MESSAGE	=	'service unavailable';
		
		/**
		 * Throws exception
		 * 
		 * @var Exception
		 */
		private $exception;
		
		
		
		
		/**
		 * Construct a new exception.
		 * 
		 * @param	\Exception	$exception	Exception that has occurred
		 */
		function __construct($exception)
		{
			parent::__construct(
				self::MESSAGE,
				self::CODE,
				$exception->getMessage()
			);
			
			// Store values
			$this->exception = $exception;
		}
		
		
		
		
		/**
		 * Get the exception that hat occurred
		 * 
		 * @return	\Exception	Exception that has occurred
		 */
		public function getException()
		{
			return $this->exception;
		}
		
	}

?>
