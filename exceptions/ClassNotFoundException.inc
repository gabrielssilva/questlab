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
     * Exception: Class not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class ClassNotFoundException extends \nre\core\Exception
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 64;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'class not found';

        /**
         * Name of the class that was not found
         * 
         * @var string
         */
        private $className;




        /**
         * Construct a new exception
         * 
         * @param   string  $className  Name of the class that was not found
         * @param   string  $message    Error message (superclass)
         * @param   int     $code       Error code (superclass)
         */
        function __construct($className, $message=self::MESSAGE, $code=self::CODE)
        {
            parent::__construct(
                $message,
                $code,
                $className
            );

            // Store values
            $this->className = $className;
        }




        /**
         * Get the name of the class that was not found.
         * 
         * @return  string  Name of the class that was not found
         */
        public function getClassName()
        {
            return $this->className;
        }

    }

?>
