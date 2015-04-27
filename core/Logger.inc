<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\core;


    /**
     * Class to log messages to different targets.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class Logger
    {
        /**
         * Log mode: Detect automatic
         * 
         * @var int
         */
        const LOGMODE_AUTO = 0;
        /**
         * Log mode: Print to screen
         * 
         * @var int
         */
        const LOGMODE_SCREEN = 1;
        /**
         * Log mode: Use PHP-logging mechanism
         * 
         * @var int
         */
        const LOGMODE_PHP = 2;

        /**
         * Do not auto-log to screen
         * 
         * @var boolean
         */
        private $autoLogToScreenDisabled = false;




        /**
         * Construct a new logger.
         */
        public function __construct()
        {
        }




        /**
         * Log a message.
         * 
         * @param   string  $message    Message to log
         * @param   int     $logMode    Log mode to use
         */
        public function log($message, $logMode=self::LOGMODE_SCREEN)
        {
            // Choose log mode automatically
            if($logMode == self::LOGMODE_AUTO) {
                $logMode = $this->getAutoLogMode();
            }

            // Print message to screen
            if($logMode & self::LOGMODE_SCREEN) {
                $this->logToScreen($message);
            }

            // Use PHP-logging mechanism
            if($logMode & self::LOGMODE_PHP) {
                $this->logToPhp($message);
            }
        }


        /**
         * Disable logging to screen when the log mode is automatically
         * detected.
         */
        public function disableAutoLogToScreen()
        {
            $this->autoLogToScreenDisabled = true;
        }



        /**
         * Print a message to screen.
         * 
         * @param   string  $message    Message to print
         */
        private function logToScreen($message)
        {
            echo "$message<br>\n";
        }


        /**
         * Log a message by using PHP-logging mechanism.
         * 
         * @param   string  $message    Message to log
         */
        private function logToPhp($message)
        {
            error_log($message, 0);
        }


        /**
         * Detect log mode automatically by distinguishing between
         * production and test environment.
         * 
         * @return  int Automatically detected log mode
         */
        private function getAutoLogMode()
        {
            return ($this->isLocalhost() && !$this->autoLogToScreenDisabled) ? self::LOGMODE_SCREEN : self::LOGMODE_PHP;
        }


        /**
         * Detect if the server is running as localhost without domain.
         * 
         * @return  boolean Wheather server is running as localhost or not
         */
        private function isLocalhost()
        {
            return ($_SERVER['SERVER_ADDR'] == '127.0.0.1' || $_SERVER['SERVER_ADDR'] = '::1');
        }

    }

?>
