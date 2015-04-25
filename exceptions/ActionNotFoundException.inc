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
     * Exception: Action not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class ActionNotFoundException extends \nre\core\Exception
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 70;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'action not found';

        /**
         * Name of the action that was not found
         * 
         * @var string
         */
        private $action;




        /**
         * Construct a new exception.
         * 
         * @param   string  $action Name of the action that was not found
         */
        function __construct($action)
        {
            parent::__construct(
                self::MESSAGE,
                self::CODE,
                $action
            );

            // Store values
            $this->action = $action;
        }




        /**
         * Get the name of the action that was not found.
         * 
         * @return  string  Name of the action that was not found
         */
        public function getAction()
        {
            return $this->action;
        }

    }

?>
