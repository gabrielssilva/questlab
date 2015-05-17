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
     * Model to interact with the maps-table.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MapModel extends \hhu\z\Model
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('media');




        /**
         * Construct a new MapModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get the map of a Seminary.
         *
         * @param   int     $seminaryId ID of Seminary to get map of
         * @return  array               Map data
         */
        public function getMapOfSeminary($seminaryId)
        {
            $data = $this->db->query(
                'SELECT seminary_id, seminarymedia_id, width, height '.
                'FROM maps '.
                'WHERE seminary_id = ?',
                'i',
                $seminaryId
            );
            if(!empty($data)) {
                return $data[0];
            }


            return null;
        }


        /**
         * Set map of a Seminary.
         * 
         * @param   int $seminaryId         ID of Seminary to set map of
         * @param   int $seminarymediaId    ID of Seminary media of map to set
         */
        public function setMapOfSeminary($seminaryId, $seminarymediaId)
        {
            // Get image measurements
            $infos = $this->Media->getSeminarymediaInfos($seminarymediaId);

            // Insert record
            $this->db->query(
                'INSERT INTO maps '.
                '(seminary_id, seminarymedia_id, width, height) '.
                'VALUES '.
                '(?, ?, ?, ?) '.
                'ON DUPLICATE KEY UPDATE '.
                'seminarymedia_id = ?, width = ?, height = ?',
                'iiiiiii',
                $seminaryId, $seminarymediaId, $infos['width'], $infos['height'],
                $seminarymediaId, $infos['width'], $infos['height']
            );
        }


        /**
         * Copy the map of a Seminary.
         *
         * @param   int     $sourceSeminaryId   Seminary to copy from
         * @param   int     $targetSeminaryId   Seminary to copy to
         * @param   array   $seminaryMediaIds   Mapping of Seminarymedia-IDs from source Seminary to target Seminary
         */
        public function copyMapOfSeminary($sourceSeminaryId, $targetSeminaryId, $seminaryMediaIds)
        {
            // Get map of source Seminary
            $map = $this->getMapOfSeminary($sourceSeminaryId);

            // Set map of targetSeminary
            $this->setMapOfSeminary($targetSeminaryId, $seminaryMediaIds[$map['seminarymedia_id']]);
        }


        /**
         * Delete the map of a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to delete map of
         */
        public function deleteMapOfSeminary($seminaryId)
        {
            // Get map
            $map = $this->getMap($seminaryId);
            if(is_null($map)) {
                return;
            }

            // Delete map
            $this->db->setAutocommit(false);
            try {
                // Delete map record
                $this->db->query(
                    'DELETE FROM maps '.
                    'WHERE seminary_id = ?',
                    'i',
                    $seminaryId
                );

                // Delete Seminary media
                $this->Media->deleteSeminaryMedia($map['seminarymedia_id']);

                $this->db->commit();
            }
            catch(\nre\exceptions\DatamodelException $e) {
                $this->db->rollback();
            }
            $this->db->setAutocommit(true);
        }

    }

?>
