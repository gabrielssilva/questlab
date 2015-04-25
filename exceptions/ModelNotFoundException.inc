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
    class ModelNotFoundException extends \nre\exceptions\ClassNotFoundException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 68;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'model not found';




        /**
         * Construct a new exception.
         * 
         * @param   string  $modelName  Name of the Model that was not found
         */
        function __construct($modelName)
        {
            parent::__construct(
                $modelName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the Model that was not found
         * 
         * @return  string  Name of the Model that was not found
         */
        public function getModelName()
        {
            return $this->getClassName();
        }

    }

?>
