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
	 * Exception: Class not valid.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class ClassNotValidException extends \nre\core\Exception
	{
		/**
		 * Error code
		 * 
		 * @var int
		 */
		const CODE	=	74;
		/**
		 * Error message
		 * 
		 * @var string
		 */
		const MESSAGE	=	'class not valid';
		
		/**
		 * Name of the invalid class
		 * 
		 * @var string
		 */
		private $className;
		
		
		
		
		/**
		 * Construct a new exception.
		 * 
		 * @param	string	$className	Name of the invalid class
		 * @param	string	$message	Error message (superclass)
		 * @param	int	$code		Error code (superclass)
		 */
		function __construct($className, $message=self::MESSAGE, $code=self::CODE)
		{
			parent::__construct(
				$message,
				$code,
				$className
			);
			
			// Store value
			$this->className = $className;
		}
		
		
		
		
		/**
		 * Get the name of the invalid class.
		 * 
		 * @return	string	Name of the invalid class
		 */
		public function getClassName()
		{
			return $this->className;
		}
		
	}

?>
