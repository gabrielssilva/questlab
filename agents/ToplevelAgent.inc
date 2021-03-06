<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\agents;


    /**
     * The ToplevelAgent assumes the task of a FrontController. There is
     * only one per request.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class ToplevelAgent extends \nre\core\Agent
    {
        /**
         * Stage: Load
         * 
         * @var string
         */
        const STAGE_LOAD    =    'load';
        /**
         * Stage: Run
         * 
         * @var string
         */
        const STAGE_RUN        =    'run';
        
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
         * Layout instace
         * 
         * @var \nre\core\Layout
         */
        private $layout = null;
        /**
         * IntermediateAgent instance
         * 
         * @var IntermediateAgent
         */
        private $intermediateAgent = null;




        /**
         * Construct a ToplevelAgent.
         * 
         * @throws  \nre\exceptions\ServiceUnavailableException
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotValidException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\ViewNotFoundException
         * @throws  \nre\exceptions\ModelNotValidException
         * @throws  \nre\exceptions\ModelNotFoundException
         * @throws  \nre\exceptions\ControllerNotValidException
         * @throws  \nre\exceptions\ControllerNotFoundException
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         * @param   \nre\core\Logger    $log        Log-system
         */
        protected function __construct(\nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
        {
            // Store values
            $this->request = $request;
            $this->response = $response;


            // Create response
            $response = clone $response;
            $response->clearParams(1);
            $response->addParams(
                null,
                \nre\configs\CoreConfig::$defaults['action']
            );
            
            // Call parent constructor
            parent::__construct($request, $response, $log, true);
            
            
            // Load IntermediateAgent
            $this->loadIntermediateAgent();
        }




        /**
         * Run the Controller of this Agent and its SubAgents.
         * 
         * @throws  \nre\exceptions\ServiceUnavailableException
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         * @return  \Exception                      Last occurred exception of SubAgents
         */
        public function run(\nre\core\Request $request, \nre\core\Response $response)
        {
            try {
                return $this->_run($request, $response);
            }
            catch(\nre\exceptions\AccessDeniedException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_FORBIDDEN, self::STAGE_RUN);
            }
            catch(\nre\exceptions\ParamsNotValidException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND, self::STAGE_RUN);
            }
            catch(\nre\exceptions\IdNotFoundException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND, self::STAGE_RUN);
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE, self::STAGE_RUN);
            }
            catch(\nre\exceptions\ActionNotFoundException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND, self::STAGE_RUN);
            }
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
            // Render IntermediateAgent
            $data = array();
            $data['intermediate'] = $this->intermediateAgent->render();


            // Render ToplevelAgent
            return parent::render($data);
        }


        /**
         * Return the IntermediateAgent.
         * 
         * @return  \nre\agents\IntermediateAgent   IntermediateAgent
         */
        public function getIntermediateAgent()
        {
            return $this->intermediateAgent;
        }




        /**
         * Load a SubAgent and add it.
         * 
         * @throws  \nre\exceptions\ServiceUnavailableException
         * @throws  \nre\exceptions\FatalDatamodelException
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
            catch(\nre\exceptions\DatamodelException $e) {
                throw new \nre\exceptions\FatalDatamodelException($e->getDatamodelMessage(), $e->getDatamodelErrorNumber());
            }
        }




        /**
         * Load IntermediateAgent defined by the current request.
         * 
         * @throws  \nre\exceptions\ServiceUnavailableException
         */
        private function loadIntermediateAgent()
        {
            try {
                $this->_loadIntermediateAgent();
            }
            catch(\nre\exceptions\ViewNotFoundException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND);
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
            }
            catch(\nre\exceptions\DriverNotValidException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
            }
            catch(\nre\exceptions\DriverNotFoundException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
            }
            catch(\nre\exceptions\ModelNotValidException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
            }
            catch(\nre\exceptions\ModelNotFoundException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
            }
            catch(\nre\exceptions\ControllerNotValidException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
            }
            catch(\nre\exceptions\ControllerNotFoundException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND);
            }
            catch(\nre\exceptions\AgentNotValidException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
            }
            catch(\nre\exceptions\AgentNotFoundException $e) {
                $this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND);
            }
        }


        /**
         * Load IntermediateAgent defined by the current request.
         * 
         * @throws  \nre\exceptions\ServiceUnavailableException
         */
        private function _loadIntermediateAgent()
        {
            // Determine IntermediateAgent
            $agentName = $this->response->getParam(1);
            if(is_null($agentName)) {
                $agentName = $this->request->getParam(1, 'intermediate');
                $this->response->addParam($agentName);
            }

            // Load IntermediateAgent
            IntermediateAgent::load($agentName);


            // Determine Action
            $action = $this->response->getParam(2);
            if(is_null($action)) {
                $action = $this->request->getParam(2, 'action');
                $this->response->addParam($action);
            }

            // Construct IntermediateAgent
            $this->intermediateAgent = \nre\agents\IntermediateAgent::factory(
                $agentName,
                $this->request,
                $this->response,
                $this->log
            );
        }


        /**
         * Run the Controller of this Agent and its SubAgents.
         * 
         * @throws  \nre\exceptions\AccessDeniedException
         * @throws  \nre\exceptions\IdNotFoundException
         * @throws  \nre\exceptions\ServiceUnavailableException
         * @throws  \nre\exceptions\DatamodelException
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         * @return  \Exception                      Last occurred exception of SubAgents
         */
        private function _run(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Run IntermediateAgent
            $this->runIntermediateAgent();


            // TODO Request instead of response?
            $response = clone $response;
            $response->clearParams(2);
            $response->addParam(\nre\configs\CoreConfig::$defaults['action']);


            // Run ToplevelAgent
            return parent::run($request, $response);
        }


        /**
         * Run IntermediateAgent.
         * 
         * @throws  \nre\exceptions\AccessDeniedException
         * @throws  \nre\exceptions\ParamsNotValidException
         * @throws  \nre\exceptions\IdNotFoundException
         * @throws  \nre\exceptions\ServiceUnavailableException
         * @throws  \nre\exceptions\DatamodelException
         */
        private function runIntermediateAgent()
        {
            $this->intermediateAgent->run(
                $this->request,
                $this->response
            );
        }


        /**
         * Handle an error that occurred during
         * loading/cnostructing/running of the IntermediateAgent.
         * 
         * @throws  \nre\exceptions\ServiceUnavailableException
         * @param   \Exception  $exception      Occurred exception
         * @param   int         $httpStatusCode HTTP-statuscode
         * @param   string      $stage          Stage of execution
         */
        private function error($exception, $httpStatusCode, $stage=self::STAGE_LOAD)
        {
            // Log error
            $this->log($exception, \nre\core\Logger::LOGMODE_AUTO);


            try {
                // Define ErrorAgent
                $this->response->clearParams(1);
                $this->response->addParams(
                    \nre\configs\AppConfig::$defaults['intermediate-error'],
                    \nre\configs\CoreConfig::$defaults['action'],
                    $httpStatusCode
                );

                // Load ErrorAgent
                $this->_loadIntermediateAgent();

                // Run ErrorAgent
                if($stage == self::STAGE_RUN) {
                    $this->_run($this->request, $this->response);
                }
            }
            catch(\nre\exceptions\ActionNotFoundException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
            }
            catch(\nre\exceptions\DatamodelException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
             }
            catch(\nre\exceptions\DriverNotValidException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
             }
            catch(\nre\exceptions\DriverNotFoundException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
             }
            catch(\nre\exceptions\ModelNotValidException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
             }
             catch(\nre\exceptions\ModelNotFoundException $e) {
                 throw new \nre\exceptions\ServiceUnavailableException($e);
             }
             catch(\nre\exceptions\ViewNotFoundException $e) {
                 throw new \nre\exceptions\ServiceUnavailableException($e);
             }
            catch(\nre\exceptions\ControllerNotValidException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
            }
            catch(\nre\exceptions\ControllerNotFoundException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
            }
            catch(\nre\exceptions\AgentNotValidException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
            }
            catch(\nre\exceptions\AgentNotFoundException $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
            }
            catch(Exception $e) {
                throw new \nre\exceptions\ServiceUnavailableException($e);
            }
        }


    }

?>
