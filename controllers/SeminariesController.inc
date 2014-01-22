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
	 * Controller of the Agent to list registered seminaries.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class SeminariesController extends \hhu\z\Controller
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'users');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index' => array(),
			'seminary' => array()
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * List registered seminaries.
		 */
		public function index()
		{
			// Get seminaries
			$seminaries = $this->Seminaries->getSeminaries();
			
			// Get additional data
			foreach($seminaries as &$seminary)
			{
				// Created user
				$seminary['creator'] = $this->Users->getUserById($seminary['created_user_id']);
			}
			
			
			// Pass data to view
			$this->set('seminaries', $seminaries);
		}
		
		
		/**
		 * Action: seminary.
		 * 
		 * Show a seminary and its details.
		 * 
		 * @throws	IdNotFoundException
		 * @param	string	$seminaryUrl	URL-Title of a seminary
		 */
		public function seminary($seminaryUrl)
		{
			// Get seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Created user
			$seminary['creator'] = $this->Users->getUserById($seminary['created_user_id']);
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
		}
		
	}

?>
