<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\agents;


    /**
     * Abstract class for implementing a QuesttypeAgent.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    abstract class QuesttypeAgent extends \nre\agents\BottomlevelAgent
    {
        /**
         * Current request
         *
         * @var \nre\core\Request
         */
        private $request;
        /**
         * Current response
         *
         * @var \nre\core\Response
         */
        private $response;




        /**
         * Load a QuesttypeAgent.
         *
         * @static
         * @throws  \hhu\z\exceptions\QuesttypeAgentNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeAgentNotValidException
         * @param   string  $questtypeName  Name of the QuesttypeAgent to load
         */
        public static function load($questtypeName)
        {
            // Determine full classname
            $className = self::getClassName($questtypeName);

            try {
                // Load class
                static::loadClass($questtypeName, $className);

                // Validate class
                static::checkClass($className, get_class());
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \hhu\z\exceptions\QuesttypeAgentNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \hhu\z\exceptions\QuesttypeAgentNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a QuesttypeAgent (Factory Pattern).
         *
         * @static
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeControllerNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeControllerNotFoundException
         * @param   string      $questtypeName  Name of the QuesttypeAgent to instantiate
         * @param   Request     $request    Current request
         * @param   Response    $response   Current respone
         * @param   Logger      $log        Log-system
         */
        public static function factory($questtypeName, \nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
        {
            // Determine full classname
            $className = self::getClassName($questtypeName);

            // Construct and return Questmodule
            return new $className($request, $response, $log);
        }


        /**
         * Determine the Agent-classname for the given Questtype-name.
         *
         * @static
         * @param   string  $questtypeName  Questtype-name to get Agent-classname of
         * @param   string  $agentType  Agent type of given Agent name
         * @return  string          Classname for the Questtype-name
         */
        private static function getClassName($questtypeName, $agentType=null)
        {
            $className = \nre\core\ClassLoader::concatClassNames($questtypeName, \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripNamespace(get_class())), 'agent');


            return \nre\configs\AppConfig::$app['namespace']."questtypes\\$className";
        }


        /**
         * Load the class of a QuesttypeAgent.
         *
         * @static
         * @throws  \nre\exceptions\ClassNotFoundException
         * @param   string  $questtypeName  Name of the QuesttypeAgent to load
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
         * Check inheritance of the QuesttypeAgent-class.
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
         * Construct a new QuesttypeAgent.
         *
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeControllerNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeControllerNotFoundException
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         * @param   \nre\core\Logger    $log        Log-system
         */
        protected function __construct(\nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
        {
            // Store values
            $this->request = $request;
            $this->response = $response;


            // Call parent constructor
            parent::__construct($request, $response, $log);
        }




        /**
         * Save the answers of a Character for a Quest.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $answers    Character answers for the Quest
         */
        public function saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
        {
            $this->controller->saveAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers);
        }


        /**
         * Check if answers of a Character for a Quest match the correct ones.
         *
         * @param   array   $seminary   Current Seminary data
         * @param   array   $questgroup Current Questgroup data
         * @param   array   $quest      Current Quest data
         * @param   array   $character  Current Character data
         * @param   array   $answers    Character answers for the Quest
         */
        public function matchAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers)
        {
            return $this->controller->matchAnswersOfCharacter($seminary, $questgroup, $quest, $character, $answers);
        }




        /**
         * Load the Controller of this Agent.
         *
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeModelNotFoundException
         * @throws  \hhu\z\exceptions\QuesttypeControllerNotValidException
         * @throws  \hhu\z\exceptions\QuesttypeControllerNotFoundException
         */
        protected function loadController()
        {
            // Determine Controller name
            $controllerName = \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::getClassName(get_class($this)));

            // Determine ToplevelAgent
            $toplevelAgentName = $this->response->getParam(0);
            if(is_null($toplevelAgentName)) {
                $toplevelAgentName = $this->request->getParam(0, 'toplevel');
                $this->response->addParam($toplevelAgentName);
            }

            // Determine Action
            $action = $this->response->getParam(2);
            if(is_null($action)) {
                $action = $this->request->getParam(2, 'action');
                $this->response->addParam($action);
            }


            // Load Controller
            \hhu\z\controllers\QuesttypeController::load($controllerName);

            // Construct Controller
            $this->controller = \hhu\z\controllers\QuesttypeController::factory($controllerName, $toplevelAgentName, $action, $this);
        }

    }

?>
