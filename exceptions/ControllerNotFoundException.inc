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
     * Exception: Controller not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class ControllerNotFoundException extends \nre\exceptions\ClassNotFoundException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 67;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'controller not found';




        /**
         * Construct a new exception.
         * 
         * @param   string  $controllerName Name of the Controller that was not found
         */
        function __construct($controllerName)
        {
            parent::__construct(
                $controllerName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the Controller that was not found.
         * 
         * @return  string  Name of the Controller that was not found
         */
        public function getControllerName()
        {
            return $this->getClassName();
        }

    }

?>
