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
     * Model of the SeminariesAgent to list registered seminaries.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class SeminariesModel extends \hhu\z\Model
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('questgroupshierarchy', 'questgroups', 'quests', 'questtopics', 'media', 'characters', 'charactertypes', 'xplevels', 'avatars', 'achievements', 'charactergroups', 'charactergroupsquests', 'charactergroupsqueststations', 'charactergroupsachievements', 'seminarycharacterfields', 'map', 'uploads');




        /**
         * Construct a new SeminariesModel.
         */
        public function __construct()
        {
            parent::__construct();
        }




        /**
         * Get registered seminaries.
         *
         * @return  array   Seminaries
         */
        public function getSeminaries()
        {
            // Get seminaries
            return $this->db->query(
                'SELECT id, created, created_user_id, title, url, course, description, seminarymedia_id, charactergroups_seminarymedia_id, achievements_seminarymedia_id, library_seminarymedia_id, map_seminarymedia_id '.
                'FROM seminaries '.
                'ORDER BY created DESC'
            );
        }


        /**
         * Get a seminary and its data by its ID.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryId ID of a seminary
         * @return  array           Seminary
         */
        public function getSeminaryById($seminaryId)
        {
            $seminary = $this->db->query(
                'SELECT id, created, created_user_id, title, url, course, description, latitude, longitude, seminarymedia_id, charactergroups_seminarymedia_id, achievements_seminarymedia_id, library_seminarymedia_id, map_seminarymedia_id '.
                'FROM seminaries '.
                'WHERE id = ?',
                'i',
                $seminaryId
            );
            if(empty($seminary)) {
                throw new \nre\exceptions\IdNotFoundException($seminaryId);
            }


            return $seminary[0];
        }


        /**
         * Get a seminary and its data by its URL-title.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a seminary
         * @return  array           Seminary
         */
        public function getSeminaryByUrl($seminaryUrl)
        {
            $seminary = $this->db->query(
                'SELECT id, created, created_user_id, title, url, course, description, latitude, longitude, seminarymedia_id, charactergroups_seminarymedia_id, achievements_seminarymedia_id, library_seminarymedia_id, map_seminarymedia_id '.
                'FROM seminaries '.
                'WHERE url = ?',
                's',
                $seminaryUrl
            );
            if(empty($seminary)) {
                throw new \nre\exceptions\IdNotFoundException($seminaryUrl);
            }


            return $seminary[0];
        }


        /**
         * Calculate sum of XPs for a Seminary.
         *
         * @param   int $seminaryId ID of Seminary
         * @return  int         Total sum of XPs
         */
        public function getTotalXPs($seminaryId)
        {
            $xps = 0;

            // Questgroups
            $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyOfSeminary($seminaryId);
            foreach($questgroupshierarchy as &$hierarchy)
            {
                // Get Questgroups
                $questgroups = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id']);
                foreach($questgroups as &$questgroup) {
                    $xps += $questgroup['achievable_xps'];
                }
            }


            return $xps;
        }


        /**
         * Check if a Seminary title already exists.
         *
         * @param   string  $title      Seminary title to check
         * @param   int $seminaryId Do not check this ID (for editing)
         * @return  boolean         Whether Seminary title exists or not
         */
        public function seminaryTitleExists($title, $seminaryId=null)
        {
            $data = $this->db->query(
                'SELECT id '.
                'FROM seminaries '.
                'WHERE title = ? OR url = ?',
                'ss',
                $title,
                \nre\core\Linker::createLinkParam($title)
            );

            return (!empty($data) && (is_null($seminaryId) || $seminaryId != $data[0]['id']));
        }


        /**
         * Create a new Seminary.
         *
         * @param   int $userId     ID of creating user
         * @param   string  $title      Title of Seminary to create
         * @param   string  $course     Course of Seminary
         * @param   string  $description    Description of new Seminary
         * @return  int         ID of the newly created Seminary
         */
        public function createSeminary($userId, $title, $course, $description)
        {
            $this->db->query(
                'INSERT INTO seminaries '.
                '(created_user_id, title, url, course, description) '.
                'VALUES '.
                '(?, ?, ?, ?, ?)',
                'issss',
                $userId,
                $title,
                \nre\core\Linker::createLinkParam($title),
                $course,
                $description
            );


            return $this->db->getInsertId();
        }


        /**
         * Set the moodpic for a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to set moodpic for
         * @param   int $mediaId    ID of moodpic media
         */
        public function setMoodpicForSeminary($seminaryId, $mediaId)
        {
            $this->db->query(
                'UPDATE seminaries '.
                'SET seminarymedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $mediaId,
                $seminaryId
            );
        }


        /**
         * Set the moodpic for the Character groups of a Seminary.
         *
         * @param   int $seminaryId         ID of Seminary to set moodpic for Character groups for
         * @param   int $seminaryMediaId    ID of Seminarymedia to set as moodpic
         */
        public function setMoodpicForCharactergroups($seminaryId, $seminaryMediaId)
        {
            $this->db->query(
                'UPDATE seminaries '.
                'SET charactergroups_seminarymedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $seminaryMediaId,
                $seminaryId
            );
        }


        /**
         * Set the moodpic for the Achievements of a Seminary.
         *
         * @param   int $seminaryId         ID of Seminary to set moodpic for Achievements for
         * @param   int $seminaryMediaId    ID of Seminarymedia to set as moodpic
         */
        public function setMoodpicForAchievements($seminaryId, $seminaryMediaId)
        {
            $this->db->query(
                'UPDATE seminaries '.
                'SET achievements_seminarymedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $seminaryMediaId,
                $seminaryId
            );
        }


        /**
         * Set the moodpic for the library of a Seminary.
         *
         * @param   int $seminaryId         ID of Seminary to set moodpic for Library for
         * @param   int $seminaryMediaId    ID of Seminarymedia to set as moodpic
         */
        public function setMoodpicForLibrary($seminaryId, $seminaryMediaId)
        {
            $this->db->query(
                'UPDATE seminaries '.
                'SET library_seminarymedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $seminaryMediaId,
                $seminaryId
            );
        }


        /**
         * Set the moodpic for the map of a Seminary.
         *
         * @param   int $seminaryId         ID of Seminary to set moodpic for Map for
         * @param   int $seminaryMediaId    ID of Seminarymedia to set as moodpic
         */
        public function setMoodpicForMap($seminaryId, $seminaryMediaId)
        {
            $this->db->query(
                'UPDATE seminaries '.
                'SET map_seminarymedia_id = ? '.
                'WHERE id = ?',
                'ii',
                $seminaryMediaId,
                $seminaryId
            );
        }


        /**
         * (Re-) Calculate the amount of achievable XPs for a Seminary.
         *
         * @param   int $seminaryId ID of Seminary to calculate XPs for
         */
        public function calculateXPsForSeminary($seminaryId)
        {
            // Questgrouphierarchy and Questgroups
            $questgroupshierarchy = $this->Questgroupshierarchy->getHierarchyOfSeminary($seminaryId);
            foreach($questgroupshierarchy as &$hierarchy)
            {
                // Get Questgroups
                $hierarchy['questgroups'] = $this->Questgroups->getQuestgroupsForHierarchy($hierarchy['id']);
                foreach($hierarchy['questgroups'] as &$questgroup)
                {
                    // Calculate achievable XPs
                    $this->Questgroups->calculateXPsForQuestgroup($questgroup['id']);
                }
            }
        }


        /**
         * Edit a seminary.
         *
         * @throws  \nre\exceptions\DatamodelException
         * @param   int $seminaryId ID of Seminary to edit
         * @param   string  $title      New title of Seminary
         * @param   string  $course     New course of Seminary
         * @param   string  $description    New description of Seminary
         */
        public function editSeminary($seminaryId, $title, $course, $description, $latitude, $longitude)
        {
            $this->db->query(
                'UPDATE seminaries '.
                'SET title = ?, url = ?, course = ?, description = ?, latitude = ?, longitude = ? '.
                'WHERE id = ?',
                'ssssddi',
                $title,
                \nre\core\Linker::createLinkParam($title),
                $course,
                $description,
                $latitude,
                $longitude,
                $seminaryId
            );
        }


        /**
         * Copy a Seminary and its content.
         *
         * @param   int     $userId                             ID of copying user
         * @param   int     $sourceSeminaryId                   ID of Seminary to copy
         * @param   string  $title                              Title of new Seminary
         * @param   string  $course                             Course of now Seminary
         * @param   string  $description                        Description of new Seminary
         * @param   boolean $copySeminaryfields                 Whether to copy Seminary Character fields of not
         * @param   boolean $copyMedia                          Whether to copy media or not
         * @param   boolean $copyQuestgroupshierarchy           Whether to copy Questgroupshierarchy or not
         * @param   boolean $copyQuestgroups                    Whether to copy Questgroups or not
         * @param   boolean $copyQuests                         Whether to copy Quests or not
         * @param   boolean $copyQuesttopics                    Whether to copy Quest topics or not
         * @param   boolean $copyCharactertypes                 Whether to copy Charactertypes or not
         * @param   boolean $copyXPlevels                       Whether to copy XP-levels or not
         * @param   boolean $copyAvatars                        Whether to copy Avatars or not
         * @param   boolean $copyAchievements                   Whether to copy Achievements or not
         * @param   boolean $copyCharactergroupsgroups          Whether to copy Character groups-groups or not
         * @param   boolean $copyCharactergroupsquests          Whether to copy Character groups Quests or not
         * @param   boolean $copyCharactergroupsqueststations   Whether to copy Character groups Quest Stations or not
         * @param   boolean $copyCharactergroupsachievements    Whether to copy Character groups Achievements or not
         * @param   boolean $copyMap                            Whether to copy Map or not
         * @return                                              ID of newly created Seminary
         */
        public function copySeminary($userId, $sourceSeminaryId, $title, $course, $description, $copySeminaryfields, $copyMedia, $copyQuestgroupshierarchy, $copyQuestgroups, $copyQuests, $copyQuesttopics, $copyCharactertypes, $copyXPlevels, $copyAvatars, $copyAchievements, $copyCharactergroupsgroups, $copyCharactergroupsquests, $copyCharactergroupsqueststations, $copyCharactergroupsachievements, $copyMap)
        {
            // Get Seminary
            $seminary = $this->getSeminaryById($sourceSeminaryId);

            // Copy Seminary
            $this->db->setAutocommit(false);
            try {
                // Create new Seminary
                $targetSeminaryId = $this->createSeminary($userId, $title, $course, $description);

                // Copy Seminary fields
                if($copySeminaryfields) {
                    $this->Seminarycharacterfields->copyFieldsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId);
                }

                // Copy media
                $seminaryMediaIds = null;
                if($copyMedia)
                {
                    $seminaryMediaIds = $this->Media->copySeminaryMedia($userId, $sourceSeminaryId, $targetSeminaryId);
                    // Set Seminary media
                    if(!is_null($seminary['seminarymedia_id'])) {
                        $this->setMoodpicForSeminary($targetSeminaryId, $seminaryMediaIds[$seminary['seminarymedia_id']]);
                    }
                    if(!is_null($seminary['charactergroups_seminarymedia_id'])) {
                        $this->setMoodpicForCharactergroups($targetSeminaryId, $seminaryMediaIds[$seminary['charactergroups_seminarymedia_id']]);
                    }
                    if(!is_null($seminary['achievements_seminarymedia_id'])) {
                        $this->setMoodpicForAchievements($targetSeminaryId, $seminaryMediaIds[$seminary['achievements_seminarymedia_id']]);
                    }
                    if(!is_null($seminary['library_seminarymedia_id'])) {
                        $this->setMoodpicForLibrary($targetSeminaryId, $seminaryMediaIds[$seminary['library_seminarymedia_id']]);
                    }
                    if(!is_null($seminary['map_seminarymedia_id'])) {
                        $this->setMoodpicForMap($targetSeminaryId, $seminaryMediaIds[$seminary['map_seminarymedia_id']]);
                    }
                }

                // Copy Quest content
                $questIds = null;
                $questgroupIds = null;
                // Questgroupshierarchy
                if($copyQuestgroupshierarchy)
                {
                    $questgroupshierarchyIds = $this->Questgroupshierarchy->copyQuestgroupshierarchy($userId, $sourceSeminaryId, $targetSeminaryId);
                    // Questgroups
                    if($copyQuestgroups)
                    {
                        $questgroupIds = $this->Questgroups->copyQuestgroupsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId, $questgroupshierarchyIds, $seminaryMediaIds);
                        $this->Questgroups->copyQuestgroupsHierarchy($questgroupshierarchyIds, $questgroupIds);
                        // Quests
                        if($copyQuests)
                        {
                            $questAndTextIds = $this->Quests->copyQuests($userId, $sourceSeminaryId, $questgroupIds, $seminaryMediaIds);
                            $questIds = $questAndTextIds['quests'];
                            $questtextIds = $questAndTextIds['questtexts'];
                            $this->Questgroups->copyRelatedQuestgroups($questgroupIds, $questtextIds);
                            // Questtopics
                            if($copyQuesttopics) {
                                $questsubtopicIds = $this->Questtopics->copyQuesttopicsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId, $questIds);
                            }
                        }
                    }
                }

                // Copy Character content
                // Charactertypes
                if($copyCharactertypes)
                {
                    $charactertypeIds = $this->Charactertypes->copyCharactertypesOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId);
                    // XP-levels
                    if($copyXPlevels)
                    {
                        $xplevelIds = $this->Xplevels->copyXPLevelsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId);
                        // Avatars
                        if($copyAvatars && !is_null($seminaryMediaIds)) {
                            $this->Avatars->copyAvatars($userId, $charactertypeIds, $xplevelIds, $seminaryMediaIds);
                        }
                    }
                }

                // Copy Achievements
                if($copyAchievements && !is_null($seminaryMediaIds)) {
                    $this->Achievements->copyAchievementsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId, $seminaryMediaIds, $questIds);
                }

                // Copy Charactergroups content
                // Charactergroupsgroups
                $characterGroupsgroupIds = null;
                $charactergroupsquestIds = null;
                if($copyCharactergroupsgroups)
                {
                    $characterGroupsgroupIds = $this->Charactergroups->copyGroupsgroupsOfSeminary($userId, $sourceSeminaryId, $targetSeminaryId);
                    // Copy Charactergroupsquests
                    if($copyCharactergroupsquests &!is_null($questgroupIds)) {
                        $charactergroupsquestIds = $this->Charactergroupsquests->copyQuestsOfSeminary($userId, $characterGroupsgroupIds, $questgroupIds, $seminaryMediaIds);
                        if($copyCharactergroupsqueststations && !is_null($charactergroupsquestIds)) {
                            $this->Charactergroupsqueststations->copyStationsOfSeminary($userId, $charactergroupsquestIds, $seminaryMediaIds);
                        }
                    }
                    // Copy Charactergroupsachievements
                    if($copyCharactergroupsachievements) {
                        $this->Charactergroupsachievements->copyAchievementsOfSeminary($userId, $characterGroupsgroupIds, $seminaryMediaIds);
                    }
                }

                // Copy Map
                if($copyMap && !is_null($seminaryMediaIds)) {
                    $this->Map->copyMapOfSeminary($sourceSeminaryId, $targetSeminaryId, $seminaryMediaIds);
                }

                // Recalculate XPs
                $this->calculateXPsForSeminary($targetSeminaryId);

                $this->db->commit();
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }
            $this->db->setAutocommit(true);


            return $targetSeminaryId;
        }


        /**
         * Delete a seminary.
         *
         * @param   int $seminaryId ID of the seminary to delete
         */
        public function deleteSeminary($seminaryId)
        {
            $this->db->setAutocommit(false);
            try {
                // Map
                $this->Map->deleteMapOfSeminary($seminaryId);

                // Charactergroups content
                $this->Charactergroups->deleteGroupsgroupsOfSeminary($seminaryId);

                // Achievements
                $this->Achievements->deleteAchievementsOfSeminary($seminaryId);

                // Character content
                // Delete Characters
                $characters = $this->Characters->getCharactersForSeminary($seminaryId);
                foreach($characters as &$character) {
                    $this->Characters->deleteCharacter($character['id']);
                }
                // Delete Avatars
                $charactertypes = $this->Charactertypes->getCharacterTypesForSeminary($seminaryId);
                $charactertypeIds = array_map(function($type) { return $type['id']; }, $charactertypes);
                $xplevels = $this->Xplevels->getXPLevelsForSeminary($seminaryId);
                $xplevelIds = array_map(function($level) { return $level['id']; }, $xplevels);
                $this->Avatars->deleteAvatars($charactertypeIds, $xplevelIds);
                // Delete XP-levels
                $this->Xplevels->deleteXPLevelsOfSeminary($seminaryId);
                // Delete Charactertypes
                $this->Charactertypes->deleteCharactertypesOfSeminary($seminaryId);

                // Delete Quests content
                // Delete Quest topics
                $this->Questtopics->deleteQuesttopicsOfSeminary($seminaryId);
                // Delete Quests
                $this->Quests->deleteQuestsOfSeminary($seminaryId);
                // Delete Questgroups
                $this->Questgroups->deleteQuestgroupsOfSeminary($seminaryId);
                // Delete Questgroupshierarchy
                $this->Questgroupshierarchy->deleteQuestgroupshierarchyOfSeminary($seminaryId);

                // Media
                $this->Media->deleteSeminaryMediaOfSeminary($seminaryId);

                // Uploads
                $this->Uploads->deleteSeminaryUploadsOfSeminary($seminaryId);

                // Delete Seminary
                $this->db->query('DELETE FROM seminaries WHERE id = ?', 'i', $seminaryId);
            }
            catch(\Exception $e) {
                $this->db->rollback();
                $this->db->setAutocommit(true);
                throw $e;
            }
            $this->db->setAutocommit(true);
        }

    }

?>
