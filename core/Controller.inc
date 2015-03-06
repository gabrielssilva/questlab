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
	 * Abstract class for implementing a Controller.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	abstract class Controller
	{
		/**
		 * Corresponding Agent
		 * 
		 * @var Agent
		 */
		protected $agent;
		/**
		 * View of the Controller
		 * 
		 * @var View
		 */
		protected $view = null;
		/**
		 * Data to pass to the View
		 * 
		 * @var array
		 */
		protected $viewData = array();
		/**
		 * Current request
		 * 
		 * @var Request
		 */
		protected $request = null;
		/**
		 * Current response
		 * 
		 * @var Response
		 */
		protected $response = null;
		
		
		
		
		/**
		 * Load the class of a Controller.
		 * 
		 * @throws	\nre\exceptions\ControllerNotFoundException
		 * @throws	\nre\exceptions\ControllerNotValidException
		 * @param	string	$controllerName		Name of the Controller to load
		 */
		public static function load($controllerName)
		{
			// Determine full classname
			$className = self::getClassName($controllerName);
			
			try {
				// Load class
				ClassLoader::load($className);
				
				// Validate class
				ClassLoader::check($className, get_class());
			}
			catch(\nre\exceptions\ClassNotValidException $e) {
				throw new \nre\exceptions\ControllerNotValidException($e->getClassName());
			}
			catch(\nre\exceptions\ClassNotFoundException $e) {
				throw new \nre\exceptions\ControllerNotFoundException($e->getClassName());
			}
		}
		
		
		/**
		 * Instantiate a Controller (Factory Pattern).
		 * 
		 * @throws	\nre\exceptions\DatamodelException
		 * @throws	\nre\exceptions\DriverNotFoundException
		 * @throws	\nre\exceptions\DriverNotValidException
		 * @throws	\nre\exceptions\ModelNotValidException
		 * @throws	\nre\exceptions\ModelNotFoundException
		 * @throws	\nre\exceptions\ViewNotFoundException
		 * @param	string	$controllerName	Name of the Controller to instantiate
		 * @param	string	$layoutName	Name of the current Layout
		 * @param	string	$action		Current Action
		 * @param	string	$agent		Corresponding Agent
		 */
		public static function factory($controllerName, $layoutName, $action, $agent)
		{
			// Determine full classname
			$className = self::getClassName($controllerName);
			
			// Construct and return Controller
			return new $className($layoutName, $action, $agent);
		}
		
		
		/**
		 * Determine the classname for the given Controller name.
		 * 
		 * @param	string	$controllerName	Controller name to get classname of
		 * @return	string			Classname for the Controller name
		 */
		private static function getClassName($controllerName)
		{
			$className = \nre\core\ClassLoader::concatClassNames($controllerName, \nre\core\ClassLoader::stripNamespace(get_class()));
			
			
			return \nre\configs\AppConfig::$app['namespace']."controllers\\$className";
		}
		
		
		
		
		/**
		 * Construct a new Controller.
		 * 
		 * @throws	\nre\exceptions\DriverNotFoundException
		 * @throws	\nre\exceptions\DriverNotValidException
		 * @throws	\nre\exceptions\ModelNotValidException
		 * @throws	\nre\exceptions\ModelNotFoundException
		 * @throws	\nre\exceptions\ViewNotFoundException
		 * @param	string	$layoutName	Name of the current Layout
		 * @param	string	$action		Current Action
		 * @param	Agent	$agent		Corresponding Agent
		 */
		protected function __construct($layoutName, $action, $agent)
		{
			// Store values
			$this->agent = $agent;
			
			// Load Components
			$this->loadComponents();
			
			// Load Models
			$this->loadModels();
			
			// Load View
			$this->loadView($layoutName, $action);
		}
		
		
		
		
		/**
		 * Prefilter that is executed before running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function preFilter(Request $request, Response $response)
		{
			// Request speichern
			$this->request = $request;
			
			// Response speichern
			$this->response = $response;
			
		}
		
		
		/**
		 * Prefilter that is executed after running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function postFilter(Request $request, Response $response)
		{
		}
		
		
		/**
		 * Run the Controller.
		 * 
		 * This method executes the Action of the Controller defined by
		 * the current Request.
		 * 
		 * @throws	\nre\exceptions\ParamsNotValidException
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @throws	\nre\exceptions\DatamodelException
		 * @throws	\nre\exceptions\ActionNotFoundException
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function run(Request $request, Response $response)
		{
			// Determine Action
			$action = $response->getParam(2, 'action');
			if(!method_exists($this, $action)) {
				throw new \nre\exceptions\ActionNotFoundException($action);
			}
			
			// Determine parameters
			$params = $response->getParams(3);
			if(empty($params)) {
				$params = $request->getParams(3);
			}
			
			// Fill missing parameters
			$rc = new \ReflectionClass($this);
			$nullParamsCount = $rc->getMethod($action)->getNumberOfParameters() - count($params);
			$nullParams = ($nullParamsCount > 0 ? array_fill(0, $nullParamsCount, NULL) : array());
			
			
			// Call Action
			call_user_func_array(
				array(
					$this,
					$action
				),
				array_merge(
					$params,
					$nullParams
				)
			);
		}
		
		
		/**
		 * Generate the output.
		 * 
		 * @param	array	$viewData	Data to pass to the View
		 * @return	string			Generated output
		 */
		public function render($viewData=null)
		{
			// Combine given data and data of this Controller
			$data = $this->viewData;
			if(!is_null($viewData)) {
				$data = array_merge($viewData, $data);
			}
			
			// Rendern and return output
			return $this->view->render($data);
		}
		
		
		
		
		/**
		 * Set data for the View.
		 * 
		 * @param	string	$name	Key
		 * @param	mixed	$data	Value
		 */
		protected function set($name, $data)
		{
			$this->viewData[$name] = $data;
		}
		
		
		/**
		 * Redirect to the given URL.
		 * 
		 * @param	string	$url	Relative URL
		 */
		protected function redirect($url)
		{
			$url = 'http://'.$_SERVER['HTTP_HOST'].$url;
			header('Location: '.$url);
			exit;
		}
		
		
		/**
		 * Check if Models of this Controller are loaded and available.
		 * 
		 * @param	string	$modelName	Arbitrary number of Models to check
		 * @return	bool			All given Models are loaded and available
		 */
		protected function checkModels($modelName)
		{
			foreach(func_get_args() as $modelName)
			{
				if(!isset($this->$modelName) || !is_subclass_of($this->$modelName, 'Model')) {
					return false;
				}
			}
			
			
			return true;
		}
		
		
		/**
		 * Get the View of the Controller
		 * 
		 * @return	View	View of the Controller
		 */
		protected function getView()
		{
			return $this->view;
		}
		
		
		
		
		/**
		 * Load the Components of this Controller.
		 * 
		 * @throws	\nre\exceptions\ComponentNotValidException
		 * @throws	\nre\exceptions\ComponentNotFoundException
		 */
		private function loadComponents()
		{
			// Determine components
			$components = array();
			if(property_exists($this, 'components')) {
				$components = $this->components;
			}
			if(!is_array($components)) {
				$components = array($components);
			}
			// Components of parent classes
			$parent = $this;
			while($parent = get_parent_class($parent))
			{
				$properties = get_class_vars($parent);
				if(array_key_exists('components', $properties)) {
					$components = array_merge($components, $properties['components']);
				}
			}
			
			// Load components
			foreach($components as &$component)
			{
				// Load class
				Component::load($component);
					
				// Construct component
				$componentName = ucfirst(strtolower($component));
				$this->$componentName = Component::factory($component);
			}
		}
		
		
		/**
		 * Load the Models of this Controller.
		 * 
		 * @throws	\nre\exceptions\DatamodelException
		 * @throws	\nre\exceptions\DriverNotFoundException
		 * @throws	\nre\exceptions\DriverNotValidException
		 * @throws	\nre\exceptions\ModelNotValidException
		 * @throws	\nre\exceptions\ModelNotFoundException
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
		
		
		/**
		 * Load the View of this Controller.
		 * 
		 * @throws	\nre\exceptions\ViewNotFoundException
		 * @param	string	$layoutName	Name of the current Layout
		 * @param	string	$action		Current Action
		 */
		protected function loadView($layoutName, $action)
		{
			// Check Layout name
			if(is_null($layoutName)) {
				return;
			}
			
			// Determine controller name
			$controllerName = \nre\core\ClassLoader::getClassName(get_class($this));
			
			
			// Load view
			$isToplevel = is_subclass_of($this->agent, '\nre\agents\ToplevelAgent');
			$this->view = View::loadAndFactory($layoutName, $controllerName, $action, $isToplevel);
		}
		
	}

?>
