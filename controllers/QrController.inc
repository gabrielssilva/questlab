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
        public $models = array('seminaries', 'achievements', 'charactertitles', 'charactergroups', 'charactergroupsquests', 'charactergroupsqueststations', 'charactergroupsachievements');




        /**
         * Action: a.
         *
         * Trigger an Achievement by a hash typically provided via a QR-code.
         *
         * @param   $achievementConditionHash   Hash value of QR-code condition of an Achievement
         */
        public function a($achievementConditionHash)
        {
            // Check Achievement condition
            $condition = $this->Achievements->getAchievementConditionQrcode(
                $achievementConditionHash
            );
            if(empty($condition)) {
                throw new \nre\exceptions\IdNotFoundException($achievementConditionHash);
            }

            // Get Achievement
            $achievement = $this->Achievements->getAchievementById($condition['achievement_id']);

            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryById($achievement['seminary_id']);

            // Get Character
            $character = $this->Characters->getCharacterForUserAndSeminary(
                self::$user['id'],
                $seminary['id']
            );

            // Set Achievement achieved
            $this->Achievements->setAchievementAchieved(
                $achievement['id'],
                $character['id']
            );

            // Add notification
            $this->Notification->addNotification(
                \hhu\z\controllers\components\NotificationComponent::TYPE_ACHIEVEMENT,
                $achievement['title'],
                $this->linker->link(
                    array(
                        'achievements',
                        'index',
                        $seminary['url']
                    ), 0, true, null, true, $achievement['url']
                ),
                (
                    !is_null($achievement['achieved_achievementsmedia_id'])
                        ? $this->linker->link(
                            array(
                                'media',
                                'achievement',
                                $seminary['url'],
                                $achievement['url']
                            )
                        )
                        : null
                )
            );

            // Redirect to Character profile
            $this->redirect(
                $this->linker->link(
                    array(
                        'achievements',
                        'index',
                        $seminary['url']
                    )
                )
            );
        }


        /**
         * Action: ct.
         *
         * Trigger a Character title by a hash typically provided via a QR-code.
         *
         * @param   $titleHash  Hash value of Character title
         */
        public function ct($titleHash)
        {
            // Get Character title
            $title = $this->Charactertitles->getTitleByHash($titleHash);

            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryById($title['seminary_id']);

            // Get Character
            $character = $this->Characters->getCharacterForUserAndSeminary(
                self::$user['id'],
                $seminary['id']
            );

            // Assign title to Character
            $this->Charactertitles->assignTitleToCharacter(
                $title['id'],
                $character['id']
            );

            // Add notification
            $this->Notification->addNotification(
                \hhu\z\controllers\components\NotificationComponent::TYPE_CHARACTERTITLE,
                ($character['gender'] === 1)
                    ? $title['title_male']
                    : $title['title_female']
            );

            // Redirect
            $this->redirect(
                $this->linker->link(
                    array(
                        'characters',
                        'character',
                        $seminary['url'],
                        $character['url']
                    )
                )
            );
        }


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
