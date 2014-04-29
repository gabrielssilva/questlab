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
	 * Exception: Component not valid.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class ComponentNotValidException extends \nre\exceptions\ClassNotValidException
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
		const MESSAGE	=	'component not valid';
		
		
		
		
		/**
		 * Construct a new exception.
		 * 
		 * @param	string	$componentName	Name of the invalid Component
		 */
		function __construct($componentName)
		{
			parent::__construct(
				$componentName,
				self::MESSAGE,
				self::CODE
			);
		}
		
		
		
		
		/**
		 * Get the name of the invalid Component.
		 * 
		 * @return	string	Name of the invalid Component
		 */
		public function getComponentName()
		{
			return $this->getClassName();
		}
		
	}

?>
