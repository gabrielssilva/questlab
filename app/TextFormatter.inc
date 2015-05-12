<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z;


    /**
     * Class to format text with different syntax tags.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class TextFormatter
    {
        /**
         * Linker to create links.
         *
         * @var \nre\core\Linker
         */
        private $linker;
        /**
         * Media-Model to retrieve media data
         *
         * @static
         * @var \nre\core\Model
         */
        private static $Media = null;




        /**
         * Create a new text formatter.
         *
         * @param   \nre\core\Linker $linker    Linker to create links with
         */
        public function __construct(\nre\core\Linker $linker)
        {
            $this->linker = $linker;
        }




        /**
         * Format a string.
         *
         * @param   string  $string String to format
         * @return  string      Formatted string
         */
        public function t($string)
        {
            // Remove chars
            $string = htmlspecialchars($string, ENT_NOQUOTES);

            // Important text
            $string = str_replace('[strong]', '<strong>', $string);
            $string = str_replace('[/strong]', '</strong>', $string);

            // Create tables
            $string = preg_replace('/(\[table\])\s+/u', '$1', $string);
            $string = preg_replace('/\s*(\[tr\])\s*/u', '$1', $string);
            $string = preg_replace('%\s+(\[/table\])%u', '$1', $string);
            $string = preg_replace('%\s*(\[/tr\])\s*%u', '$1', $string);
            $string = str_replace('[table]', '</p><table>', $string);
            $string = str_replace('[/table]', '</table><p>', $string);
            $string = str_replace('[tr]', '<tr>', $string);
            $string = str_replace('[/tr]', '</tr>', $string);
            $string = str_replace('[th]', '<th>', $string);
            $string = str_replace('[/th]', '</th>', $string);
            $string = str_replace('[td]', '<td>', $string);
            $string = str_replace('[/td]', '</td>', $string);

            // Create links
            $string = preg_replace('!(^|\s)"([^"]+)":(https?://[^\s]+)(\s|$)!i', '$1<a href="$3">$2</a>$4', $string);
            $string = preg_replace('!(^|\s)(https?://[^\s]+)(\s|$)!i', '$1<a href="$2">$2</a>$3', $string);

            // Handle Seminarymedia
            $seminarymedia = array();
            preg_match_all('/\[seminarymedia:(\d+)\]/iu', $string, $matches); //, PREG_SET_ORDER | PREG_OFFSET_CAPTURE);
            $seminarymediaIds = array_unique($matches[1]);
            foreach($seminarymediaIds as &$seminarymediaId)
            {
                $replacement = null;
                if(!is_null(\hhu\z\controllers\SeminaryController::$seminary) && $this->loadMediaModel())
                {
                    try {
                        $medium = self::$Media->getSeminaryMediaById($seminarymediaId);
                        $replacement = sprintf(
                            '<img src="%s" alt="%s" />',
                            $this->linker->link(array('media','seminary', \hhu\z\controllers\SeminaryController::$seminary['url'],$medium['url'])),
                            $medium['description']
                        );
                    }
                    catch(\nre\exceptions\IdNotFoundException $e) {
                    }
                }

                $seminarymedia[$seminarymediaId] = $replacement;
            }
            foreach($seminarymedia as $seminarymediaId => $replacement) {
                $string = str_replace("[seminarymedia:$seminarymediaId]", $replacement, $string);
            }


            // Return processed string
            return nl2br($string);
        }




        /**
         * Load the Media-Model if it is not loaded
         *
         * @return  boolean Whether the Media-Model has been loaded or not
         */
        private function loadMediaModel()
        {
            // Do not load Model if it has already been loaded
            if(!is_null(self::$Media)) {
                return true;
            }

            try {
                // Load class
                Model::load('media');

                // Construct Model
                self::$Media = Model::factory('media');
            }
            catch(\Exception $e) {
            }


            // Return whether Media-Model has been loaded or not
            return !is_null(self::$Media);
        }

    }

?>
