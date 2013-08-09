<?php

	/**
	 * NRE
	 *
	 * @author	coderkun <olli@coderkun.de>
	 * @copyright	2013 coderkun (http://www.coderkun.de)
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	http://www.coderkun.de/projects/nre
	 */
	
	namespace nre\agents;
	
	
	/**
	 * The BottomlevelAgent is the standard Agent and can have indefinite
	 * SubAgents.
	 * 
	 * @author	coderkun <olli@coderkun.de>
	 */
	abstract class BottomlevelAgent extends \nre\core\Agent
	{
		
		
		
		
		/**
		 * Load a BottomlevelAgent.
		 * 
		 * @throws	AgentNotFoundException
		 * @throws	AgentNotValidException
		 * @param	string	$agentName	BottomlevelAgent name
		 */
		public static function load($agentName)
		{
			// Load class
			parent::load_agent($agentName, Autoloader::getClassName(get_class()));
			
			// Determine full classname
			$className = Autoloader::concatClassNames($agentName, Autoloader::getClassType(get_class()));
			
			// Validate class
			try {
				ClassLoader::check($className, get_class());
			}
			catch(ClassNotValidException $e) {
				throw new AgentNotValidException($e->getClassName());
			}
		}
		
	}

?>
