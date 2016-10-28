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
     * Exception: StationxuesttypeModel not valid.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class StationtypeModelNotValidException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 406;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'StationtypeModel not valid';

        /**
         * Name of the invalid class
         *
         * @var string
         */
        private $stationtypeName;




        /**
         * Construct a new exception.
         *
         * @param   string  $stationtypeName    Name of the invalid StationtypeModel
         * @param   string  $message            Error message
         * @param   int     $code               Error code
         */
        function __construct($stationtypeName, $message=self::MESSAGE, $code=self::CODE)
        {
            parent::__construct(
                $message,
                $code,
                $stationtypeName
            );

            // Store value
            $this->stationtypeName = $stationtypeName;
        }




        /**
         * Get the name of the invalid StationtypeModel.
         *
         * @return  string  Name of the invalid StationtypeModel
         */
        public function getClassName()
        {
            return $this->stationtypeName;
        }

    }

?>
