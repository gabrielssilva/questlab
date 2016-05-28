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
     * Abstract class for the implementation af an Agent.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    abstract class Agent
    {
        /**
         * Name of BottomlevelAgent for showing inline errors
         * 
         * @var string
         */
        const INLINEERROR_AGENT        =    'inlineerror';

        /**
         * Current request
         * 
         * @var Request
         */
        private $request;
        /**
         * Current response
         * 
         * @var Response
         */
        private $response;
        /**
         * Log-system
         * 
         * @var Logger
         */
        protected $log;
        /**
         * SubAgents
         * 
         * @var array
         */
        protected $subAgents = array();
        /**
         * Controller of this Agent
         * 
         * @var Controller
         */
        public $controller = null;




        /**
         * Load the class of an Agent.
         * 
         * @static
         * @throws  \nre\exceptions\AgentNotFoundException
         * @throws  \nre\exceptions\AgentNotValidException
         * @param   string  $agentName  Name of the Agent to load
         */
        public static function load($agentName)
        {
            // Determine full classname
            $agentType = self::getAgentType();
            $className = self::getClassName($agentName, $agentType);

            try {
                // Load class
                ClassLoader::load($className);

                // Validate class
                $parentAgentClassName = ClassLoader::concatClassNames($agentType, 'agent');
                $parentAgentClassName = "\\nre\\agents\\$parentAgentClassName";
                ClassLoader::check($className, $parentAgentClassName);
            }
            catch(\nre\exceptions\ClassNotValidException $e) {
                throw new \nre\exceptions\AgentNotValidException($e->getClassName());
            }
            catch(\nre\exceptions\ClassNotFoundException $e) {
                throw new \nre\exceptions\AgentNotFoundException($e->getClassName());
            }
        }



        /**
         * Instantiate an Agent (Factory Pattern).
         * 
         * @static
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ControllerNotValidException
         * @throws  \nre\exceptions\ControllerNotFoundException
         * @param   string      $agentName  Name of the Agent to instantiate
         * @param   Request     $request    Current request
         * @param   Response    $response   Current respone
         * @param   Logger      $log        Log-system
         */
        public static function factory($agentName, Request $request, Response $response, Logger $log=null)
        {
            // Determine full classname
            $agentType = self::getAgentType();
            $className = self::getClassName($agentName, $agentType);


            // Construct and return Agent
            return new $className($request, $response, $log);
        }


        /**
         * Determine the type of an Agent.
         * 
         * @static
         * @return    string    Agent type
         */
        private static function getAgentType()
        {
            return strtolower(ClassLoader::getClassName(get_called_class()));
        }


        /**
         * Determine the classname for the given Agent name.
         * 
         * @static
         * @param   string  $agentName  Agent name to get classname of
         * @param   string  $agentType  Agent type of given Agent name
         * @return  string              Classname for the Agent name
         */
        private static function getClassName($agentName, $agentType)
        {
            $className = ClassLoader::concatClassNames($agentName, 'agent');


            return \nre\configs\AppConfig::$app['namespace']."agents\\$agentType\\$className";
        }




        /**
         * Construct a new Agent.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ControllerNotValidException
         * @throws  \nre\exceptions\ControllerNotFoundException
         * @param   Request     $request    Current request
         * @param   Response    $response   Current response
         * @param   Logger      $log        Log-system
         */
        protected function __construct(Request $request, Response $response, Logger $log=null)
        {
            // Store values
            $this->request = $request;
            $this->response = $response;
            $this->log = $log;

            // Construct SubAgent
            $this->actionConstruct();

            // Load corresponding Controller
            $this->loadController();
        }




        /**
         * Run the Controller of this Agent and its SubAgents.
         * 
         * @throws  \nre\exceptions\ParamsNotValidException
         * @throws  \nre\exceptions\IdNotFoundException
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\ActionNotFoundException
         * @param   Request     $request    Current request
         * @param   Response    $response   Current response
         * @return  \Exception              Last occurred exception of SubAgents
         */
        public function run(Request $request, Response $response)
        {
            // Check Controller
            if(!is_null($this->controller))
            {
                // Call prefilter
                $this->controller->preFilter($request, $response);

                // Run controller
                $this->controller->run($request, $response);

                // Call postfilter
                $this->controller->postFilter($request, $response);
            }


            // Run SubAgents
            $exception = null;
            foreach($this->subAgents as &$subAgent)
            {
                try {
                    $subAgent['object']->run(
                        $request,
                        $subAgent['response']
                    );
                }
                 catch(ParamsNotValidException $e) {
                     $subAgent = $this->errorInline($subAgent, $request, $e);
                 }
                 catch(IdNotFoundException $e) {
                     $subAgent = $this->errorInline($subAgent, $request, $e);
                 }
                 catch(DatamodelException $e) {
                     $exception = $e;
                     $subAgent = $this->errorInline($subAgent, $request, $e);
                 }
                catch(ActionNotFoundException $e) {
                    $subAgent = $this->errorInline($subAgent, $request, $e);
                }
            }


            // Return last occurred exception
            return $exception;
        }


        /**
         * Generate output of the Controller of this Agent and its
         * SubAgents.
         * 
         * @param   array   $data   View data
         * @return  string          Generated output
         */
        public function render($data=array())
        {
            // Check Controller
            if(!is_null($this->controller))
            {
                // Render SubAgents
                foreach($this->subAgents as $subAgent)
                {
                    $label = array_key_exists('label', $subAgent) ? $subAgent['label'] : $subAgent['name'];
                    $data[$label] = $this->renderSubAgent($subAgent);
                }

                // Render the Controller of this agent
                return $this->controller->render($data);
            }
        }




        /**
         * Construct SubAgents (per Action).
         */
        protected function actionConstruct()
        {
            // Action ermitteln
            $action = $this->response->getParam(2);
            if(is_null($action)) {
                $action = $this->request->getParam(2, 'action');
                $this->response->addParam($action);
            }

            // Initialisierungsmethode für diese Action ausführen
            if(method_exists($this, $action))
            {
                call_user_func_array(
                    array(
                        $this,
                        $action
                    ),
                    array(
                        $this->request,
                        $this->response
                    )
                );
            }
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
         * @throws  \nre\exceptions\ControllerNotValidException
         * @throws  \nre\exceptions\ControllerNotFoundException
         */
        protected function loadController()
        {
            // Determine Controller name
            $controllerName = ClassLoader::getClassName(get_class($this));

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
            Controller::load($controllerName);

            // Construct Controller
            $this->controller = Controller::factory($controllerName, $toplevelAgentName, $action, $this);
        }


        /**
         * Log an error.
         * 
         * @param   \Exception  $exception  Occurred exception
         * @param   int         $logMode    Log mode
         */
        protected function log($exception, $logMode)
        {
            if(is_null($this->log)) {
                return;
            }

            $this->log->log(
                $exception->getMessage(),
                $logMode
            );
        }


        /**
         * Load a SubAgent and add it.
         * 
         * @throws  \nre\exceptions\ServiceUnavailableException
         * @throws  \nre\exceptions\AgentNotFoundException
         * @throws  \nre\exceptions\AgentNotValidException
         * @param   string  $agentName  Name of the Agent to load
         * @param   mixed   …           Additional parameters for the agent
         */
        protected function addSubAgent($agentName)
        {
            try {
                call_user_func_array(
                    array(
                        $this,
                        '_addSubAgent'
                    ),
                    func_get_args()
                );
            }
            catch(DatamodelException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
        }


        /**
         * Load a SubAgent and add it.
         * 
         * @throws  \nre\exceptions\ServiceUnavailableException
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\AgentNotFoundException
         * @throws  \nre\exceptions\AgentNotValidException
         * @param   string  $agentName  Name of the Agent to load
         * @param   mixed   …           Additional parameters for the agent
         */
        protected function _addSubAgent($agentName)
        {
            try {
                // Load Agent
                \nre\agents\BottomlevelAgent::load($agentName);

                // Construct Agent
                $this->subAgents[] = call_user_func_array(
                    array(
                        $this,
                        'newSubAgent'
                    ),
                    func_get_args()
                 );
            }
            catch(ViewNotFoundException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
            catch(DriverNotValidException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
            catch(DriverNotFoundException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
            catch(ModelNotValidException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
            catch(ModelNotFoundException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
            catch(ControllerNotValidException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
            catch(ControllerNotFoundException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
            catch(AgentNotValidException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
            catch(AgentNotFoundException $e) {
                $this->subAgents[] = $this->newInlineError($agentName, $e);
            }
        }




        /**
         * Create a new SubAgent.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @param   string  $agentName  Agent name
         * @return  array               SubAgent
         */
        private function newSubAgent($agentName)
        {
            // Response
            $response = clone $this->response;
            $response->clearParams(1);
            $params = func_get_args();
            if(count($params) < 2 || empty($params[1])) { 
                $params[1] = \nre\configs\CoreConfig::$defaults['action'];
            }
            call_user_func_array(
                array(
                    $response,
                    'addParams'
                ),
                $params
            );

            return array(
                'name'        =>    strtolower($agentName),
                'response'    =>    $response,
                'object'    =>    \nre\agents\BottomlevelAgent::factory(
                    $agentName,
                    $this->request,
                    $response,
                    $this->log
                )
            );
        }


        /**
         * Render a SubAgent.
         * 
         * @param   array   $subAgent   SubAgent to render
         * @return  string              Generated output
         */
        private function renderSubAgent(&$subAgent)
        {
            // Check for InlineError
            if(array_key_exists('inlineerror', $subAgent) && !empty($subAgent['inlineerror'])) {
                return file_get_contents($subAgent['inlineerror']);
            }


            // Rendern SubAgent and return its output
            return $subAgent['object']->render();
        }


        /**
         * Handle the exception of a SubAgent.
         * 
         * @param   array       $subAgent   Original (Sub-) Agent
         * @param   Request     $request    Current request
         * @param   Exception   $exception  Occurred exception
         * @return  array                   InlineError-SubAgent
         */
        private function errorInline($subAgent, $request, $exception)
        {
            // Create the SubAgent for the exception
            $subAgent = $this->newInlineError($subAgent['name'], $exception);


            // Run the InlineError-SubAgent
            try {
                $subAgent['object']->run(
                    $request,
                    $subAgent['response']
                );
            }
            catch(ActionNotFoundException $e) {
                $this->log($e, Logger::LOGMODE_AUTO);
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }


            // Return the InlineError-SubAgent
            return $subAgent;
        }


        /**
         * Create a new InlineError.
         * 
         * @param   string      $label      Name of the original Agent
         * @param   \Exception  $exception  Occurred exception
         */
        private function newInlineError($label, $exception)
        {
            // Log error
            $this->log($exception, Logger::LOGMODE_AUTO);

            // Determine Agent name
            $agentName = self::INLINEERROR_AGENT;

            // Create SugAgent
            $subAgent = array();


            try {
                // Load Agenten
                \nre\agents\BottomlevelAgent::load($agentName);

                // Construct Agent
                $subAgent = $this->newSubAgent($agentName);
                $subAgent['label'] = $label;
                $subAgent['response']->addParam($exception);
            }
            catch(ViewNotFoundException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(DatamodelException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(DriverNotValidException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(DriverNotFoundException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(ModelNotValidException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(ModelNotFoundException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(ControllerNotValidException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(ControllerNotFoundException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(AgentNotValidException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }
            catch(AgentNotFoundException $e) {
                $subAgent['inlineerror'] = $this->newInlineErrorService();
            }


            // Return SubAgent
            return $subAgent;
        }


        /**
         * Handle a hardcore error that could not be handled by the
         * system.
         */
        private function newInlineErrorService()
        {
            // Read and return static error file
            return ROOT.DS.\nre\configs\CoreConfig::getClassDir('views').DS.\nre\configs\CoreConfig::$defaults['inlineErrorFile'].\nre\configs\Config::getFileExt('views');
        }

    }

?>
