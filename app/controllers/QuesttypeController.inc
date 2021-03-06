<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\controllers;


    /**
     * Abstract class for implementing a QuesttypeController.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    abstract class QuesttypeController extends \hhu\z\Controller
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'questgroups', 'quests', 'characters');




        /**
         * Save the answers of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $answers    Character answers for the Quest
         */
        public abstract function saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers);


        /**
         * Save additional data for the answers of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $data       Additional (POST-) data
         */
        public abstract function saveDataForCharacterAnswers($seminary, $questgroup, $quest, $character, $data);


        /**
         * Check if answers of a Character for a Quest match the correct ones.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $answers    Character answers for the Quest
         * @return  boolean         True/false for a right/wrong answer or null for moderator evaluation
         */
        public abstract function matchAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers);


        /**
         * Action: quest.
         *
         * Show the task of a Quest.
         *
         * @param   array       $seminary   Current Seminary data
         * @param   array       $questgroup Current Questgroup data
         * @param   array       $quest      Current Quest data
         * @param   array       $character  Current Character data
         * @param   \Exception  $exception  Character submission exception
         */
        public abstract function quest($seminary, $questgroup, $quest, $character, $exception);


        /**
         * Action: submission.
         *
         * Show the submission of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         */
        public abstract function submission($seminary, $questgroup, $quest, $character);


        /**
         * Action: edittask.
         *
         * Edit the task of a Quest.
         *
         * @param   array       $seminary   Current Seminary data
         * @param   array       $questgroup Current Questgroup data
         * @param   array       $quest      Current Quest data
         */
        public abstract function edittask($seminary, $questgroup, $quest);




        /**
         * Load a QuesttypeController.
         *
         * @static
         * @throws  \hhu\z\exceptions\QuesttypeControllerNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeControllerNotValidException
         * @param   string  $controllerName     Name of the QuesttypeController to load
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
                throw new \hhu\z\exceptions\QuesttypeControllerNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \hhu\z\exceptions\QuesttypeControllerNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a QuesttypeController (Factory Pattern).
         *
         * @static
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
         * @param   string      $controllerName Name of the QuesttypeController to instantiate
         * @param   string      $layoutName Name of the current Layout
         * @param   string      $action     Current Action
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
         * Determine the Controller-classname for the given Questtype-name.
         *
         * @static
         * @param   string  $questtypeName  Questtype-name to get Controller-classname of
         * @return  string          Classname for the Questtype-name
         */
        private static function getClassName($questtypeName)
        {
            $className = \nre\core\ClassLoader::concatClassNames($questtypeName, \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripNamespace(get_class())), 'controller');


            return \nre\configs\AppConfig::$app['namespace']."questtypes\\$className";
        }


        /**
         * Load the class of a QuesttypeController
         *
         * @static
         * @throws  \nre\exceptions\ClassNotFoundException
         * @param   string  $questtypeName  Name of the QuesttypeController to load
         * @param   string  $fullClassName  Name of the class to load
         */
        private static function loadClass($questtypeName, $fullClassName)
        {
            // Determine folder to look in
            $className = explode('\\', $fullClassName);
            $className = array_pop($className);

            // Determine filename
            $fileName = ROOT.DS.\nre\configs\AppConfig::$dirs['questtypes'].DS.strtolower($questtypeName).DS.$className.\nre\configs\CoreConfig::getFileExt('includes');

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
         * Check inheritance of the QuesttypeController-class.
         *
         * @static
         * @throws  \nre\exceptions\ClassNotValidException
         * @param   string  $className      Name of the class to check
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
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
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
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
         */
        protected function loadModels()
        {
            // Load default models
            parent::loadModels();

            // Load QuesttypeModel
            $this->loadModel();
        }


        /**
         * Load the Model of the Questtype.
         *
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
         */
        private function loadModel()
        {
            // Determine Model
            $model = \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripNamespace(get_class($this))));

            // Load class
            \hhu\z\models\QuesttypeModel::load($model);

            // Construct Model
            $modelName = ucfirst(strtolower($model));
            $this->$modelName = \hhu\z\models\QuesttypeModel::factory($model);
        }


        /**
         * Load the View of this QuesttypeController.
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
            $controllerName = \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::getClassName(get_class($this)));


            // Load view
            $this->view = \hhu\z\views\QuesttypeView::loadAndFactory($layoutName, $controllerName, $action);
        }

    }

?>
