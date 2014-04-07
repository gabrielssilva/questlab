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
			'index' => array('admin', 'moderator', 'user', 'guest'),
			'seminary' => array('admin', 'moderator', 'user', 'guest')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'seminary' => array('admin', 'moderator', 'user', 'guest')
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
		 * Action: index
		 * 
		 * Display a medium.
		 * 
		 * @param	string	$mediaUrl	URL-name of the medium
		 */
		public function index($mediaUrl, $action=null)
		{
			// Get Media
			$media = $this->Media->getMediaByUrl($mediaUrl);
			
			// Get format
			$format = explode('/', $media['mimetype']);
			$format = $format[1];
			
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
			
			// Load and process file
			$file = null;
			switch($action)
			{
				// No action
				case null:
					// Do not process the file
					$file = file_get_contents($media['filename']);
				break;
				default:
					throw new ParamsNotValidException($action);
				break;
			}
			
			
			
			// Pass data to view
			$this->set('media', $media);
			$this->set('file', $file);
		}
		
		
		/**
		 * Action: seminary.
		 * 
		 * Display a Seminary medium.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of the Seminary
		 * @param	string	$mediaUrl	URL-name of the medium
		 */
		public function seminary($seminaryUrl, $mediaUrl, $action=null)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Media
			$media = $this->Media->getSeminaryMediaByUrl($seminary['id'], $mediaUrl);
			
			// Get format
			$format = explode('/', $media['mimetype']);
			$format = $format[1];
			
			// Set content-type
			$this->response->addHeader("Content-type: ".$media['mimetype']."");
			
			// Set filename
			$media['filename'] = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$media['id'];
			if(!file_exists($media['filename'])) {
				throw new \nre\exceptions\IdNotFoundException($mediaUrl);
			}
			
			// Cache
			if($this->setCacheHeaders($media['filename'])) {
				return;
			}
			
			// Load and process file
			$file = null;
			switch($action)
			{
				// No action
				case null:
					// Do not process the file
					$file = file_get_contents($media['filename']);
				break;
				case 'questgroup':
					if(!in_array(strtoupper($format), self::getImageTypes())) {
						$file = file_get_contents($media['filename']);
					}
					else
					{
						$file = self::resizeImage(
							$media['filename'],
							$format,
							480
						);
					}
				break;
				default:
					throw new ParamsNotValidException($action);
				break;
			}
			
			
			
			// Pass data to view
			$this->set('media', $media);
			$this->set('file', $file);
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
		
		
		
		
		/**
		 * Get supported image types.
		 * 
		 * @return	array	List of supported image types
		 */
		private static function getImageTypes()
		{
			$im = new \Imagick();
			
			
			return $im->queryFormats();
		}
		
		
		/**
		 * Resize an image.
		 * 
		 * @param	string	$fileName	Absolute pathname of image to resize
		 * @param	string	$mimeType	Mimetype of target image
		 * @param	int	$size		New size to resize to
		 */
		private static function resizeImage($fileName, $mimeType, $size)
		{
			// Read image from cache
			$tempFileName = ROOT.DS.\nre\configs\AppConfig::$dirs['temporary'].DS.'media-'.basename($fileName).'-'.$size;
			if(file_exists($tempFileName))
			{
				// Check age of file
				if(date('r', filemtime($tempFileName)+(60*60*24)) > date('r', time())) {
					// Too old, delete
					unlink($tempFileName);
				}
				else {
					// Valid, read and return
					return file_get_contents($tempFileName);
				}
			}
			
			
			// ImageMagick
			$im = new \Imagick($fileName);
			
			// Calculate new size
			$geometry = $im->getImageGeometry();
			if($geometry['width'] < $size) {
				$size = $geometry['width'];
			}
			
			// Process 
			$im->thumbnailImage($size, 5000, true);
			$im->contrastImage(1);
			$im->setImageFormat($mimeType);
			
			// Save temporary file
			$im->writeImage($tempFileName);
			
			
			// Return resized image
			return $im;
		}
		
	}

?>
