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
     * Exception: Layout not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class LayoutNotFoundException extends \nre\exceptions\AgentNotFoundException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 65;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'layout not found';




        /**
         * Construct a new exception.
         * 
         * @param   string  $layoutName Name of the Layout that was not found
         */
        function __construct($layoutName)
        {
            // Elternkonstruktor aufrufen
            parent::__construct(
                $layoutName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the Layout that was not found.
         * 
         * @return  string  Name of the Layout that was not found
         */
        public function getLayoutName()
        {
            return $this->getAgentName();
        }

    }

?>
