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
	 * Controller of the MapAgent to display a map.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MapController extends \hhu\z\controllers\SeminaryController
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'map');
		/**
		 * User permissions
		 * 
		 * @var array
		 */
		public $permissions = array(
			'index'		=> array('admin', 'moderator', 'user')
		);
		/**
		 * User seminary permissions
		 * 
		 * @var array
		 */
		public $seminaryPermissions = array(
			'index' 	=> array('admin', 'moderator', 'user')
		);
		
		
		
		
		/**
		 * Action: index.
		 * 
		 * Draw the map.
		 * 
		 * @throws	\nre\exceptions\IdNotFoundException
		 * @param	string	$seminaryUrl		URL-Title of Seminary
		 */
		public function index($seminaryUrl)
		{
            // Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get map
            $map = $this->Map->getMapOfSeminary($seminary['id']);


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('map', $map);
		}
		
	}

?>
