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
     * Abstract class to implement a (Controller) Component.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    abstract class Component
    {




        /**
         * Load the class of a Component.
         * 
         * @throws  \nre\exceptions\ComponentNotFoundException
         * @throws  \nre\exceptions\ComponentNotValidException
         * @param   string  $componentName  Name of the Component to load
         */
        public static function load($componentName)
        {
            // Determine full classname
            $className = self::getClassName($componentName);

            try {
                // Load class
                ClassLoader::load($className);

                // Validate class
                ClassLoader::check($className, get_class());
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \nre\exceptions\ComponentNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \nre\exceptions\ComponentNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a Component (Factory Pattern).
         * 
         * @param   string  $componentName  Name of the Component to instantiate
         */
        public static function factory($componentName)
        {
            // Determine full classname
            $className = self::getClassName($componentName);

            // Construct and return Controller
            return new $className();
        }


        /**
         * Determine the classname for the given Component name.
         * 
         * @param   string  $componentName  Component name to get classname of
         * @return  string                  Classname for the Component name
         */
        private static function getClassName($componentName)
        {
            $className = \nre\core\ClassLoader::concatClassNames($componentName, \nre\core\ClassLoader::stripNamespace(get_class()));


            return \nre\configs\AppConfig::$app['namespace']."controllers\\components\\$className";
        }




        /**
         * Construct a new (Controller) Component.
         *
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
         * Load the Models of this Controller.
         * 
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         */
        protected function loadModels()
        {
            // Determine Models
            $explicit = false;
            $models = \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripNamespace(get_class($this)));
            if(property_exists($this, 'models'))
            {
                $models = $this->models;
                $explicit = true;
            }
            if(!is_array($models)) {
                $models = array($models);
            }
            // Models of parent classes
            $parent = $this;
            while($parent = get_parent_class($parent))
            {
                $properties = get_class_vars($parent);
                if(array_key_exists('models', $properties)) {
                    $models = array_merge($models, $properties['models']);
                }
            }
            $models = array_unique($models);

            // Load Models
            foreach($models as &$model)
            {
                try {
                    // Load class
                    Model::load($model);

                    // Construct Model
                    $modelName = ucfirst(strtolower($model));
                    $this->$modelName = Model::factory($model);
                }
                catch(\nre\exceptions\ModelNotValidException $e) {
                    if($explicit) {
                        throw $e;
                    }
                }
                catch(\nre\exceptions\ModelNotFoundException $e) {
                    if($explicit) {
                        throw $e;
                    }
                }
            }
        }

    }

?>
