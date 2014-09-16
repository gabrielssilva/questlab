<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	
	namespace nre\apis;
	
	
	/**
	 * WebApi-implementation.
	 * 
	 * This class runs and renders an web-applictaion.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	class WebApi extends \nre\core\Api
	{
		
		
		
		
		/**
		 * Construct a new WebApi.
		 */
		public function __construct()
		{
			parent::__construct(
				new \nre\requests\WebRequest(),
				new \nre\responses\WebResponse()
			);
			
			// Add routes
			$this->addRoutes();
			
			// Disable screen logging for AJAX requests
			if($this->request->getParam(0, 'toplevel') == 'ajax') {
				$this->log->disableAutoLogToScreen();
			}
		}
		
		
		
		
		/**
		 * Run application.
		 * 
		 * This method runs the application and handles all errors.
		 */
		public function run()
		{
			try {
				$exception = parent::run();
				
				if(!is_null($exception)) {
					$this->errorService($exception);
				}
			}
			catch(\nre\exceptions\ServiceUnavailableException $e) {
				$this->errorService($e);
			}
			catch(\nre\exceptions\ActionNotFoundException $e) {
				$this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND);
			}
			catch(\nre\exceptions\FatalDatamodelException $e) {
				$this->errorService($e);
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
		 	catch(\nre\exceptions\ViewNotFoundException $e) {
		 		$this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND);
		 	}
			catch(\nre\exceptions\ControllerNotValidException $e) {
				$this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
			}
			catch(\nre\exceptions\ControllerNotFoundException $e) {
				$this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND);
			}
			catch(\nre\exceptions\AgentNoaatValidException $e) {
				$this->error($e, \nre\core\WebUtils::HTTP_SERVICE_UNAVAILABLE);
			}
			catch(\nre\exceptions\AgentNotFoundException $e) {
				$this->error($e, \nre\core\WebUtils::HTTP_NOT_FOUND);
			}
			catch(\nre\exceptions\ClassNotValidException $e) {
				$this->errorService($e);
			}
			catch(\nre\exceptions\ClassNotFoundException $e) {
				$this->errorService($e);
			}
		}
		
		
		/**
		 * Render output.
		 */
		public function render()
		{
			// Generate output
			parent::render();
			
			
			// Set HTTP-header
			$this->response->header();
			
			// Show output
			echo $this->response->getOutput();
		}
		
		
		
		
		/**
		 * Add routes (normal and reverse) defined in the AppConfig.
		 */
		private function addRoutes()
		{
			// Normal routes
			if(property_exists('\nre\configs\AppConfig', 'routes')) {
				foreach(\nre\configs\AppConfig::$routes as &$route) {
					$this->request->addRoute($route[0], $route[1], $route[2]);
				}
			}

			// Reverse routes
			if(property_exists('\nre\configs\AppConfig', 'reverseRoutes')) {
				foreach(\nre\configs\AppConfig::$reverseRoutes as &$route) {
					$this->request->addReverseRoute($route[0], $route[1], $route[2]);
				}
			}
			
			// Revalidate request
			$this->request->revalidate();
		}


		/**
		 * Handle an error that orrcurred during the
		 * loading/constructing/running of the ToplevelAgent.
		 * 
		 * @param	Exception	$exception	Occurred exception
		 * @param	int		$httpStatusCode	HTTP-statuscode
		 */
		private function error(\nre\core\Exception $exception, $httpStatusCode)
		{
			// Log error message
			$this->log($exception, \nre\core\Logger::LOGMODE_AUTO);
			
			try {
				// Set agent for handling errors
				$this->response->clearParams();
				$this->response->addParams(
					\nre\configs\AppConfig::$defaults['toplevel-error'],
					\nre\configs\AppConfig::$defaults['intermediate-error'],
					\nre\configs\CoreConfig::$defaults['action'],
					$httpStatusCode
				);
				
				// Run this agent
				parent::run();
			}
			catch(\nre\exceptions\ServiceUnavailableException $e) {
				$this->errorService($e);
			}
			catch(\nre\exceptions\ActionNotFoundException $e) {
				$this->errorService($e);
			}
			catch(\nre\exceptions\DatamodelException $e) {
				$this->errorService($e);
		 	}
			catch(\nre\exceptions\DriverNotValidException $e) {
				$this->errorService($e);
		 	}
			catch(\nre\exceptions\DriverNotFoundException $e) {
				$this->errorService($e);
		 	}
			catch(\nre\exceptions\ModelNotValidException $e) {
				$this->errorService($e);
		 	}
		 	catch(\nre\exceptions\ModelNotFoundException $e) {
		 		$this->errorService($e);
		 	}
		 	catch(\nre\exceptions\ViewNotFoundException $e) {
		 		$this->errorService($e);
		 	}
			catch(\nre\exceptions\ControllerNotValidException $e) {
				$this->errorService($e);
			}
			catch(\nre\exceptions\ControllerNotFoundException $e) {
				$this->errorService($e);
			}
			catch(\nre\exceptions\AgentNotValidException $e) {
				$this->errorService($e);
			}
			catch(\nre\exceptions\AgentNotFoundException $e) {
				$this->errorService($e);
			}
			catch(Exception $e) {
				$this->errorService($e);
			}
		}
		
		
		/**
		 * Handle a error which cannot be handles by the system (and
		 * HTTP 503).
		 * 
		 * @param	\Exception	$exception	Occurred exception
		 */
		private function errorService($exception)
		{
			// Log error message
			$this->log($exception, \nre\core\Logger::LOGMODE_AUTO);
			
			// Set HTTP-rtatuscode
			$this->response->addHeader(\nre\core\WebUtils::getHttpHeader(503));
			
			
			// Read and print static error file
			$fileName = ROOT.DS.\nre\configs\CoreConfig::getClassDir('views').DS.\nre\configs\CoreConfig::$defaults['errorFile'].\nre\configs\CoreConfig::getFileExt('views');
			ob_start();
			include($fileName);
			$this->response->setOutput(ob_get_clean());
			
			
			// Prevent further execution
			$this->response->setExit();
		}
		
	}

?>
