<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\lib;


    /**
     * Class to ensure that Compatibility library below is loaded.
     * 
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class Phpqrcode
    {

        /**
         * Call this function to load necessary files.
         */
        public static function load()
        {
            require_once('phpqrcode'.DS.'qrlib.php');
        }

    }

?>
