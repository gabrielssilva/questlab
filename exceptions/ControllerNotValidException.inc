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
	 * Exception: Controller not valid.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class ControllerNotValidException extends \nre\exceptions\ClassNotValidException
	{
		/**
		 * Error code
		 * 
		 * @var int
		 */
		const CODE	=	77;
		/**
		 * Error message
		 * 
		 * @var string
		 */
		const MESSAGE	=	'controller not valid';
		
		
		
		
		/**
		 * Construct a new exception.
		 * 
		 * @param	string	$controllerName	Name of the invalid Controller
		 */
		function __construct($controllerName)
		{
			// Elternkonstruktor aufrufen
			parent::__construct(
				$controllerName,
				self::MESSAGE,
				self::CODE
			);
		}
		
		
		
		
		/**
		 * Get the name of the invalid Controller.
		 * 
		 * @return	string	Name of the invalid Controller
		 */
		public function getControllerName()
		{
			return $this->getClassName();
		}
		
	}

?>
