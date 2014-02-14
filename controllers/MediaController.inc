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
			'quest' => array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'quest' => array('admin', 'moderator', 'user')
		);
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'media');
		
		
		
		
		/**
		 * TODO Action: index.
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
			$media['filename'] = ROOT.DS.'media'.DS.$media['id'];
			
			
			// Pass data to view
			$this->set('media', $media);
		}
		
	}

?>
