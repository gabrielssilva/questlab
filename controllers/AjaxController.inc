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
     * Controller of the AjaxAgent to return a JSON-string used by AJAX.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class AjaxController extends \hhu\z\Controller
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

            // Set content-type
            $this->response->addHeader("Content-type: application/json; charset=utf-8");
        }


        /**
         * Action: index.
         *
         * Create the JSON-string.
         */
        public function index()
        {
        }

    }

?>
