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
     * Controller of the Agent to display and manage userroles.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class UserrolesController extends \hhu\z\Controller
    {




        /**
         * Action: user.
         *
         * Show a user and its details.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $userUrl    URL-Username of an user
         */
        public function user($userUrl)
        {
            // Get userroles
            $roles = $this->Userroles->getUserrolesForUserByUrl($userUrl);


            // Pass data to view
            $this->set('roles', $roles);
        }


    }

?>
