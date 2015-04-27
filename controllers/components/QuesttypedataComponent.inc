<?php

    /**
     * The Legend of Z
     *
     * @author    Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright    2014 Heinrich-Heine-Universität Düsseldorf
     * @license    http://www.gnu.org/licenses/gpl.html
     * @link    https://bitbucket.org/coderkun/the-legend-of-z
     */
    
    namespace hhu\z\controllers\components;
    
    
    /**
     * Component to handle data for Questtypes between different Quest states.
     * 
     * @author    Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuesttypedataComponent extends \nre\core\Component
    {
        /**
         * Session key
         * 
         * @var string
         */
        const SESSION_KEY = 'questtypes';




        /**
         * Construct a new QuesttypesData-component.
         */
        public function __construct()
        {
            // Construct session place
            if(!array_key_exists(self::SESSION_KEY, $_SESSION)) {
                $_SESSION[self::SESSION_KEY] = array();
            }
        }




        /**
         * Set data with a key-value pair.
         * 
         * @param   int     $questId    ID of Quest to set data for
         * @param   mixed   $key        Key
         * @param   mixed   $value      Value
         */
        public function set($questId, $key, $value)
        {
            // Construct array
            if(!array_key_exists($questId, $_SESSION[self::SESSION_KEY])) {
                $_SESSION[self::SESSION_KEY][$questId] = array();
            }

            // Set data
            $_SESSION[self::SESSION_KEY][$questId][$key] = $value;
        }


        /**
         * Get data by a key.
         * 
         * @param   int     $questId    ID of Quest to set data for
         * @param   mixed   $key        Key
         * @return  mixed               Value
         */
        public function get($questId, $key)
        {
            // Check array
            if(!array_key_exists($questId, $_SESSION[self::SESSION_KEY])) {
                return null;
            }
            if(!array_key_exists($key, $_SESSION[self::SESSION_KEY][$questId])) {
                return null;
            }


            // Return data
            return $_SESSION[self::SESSION_KEY][$questId][$key];
        }

    }

?> 
