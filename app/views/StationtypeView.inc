<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\views;


    /**
     * Abstract class for implementing a StationtypeView.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class StationtypeView extends \nre\core\View
    {




        /**
         * Load and instantiate the StationtypeView of a StationtypeAgent.
         *
         * @throws  \nre\exceptions\ViewNotFoundException
         * @param   string  $layoutName Name of Layout in use
         * @param   string  $agentName  Name of the Agent
         * @param   string  $action     Current Action
         * @param   bool    $isToplevel Agent is a ToplevelAgent
         */
        public static function loadAndFactory($layoutName, $agentName=null, $action=null, $isToplevel=false)
        {
            return new StationtypeView($layoutName, $agentName, $action, $isToplevel);
        }




        /**
         * Construct a new StationtypeView.
         *
         * @throws  \nre\exceptions\ViewNotFoundException
         * @param   string  $layoutName Name of Layout in use
         * @param   string  $agentName  Name of the Agent
         * @param   string  $action     Current Action
         * @param   bool    $isToplevel Agent is a ToplevelAgent
         */
        protected function __construct($layoutName, $agentName=null, $action=null, $isToplevel=false)
        {
            // Create template filename
            // LayoutName
            $fileName = ROOT.DS.
                \nre\configs\AppConfig::$dirs['stationtypes'].DS.
                strtolower($agentName).DS.
                strtolower($layoutName).DS;

            // Action
            $fileName .= strtolower($action);

            // File extension
            $fileName .= \nre\configs\CoreConfig::getFileExt('views');


            // Check template file
            if(!file_exists($fileName)) {
                throw new \nre\exceptions\ViewNotFoundException($fileName);
            }

            // Save filename
            $this->templateFilename = $fileName;
        }

    }

?>
