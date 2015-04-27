<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\drivers;


    /**
     * Abstract class for implementing a database driver.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    abstract class DatabaseDriver extends \nre\core\Driver
    {
        /**
         * Driver class instance
         * 
         * @static
         * @var DatabaseDriver
         */
        protected static $driver = null;
        /**
         * Connection resource
         * 
         * @var resource
         */
        protected $connection = null;




        /**
         * Singleton-pattern.
         * 
         * @param   array           $config Database driver configuration
         * @return  DatabaseDriver          Singleton-instance of database driver class
         */
        public static function singleton($config)
        {
            // Singleton
            if(self::$driver !== null) {
                return self::$driver;
            }

            // Construct
            $className = get_called_class();
            self::$driver = new $className($config);


            return self::$driver;
        }


        /**
         * Construct a new database driver.
         * 
         * @param   array   $config Connection and login settings
         */
        protected function __construct($config)
        {
            parent::__construct();

            // Establish connection
            $this->connect($config);
        }




        /**
         * Establish a connect to a MqSQL-database.
         * 
         * @throws  \nre\exceptions\DatamodelException
         * @param   array   $config Connection and login settings
         */
        protected abstract function connect($config);

    }

?>
