<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z;
	
	
	/**
	 * Abstract class for implementing an application Model.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class Model extends \nre\models\DatabaseModel
	{
		
		
		
		
		/**
		 * Construct a new application Model.
		 * 
		 * @throws	\nre\exceptions\DatamodelException
		 * @throws	\nre\exceptions\DriverNotFoundException
		 * @throws	\nre\exceptions\DriverNotValidException
		 * @throws	\nre\exceptions\ModelNotValidException
		 * @throws	\nre\exceptions\ModelNotFoundException
		 */
		public function __construct()
		{
			parent::__construct('mysqli', \nre\configs\AppConfig::$database);
		}
		
	}

?>
