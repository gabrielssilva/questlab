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
     * Agent to list Achievements.
     * 
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class AchievementsAgent extends \nre\agents\IntermediateAgent
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
         * Action: create.
         * 
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function create(\nre\core\Request $request, \nre\core\Response $response)
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


        /**
         * Action: manage.
         * 
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function manage(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3), $request->getParam(1));
        }


        /**
         * Action: conditions.
         * 
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function conditions(\nre\core\Request $request, \nre\core\Response $response)
        {
            // Add Moodpic
            $this->addSubAgent('Moodpic', 'seminary', $request->getParam(3));
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
