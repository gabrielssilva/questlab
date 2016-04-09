<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\controllers;


    /**
     * Abstract class for implementing a StationtypeController.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    abstract class StationtypeController extends \hhu\z\Controller
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries');





        /**
         * Save the answer of a Character group for a Station.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         * @param   array   $charactergroup Current Character group data
         * @param   array   $answer         Character group answer for the Station
         */
        public abstract function saveAnswer($seminary, $groupsgroup, $quest, $station, $charactergroup, $answer);


        /**
         * Check if answer of a Character group for a Station matches the correct one.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         * @param   array   $charactergroup Current Character group data
         * @param   array   $answer         Character group answer for the Station
         * @return  boolean                 True/false for a right/wrong answer
         */
        public abstract function matchAnswer($seminary, $groupsgroup, $quest, $station, $charactergroup, $answer);


        /**
         * Action: quest.
         *
         * Show the task of a Station.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         * @param   array   $charactergroup Current Character group data
         */
        public abstract function quest($seminary, $groupsgroup, $quest, $station, $charactergroup);


        /**
         * Action: edittask.
         *
         * Edit the task of a Station.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         */
        public abstract function edittask($seminary, $groupsgroup, $quest, $station);




        /**
         * Load a StationtypeController.
         *
         * @static
         * @throws  \hhu\z\exceptions\StationtypeControllerNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeControllerNotValidException
         * @param   string  $controllerName     Name of the StationtypeController to load
         */
        public static function load($controllerName)
        {
            // Determine full classname
            $className = self::getClassName($controllerName);

            try {
                // Load class
                static::loadClass($controllerName, $className);

                // Validate class
                static::checkClass($className, get_class());
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \hhu\z\exceptions\StationtypeControllerNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \hhu\z\exceptions\StationtypeControllerNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a StationtypeController (Factory Pattern).
         *
         * @static
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeModelNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         * @param   string      $controllerName Name of the StationtypeController to instantiate
         * @param   string      $layoutName     Name of the current Layout
         * @param   string      $action         Current Action
         * @param   \nre\core\Agent $agent      Corresponding Agent
         */
        public static function factory($controllerName, $layoutName, $action, $agent)
        {
            // Determine full classname
            $className = self::getClassName($controllerName);

            // Construct and return Controller
            return new $className($layoutName, $action, $agent);
        }


        /**
         * Determine the Controller-classname for the given Stationtype-name.
         *
         * @static
         * @param   string  $stationtypeName    Stationtype-name to get Controller-classname of
         * @return  string                      Classname for the Stationtype-name
         */
        private static function getClassName($stationtypeName)
        {
            $className = \nre\core\ClassLoader::concatClassNames(
                $stationtypeName,
                \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripNamespace(get_class())),
                'controller'
            );


            return \nre\configs\AppConfig::$app['namespace']."stationtypes\\$className";
        }


        /**
         * Load the class of a StationtypeController
         *
         * @static
         * @throws  \nre\exceptions\ClassNotFoundException
         * @param   string  $stationtypeName    Name of the StationtypeController to load
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
         * Check inheritance of the StationtypeController-class.
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
         * Construct a new application Controller.
         *
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeModelNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         * @param   string  $layoutName Name of the current Layout
         * @param   string  $action     Current Action
         * @param   Agent   $agent      Corresponding Agent
         */
        public function __construct($layoutName, $action, $agent)
        {
            parent::__construct($layoutName, $action, $agent);
        }




        /**
         * Load the Models of this Controller.
         *
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeModelNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         */
        protected function loadModels()
        {
            // Load default models
            parent::loadModels();

            // Load StationtypeModel
            $this->loadModel();
        }


        /**
         * Load the Model of the Stationtype.
         *
         * @throws  \hhu\z\exceptions\StationtypeModelNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         */
        private function loadModel()
        {
            // Determine Model
            $model = \nre\core\ClassLoader::stripClassType(
                \nre\core\ClassLoader::stripClassType(
                    \nre\core\ClassLoader::stripNamespace(
                        get_class($this)
                    )
                )
            );

            // Load class
            \hhu\z\models\StationtypeModel::load($model);

            // Construct Model
            $modelName = ucfirst(strtolower($model));
            $this->$modelName = \hhu\z\models\StationtypeModel::factory($model);
        }


        /**
         * Load the View of this StationtypeController.
         *
         * @throws  \nre\exceptions\ViewNotFoundException
         * @param   string  $layoutName Name of the current Layout
         * @param   string  $action     Current Action
         */
        protected function loadView($layoutName, $action)
        {
            // Check Layout name
            if(is_null($layoutName)) {
                return;
            }

            // Determine controller name
            $controllerName = \nre\core\ClassLoader::stripClassType(
                \nre\core\ClassLoader::getClassName(
                    get_class($this)
                )
            );


            // Load view
            $this->view = \hhu\z\views\StationtypeView::loadAndFactory(
                $layoutName,
                $controllerName,
                $action
            );
        }

    }

?>
