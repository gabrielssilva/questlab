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
     * Agent to list registered seminaries.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SeminariesAgent extends \nre\agents\IntermediateAgent
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
            $this->addSubAgent('Moodpic', 'index');
        }


        /**
         * Action: seminary.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function seminary(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3));
        }


        /**
         * Action: create.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function create(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'index');
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


        /**
         * Action: copy.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function copy(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), $request->getParam(1));
        }


        /**
         * Action: delete.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function delete(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), $request->getParam(1));
        }

    }

?>
