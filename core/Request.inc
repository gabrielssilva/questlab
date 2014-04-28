<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */

	namespace nre\core;
	
	
	/**
	 * Base class to represent a request.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class Request
	{
		/**
		 * Passed parameters
		 * 
		 * @var array
		 */
		protected $params = array();
		
		
		
		
		/**
		 * Get a parameter.
		 * 
		 * @param	int	$index		Index of parameter
		 * @param	string	$defaultIndex	Index of default configuration value for this parameter
		 * @return	string			Value of parameter
		 */
		public function getParam($index, $defaultIndex=null)
		{
			// Return parameter
			if(count($this->params) > $index) {
				return $this->params[$index];
			}
			
			// Return default value
			return \nre\core\Config::getDefault($defaultIndex);
		}
		
		
		/**
		 * Get all parameters from index on.
		 * 
		 * @param	int	$offset	Offset-index
		 * @return	array		Parameter values
		 */
		public function getParams($offset=0)
		{
			return array_slice($this->params, $offset);
		}
		
	}

?>
