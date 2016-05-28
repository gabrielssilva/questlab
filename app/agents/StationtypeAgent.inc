<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\agents;


    /**
     * Abstract class for implementing a StationtypeAgent.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    abstract class StationtypeAgent extends \nre\agents\BottomlevelAgent
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
         * Load a StationtypeAgent.
         *
         * @static
         * @throws  \hhu\z\exceptions\StationtypeAgentNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeAgentNotValidException
         * @param   string  $stationtypeName    Name of the StationtypeAgent to load
         */
        public static function load($stationtypeName)
        {
            // Determine full classname
            $className = self::getClassName($stationtypeName);

            try {
                // Load class
                static::loadClass($stationtypeName, $className);

                // Validate class
                static::checkClass($className, get_class());
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \hhu\z\exceptions\StationtypeAgentNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \hhu\z\exceptions\StationtypeAgentNotFoundException($e->getClassName());
            }
        }


        /**
         * Instantiate a StationtypeAgent (Factory Pattern).
         *
         * @static
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeModelNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeControllerNotValidException
         * @throws  \hhu\z\exceptions\StationtypeControllerNotFoundException
         * @param   string      $stationtypeName    Name of the StationtypeAgent to instantiate
         * @param   Request     $request            Current request
         * @param   Response    $response           Current respone
         * @param   Logger      $log                Log-system
         */
        public static function factory($stationtypeName, \nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
        {
            // Determine full classname
            $className = self::getClassName($stationtypeName);

            // Construct and return Stationmodule
            return new $className($request, $response, $log);
        }


        /**
         * Determine the Agent-classname for the given Stationtype-name.
         *
         * @static
         * @param   string  $stationtypeName    Stationtype-name to get Agent-classname of
         * @param   string  $agentType          Agent type of given Agent name
         * @return  string                      Classname for the Stationtype-name
         */
        private static function getClassName($stationtypeName, $agentType=null)
        {
            $className = \nre\core\ClassLoader::concatClassNames(
                $stationtypeName,
                \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripNamespace(get_class())),
                'agent'
            );


            return \nre\configs\AppConfig::$app['namespace']."stationtypes\\$className";
        }


        /**
         * Load the class of a StationtypeAgent.
         *
         * @static
         * @throws  \nre\exceptions\ClassNotFoundException
         * @param   string  $stationtypeName    Name of the StationtypeAgent to load
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
                strtolower($stationtypeName).DS.$className.\nre\configs\CoreConfig::getFileExt('includes');

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
         * Check inheritance of the StationtypeAgent-class.
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
         * Construct a new StationtypeAgent.
         *
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeModelNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeControllerNotValidException
         * @throws  \hhu\z\exceptions\StationtypeControllerNotFoundException
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
         * Save the answer of a Character group for a Station.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         * @param   array   $group          Current Character group data
         * @param   array   $answer         Character group answer for the Station
         */
        public function saveAnswer($seminary, $groupsgroup, $quest, $station, $group, $answer)
        {
            $this->controller->saveAnswer(
                $seminary,
                $groupsgroup,
                $quest,
                $station,
                $group,
                $answer
            );
        }


        /**
         * Check if the answer of a Character group for a Station matches the
         * correct one.
         *
         * @param   array   $seminary       Current Seminary data
         * @param   array   $groupsgroup    Current Groups group data
         * @param   array   $quest          Current Quest data
         * @param   array   $station        Current Station data
         * @param   array   $group          Current Character group data
         * @param   array   $answer         Character group answer for the Station
         */
        public function matchAnswer($seminary, $groupsgroup, $quest, $station, $group, $answer)
        {
            return $this->controller->matchAnswer(
                $seminary,
                $groupsgroup,
                $quest,
                $station,
                $group,
                $answer
            );
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
         * @throws  \hhu\z\exceptions\StationxuesttypeModelNotValidException
         * @throws  \hhu\z\exceptions\StationtypeModelNotFoundException
         * @throws  \hhu\z\exceptions\StationtypeControllerNotValidException
         * @throws  \hhu\z\exceptions\StationtypeControllerNotFoundException
         */
        protected function loadController()
        {
            // Determine Controller name
            $controllerName = \nre\core\ClassLoader::stripClassType(
                \nre\core\ClassLoader::getClassName(get_class($this))
            );

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
            \hhu\z\controllers\StationtypeController::load($controllerName);

            // Construct Controller
            $this->controller = \hhu\z\controllers\StationtypeController::factory(
                $controllerName,
                $toplevelAgentName,
                $action,
                $this
            );
        }

    }

?>
