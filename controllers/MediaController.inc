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
     * Controller of the MediaAgent to process and show Media.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class MediaController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * User permissions
         *
         * @var array
         */
        public $permissions = array(
            'index'                         => array('admin', 'moderator', 'user', 'guest'),
            'seminarymoodpic'               => array('admin', 'moderator', 'user'),
            'seminarymap'                   => array('admin', 'moderator', 'user'),
            'seminary'                      => array('admin', 'moderator', 'user'),
            'avatar'                        => array('admin', 'moderator', 'user'),
            'achievement'                   => array('admin', 'moderator', 'user'),
            'charactergroup'                => array('admin', 'moderator', 'user'),
            'charactergroupsquest'          => array('admin', 'moderator', 'user'),
            'charactergroupsqueststation'   => array('admin', 'moderator', 'user')
        );
        /**
         * User seminary permissions
         *
         * @var array
         */
        public $seminaryPermissions = array(
            'seminary'                      => array('admin', 'moderator', 'user', 'guest'),
            'achievement'                   => array('admin', 'moderator', 'user', 'guest'),
            'charactergroup'                => array('admin', 'moderator', 'user', 'guest'),
            'charactergroupsquest'          => array('admin', 'moderator', 'user', 'guest'),
            'charactergroupsqueststation'   => array('admin', 'moderator', 'user', 'guest')
        );
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'achievements', 'media', 'avatars', 'charactergroups', 'charactergroupsquests', 'charactergroupsqueststations', 'map');




        /**
         * Prefilter.
         *
         * @param   \nre\core\Request   $request    Current request
         * @param   \nre\core\Response  $response   Current response
         */
        public function preFilter(\nre\core\Request $request, \nre\core\Response $response)
        {
            parent::preFilter($request, $response);

            // Set headers for caching control
            $response->addHeader("Pragma: public");
            $response->addHeader("Cache-control: must-revalidate");
            $response->addHeader("Date: ".gmdate(\DateTime::RFC822));
        }


        /**
         * Action: index
         *
         * Display a medium.
         *
         * @param   string  $mediaUrl   URL-name of the medium
         * @param   string  $action     Action for processing the media
         */
        public function index($mediaUrl, $action=null)
        {
            // Check action
            if(!is_null($action) && !array_key_exists($action, \nre\configs\AppConfig::$media)) {
                throw new \nre\exceptions\ParamsNotValidException($action);
            }

            // Get Media
            $media = $this->Media->getMediaByUrl($mediaUrl);

            // Get file
            $file = $this->getMediaFile(
                $media, 
                (!is_null($action)) ? \nre\configs\AppConfig::$media[$action] : false
            );
            if(is_null($media)) {
                return;
            }


            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }


        /**
         * Action: seminarymoodpic
         *
         * Display the moodpic for a category of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of the Seminary
         * @param   string  $category   Category to show moodpic of
         * @param   string  $action     Action for processing the media
         */
        public function seminarymoodpic($seminaryUrl, $category=null, $action=null)
        {
            // Check action
            if(!is_null($action) && !array_key_exists($action, \nre\configs\AppConfig::$media)) {
                throw new \nre\exceptions\ParamsNotValidException($action);
            }

            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Set index
            switch($category)
            {
                case null:
                    $index = 'seminarymedia_id';
                break;
                case 'charactergroups':
                    $index = 'charactergroups_seminarymedia_id';
                break;
                case 'achievements':
                    $index = 'achievements_seminarymedia_id';
                break;
                case 'library':
                    $index = 'library_seminarymedia_id';
                break;
                case 'map':
                    $index = 'map_seminarymedia_id';
                break;
            }

            // Get media
            $media = $this->Media->getSeminaryMediaById($seminary[$index]);

            // Get file
            $file = $this->getMediaFile(
                $media,
                (!is_null($action)) ? \nre\configs\AppConfig::$media[$action] : false
            );
            if(is_null($file)) {
                return;
            }

            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }


        /**
         * Action: seminarymap
         *
         * Display the map of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of the Seminary
         */
        public function seminarymap($seminaryUrl)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get map
            $map = $this->Map->getMapOfSeminary($seminary['id']);
            if(is_null($map)) {
                throw new \nre\exceptions\IdNotFoundException($seminaryUrl);
            }

            // Get media
            $media = $this->Media->getSeminaryMediaById($map['seminarymedia_id']);

            // Get file
            $file = $this->getMediaFile($media);
            if(is_null($file)) {
                return;
            }

            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }


        /**
         * Action: seminary.
         *
         * Display a Seminary medium.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of the Seminary
         * @param   string  $mediaUrl   URL-name of the medium
         * @param   string  $action     Action for processing the media
         */
        public function seminary($seminaryUrl, $mediaUrl, $action=null)
        {
            // Check action
            if(!is_null($action) && !array_key_exists($action, \nre\configs\AppConfig::$media)) {
                throw new \nre\exceptions\ParamsNotValidException($action);
            }

            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Media
            $media = $this->Media->getSeminaryMediaByUrl($seminary['id'], $mediaUrl);

            // Get file
            $file = $this->getMediaFile(
                $media,
                (!is_null($action)) ? \nre\configs\AppConfig::$media[$action] : false
            );
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }


        /**
         * Action: avatar.
         *
         * Display an Avatar as full size or portrait.
         *
         * @throws  \nre\exceptions\ParamsNotValidException
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl        URL-title of the Seminary
         * @param   string  $charactertypeUrl   URL-title of Character type
         * @param   int $xplevel        XP-level
         * @param   string  $action         Size to show (avatar or portrait)
         */
        public function avatar($seminaryUrl, $charactertypeUrl, $xplevel, $action='avatar')
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Avatar
            $avatar = $this->Avatars->getAvatarByTypeAndLevel($seminary['id'], $charactertypeUrl, $xplevel);

            // Get media
            switch($action)
            {
                case null:
                case 'avatar':
                    $media = $this->Media->getSeminaryMediaById($avatar['avatarpicture_id']);
                    $file = $this->getMediaFile(
                        $media,
                        \nre\configs\AppConfig::$media['avatar']
                    );
                break;
                case 'portrait':
                    $media = $this->Media->getSeminaryMediaById($avatar['small_avatarpicture_id']);
                    $file = $this->getMediaFile($media);
                break;
                default:
                    throw new \nre\exceptions\ParamsNotValidException($action);
                break;
            }

            // Get file
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }


        /**
         * Action: achievement
         *
         * Display the achievement of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-title of the Seminary
         * @param   string  $achievementUrl URL-title of the Achievement
         * @param   string  $action     Action for processing the media
         */
        public function achievement($seminaryUrl, $achievementUrl, $locked=null)
        {
            // Get Seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character
            $character = SeminaryController::$character;

            // Get Achievement
            $achievement = $this->Achievements->getAchievementByUrl($seminary['id'], $achievementUrl);

            // Get media
            switch($locked)
            {
                case null:
                    if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) == 0) {
                        if(is_null($character) || !$this->Achievements->hasCharacterAchievedAchievement($achievement['id'], $character['id'])) {
                            throw new \nre\exceptions\AccessDeniedException();
                        }
                    }
                    $index = 'achieved_achievementsmedia_id';
                break;
                case 'locked':
                    $index = 'unachieved_achievementsmedia_id';
                break;
                default:
                    throw new \nre\exceptions\ParamsNotValidException($locked);
                break;
            }
            if(is_null($achievement[$index])) {
                throw new \nre\exceptions\IdNotFoundException($achievementUrl);
            }
            $media = $this->Media->getSeminaryMediaById($achievement[$index]);

            // Get file
            $file = $this->getMediaFile($media);
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }


        /**
         * Action: charactergroup
         *
         * Display the icon for a Character group of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $groupUrl   URL-Title of a Character group
         */
        public function charactergroup($seminaryUrl, $groupsgroupUrl, $groupUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character group
            $group = $this->Charactergroups->getGroupByUrl($groupsgroup['id'], $groupUrl);

            // Check media
            if(is_null($group['charactergroupsmedia_id'])) {
                $this->redirect($this->linker->link(array('grafics','charactergroup.jpg')));
            }

            // Get media
            $media = $this->Media->getSeminaryMediaById($group['charactergroupsmedia_id']);

            // Get file
            $file = $this->getMediaFile(
                $media,
                \nre\configs\AppConfig::$media['charactergroup']
            );
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }


        /**
         * Action: charactergroupsquest
         *
         * Display the icon for a Character groups Quest of a Seminary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl   URL-Title of a Character groups Quest
         */
        public function charactergroupsquest($seminaryUrl, $groupsgroupUrl, $questUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Check media
            if(is_null($quest['questsmedia_id'])) {
                $this->redirect($this->linker->link(array('grafics','charactergroup.jpg')));
            }

            // Get media
            $media = $this->Media->getSeminaryMediaById($quest['questsmedia_id']);

            // Get file
            $file = $this->getMediaFile(
                $media,
                \nre\configs\AppConfig::$media['charactergroupquest']
            );
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }


        /**
         * Action: charactergroupsqueststation
         *
         * Display the icon for a Character groups Quest Station.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         * @param   string  $stationUrl     URL-title of Station
         */
        public function charactergroupsqueststation($seminaryUrl, $groupsgroupUrl, $questUrl, $stationUrl)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get Station
            $station = $this->Charactergroupsqueststations->getStationByUrl($quest['id'], $stationUrl);

            // Get Character group(s)
            $stationgroups = null;
            $stationgroup = null;
            if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) {
                $stationgroups = $this->Charactergroups->getGroupsForGroupsgroup($groupsgroup['id']);
            }
            else
            {
                $character = $this->Characters->getCharacterForUserAndSeminary($this->Auth->getUserId(), $seminary['id']);
                $stationgroups = $this->Charactergroups->getGroupsForCharacter($character['id']);
                if(!empty($stationgroups)) {
                    $stationgroup = $stationgroups[0];
                }
            }
            // Select group by parameter
            $selectedStationGroupId = $this->request->getGetParam('stationgroup');
            if(!is_null($selectedStationGroupId))
            {
                $selectedStationGroupId = intval($selectedStationGroupId);
                foreach($stationgroups as &$group) {
                    if($group['id'] == $selectedStationGroupId) {
                        $stationgroup = $group;
                        break;
                    }
                }
            }

            // Status
            $solved = (count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0);
            if(!is_null($stationgroup)) {
                $solved = $this->Charactergroupsqueststations->hasCharactergroupSolvedStation(
                    $station['id'],
                    $stationgroup['id']
                );
            }

            // Get media
            $media = $this->Media->getSeminaryMediaById($station['stationpicture_id']);

            // Get file
            $file = $this->getMediaFile(
                $media,
                \nre\configs\AppConfig::$media['charactergroupsqueststation'],
                !$solved
            );
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('media', $media);
            $this->set('file', $file);
        }




        /**
         * Determine file information and set the HTTP-header for
         * caching accordingly.
         *
         * @param   string  $fileName   Filename
         * @return  boolean         HTTP-status 304 was set (in cache)
         */
        private function setCacheHeaders($fileName)
        {
            // Determine last change of file
            $fileLastModified = gmdate('r', filemtime($fileName));

            // Generate E-Tag
            $fileEtag = hash('sha256', $fileLastModified.$fileName);


            // Set header
            $this->response->addHeader("Last-Modified: ".$fileLastModified);
            $this->response->addHeader("Etag: ".$fileEtag);
            // HTTP-status
            $headerModifiedSince = $this->request->getServerParam('HTTP_IF_MODIFIED_SINCE');
            $headerNoneMatch = $this->request->getServerParam('HTTP_IF_NONE_MATCH');
            if(
                !is_null($headerModifiedSince) && strtotime($fileLastModified) <= strtotime($headerModifiedSince) &&
                !is_null($headerNoneMatch) && $headerNoneMatch == $fileEtag
            ) {
                $this->response->setExit(true);
                $this->response->addHeader(\nre\core\WebUtils::getHttpHeader(304));

                return true;
            }


            return false;
        }


        /**
         * Determine the file for a medium and process it if necessary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @throws  \nre\exceptions\ParamsNotValidException
         * @param   array   $media      Medium to get file for
         * @param   mixed   $resize     Size to resize image to
         * @param   boolean $grayscale  Whether to grayscale image or not
         * @return  object              File for the medium (or null if medium is cached)
         */
        private function getMediaFile($media, $resize=false, $grayscale=false)
        {
            // Get format
            $format = explode('/', $media['mimetype']);
            $format = $format[1];

            // Set content-type
            $this->response->addHeader("Content-type: ".$media['mimetype']."");

            // Set filename
            $media['filename'] = ROOT.DS.\nre\configs\AppConfig::$dirs['seminarymedia'].DS.$media['id'];
            if(!file_exists($media['filename'])) {
                throw new \nre\exceptions\IdNotFoundException($media['id'].': '.$media['url']);
            }

            // Cache
            if($this->setCacheHeaders($media['filename'])) {
                return null;
            }

            // Determine processing
            $resize = (is_array($resize)) ? $resize : false;
            $grayscale = ($grayscale === true);

            // Load image without processing
            if((!$grayscale && $resize === false) || !in_array(strtoupper($format), self::getImageTypes()))
            {
                // Do not process the file
                return file_get_contents($media['filename']);
            }

            // Read image from cache
            $tempFileName = ROOT.DS.\nre\configs\AppConfig::$dirs['temporary'].DS.'media-'.basename($media['filename']).'-'.$resize['width'].'x'.$resize['height'].'-'.(int) $grayscale;
            if(file_exists($tempFileName))
            {
                // Check age of file
                if(filemtime($media['filename']) > filemtime($tempFileName)) {
                    // Too old, delete
                    unlink($tempFileName);
                }
                else {
                    // Valid, read and return
                    return file_get_contents($tempFileName);
                }
            }

            // Load file with ImageMagick
            $file = new \Imagick($media['filename']);

            // Apply grayscale
            if($grayscale) {
                self::grayscaleImage($file);
            }

            // Risize image
            if($resize !== false) {
                self::resizeImage($file, $resize['width'], $resize['height']);
            }

            // Save temporary file
            $file->setImageFormat($format);
            $file->writeImage($tempFileName);


            // Return file
            return $file;
        }


        /**
         * Get supported image types.
         *
         * @return  array   List of supported image types
         */
        private static function getImageTypes()
        {
            $im = new \Imagick();


            return $im->queryFormats();
        }


        /**
         * Resize an image.
         *
         * @param   \Imagick    $im     Image object
         * @param   int         $width  Max. width to resize to
         * @param   int         $height Max. height to resize to
         */
        private static function resizeImage($im, $width, $height)
        {
            // Calculate new size
            $geometry = $im->getImageGeometry();
            if($geometry['width'] < $width) {
                $width = $geometry['width'];
            }
            if($geometry['height'] < $height) {
                $height = $geometry['width'];
            }

            // Process
            $im->thumbnailImage($width, $height, true);
            $im->contrastImage(1);
        }


        /**
         * Turn the colors of an image into grayscale.
         *
         * @param   \Imagick    $im Image object
         */
        private static function grayscaleImage($im)
        {
            $im->modulateImage(100, 0, 100);
        }

    }

?>
