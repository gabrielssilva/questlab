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
     * Exception: ID not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class IdNotFoundException extends \nre\core\Exception
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 85;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'id not found';

        /**
         * ID that was not found
         * 
         * @var mixed
         */
        private $id;




        /**
         * Consturct a new exception.
         * 
         * @param   mixed   $id ID that was not found
         */
        function __construct($id)
        {
            parent::__construct(
                self::MESSAGE,
                self::CODE,
                $id
            );

            // Store values
            $this->id = $id;
        }




        /**
         * Get the ID that was not found.
         * 
         * @return  mixed   ID that was not found
         */
        public function getId()
        {
            return $this->id;
        }

    }

?>
