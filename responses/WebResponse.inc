<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	 
	namespace nre\responses;
	
	
	/**
	 * Representation of a web-response.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class WebResponse extends \nre\core\Response
	{
		/**
		 * Applied GET-parameters
		 * 
		 * @var array
		 */
		private $getParams = array();
		/**
		 * Changed header lines
		 * 
		 * @var array
		 */
		private $headers = array();
		
		
		
		
		/**
		 * Add a parameter.
		 * 
		 * @param	mixed	$value	Value of parameter
		 */
		public function addParam($value)
		{
			if(array_key_exists('layout', $this->getParams)) {
				parent::addParam($value);
			}
			else {
				$this->addGetParam('layout', $value);
			}
		}
		
		
		/**
		 * Add multiple parameters.
		 * 
		 * @param	mixed	$value1	Value of first parameter
		 * @param	mixed	…	Values of further parameters
		 */
		public function addParams($value1)
		{
			$this->addParam($value1);
			
			$this->params = array_merge(
				$this->params,
				array_slice(
					func_get_args(),
					1
				)
			);
		}
		
		
		/**
		 * Delete all stored parameters (from offset on).
		 * 
		 * @param	int	$offset	Offset-index
		 */
		public function clearParams($offset=0)
		{
			if($offset == 0) {
				unset($this->getParams['layout']);
			}
			
			parent::clearParams(max(0, $offset-1));
		}
		
		
		/**
		 * Get a parameter.
		 * 
		 * @param	int	$index		Index of parameter
		 * @param	string	$defaultIndex	Index of default configuration value for this parameter
		 * @return	string			Value of parameter
		 */
		public function getParam($index, $defaultIndex=null)
		{
			if($index == 0) {
				return $this->getGetParam('layout', $defaultIndex);
			}
			else {
				return parent::getParam($index-1, $defaultIndex);
			}
		}
		
		
		/**
		 * Get all parameters from index on.
		 * 
		 * @param	int	$offset	Offset-index
		 * @return	array		Parameter values
		 */
		public function getParams($offset=0)
		{
			if($offset == 0)
			{
				if(!array_key_exists('layout', $this->getParams)) {
					return array();
				}
				
				return array_merge(
					array(
						$this->getParams['layout']
					),
					$this->params
				);
			}
			
			
			return array_slice($this->params, $offset-1);
		}
		
		
		/**
		 * Add a GET-parameter.
		 * 
		 * @param	string	$key	Key of GET-parameter
		 * @param	mixed	$value	Value of GET-parameter
		 */
		public function addGetParam($key, $value)
		{
			$this->getParams[$key] = $value;
		}
		
		
		/**
		 * Add multiple GET-parameters.
		 * 
		 * @param	array	$params	Associative arary with key-value GET-parameters
		 */
		public function addGetParams($params)
		{
			$this->getParams = array_merge(
				$this->getParams,
				$params
			);
		}
		
		
		/**
		 * Get a GET-parameter.
		 * 
		 * @param	int	$index		Index of GET-parameter
		 * @param	string	$defaultIndex	Index of default configuration value for this parameter
		 * @return	string			Value of GET-parameter
		 */
		public function getGetParam($key, $defaultIndex=null)
		{
			// Check key
			if(array_key_exists($key, $this->getParams))
			{
				// Return value
				return $this->getParams[$key];
			}
			
			// Return default value
			return \nre\core\Config::getDefault($defaultIndex);
		}
		
		
		/**
		 * Get all GET-parameters.
		 * 
		 * @return	array	All GET-parameters
		 */
		public function getGetParams()
		{
			return $this->getParams;
		}
		
		
		/**
		 * Add a line to the response header.
		 * 
		 * @param	string	$headerLine		Header line
		 * @param	bool	$replace		Replace existing header line
		 * @param	int	$http_response_code	HTTP-response code
		 */
		public function addHeader($headerLine, $replace=true, $http_response_code=null)
		{
			$this->headers[] = $this->newHeader($headerLine, $replace, $http_response_code);
		}
		
		
		/**
		 * Clear all stored headers.
		 */
		public function clearHeaders()
		{
			$this->headers = array();
		}
		
		
		/**
		 * Send stored headers.
		 */
		public function header()
		{
			foreach($this->headers as $header)
			{
				header(
					$header['string'],
					$header['replace'],
					$header['responseCode']
				);
			}
		}
		
		
		
		
		/**
		 * Create a new header line.
		 * 
		 * @param	string	$headerLine		Header line
		 * @param	bool	$replace		Replace existing header line
		 * @param	int	$http_response_code	HTTP-response code
		 */
		private function newHeader($headerLine, $replace=true, $http_response_code=null)
		{
			return array(
				'string'	=>	$headerLine,
				'replace'	=>	$replace,
				'responseCode'	=>	$http_response_code
			);
		}
		
	}

?>
