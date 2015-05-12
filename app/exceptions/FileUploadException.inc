<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\exceptions;


    /**
     * Exception: File upload went wrong
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class FileUploadException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 203;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'File upload went wrong';

        /**
         * Nested message
         *
         * @var string
         */
        private $nestedMessage;




        /**
         * Construct a new exception.
         *
         * @param   string  $nestedMessage  Nested message
         * @param   string  $message    Error message
         * @param   int $code       Error code
         */
        function __construct($nestedMessage=null, $message=self::MESSAGE, $code=self::CODE)
        {
            parent::__construct(
                $message,
                $code,
                $nestedMessage
            );

            // Store values
            $this->nestedMessage = $nestedMessage;
        }




        /**
         * Get nested message.
         *
         * @return  Nested message
         */
        public function getNestedMessage()
        {
            return $this->nestedMessage;
        }

    }

?>
