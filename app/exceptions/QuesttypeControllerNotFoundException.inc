<?php

    /**
     * The Legend of Z
     *
     * @author      Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\exceptions;


    /**
     * Exception: QuesttypeController not found.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuesttypeControllerNotFoundException extends \nre\core\Exception
    {
        /**
         * Error code
         *
         * @var int
         */
        const CODE = 103;
        /**
         * Error message
         *
         * @var string
         */
        const MESSAGE = 'QuesttypeController not found';

        /**
         * Name of the class that was not found
         *
         * @var string
         */
        private $questtypeName;




        /**
         * Construct a new exception.
         *
         * @param   string  $questtypeName  Name of the QuesttypeController that was not found
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

            // Store values
            $this->questtypeName = $questtypeName;
        }




        /**
         * Get the name of the QuesttypeController that was not found.
         *
         * @return  string  Name of the QuesttypeController that was not found
         */
        public function getClassName()
        {
            return $this->questtypeName;
        }

    }

?>
