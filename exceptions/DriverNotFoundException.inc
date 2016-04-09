<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\exceptions;


    /**
     * Exception: Driver not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class DriverNotFoundException extends \nre\exceptions\ClassNotFoundException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 71;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'driver not found';




        /**
         * Construct a new exception.
         * 
         * @param   string  $driverName Name of the driver that was not found
         */
        function __construct($driverName)
        {
            // Elternkonstruktor aufrufen
            parent::__construct(
                $driverName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the driver that was not found.
         * 
         * @return  string  Name of the driver that was not found
         */
        public function getDriverName()
        {
            return $this->getClassName();
        }

    }

?>
