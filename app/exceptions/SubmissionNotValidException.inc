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
     * Exception: Character submission not valid.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SubmissionNotValidException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 200;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'Character submission not valid';

        /**
         * Nested exception
         *
         * @var Exception
         */
        private $nestedException;




        /**
         * Construct a new exception.
         *
         * @param   string  $nestedException    Nested exception
         * @param   string  $message    Error message
         * @param   int $code       Error code
         */
        function __construct($nestedException, $message=self::MESSAGE, $code=self::CODE)
        {
            parent::__construct(
                $message,
                $code,
                $nestedException
            );

            // Store value
            $this->nestedException = $nestedException;
        }




        /**
         * Get Nested exception.
         *
         * @return  string  Nested exception
         */
        public function getNestedException()
        {
            return $this->nestedException;
        }

    }

?>
