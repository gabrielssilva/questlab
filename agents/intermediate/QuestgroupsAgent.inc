<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\agents\intermediate;


    /**
     * Agent to display Questgroups.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuestgroupsAgent extends \nre\agents\IntermediateAgent
    {




        /**
         * Action: questgroup.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function questgroup(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'questgroup', $request->getParam(3), $request->getParam(4));

            // Add Questgroups hierarchy path
            $this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
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
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3));
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
            $this->addSubAgent('Moodpic', 'questgroup', $request->getParam(3), $request->getParam(4));

            // Add Questgroups hierarchy path
            $this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
        }


        /**
         * Action: edittexts.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function edittexts(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'questgroup', $request->getParam(3), $request->getParam(4));

            // Add Questgroups hierarchy path
            $this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
        }


        /**
         * Action: moveup.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function moveup(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'questgroup', $request->getParam(3), $request->getParam(4));

            // Add Questgroups hierarchy path
            $this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
        }


        /**
         * Action: movedown.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function movedown(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'questgroup', $request->getParam(3), $request->getParam(4));

            // Add Questgroups hierarchy path
            $this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
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
            $this->addSubAgent('Moodpic', 'questgroup', $request->getParam(3), $request->getParam(4));

            // Add Questgroups hierarchy path
            $this->addSubAgent('Questgroupshierarchypath', 'index', $request->getParam(3), $request->getParam(4));
        }

    }

?>
