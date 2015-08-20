<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\agents\intermediate;


    /**
     * Agent to display a map.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MapAgent extends \nre\agents\IntermediateAgent
    {




        /**
         * Action: index.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function index(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), $request->getParam(1));
        }


        /**
         * Action: edit.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function edit(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), $request->getParam(1));
        }

    }

?>
