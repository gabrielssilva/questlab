<?php

    /**
     * NRE
     *
     * @author      coderkun <olli@coderkun.de>
     * @copyright   2013 coderkun (http://www.coderkun.de)
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        http://www.coderkun.de/projects/nre
     */

    namespace nre\core;


    /**
     * View.
     * 
     * Class to encapsulate a template file and to provide rendering methods.
     * 
     * @author  coderkun <olli@coderkun.de>
     */
    class View
    {
        /**
         * Template filename
         * 
         * @var string
         */
        protected $templateFilename;




        /**
         * Load and instantiate the View of an Agent.
         * 
         * @throws  \nre\exceptions\ViewNotFoundException
         * @param   string  $layoutName Name of Layout in use
         * @param   string  $agentName  Name of the Agent
         * @param   string  $action     Current Action
         * @param   bool    $isToplevel Agent is a ToplevelAgent
         */
        public static function loadAndFactory($layoutName, $agentName=null, $action=null, $isToplevel=false)
        {
            return new View($layoutName, $agentName, $action, $isToplevel);
        }




        /**
         * Construct a new View.
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
            $fileName = ROOT.DS. \nre\configs\CoreConfig::getClassDir('views').DS. strtolower($layoutName).DS;
            // AgentName and Action
            if(strtolower($agentName) != strtolower($layoutName) || !$isToplevel) {
                $fileName .= strtolower($agentName).DS.strtolower($action);
            }
            else {
                $fileName .= strtolower($layoutName);
            }
            // File extension
            $fileName .= \nre\configs\CoreConfig::getFileExt('views');


            // Check template file
            if(!file_exists($fileName)) {
                throw new \nre\exceptions\ViewNotFoundException($fileName);
            }

            // Save filename
            $this->templateFilename = $fileName;
        }




        /**
         * Generate output
         * 
         * @param   array   $data   Data to have available in the template file
         */
        public function render($data)
        {
            // Extract data
            if(!is_null($data)) {
                extract($data, EXTR_SKIP);
            }

            // Buffer output
            ob_start();

            // Include template
            include($this->templateFilename);


            // Return buffered output
            return ob_get_clean();
        }


        /**
         * Get template filename.
         * 
         * @return  string  Template filename
         */
        public function getTemplateFilename()
        {
            return $this->templateFilename;
        }

    }

?>
