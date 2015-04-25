<?php

    /**
     * NRE
     *
     * @author    coderkun <olli@coderkun.de>
     * @copyright    2013 coderkun (http://www.coderkun.de)
     * @license    http://www.gnu.org/licenses/gpl.html
     * @link    http://www.coderkun.de/projects/nre
     */

    namespace nre\configs;


    /**
     * Application configuration.
     * 
     * This class contains static variables with configuration values for
     * the specific application.
     * 
     * @author    coderkun <olli@coderkun.de>
     */
    final class AppConfig
    {

        /**
         * Application values
         * 
         * @static
         * @var array
         */
        public static $app = array(
            //'namespace'        =>    '',
            //'timeZone'        =>    ''
        );


        /**
         * Default values
         * 
         * @static
         * @var array
         */
        public static $defaults = array(
            //'toplevel'        =>    '',
            //'toplevel-error'    =>    '',
            //'intermediate'    =>    '',
            //'intermediate-error'    =>    ''
        );


        /**
         * Routes
         *
         * @static
         * @var array
         */
        public static $routes = array(
            //array('<pattern>', '<replace>', '<is_last>')
        );


        /**
         * Reverse routes
         * 
         * @static
         * @var array
         */
        public static $reverseRoutes = array(
            //array('<pattern>', '<replace>', '<is_last>')
        );

    }

?>
