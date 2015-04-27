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
     * Autoloader.
     * 
     * This class tries to load not yet used classes.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class Autoloader
    {
        /**
         * Private construct().
         */
        private function __construct() {}

        /**
         * Private clone().
         */
        private function __clone() {}




        /**
         * Register load-method.
         */
        public static function register()
        {
            spl_autoload_register(
                array(
                    get_class(),
                    'load'
                )
            );
        }


        /**
         * Look for the given class and try to load it.
         * 
         * @param   string  $fullClassName  Name of class to load
         */
        public static function load($fullClassName)
        {
            $fullClassNameA = explode('\\', $fullClassName);

            if(strpos($fullClassName, \nre\configs\CoreConfig::$core['namespace']) !== 0)
            {
                // App
                $className = array_slice($fullClassNameA, substr_count(\nre\configs\AppConfig::$app['namespace'], '\\'));
                array_unshift($className, \nre\configs\CoreConfig::getClassDir('app'));
                $filename = ROOT.DS.implode(DS, $className).\nre\configs\CoreConfig::getFileExt('includes');
                if(file_exists($filename)) {
                    require_once($filename);
                }
            }
            else
            {
                // Core
                $className = array_slice($fullClassNameA, substr_count(\nre\configs\CoreConfig::$core['namespace'], '\\'));
                $filename = ROOT.DS.implode(DS, $className).\nre\configs\CoreConfig::getFileExt('includes');
                if(file_exists($filename)) {
                    require_once($filename);
                }
            }


        }


        /**
         * Determine classtype of a class.
         * 
         * @param   string  $className  Name of the class to determine the classtype of
         * @return  string              Classtype of the given class
         */
        public static function getClassType($className)
        {
            // CamelCase
            return strtolower(preg_replace('/^.*([A-Z][^A-Z]+)$/', '$1', $className));
        }

    }

?>
