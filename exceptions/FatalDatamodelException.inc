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
	 * Exception: Datamodel exception that is fatal for the application.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class FatalDatamodelException extends \nre\core\Exception
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
		const MESSAGE	=	'fatal datamodel error';
		
		/**
		 * Error message of datamodel
		 * 
		 * @var string
		 */
		private $datamodelMessage;
		/**
		 * Error code of datamodel
		 * 
		 * @var int
		 */
		private $datamodelErrorNumber;
		
		
		
		
		/**
		 * Consturct a new exception.
		 * 
		 * @param	string	$datamodelMessage	Error message of datamodel
		 * @param	int	$datamodelErrorNumber	Error code of datamodel
		 */
		function __construct($datamodelMessage, $datamodelErrorNumber)
		{
			parent::__construct(
				self::MESSAGE,
				self::CODE,
				$datamodelMessage." ($datamodelErrorNumber)"
			);
			
			// Store values
			$this->datamodelMessage = $datamodelMessage;
			$this->datamodelErrorNumber = $datamodelErrorNumber;
		}
		
		
		
		
		/**
		 * Get the error message of datamodel.
		 * 
		 * @return 	string	Error message of datamodel
		 */
		public function getDatamodelMessage()
		{
			return $this->datamodelMessage;
		}
		
		
		/**
		 * Get the error code of datamodel.
		 * 
		 * @return 	string	Error code of datamodel
		 */
		public function getDatamodelErrorNumber()
		{
			return $this->datamodelErrorNumber;
		}
		
	}

?>
