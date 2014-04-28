<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\controllers\components;
	
	
	/**
	 * Component to handle achievements.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class AchievementComponent extends \nre\core\Component
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('achievements');
		
		
		
		
		/**
		 * Construct a new Achievements-component.
		 */
		public function __construct()
		{
		}
	
	}

?>
