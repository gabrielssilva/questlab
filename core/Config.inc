<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\core;


    /**
     * Configuration.
     * 
     * This class does not hold any configuration value but helps to
     * determine values that can be hold by AppConfig or CoreConfig.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    final class Config
    {




        /**
         * Get a default value.
         * 
         * @param   string  $index  Index of value to get
         */
        public static function getDefault($index)
        {
            if(array_key_exists($index, \nre\configs\AppConfig::$defaults)) {
                return \nre\configs\AppConfig::$defaults[$index];
            }
            if(array_key_exists($index, \nre\configs\CoreConfig::$defaults)) {
                return \nre\configs\CoreConfig::$defaults[$index];
            }


            return null;
        }

    }

?>
