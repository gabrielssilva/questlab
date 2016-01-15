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
     * Exception: StationtypeModel not found.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class StationtypeModelNotFoundException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 405;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'StationtypeModel not found';

        /**
         * Name of the class that was not found
         *
         * @var string
         */
        private $stationtypeName;




        /**
         * Construct a new exception.
         *
         * @param   string  $stationtypeName    Name of the StationtypeModel that was not found
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

            // Store values
            $this->stationtypeName = $stationtypeName;
        }




        /**
         * Get the name of the StationtypeModel that was not found.
         *
         * @return  string  Name of the StationtypeModel that was not found
         */
        public function getClassName()
        {
            return $this->stationtypeName;
        }

    }

?>
