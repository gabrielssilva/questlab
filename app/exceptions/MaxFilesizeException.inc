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
     * Exception: File exceeds size maximum.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MaxFilesizeException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 202;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'File exceeds size maximum';




        /**
         * Construct a new exception.
         *
         * @param   string  $message    Error message
         * @param   int $code       Error code
         */
        function __construct($message=self::MESSAGE, $code=self::CODE)
        {
            parent::__construct(
                $message,
                $code
            );
        }

    }

?>
