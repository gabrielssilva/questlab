<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z\models;


    /**
     * Model to interact with Questtypes-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QuesttypesModel extends \hhu\z\Model
    {




        /**
         * Construct a new QuesttypesModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get all registered Questtypes.
         *
         * @return  array   List of registered Questtypes
         */
        public function getQuesttypes()
        {
            return $this->db->query(
                'SELECT id, title, url, classname '.
                'FROM questtypes '.
                'ORDER BY title ASC'
            );
        }


        /**
         * Get a Questtype by its ID
         *
         * @param   int $questtypeId    ID of Questtype
         * @return  array           Questtype data
         */
        public function getQuesttypeById($questtypeId)
        {
            $data = $this->db->query(
                'SELECT title, classname '.
                'FROM questtypes '.
                'WHERE id = ?',
                'i',
                $questtypeId
            );
            if(empty($data)) {
                throw new \nre\exceptions\IdNotFoundException($questtypeId);
            }


            return $data = $data[0];
        }

    }

?>
