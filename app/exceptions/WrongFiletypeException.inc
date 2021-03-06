<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\exceptions;


    /**
     * Exception: File has wrong filetype.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class WrongFiletypeException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 201;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'File has wrong type “%s”';

        /**
         * Type of file
         *
         * @var string
         */
        private $type;




        /**
         * Construct a new exception.
         *
         * @param   string  $type       Type of file
         * @param   string  $message    Error message
         * @param   int $code       Error code
         */
        function __construct($type, $message=self::MESSAGE, $code=self::CODE)
        {
            parent::__construct(
                $message,
                $code,
                $type
            );

            // Store values
            $this->type = $type;
        }




        /**
         * Get type of file.
         *
         * @return  Type of file
         */
        public function getType()
        {
            return $this->type;
        }

    }

?>
