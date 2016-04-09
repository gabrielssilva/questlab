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
    class ModelNotValidException extends \nre\exceptions\ClassNotValidException
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 78;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'model not valid';




        /**
         * Construct a new exception.
         * 
         * @param   string  $modelName  Name of the invalid Model
         */
        function __construct($modelName)
        {
            // Elternkonstruktor aufrufen
            parent::__construct(
                $modelName,
                self::MESSAGE,
                self::CODE
            );
        }




        /**
         * Get the name of the invalid Model
         * 
         * @return  string  Name of the invalid Model
         */
        public function getModelName()
        {
            return $this->getClassName();
        }

    }

?>
