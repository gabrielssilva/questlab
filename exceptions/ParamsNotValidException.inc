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
     * Exception Parameters not valid.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class ParamsNotValidException extends \nre\core\Exception
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 86;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'parameters not valid';

        /**
         * Invalid parameters.
         * 
         * @var array
         */
        private $params;




        /**
         * Construct a new exception.
         * 
         * @param   mixed   $param1 Invalid parameters as argument list
         */
        function __construct($param1)
        {
            parent::__construct(
                self::MESSAGE,
                self::CODE,
                implode(', ', func_get_args())
            );

            // Store values
            $this->params = func_get_args();
        }




        /**
         * Get invalid parameters.
         * 
         * @return  array   Invalid parameters
         */
        public function getParams()
        {
            return $this->params;
        }

    }

?>
