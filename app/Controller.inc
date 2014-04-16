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
	 * Abstract class for implementing an application Controller.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	abstract class Controller extends \nre\core\Controller
	{
		/**
		 * Required components
		 * 
		 * @var array
		 */
		public $components = array('auth');
		/**
		 * Linker instance
		 * 
		 * @var Linker
		 */
		protected $linker = null;
		
		
		
		
		/**
		 * Construct a new application Controller.
		 * 
		 * @throws	DriverNotFoundException
		 * @throws	DriverNotValidException
		 * @throws	ModelNotValidException
		 * @throws	ModelNotFoundException
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
		 * Prefilter that is executed before running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::preFilter($request, $response);
			
			// Create linker
			$this->linker = new \nre\core\Linker($this->request);
			
			// Create date and time and number formatter
			$this->set('dateFormatter', new \IntlDateFormatter(
				\nre\core\Config::getDefault('locale'),
				\IntlDateFormatter::MEDIUM,
				\IntlDateFormatter::NONE,
				NULL
			));
			$this->set('timeFormatter', new \IntlDateFormatter(
				\nre\core\Config::getDefault('locale'),
				\IntlDateFormatter::NONE,
				\IntlDateFormatter::SHORT,
				NULL
			));
			$this->set('numberFormatter', new \NumberFormatter(
				\nre\core\Config::getDefault('locale'),
				\NumberFormatter::DEFAULT_STYLE
			));
		}
		
		
		/**
		 * Postfilter that is executed after running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function postFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::postFilter($request, $response);
		}
		
	}

?>
