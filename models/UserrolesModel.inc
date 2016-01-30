<?php

    /**
     * The Legend of Z
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://bitbucket.org/coderkun/the-legend-of-z
     */

    namespace hhu\z\models;


    /**
     * Model to interact with userroles-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class UserrolesModel extends \hhu\z\Model
    {




        /**
         * Construct a new UserrolesModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get all userroles for an user referenced by its ID.
         *
         * @param   int $userId ID of an user
         * @return  array       Userroles for an user
         */
        public function getUserrolesForUserById($userId)
        {
            return $this->db->query(
                'SELECT userroles.id, userroles.created, userroles.name '.
                'FROM users_userroles '.
                'LEFT JOIN userroles ON userroles.id = users_userroles.userrole_id '.
                'WHERE users_userroles.user_id = ?',
                'i',
                $userId
            );
        }


        /**
         * Get all userroles for an user referenced by its URL-username.
         *
         * @param   string  $userUrl    URL-Username of an user
         * @return  array           Userroles for an user
         */
        public function getUserrolesForUserByUrl($userUrl)
        {
            return $this->db->query(
                'SELECT userroles.id, userroles.created, userroles.name '.
                'FROM users '.
                'LEFT JOIN users_userroles ON users_userroles.user_id = users.id '.
                'LEFT JOIN userroles ON userroles.id = users_userroles.userrole_id '.
                'WHERE users.url = ?',
                's',
                $userUrl
            );
        }


        /**
         * Add a role to a user.
         *
         * @param   int $userId     ID of user to add role to
         * @param   string  $userrole   Role to add
         */
        public function addUserroleToUser($userId, $userrole)
        {
            $this->db->query(
                'INSERT IGNORE INTO users_userroles '.
                '(user_id, userrole_id) '.
                'SELECT ?, id '.
                'FROM userroles '.
                'WHERE name = ?',
                'is',
                $userId,
                $userrole
            );
        }


        /**
         * Remove a role from a user.
         *
         * @param   int $userId     ID of user to remove role from
         * @param   string  $userrole   Role to remove
         */
        public function removeUserroleFromUser($userId, $userrole)
        {
            $this->db->query(
                'DELETE FROM users_userroles '.
                'WHERE user_id = ? AND userrole_id = ('.
                    'SELECT id '.
                    'FROM userroles '.
                    'WHERE name = ?'.
                ')',
                'is',
                $userId,
                $userrole
            );
        }

    }

?>
