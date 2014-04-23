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
	 * Controller of the UploadsAgent to process and show user uploads.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class UploadsController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('uploads', 'users', 'userroles', 'characterroles', 'seminaries');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array('admin', 'moderator', 'user', 'guest')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'seminary' 	=> array('admin', 'moderator', 'user', 'guest')
		);
		
		
		
		
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
		 * Action: seminary.
		 * 
		 * Display a Seminary upload.
		 * 
		 * @throws	AccessDeniedException
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-title of Seminary
		 * @param	string	$uploadUrl	URL-name of the upload
		 */
		public function seminary($seminaryUrl, $uploadUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Upload
			$upload = $this->Uploads->getSeminaryuploadByUrl($seminary['id'], $uploadUrl);
			
			// Check permissions
			if(!$upload['public'])
			{
				$user = $this->Users->getUserById($this->Auth->getUserId());
				$user['roles'] = array_map(function($r) { return $r['name']; }, $this->Userroles->getUserrolesForUserById($user['id']));
				
				// System roles
				if(count(array_intersect(array('admin', 'moderator'), $user['roles'])) == 0)
				{
					// Owner of file
					if($upload['created_user_id'] != $user['id'])
					{
						// Seminary permissions
						$characterRoles = array_map(function($r) { return $r['name']; }, $this->Characterroles->getCharacterrolesForCharacterById($character['id']));
						if(count(array_intersect(array('admin', 'moderator'), $characterRoles)) == 0) {
							throw new \nre\exceptions\AccessDeniedException();
						}
					}
				}
			}
			
			// Set content-type
			$this->response->addHeader("Content-type: ".$upload['mimetype']."");
			
			// Set filename
			$upload['filename'] = ROOT.DS.\nre\configs\AppConfig::$dirs['seminaryuploads'].DS.$upload['url'];
			if(!file_exists($upload['filename'])) {
				throw new \nre\exceptions\IdNotFoundException($uploadUrl);
			}
			
			// Cache
			if($this->setCacheHeaders($upload['filename'])) {
				return;
			}
			
			// Load file
			$file = file_get_contents($upload['filename']);

			
			
			
			// Pass data to view
			$this->set('upload', $upload);
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
		
	}

?>
