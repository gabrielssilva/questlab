<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\controllers;
	
	
	/**
	 * Controller of the CssAgent to show CSS-stylesheets.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class CssController extends \hhu\z\Controller
	{
		
		
		
		/**
		 * Prefilter that is executed before running the Controller.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::preFilter($request, $response);
			
			// Set content-type for CSS-stylesheets
			$response->addHeader('Content-type: text/css');
			
			// Set expires-header for caching
			$response->addHeader("Pragma: public");
			$response->addHeader("Expires: ".gmdate('r', time()+(60*60*24)));
			$response->addHeader("Date: ".gmdate(\DateTime::RFC822));
		}
		
		
		/**
		 * Action: desktop.
		 * 
		 * Show CSS for desktops.
		 */
		public function desktop()
		{
			// Set HTTP-header
			$this->setHeader();
		}
		
		
		/**
		 * Action: adds.
		 * 
		 * Show additional CSS for desktops.
		 */
		public function desktop_adds()
		{
			// Set HTTP-header
			$this->setHeader();
		}
		
		
		
		
		/**
		 * Set HTTP-header for caching.
		 */
		private function setHeader()
		{
			// Determine filename of template
			$templateFilename = $this->getView()->getTemplateFilename();
			
			// Determine date of last change
			$templateLastModified = gmdate('r', filemtime($templateFilename));
			
			// Create E-tag
			$templateEtag = hash('sha256', $templateLastModified.$templateFilename);
			
			
			// Set header
			$this->response->addHeader("Last-Modified: ".$templateLastModified);
			$this->response->addHeader("Etag: ".$templateEtag);
			// HTTP-status
			$headerModifiedSince = $this->request->getServerParam('HTTP_IF_MODIFIED_SINCE');
			$headerNoneMatch = $this->request->getServerParam('HTTP_IF_NONE_MATCH');
			if(
				!is_null($headerModifiedSince) && $templateLastModified < strtotime($headerModifiedSince) &&
				!is_null($headerNoneMatch) && $headerNoneMatch == $templateEtag
			) {
				$this->response->setExit(true);
				$this->response->addHeader(\nre\core\WebUtils::getHttpHeader(304));
			}
		}
		
	}

?>
