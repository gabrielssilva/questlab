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
     * Exception: QuesttypeModel not valid.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuesttypeModelNotValidException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 106;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'QuesttypeModel not valid';

        /**
         * Name of the invalid class
         *
         * @var string
         */
        private $questtypeName;




        /**
         * Construct a new exception.
         *
         * @param   string  $questtypeName  Name of the invalid QuesttypeModel
         * @param   string  $message    Error message
         * @param   int $code       Error code
         */
        function __construct($questtypeName, $message=self::MESSAGE, $code=self::CODE)
        {
            parent::__construct(
                $message,
                $code,
                $questtypeName
            );

            // Store value
            $this->questtypeName = $questtypeName;
        }




        /**
         * Get the name of the invalid QuesttypeModel.
         *
         * @return  string  Name of the invalid QuesttypeModel
         */
        public function getClassName()
        {
            return $this->questtypeName;
        }

    }

?>
