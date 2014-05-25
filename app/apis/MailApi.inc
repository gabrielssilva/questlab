<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\apis;
	
	
	/**
	 * MailApi-implementation.
	 * 
	 * This class runs and renders e‑mail text and subject.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MailApi extends \nre\core\Api
	{
		
		
		
		
		/**
		 * Construct a new MailApi.
		 */
		public function __construct()
		{
			parent::__construct(
				new \hhu\z\requests\MailRequest(),
				new \hhu\z\responses\MailResponse()
			);
			
			// Set ToplevelAgent
			$this->response->addParam(\nre\configs\AppConfig::$defaults['toplevel-mail']);
			$this->response->addParam(\nre\configs\AppConfig::$defaults['intermediate-mail']);
		}
		
		
		
		
		/**
		 * Use a ToplevelAgent for HTML-mail
		 */
		public function setHTML()
		{
			$this->response->clearParams();
			$this->response->addParam(\nre\configs\AppConfig::$defaults['toplevel-htmlmail']);
			$this->response->addParam(\nre\configs\AppConfig::$defaults['intermediate-mail']);
		}
		
		
		/**
		 * Set the Action for the message to render.
		 */
		public function setMessage($messageAgent)
		{
			$this->response->clearParams(2);
			$this->response->addParam($messageAgent);
		}
		
		
		/**
		 * Set additional params to pass to the Action.
		 * 
		 * @param	array	$params	Additional params to set
		 */
		public function setParams($params)
		{
			$this->response->addParams($params);
		}
		
		
		/**
		 * Return the subject set by the Controller.
		 * 
		 * @return	string	Subject set by Controller
		 */
		public function getSubject()
		{
			return $this->response->getSubject();
		}
		
		
		/**
		 * Run mailtext generation.
		 * 
		 * This method runs the generation of mailtext.
		 * 
		 * @return	Exception	Occured exception or null
		 */
		public function run()
		{
			try {
				$exception = parent::run();
				
				
				return $exception;
			}
			catch(\nre\Exception $e) {
				return $e;
			}
		}
		
		
		/**
		 * Render output.
		 * 
		 * @return	string	Rendered output
		 */
		public function render()
		{
			// Generate output
			parent::render();
			
			
			// Return output
			return $this->response->getOutput();
		}
		
	}

?>
