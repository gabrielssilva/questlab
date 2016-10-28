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
     * Controller of the MailreceiverAgent to generate a mail receiver
     * salutation.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MailreceiverController extends \nre\core\Controller
    {




        /**
         * Action: index.
         *
         * @param   array   $user   User receiving mail
         */
        public function index($user)
        {
            $this->set('user', $user);
        }

    }

?>
