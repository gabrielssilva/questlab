<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\controllers;


    /**
     * Controller of the MoodpicAgent to display a Moodpic.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MoodpicController extends \hhu\z\Controller
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array();




        /**
         * Action: index.
         */
        public function index($agentName)
        {
            // Seminary moodpic
            $seminary = SeminaryController::$seminary;
            $seminaryMoodpicIndex = sprintf('%s_seminarymedia_id', $agentName);


            // Pass data to view
            $this->set('seminary', $seminary);
            $this->set('seminaryMoodpicIndex', $seminaryMoodpicIndex);
            $this->set('agentName', $agentName);
        }

    }

?>
