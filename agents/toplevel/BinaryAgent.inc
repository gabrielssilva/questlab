<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\agents\toplevel;


    /**
     * Agent to display binary data (e. g. images).
     * 
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class BinaryAgent extends \hhu\z\agents\ToplevelAgent
    {




        /**
         * Construct a new BinaryAgent.
         * 
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         * @param   \nre\core\Logger    $log        Logger instance
         */
        protected function __construct(\nre\core\Request $request, \nre\core\Response $response, \nre\core\Logger $log=null)
        {
            parent::__construct($request, $response, $log);
        }


        /**
         * Action: index.
         * 
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function index(\nre\core\Request $request, \nre\core\Response $response)
        {
        }

    }

?>
