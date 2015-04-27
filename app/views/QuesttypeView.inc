<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\views;
	
	
	/**
	 * Abstract class for implementing a QuesttypeView.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuesttypeView extends \nre\core\View
	{
		
		
		
		
		/**
		 * Load and instantiate the QuesttypeView of a QuesttypeAgent.
		 * 
		 * @throws	\nre\exceptions\ViewNotFoundException
		 * @param	string	$layoutName	Name of Layout in use
		 * @param	string	$agentName	Name of the Agent
		 * @param	string	$action		Current Action
		 * @param	bool	$isToplevel	Agent is a ToplevelAgent
		 */
		public static function loadAndFactory($layoutName, $agentName=null, $action=null, $isToplevel=false)
		{
			return new QuesttypeView($layoutName, $agentName, $action, $isToplevel);
		}
		
		
		
		
		/**
		 * Construct a new QuesttypeView.
		 * 
		 * @throws	\nre\exceptions\ViewNotFoundException
		 * @param	string	$layoutName	Name of Layout in use
		 * @param	string	$agentName	Name of the Agent
		 * @param	string	$action		Current Action
		 * @param	bool	$isToplevel	Agent is a ToplevelAgent
		 */
		protected function __construct($layoutName, $agentName=null, $action=null, $isToplevel=false)
		{
			// Create template filename
			// LayoutName
			$fileName = ROOT.DS.\nre\configs\AppConfig::$dirs['questtypes'].DS.strtolower($agentName).DS.strtolower($layoutName).DS;
			
			// Action
			$fileName .= strtolower($action);
			
			// File extension
			$fileName .= \nre\configs\CoreConfig::getFileExt('views');
			
			
			// Check template file
			if(!file_exists($fileName)) {
				throw new \nre\exceptions\ViewNotFoundException($fileName);
			}
			
			// Save filename
			$this->templateFilename = $fileName;
		}
		
	}

?>
