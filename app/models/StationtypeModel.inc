<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\models;


    /**
     * Abstract class for implementing a StationtypeModel.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    abstract class StationtypeModel extends \hhu\z\Model
    {




        /**
         * Load a Model.
         *
         * @static
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeModelNotValidException
         * @param   string  $modelName  Name of the StationtypeModel to load
         */
        public static function load($modelName)
        {
            // Determine full classname
            $className = self::getClassName($modelName);

            try {
                // Load class
                static::loadClass($modelName, $className);

                // Validate class
                static::checkClass($className, get_class());
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \hhu\z\exceptions\StationtypeModelNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \hhu\z\exceptions\StationtypeModelNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a StationtypeModel (Factory Pattern).
         *
         * @static
         * @param   string  $stationtypeName    Name of the StationtypeModel to instantiate
         */
        public static function factory($stationtypeName)
        {
            // Determine full classname
            $className = self::getClassName($stationtypeName);

            // Construct and return Model
            return new $className();
        }


        /**
         * Determine the Model-classname for the given Stationtype-name.
         *
         * @static
         * @param   string  $stationtypeName    Stationtype-name to get Model-classname of
         * @return  string                      Classname for the Stationtype-name
         */
        private static function getClassName($stationtypeName)
        {
            $className = \nre\core\ClassLoader::concatClassNames(
                $stationtypeName,
                \nre\core\ClassLoader::stripClassType(
                    \nre\core\ClassLoader::stripNamespace(
                        get_class()
                    )
                ),
                'model'
            );


            return \nre\configs\AppConfig::$app['namespace']."stationtypes\\$className";
        }


        /**
         * Load the class of a StationtypeModel.
         *
         * @static
         * @throws  \nre\exceptions\ClassNotFoundException
         * @param   string  $stationtypeName    Name of the StationtypeModel to load
         * @param   string  $fullClassName      Name of the class to load
         */
        private static function loadClass($stationtypeName, $fullClassName)
        {
            // Determine folder to look in
            $className = explode('\\', $fullClassName);
            $className = array_pop($className);

            // Determine filename
            $fileName = ROOT.DS.
                \nre\configs\AppConfig::$dirs['stationtypes'].DS.
                strtolower($stationtypeName).DS.
                $className.\nre\configs\CoreConfig::getFileExt('includes');

            // Check file
            if(!file_exists($fileName))
            {
                throw new \nre\exceptions\ClassNotFoundException(
                    $fullClassName
                );
            }

            // Include file
            include_once($fileName);
        }


        /**
         * Check inheritance of the StationtypeModel-class.
         *
         * @static
         * @throws  \nre\exceptions\ClassNotValidException
         * @param   string  $className          Name of the class to check
         * @param   string  $parentClassName    Name of the parent class
         */
        public static function checkClass($className, $parentClassName)
        {
            // Check if class is subclass of parent class
            if(!is_subclass_of($className, $parentClassName)) {
                throw new \nre\exceptions\ClassNotValidException(
                    $className
                );
            }
        }




        /**
         * Construct a new StationtypeModel.
         *
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         */
        public function __construct()
        {
            parent::__construct();
        }

    }

?>
