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
     * Controller of the QrAgent to redirect to a page from a (short) QR-code
     * link.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QrController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'charactergroups', 'charactergroupsquests', 'charactergroupsqueststations');




        /**
         * Action: cgqs.
         *
         * Redirect to a Character groups Quest Station.
         *
         * @param   int $stationId  ID of Character groups Quest Station
         */
        public function cgqs($stationId)
        {
            // Get station
            $station = $this->Charactergroupsqueststations->getStationById($stationId);

            // Get Character groups Quests
            $quest = $this->Charactergroupsquests->getQuestById($station['charactergroupsquest_id']);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupById($quest['charactergroupsgroup_id']);

            // Get seminary
            $seminary = $this->Seminaries->getSeminaryById($groupsgroup['seminary_id']);

            // Redirect
            $this->redirect($this->linker->link(array(
                'charactergroupsqueststations',
                'station',
                $seminary['url'],
                $groupsgroup['url'],
                $quest['url'],
                $station['url']
            )));
        }

    }

?>
