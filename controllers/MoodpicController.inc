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
        public $models = array('seminaries', 'questgroups', 'media');




        /**
         * Action: index.
         *
         * Show the moodpic of a Seminary Agent.
         *
         * @param   string  $agentName  Name of the Seminary Agent to show moodpic of
         */
        public function index($agentName)
        {
        }


        /**
         * Action: seminary.
         *
         * Show moodpic of a Seminary.
         *
         * @param   string  $seminaryUrl    URL of Seminary to show moodpic of
         */
        public function seminary($seminaryUrl, $agentName=null)
        {
            // Get Seminary
            if(property_exists('\hhu\z\controllers\SeminaryController', 'seminary') && !empty(SeminaryController::$seminary) && SeminaryController::$seminary['url'] == $seminaryUrl) {
                $seminary = SeminaryController::$seminary;
            }
            else {
                $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
            }

            // Get medium
            $medium = null;
            // Agent medium
            $seminaryMoodpicIndex = sprintf('%s_seminarymedia_id', $agentName);
            if(array_key_exists($seminaryMoodpicIndex, $seminary) && !is_null($seminary[$seminaryMoodpicIndex]))
            {
                $medium = $this->Media->getSeminaryMediaById($seminary[$seminaryMoodpicIndex]);
                $medium['url'] = $this->linker->link(array('media', 'seminarymoodpic', $seminary['url'], $agentName));
            }
            // Seminary medium
            elseif(!is_null($seminary['seminarymedia_id']))
            { 
                $medium = $this->Media->getSeminaryMediaById($seminary['seminarymedia_id']);
                $medium['url'] = $this->linker->link(array('media', 'seminarymoodpic', $seminary['url']));
            }


            // Pass data to view
            $this->set('medium', $medium);
        }


        /**
         * Action: questgroup.
         *
         * Show moodpic of a Questgroup.
         *
         * @param   string  $seminaryUrl    URL of Seminary
         * @param   string  $quesgroupUrl   URL of Questgroup to show moodpic of
         */
        public function questgroup($seminaryUrl, $questgroupUrl)
        {
            // Get Seminary
            if(property_exists('\hhu\z\controllers\SeminaryController', 'seminary') && !empty(SeminaryController::$seminary) && SeminaryController::$seminary['url'] == $seminaryUrl) {
                $seminary = SeminaryController::$seminary;
            }
            else {
                $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);
            }

            // Get Questgroup
            $questgroup = $this->Questgroups->getQuestgroupByUrl($seminary['id'], $questgroupUrl);

            // Get medium
            $medium = null;
            // Questgroup medium
            if(!is_null($questgroup['questgroupspicture_id']))
            {
                $medium = $this->Media->getSeminaryMediaById($questgroup['questgroupspicture_id']);
                $medium['url'] = $this->linker->link(array('media', 'seminary', $seminary['url'], $medium['url']));
            }
            // Seminary medium
            elseif(!is_null($seminary['seminarymedia_id']))
            {
                $medium = $this->Media->getSeminaryMediaById($seminary['seminarymedia_id']);
                $medium['url'] = $this->linker->link(array('media', 'seminarymoodpic', $seminary['url']));
            }


            // Pass data to view
            $this->set('medium', $medium);
        }

    }

?>
