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
     * Abstract class for implementing a Model.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    abstract class Model
    {




        /**
         * Load the class of a Model.
         * 
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ModelNotValidException
         * @param   string  $modelName  Name of the Model to load
         */
        public static function load($modelName)
        {
            // Determine full classname
            $className = self::getClassName($modelName);

            try {
                // Load class
                ClassLoader::load($className);

                // Validate class
                ClassLoader::check($className, get_class());
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \nre\exceptions\ModelNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \nre\exceptions\ModelNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a Model (Factory Pattern).
         * 
         * @param   string  $modelName  Name of the Model to instantiate
         */
        public static function factory($modelName)
        {
            // Determine full classname
            $className = self::getClassName($modelName);

            // Construct and return Model
            return new $className();
        }


        /**
         * Determine the classname for the given Model name.
         * 
         * @param   string  $modelName  Model name to get classname of
         * @return  string              Classname fore the Model name
         */
        private static function getClassName($modelName)
        {
            $className = ClassLoader::concatClassNames($modelName, ClassLoader::stripNamespace(get_class()));


            return \nre\configs\AppConfig::$app['namespace']."models\\$className";
        }




        /**
         * Construct a new Model.
         * 
         * TODO Catch exception
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         */
        protected function __construct()
        {
            // Load Models
            $this->loadModels();
        }




        /**
         * Load the Models of this Model.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         */
        private function loadModels()
        {
            // Determine Models
            $models = array();
            if(property_exists($this, 'models')) {
                $models = $this->models;
            }
            if(!is_array($models)) {
                $models = array($models);
            }


            // Load Models
            foreach($models as $model)
            {
                // Load class
                Model::load($model);

                // Construct Model
                $modelName = ucfirst(strtolower($model));
                $this->$modelName = Model::factory($model);
            }
        }

    }

?>
