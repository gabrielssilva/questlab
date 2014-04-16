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
	class UploadsController extends \hhu\z\controllers\IntermediateController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('uploads', 'users', 'userroles');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array('admin', 'moderator', 'user', 'userseminaryroles')
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
		 * Action: index.
		 * 
		 * Display an upload.
		 * 
		 * @throws	AccessDeniedException
		 * @throws	IdNotFoundException
		 * @param	string	$uploadUrl	URL-name of the upload
		 */
		public function index($uploadUrl)
		{
			// Get Upload
			$upload = $this->Uploads->getUploadByUrl($uploadUrl);
			
			// Check permissions
			$user = $this->Users->getUserById($this->Auth->getUserId());
			$user['roles'] = array();
			foreach($this->Userroles->getUserrolesForUserById($user['id']) as $role) {
				$user['roles'][] = $role['name'];
			}
			if(!$upload['public'])
			{
				// System roles
				if(count(array_intersect(array('admin', 'moderator'), $user['roles'])) == 0)
				{
					// Owner of file
					if($upload['created_user_id'] != $user['id'])
					{
						if(!is_null($upload['seminary_id'])) {
							throw new \nre\exceptions\AccessDeniedException();
						}
						else
						{
							// Seminary
							$seminary = $this->Seminaries->getSeminaryById($upload['seminary_id']);
							
							// Seminary roles
							$userSeminaryRoles = array();
							foreach($this->Userseminaryroles->getUserseminaryrolesForUserById($user['id'], $seminary['id']) as $role) {
								$userSeminaryRoles[] = $role['name'];
							}
							
							if(count(array_intersect(array('admin', 'moderator'), $userSeminaryRoles)) == 0) {
								throw new \nre\exceptions\AccessDeniedException();
							}
						}
					}
				}
			}
			
			// Set content-type
			$this->response->addHeader("Content-type: ".$upload['mimetype']."");
			
			// Set filename
			$upload['filename'] = ROOT.DS.\nre\configs\AppConfig::$dirs['uploads'].DS.$upload['id'];
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
