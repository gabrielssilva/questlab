<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	 
	namespace hhu\z\requests;
	
	
	/**
	 * Representation of a mail-request.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MailRequest extends \nre\core\Request
	{
		/**
		 * Linker
		 * 
		 * @var Linker
		 */
		private $linker = null;
		
		
		
		
		/**
		 * Add a parameter.
		 * 
		 * @param	mixed	$value	Value of parameter
		 */
		public function addParam($value)
		{
			$this->params[] = $value;
		}
		
		
		/**
		 * Add multiple parameters.
		 * 
		 * @param	mixed	$value1	Value of first parameter
		 * @param	mixed	…	Values of further parameters
		 */
		public function addParams($value1)
		{
			$this->params = array_merge(
				$this->params,
				func_get_args()
			);
		}
		
		
		/**
		 * Delete all stored parameters (from offset on).
		 * 
		 * @param	int	$offset	Offset-index
		 */
		public function clearParams($offset=0)
		{
			$this->params = array_slice($this->params, 0, $offset);
		}
		
		
		/**
		 * Set linker instance for creating links.
		 * 
		 * @param	Linker	$linker	Linker instance for creating links
		 */
		public function setLinker(\nre\core\Linker $linker)
		{
			$this->linker = $linker;
		}
		
		
		/**
		 * Get linker instance for creating links.
		 * 
		 * @return	Linker	Linker instance for creating links
		 */
		public function getLinker()
		{
			return $this->linker;
		}
		
	}

?>
