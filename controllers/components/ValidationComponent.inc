<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\controllers\components;


    /**
     * Component to validate user input.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
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
         * @param   mixed   $input      User input to validate
         * @param   array   $settings   Validation setting
         * @return  mixed               True or the settings the validation fails on
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
         * Validate an user input parameter.
         *
         * @param   array   $params User input parameters
         * @param   array   $index  Names of parameter to validate and to validate against
         * @return  mixed           True or the parameter with settings the validation failed on
         */
        public function validateParam($params, $index)
        {
            // Check parameter
            if(!array_key_exists($index, $params)) {
                throw new \nre\exceptions\ParamsNotValidException($index);
            }
            // Check settings
            if(!array_key_exists($index, $this->config)) {
                return true;
            }


            // Validate parameter and return result
            return $this->validate($params[$index], $this->config[$index]);
        }


        /**
         * Validate user input parameters.
         *
         * @param   array   $params     User input parameters
         * @param   array   $indices    Names of parameters to validate and to validate against
         * @return  mixed               True or the parameters with settings the validation failed on
         */
        public function validateParams($params, $indices)
        {
            // Validate parameters
            $validation = true;
            foreach($indices as $index) {
                $validation = $this->addValidationResults($validation, $index, $this->validateParam($params, $index));
            }


            // Return validation results
            return $validation;
        }


        /**
         * Add a custom determined validation result to a validation
         * array.
         *
         * @param   mixed   $validation Validation array to add result to
         * @param   string  $index      Name of parameter of the custom validation result
         * @param   string  $setting    Name of setting of the custom validation result
         * @param   mixed   $result     Validation result
         * @return  mixed               The altered validation array
         */
        public function addValidationResult($validation, $index, $setting, $result)
        {
            // Create validation array
            if(!is_array($validation)) {
                $validation = array();
            }

            // Add validation results
            if(!array_key_exists($index, $validation)) {
                $validation[$index] = array();
            }
            $validation[$index][$setting] = $result;


            // Return new validation result
            return $validation;
        }


        /**
         * Add custom determined validation results to a validation
         * arary.
         *
         * @param   mixed   $validation Validation array to add result to
         * @param   string  $index      Name of parameter of the custom validation result
         * @param   mixed   $results    Validation result
         * @return  mixed               The altered validation array
         */
        public function addValidationResults($validation, $index, $results)
        {
            // Create validation array
            if(!is_array($validation)) {
                $validation = array();
            }

            // Add validation results
            if($results !== true) {
                $validation[$index] = $results;
            }


            // Return new validation result
            if(empty($validation)) {
                return true;
            }
            return $validation;
        }

    }

?>
