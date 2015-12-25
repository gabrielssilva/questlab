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
     * Model to interact with stationtypes-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class StationtypesModel extends \hhu\z\Model
    {




        /**
         * Construct a new Model.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get all registered Stationtypes.
         *
         * @return  array   List of registered Stationtypes
         */
        public function getStationtypes()
        {
            return $this->db->query(
                'SELECT id, title, url, classname '.
                'FROM stationtypes '.
                'ORDER BY title ASC'
            );
        }


        /**
         * Get a Stationtype by its ID.
         *
         * @param   int     $stationtypeId  ID of Stationtype
         * @return  array                   Stationtype data
         */
        public function getStationtypeById($stationtypeId)
        {
            $data = $this->db->query(
                'SELECT title, classname '.
                'FROM stationtypes '.
                'WHERE id = ?',
                'i',
                $stationtypeId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($stationtypeId);
            }


            return $data = $data[0];
        }

    }

?>
