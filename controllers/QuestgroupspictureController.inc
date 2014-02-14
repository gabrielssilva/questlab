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
	 * Controller of QuestgroupspictureAgent to display the picture of a
	 * Questgroups.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class QuestgroupspictureController extends \hhu\z\Controller
	{
		/**
		 * Required models
		 * 
		 * @var array
		 */
		public $models = array('seminaries', 'questgroups', 'media');
		
		
		
		
		/**
		 * Action: index.
		 *
		 * Show the picture of a Questgroup.
		 * 
		 * @param	string	$seminaryUrl	URL-Title of a Seminary
		 * @param	string	$questgroupUrl	URL-Title of a Questgroup
		 */
		public function index($seminaryUrl, $questgroupUrl)
		{
			// Get Seminary
			$seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
			
			// Get Questgroup
			$questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);
			
			// Get Picture
			$picture = $this->Media->getMediaById($questgroup['questgroupspicture_id']);
			
			
			// Pass data to view
			$this->set('seminary', $seminary);
			$this->set('picture', $picture);
		}
		
	}

?>
