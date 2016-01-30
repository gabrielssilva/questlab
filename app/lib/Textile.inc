<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\lib;


    /**
     * Class to ensure that Compatibility library below is loaded.
     * 
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class Textile
    {

        /**
         * Call this function to load necessary files.
         */
        public static function load()
        {
            $path = implode(DS, array('Netcarver', 'Textile'));
            require_once($path.DS.'DataBag.php');
            require_once($path.DS.'Parser.php');
            require_once($path.DS.'Tag.php');
        }

    }

?>
