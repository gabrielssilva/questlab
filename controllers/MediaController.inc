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
	 * Controller of the MediaAgent to process and show Media.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MediaController extends \hhu\z\controllers\SeminaryRoleController
	{
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index' => array('admin', 'moderator', 'user')
		);
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'media');
		
		
		
		
		/**
		 * Prefilter.
		 * 
		 * @param	Request		$request	Current request
		 * @param	Response	$response	Current response
		 */
		public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
		{
			parent::preFilter($request, $response);
			
			// Set headers for caching control
			$response->addHeader("Pragma: public");
			$response->addHeader("Cache-control: public, max-age=".(60*60*24));
			$response->addHeader("Expires: ".gmdate('r', time()+(60*60*24)));
			$response->addHeader("Date: ".gmdate(\DateTime::RFC822));
		}
		
		
		/**
		 * Action: index.
		 * 
		 * Display a medium without processing.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of the Seminary
		 * @param	string	$mediaUrl	URL-name of the medium
		 */
		public function index($seminaryUrl, $mediaUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Media
			$media = $this->Media->getMediaByUrl($seminary['id'], $mediaUrl);
			
			// Set content-type
			$this->response->addHeader("Content-type: ".$media['mimetype']."");
			
			// Set filename
			$media['filename'] = ROOT.DS.\nre\configs\AppConfig::$dirs['media'].DS.$media['id'];
			if(!file_exists($media['filename'])) {
				throw new \nre\exceptions\IdNotFoundException($mediaUrl);
			}
			
			// Cache
			if($this->setCacheHeaders($media['filename'])) {
				return;
			}
			
			
			// Pass data to view
			$this->set('media', $media);
		}
		
		
		
		
		/**
		 * Determine file information and set the HTTP-header for
		 * caching accordingly.
		 * 
		 * @param	string	$fileName	Filename
		 * @return	boolean			HTTP-status 304 was set (in cache)
		 */
		private function setCacheHeaders($fileName)
		{
			// Determine last change of file
			$fileLastModified = gmdate('r', filemtime($fileName));
			
			// Generate E-Tag
			$fileEtag = hash('sha256', $fileLastModified.$fileName);
			
			
			// Set header
			$this->response->addHeader("Last-Modified: ".$fileLastModified);
			$this->response->addHeader("Etag: ".$fileEtag);
			// HTTP-status
			$headerModifiedSince = $this->request->getServerParam('HTTP_IF_MODIFIED_SINCE');
			$headerNoneMatch = $this->request->getServerParam('HTTP_IF_NONE_MATCH');
			if(
				!is_null($headerModifiedSince) && $fileLastModified < strtotime($headerModifiedSince) &&
				!is_null($headerNoneMatch) && $headerNoneMatch == $fileEtag
			) {
				$this->response->setExit(true);
				$this->response->addHeader(\nre\core\WebUtils::getHttpHeader(304));
				
				return true;
			}
			
			
			return false;
		}
		
	}

?>
