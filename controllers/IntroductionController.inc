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
     * Controller of the Agent to show an introduction page.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class IntroductionController extends \hhu\z\controllers\IntermediateController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('pages');




        /**
         * Action: index.
         */
        public function index()
        {
            // Get introduction text
            $page = $this->Pages->getPageByUrl(\hhu\z\models\PagesModel::PAGEURL_INTRODUCTION);
            $text = (!is_null($page)) ? $page['text'] : null;


            // Pass data to view
            $this->set('userId', $this->Auth->getUserId());
            $this->set('text', $text);
        }


        /**
         * Action: edit.
         */
        public function edit()
        {
            // Get page
            $page = $this->Pages->getPageByUrl(\hhu\z\models\PagesModel::PAGEURL_INTRODUCTION);

            // Values
            $text = (!is_null($page)) ? $page['text'] : null;

            // Check request method
            if($this->request->getRequestMethod() == 'POST')
            {
                if(!is_null($this->request->getPostParam('edit')))
                {
                    // Get values
                    $text = $this->request->getPostParam('text');

                    // Create page if necessary
                    if(is_null($page)) {
                        $pageId = $this->Pages->createPage(
                            $this->Auth->getUserId(),
                            \hhu\z\models\PagesModel::PAGEURL_INTRODUCTION
                        );
                        $page = $this->Pages->getPageById($pageId);
                    }

                    // Save text
                    $this->Pages->editPage(
                        $page['id'],
                        $page['title'],
                        $text
                    );
                }

                // Redirect
                $this->redirect($this->linker->link(array('index'), 1));
            }


            // Pass data to view
            $this->set('text', $text);
        }

    }

?>
