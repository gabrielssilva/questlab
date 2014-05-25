<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\agents\toplevel;
	
	
	/**
	 * Agent for generating a HTML-mail message.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class HtmlmailAgent extends \hhu\z\agents\ToplevelAgent
	{
		
		
		
		
		/**
		 * Construct a new HtmlmailAgent.
		 */
		protected function __construct(\nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
		{
			parent::__construct($request, $response, $log);
		}
		
		
		/**
		 * Action: index.
		 */
		public function index(\nre\core\Request $request, \nre\core\Response $response)
		{
			$this->addSubagent('mailreceiver', 'index', $request->getParam(3));
		}
		
	}

?>
