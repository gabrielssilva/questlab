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
     * Exception: View not found.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class ViewNotFoundException extends \nre\core\Exception
    {
        /**
         * Error code
         * 
         * @var int
         */
        const CODE = 69;
        /**
         * Error message
         * 
         * @var string
         */
        const MESSAGE = 'view not found';

        /**
         * Filename of the view that was not found
         * 
         * @var string
         */
        private $fileName;




        /**
         * Construct a new exception.
         * 
         * @param   string  $fileName   Filename of the view that was not found
         */
        function __construct($fileName)
        {
            parent::__construct(
                self::MESSAGE,
                self::CODE,
                $fileName
            );

            // Save values
            $this->fileName = $fileName;
        }




        /**
         * Get the filename of the view that was not found.
         * 
         * @return  string  Filename of the view that was not found
         */
        public function getFileName()
        {
            return $this->fileName;
        }

    }

?>
