<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z\models;
	
	
	/**
	 * Model to interact with the maps-table.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MapModel extends \hhu\z\Model
	{
		
		
		
		
		/**
		 * Construct a new MapModel.
		 */
		public function __construct()
		{
			parent::__construct();
		}
		
		
		
		
        /**
         * Get the map of a Seminary.
         * 
         * @param   int     $seminaryId ID of Seminary to get map of
         * @return  array               Map data
         */
        public function getMapOfSeminary($seminaryId)
        {
            $data = $this->db->query(
                'SELECT seminary_id, seminarymedia_id, width, height '.
                'FROM maps '.
                'WHERE seminary_id = ?',
                'i',
                $seminaryId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }
		
	}

?>
