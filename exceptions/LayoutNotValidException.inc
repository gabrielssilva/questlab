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
     * Exception: Layout not valid.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class LayoutNotValidException extends \nre\exceptions\AgentNotFoundException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 75;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'layout not valid';




        /**
         * Construct a new exception.
         * 
         * @param   string  $layoutName Name of the invalid Layout
         */
        function __construct($layoutName)
        {
            parent::__construct(
                $layoutName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the invalid Layout.
         * 
         * @return  string  Name of the invalid Layout
         */
        public function getLayoutName()
        {
            return $this->getAgentName();
        }

    }

?>
