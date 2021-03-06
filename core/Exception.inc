<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\core;


    /**
     * Exception class.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class Exception extends \Exception
    {




        /**
         * Construct a new exception.
         * 
         * @param   string  $message    Error message
         * @param   int     $code       Error code
         * @param   string  $name       Name to insert
         */
        function __construct($message, $code, $name=null)
        {
            parent::__construct(
                $this->concat(
                    $message,
                    $name
                ),
                $code
            );
        }




        /**
         * Insert the name in a message
         * 
         * @param   string  $message    Error message
         * @param   string  $name       Name to insert
         */
        private function concat($message, $name)
        {
            if(is_null($name)) {
                return $message;
            }


            return "$message: $name";
        }

    }

?>
