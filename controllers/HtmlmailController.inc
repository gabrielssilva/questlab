<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\controllers;


    /**
     * Controller of the HtmlmailAgent for generating a HTML-mail message.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class HtmlmailController extends \nre\core\Controller
    {




        /**
         * Prefilter.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::preFilter($request, $response);


            // Set linker
            $this->set('linker', ($request instanceof \hhu\z\requests\MailRequest && !is_null($request->getLinker())) ? $request->getLinker() : null);
        }


        /**
         * Action: index.
         *
         * Create HTML-structure of mail message.
         */
        public function index()
        {
            $this->set('appname', \nre\configs\AppConfig::$app['name']);
        }

    }

?>
