<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	 
	namespace nre\core;
	
	
	/**
	 * Abstract class to implement an API.
	 * 
	 * The API is the center of each application and specifies how and what
	 * to run and render.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	abstract class Api
	{
		/**
		 * Die aktuelle Anfrage
		 * 
		 * @var Request
		 */
		protected $request;
		/**
		 * Der Toplevelagent
		 * 
		 * @var ToplevelAgent
		 */
		private $toplevelAgent = null;
		/**
		 * Die aktuelle Antwort
		 * 
		 * @var Response
		 */
		protected $response;
		/**
		 * Log-System
		 * 
		 * @var Logger
		 */
		private $log;
		
		
		
		
		/**
		 * Construct a new API.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$respone	Current response
		 */
		public function __construct(Request $request, Response $response)
		{
			// Store request
			$this->request = $request;
			
			// Store response
			$this->response = $response;
			
			// Init logging
			$this->log = new \nre\core\Logger();
		}
		
		
		
		
		/**
		 * Run the application.
		 * 
		 * @throws	DatamodelException
		 * @throws	DriverNotValidException
		 * @throws	DriverNotFoundException
		 * @throws	ViewNotFoundException
		 * @throws	ModelNotValidException
		 * @throws	ModelNotFoundException
		 * @throws	ControllerNotValidException
		 * @throws	ControllerNotFoundException
		 * @throws	AgentNotValidException
		 * @throws	AgentNotFoundException
		 * @return	Exception	Last occurred exception of an subagent
		 */
		public function run()
		{
			// Load ToplevelAgent
			$this->loadToplevelAgent();
			
			// Run ToplevelAgent
			return $this->toplevelAgent->run($this->request, $this->response);
		}
		
		
		/**
		 * Render the output.
		 */
		public function render()
		{
			// Check exit-status
			if($this->response->getExit()) {
				return;
			}
			
			// Render ToplevelAgent
			$this->response->setOutput($this->toplevelAgent->render());
		}
		
		
		
		
		/**
		 * Log an exception
		 * 
		 * @param	Exception	$exception	Occurred exception
		 * @param	int		$logMode	Log-mode
		 */
		protected function log($exception, $logMode)
		{
			$this->log->log(
				$exception->getMessage(),
				$logMode
			);
		}
		
		
		
		
		/**
		 * Load the ToplevelAgent specified by the request.
		 * 
		 * @throws	ServiceUnavailableException
		 * @throws	AgentNotValidException
		 * @throws	AgentNotFoundException
		 */
		private function loadToplevelAgent()
		{
			// Determine agent
			$agentName = $this->response->getParam(0);
			if(is_null($agentName)) {
				$agentName = $this->request->getParam(0, 'toplevel');
				$this->response->addParam($agentName);
			}
			
			// Load agent
			\nre\agents\ToplevelAgent::load($agentName);
			
			// Construct agent
			$this->toplevelAgent = \nre\agents\ToplevelAgent::factory(
				$agentName,
				$this->request,
				$this->response,
				$this->log
			);
		}
		
	}

?>
