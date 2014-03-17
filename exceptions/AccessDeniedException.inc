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
	 * Exception: Access denied.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class AccessDeniedException extends \nre\core\Exception
	{
		/**
		 * Error code
		 * 
		 * @var int
		 */
		const CODE	=	85;
		/**
		 * Error message
		 * 
		 * @var string
		 */
		const MESSAGE	=	'access denied';
		
		
		
		
		/**
		 * Consturct a new exception.
		 */
		function __construct()
		{
			parent::__construct(
				self::MESSAGE,
				self::CODE
			);
		}
		
	}

?>
