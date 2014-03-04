<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z;
	
	
	/**
	 * Abstract class for implementing a QuesttypeController.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
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
		 * Load a QuesttypeController.
		 * 
		 * @static
		 * @throws	QuesttypeControllerNotFoundException
		 * @throws	QuesttypeControllerNotValidException
		 * @param	string	$controllerName		Name of the QuesttypeController to load
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
		 * @throws	DatamodelException
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @throws	ModelNotValidException
		 * @throws	ModelNotFoundException
		 * @throws	QuesttypeModelNotValidException
		 * @throws	QuesttypeModelNotFoundException
		 * @throws	ViewNotFoundException
		 * @param	string	$controllerName	Name of the QuesttypeController to instantiate
		 * @param	string	$layoutName	Name of the current Layout
		 * @param	string	$action		Current Action
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
		 * @param	string	$questtypeName	Questtype-name to get Controller-classname of
		 * @return	string			Classname for the Questtype-name
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
		 * @throws	ClassNotFoundException
		 * @param	string	$questtypeName	Name of the QuesttypeController to load
		 * @param	string	$fullClassName	Name of the class to load
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
		 * @throws	ClassNotValidException
		 * @param	string	$className		Name of the class to check
		 * @param	string	$parentClassName	Name of the parent class
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
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @throws	ModelNotValidException
		 * @throws	ModelNotFoundException
		 * @throws	QuesttypeModelNotValidException
		 * @throws	QuesttypeModelNotFoundException
		 * @throws	ViewNotFoundException
		 * @param	string	$layoutName	Name of the current Layout
		 * @param	string	$action		Current Action
		 * @param	Agent	$agent		Corresponding Agent
		 */
		public function __construct($layoutName, $action, $agent)
		{
			parent::__construct($layoutName, $action, $agent);
		}
		
		
		
		
		/**
		 * Load the Models of this Controller.
		 * 
		 * @throws	DatamodelException
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @throws	ModelNotValidException
		 * @throws	ModelNotFoundException
		 * @throws	QuesttypeModelNotValidException
		 * @throws	QuesttypeModelNotFoundException
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
		 * @throws	QuesttypeModelNotValidException
		 * @throws	QuesttypeModelNotFoundException
		 */
		private function loadModel()
		{
			// Determine Model
			$model = \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::stripNamespace(get_class($this))));
			
			// Load class
			QuesttypeModel::load($model);
			
			// Construct Model
			$modelName = ucfirst(strtolower($model));
			$this->$modelName = QuesttypeModel::factory($model);
		}
		
		
		/**
		 * Load the View of this QuesttypeController.
		 * 
		 * @throws	ViewNotFoundException
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
			$controllerName = \nre\core\ClassLoader::stripClassType(\nre\core\ClassLoader::getClassName(get_class($this)));
			
			
			// Load view
			$this->view = QuesttypeView::loadAndFactory($layoutName, $controllerName, $action);
		}
		
		
		/**
		 * Mark the current Quest as solved and redirect to solved page.
		 */
		protected function setQuestSolved()
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($this->request->getParam(3));
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $this->request->getParam(4));
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $this->request->getParam(5));
			
			// Sidequest
			$sidequest = null;
			if($this->request->getParam(2) == 'sidequest') {
				$sidequest = $this->Quests->getSidequestByUrl($seminary['id'], $questgroup['id'], $quest['id'], $this->request->getParam(6));
			}
			
			// Character
			$character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
			
			// Set solved
			if(is_null($sidequest)) {
				$this->Quests->setQuestSolved($quest['id'], $character['id']);
			}
			else {
				$this->Quests->setSidequestSolved($sidequest['id'], $character['id']);
			}
			
			
			// Redirect
			$this->redirect($this->linker->link('Epilog', $sidequest != null ? 6 : 5, true, array('status'=>'solved')));
		}
		
		
		/**
		 * Mark the current Quest as unsolved and redirect to unsolved
		 * page.
		 */
		protected function setQuestUnsolved()
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($this->request->getParam(3));
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $this->request->getParam(4));
			
			// Get Quest
			$quest = $this->Quests->getQuestByUrl($seminary['id'], $questgroup['id'], $this->request->getParam(5));
			
			// Sidequest
			$sidequest = null;
			if($this->request->getParam(2) == 'sidequest') {
				$sidequest = $this->Quests->getSidequestByUrl($seminary['id'], $questgroup['id'], $quest['id'], $this->request->getParam(6));
			}
			
			// Character
			$character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
			
			// Set solved
			if(is_null($sidequest)) {
				$this->Quests->setQuestUnsolved($quest['id'], $character['id']);
			}
			else {
				$this->Quests->setSidequestUnsolved($sidequest['id'], $character['id']);
			}
			
			
			
			// Redirect
			$this->redirect($this->linker->link('Prolog', $sidequest != null ? 6 : 5, true, array('status'=>'unsolved')));
		}
		
	}

?>
