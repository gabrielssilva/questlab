<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\models;


    /**
     * Default implementation of a database model.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class DatabaseModel extends \nre\core\Model
    {
        /**
         * Database connection
         * 
         * @static
         * @var \nre\drivers\DatabaseDriver
         */
        protected $db = NULL;




        /**
         * Construct a new datamase model.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @param   string  $type   Database type
         * @param   array   $config Connection settings
         */
        function __construct($type, $config)
        {
            parent::__construct();

            // Load database driver
            $this->loadDriver($type);

            // Establish database connection
            $this->connect($type, $config);
        }




        /**
         * Load the database driver.
         * 
         * @throws  \nre\exceptions\DriverNotFoundException
         * @throws  \nre\exceptions\DriverNotValidException
         * @param   string  $driverName Name of the database driver
         */
        private function loadDriver($driverName)
        {
            \nre\core\Driver::load($driverName);
        }


        /**
         * Establish a connection to the database.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @param   string  $driverName Name of the database driver
         * @param   array   $config     Connection settings
         */
        private function connect($driverName, $config)
        {
            $this->db = \nre\core\Driver::factory($driverName, $config);
        }

    }

?>
