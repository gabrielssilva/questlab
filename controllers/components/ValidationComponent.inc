<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\controllers\components;
	
	
	/**
	 * Component to validate user input.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class ValidationComponent extends \nre\core\Component
	{
		/**
		 * Validation settings
		 * 
		 * @var array
		 */
		private $config;
		
		
		
		
		/**
		 * Construct a new Validation-component.
		 */
		public function __construct()
		{
			// Get validation settings from configuration
			$this->config = \nre\configs\AppConfig::$validation;
		}
		
		
		
		
		/**
		 * Validate an user input.
		 * 
		 * @param	mixed	$input		User input to validate
		 * @param	array	$settings	Validation setting
		 * @return	mixed			True or the settings the validation fails on
		 */
		public function validate($input, $settings)
		{
			$validation = array();
			
			// Min string length
			if(array_key_exists('minlength', $settings) && strlen($input) < $settings['minlength']) {
				$validation['minlength'] = $settings['minlength'];
			}
			// Max string length
			if(array_key_exists('maxlength', $settings) && strlen($input) > $settings['maxlength']) {
				$validation['maxlength'] = $settings['maxlength'];
			}
			
			// Regex
			if(array_key_exists('regex', $settings) && !preg_match($settings['regex'], $input)) {
				$validation['regex'] = $settings['regex'];
			}
			
			
			// Return true or the failed fields
			if(empty($validation)) {
				return true;
			}
			return $validation;
		}
		
		
		/**
		 * Validate user input parameters.
		 * 
		 * @param	array	$params		User input parameters
		 * @param	array	$indices	Names of parameters to validate and to validate against
		 * @return	mixed			True or the parameters with settings the validation failed on
		 */
		public function validateParams($params, $indices)
		{
			$validation = array();
			foreach($indices as $index)
			{
				if(!array_key_exists($index, $params)) {
					throw new \nre\exceptions\ParamsNotValidException($index);
				}
				
				// Check parameter
				if(array_key_exists($index, $this->config))
				{
					$param = $params[$index];
					$check = $this->validate($param, $this->config[$index]);
					if($check !== true) {
						$validation[$index] = $check;
					}
				}
			}
			
			
			// Return true or the failed parameters with failed settings
			if(empty($validation)) {
				return true;
			}
			return $validation;
		}
		
		
		/**
		 * Add a custom determined validation result to a validation
		 * store.
		 * 
		 * @param	mixed	$validation	Validation store to add result to
		 * @param	string	$param		Name of parameter of the custom validation result
		 * @param	string	$setting	Name of setting of the custom validation result
		 * @param	mixed	$result		Validation result
		 * @return	mixed			The altered validation store
		 */
		public function addValidationResult($validation, $param, $setting, $result)
		{
			if(!is_array($validation)) {
				$validation = array();
			}
			if(!array_key_exists($param, $validation)) {
				$validation[$param] = array();
			}
			$validation[$param][$setting] = $result;
			
			
			return $validation;
		}
		
	}

?>
