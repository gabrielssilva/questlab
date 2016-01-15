<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\apis;


    /**
     * MailApi-implementation.
     *
     * This class runs and renders e‑mail text and subject.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MailApi extends \nre\core\Api
    {




        /**
         * Construct a new MailApi.
         */
        public function __construct()
        {
            parent::__construct(
                new \hhu\z\requests\MailRequest(),
                new \hhu\z\responses\MailResponse()
            );

            // Set ToplevelAgent
            $this->request->addParam(\nre\configs\AppConfig::$defaults['toplevel-mail']);
            $this->request->addParam(\nre\configs\AppConfig::$defaults['intermediate-mail']);
        }




        /**
         * Set linker instance for creating links.
         *
         * @param   \nre\core\Linker    $linker Linker instance for creating links
         */
        public function setLinker(\nre\core\Linker $linker)
        {
            $this->request->setLinker($linker);
        }


        /**
         * Use a ToplevelAgent for HTML-mail
         *
         * @param   bool    $html   Whether to use HTML or not
         */
        public function setHTML($html=true)
        {
            // Save params
            $params = $this->request->getParams(1);

            // Set ToplevelAgent
            $this->request->clearParams();
            if($html) {
                $this->request->addParam(\nre\configs\AppConfig::$defaults['toplevel-htmlmail']);
            }
            else {
                $this->request->addParam(\nre\configs\AppConfig::$defaults['toplevel-mail']);
            }

            // Restore params
            if(!empty($params)) {
                $this->addParams($params);
            }
        }


        /**
         * Set the Action for the message to render.
         *
         * @param   string  $messageAgent   Agent to handle the message
         */
        public function setMessage($messageAgent)
        {
            // Save params
            $params = $this->request->getParams(3);

            // Set messageAgent
            $this->request->clearParams(2);
            $this->request->addParam($messageAgent);

            // Restore params
            if(!empty($params)) {
                $this->addParams($params);
            }
        }


        /**
         * Set additional params to pass to the Action.
         *
         * @param   array   $params Additional params to set
         */
        public function setParams($params)
        {
            // Add placeholder params
            for($i=3; $i<count($this->request->getParams()); $i++) {
                $this->request->addParam(null);
            }

            // Set params
            call_user_func_array(
                array(
                    $this->request,
                    'addParams'
                ),
                $params
            );
        }


        /**
         * Return the subject set by the Controller.
         *
         * @return  string  Subject set by Controller
         */
        public function getSubject()
        {
            return $this->response->getSubject();
        }


        /**
         * Run mailtext generation.
         *
         * This method runs the generation of mailtext.
         *
         * @return  \Exception  Occured exception or null
         */
        public function run()
        {
            // Set response
            $this->response->clearParams();
            foreach($this->request->getParams() as $param) {
                $this->response->addParam($param);
            }

            // Run
            try {
                $exception = parent::run();


                return $exception;
            }
            catch(\nre\Exception $e) {
                return $e;
            }
        }


        /**
         * Render output.
         *
         * @return  string  Rendered output
         */
        public function render()
        {
            // Generate output
            parent::render();


            // Return output
            return $this->response->getOutput();
        }




        /**
         * Add multiple request params.
         *
         * @param   array   $params Request params to add
         */
        private function addParams($params)
        {
            call_user_func_array(
                array(
                    $this->request,
                    'addParams'
                ),
                $params
            );
        }

    }

?>
