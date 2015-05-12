<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\controllers\components;


    /**
     * Component to handle user notifications
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class NotificationComponent extends \nre\core\Component
    {
        /**
         * Type: Achievement
         *
         * @var string
         */
        const TYPE_ACHIEVEMENT = 'achievement';
        /**
         * Type: Level-up
         *
         * @var string
         */
        const TYPE_LEVELUP = 'levelup';
        /**
         * Key for Session-Array to store notifications in
         *
         * @var string
         */
        const SESSION_KEY = 'notifications';




        /**
         * Construct a new Notification-component.
         */
        public function __construct()
        {
            // Start session
            if(session_id() === '') {
                session_start();
            }

            // Prepare array
            if(!array_key_exists(self::SESSION_KEY, $_SESSION)) {
                $_SESSION[self::SESSION_KEY] = array();
            }
        }




        /**
         * Add a notification.
         *
         * @param   string  $type       Type of notification
         * @param   string  $message    Message to display
         * @param   string  $link       Optional URL to link to
         * @param   string  $image      Optional URL of image to display
         */
        public function addNotification($type, $message, $link=null, $image=null)
        {
            $_SESSION[self::SESSION_KEY][] = array(
                'type'      => $type,
                'message'   => $message,
                'link'      => $link,
                'image'     => $image
            );
        }


        /**
         * Get all registered notifiactions and clear them.
         *
         * @return  array   List of existing notifications
         */
        public function getNotifications()
        {
            $notifications = $_SESSION[self::SESSION_KEY];
            $this->clearNotifications();


            return $notifications;
        }


        /**
         * Clear all notifications currently registered
         */
        public function clearNotifications()
        {
            unset($_SESSION[self::SESSION_KEY]);
            $_SESSION[self::SESSION_KEY] = array();
        }

    }

?>
