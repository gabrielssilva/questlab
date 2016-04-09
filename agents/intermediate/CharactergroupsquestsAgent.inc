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
     * Agent to display Character groups Quests.
     * 
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class CharactergroupsquestsAgent extends \nre\agents\IntermediateAgent
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
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), 'charactergroups');
        }


        /**
         * Action: quest.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function quest(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), 'charactergroups');
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
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), 'charactergroups');
        }


        /**
         * Action: manage.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function manage(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), 'charactergroups');
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
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), 'charactergroups');
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
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), 'charactergroups');
        }

    }

?>
