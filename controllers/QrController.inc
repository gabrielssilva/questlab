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
        public $models = array('seminaries', 'charactergroups', 'charactergroupsquests', 'charactergroupsqueststations', 'charactergroupsachievements');




        /**
         * Action: cgqs.
         *
         * Redirect to a Character groups Quest Station.
         *
         * @param   string  $stationHash    Hash of Character groups Quest Station
         */
        public function cgqs($stationHash)
        {
            // Get station
            $station = $this->Charactergroupsqueststations->getStationByHash($stationHash);

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


        /**
         * Action: cga.
         *
         * Redirect to a Character groups Achievements
         *
         * @param   string  $achievementHash    Hash of Character groups Achievement
         */
        public function cga($achievementHash)
        {
            // Get Achievement
            $achievement = $this->Charactergroupsachievements->getAchievementByHash($achievementHash);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupById($achievement['charactergroupsgroup_id']);

            // Get seminary
            $seminary = $this->Seminaries->getSeminaryById($groupsgroup['seminary_id']);

            // Redirect
            $this->redirect(
                $this->linker->link(
                    array(
                        'charactergroupsachievements',
                        'achievement',
                        $seminary['url'],
                        $groupsgroup['url'],
                        $achievement['hash']
                    )
                )
            );
        }

    }

?>
