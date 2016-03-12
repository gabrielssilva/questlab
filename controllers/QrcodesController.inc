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
     * Controller of the QrcodeAgent to generate and show QR-codes.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class QrcodesController extends \hhu\z\controllers\SeminaryController
    {
        /**
         * Required models
         *
         * @var array
         */
        public $models = array('seminaries', 'achievements', 'charactergroups', 'charactergroupsquests', 'charactergroupsqueststations', 'charactergroupsachievements');




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
         * Action: achievement
         *
         * Display a QR-code for an Achievement.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $achievementUrl URL of Achievement
         */
        public function achievement($seminaryUrl, $achievementUrl, $size=1)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Achievement
            $achievement = $this->Achievements->getAchievementByUrl(
                $seminary['id'],
                $achievementUrl
            );

            // Get condition
            $conditions = $this->Achievements->getAchievementConditionsQrcode(
                $achievement['id']
            );
            if(empty($conditions)) {
                throw new IdNotFoundException($achievementUrl);
            }

            // Generate QR-code
            $url = $this->linker->link(array('qr', 'a', $conditions[0]['hash']), 0, true, null, true, null, true);
            $file = $this->generateQRcode($url, $size);
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('file', $file);
        }


        /**
         * Action: charactergroupsqueststation
         *
         * Display a QR-code for a Character groups Quest station.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $questUrl       URL-Title of a Character groups Quest
         * @param   string  $stationUrl     URL of Character groups Quest station
         */
        public function charactergroupsqueststation($seminaryUrl, $groupsgroupUrl, $questUrl, $stationUrl, $size=1)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Character groups Quests
            $quest = $this->Charactergroupsquests->getQuestByUrl($groupsgroup['id'], $questUrl);

            // Get station
            $station = $this->Charactergroupsqueststations->getStationByUrl($quest['id'], $stationUrl);

            // Generate QR-code
            $url = $this->linker->link(array('qr', 'cgqs', $station['url']), 0, true, null, true, null, true);
            $file = $this->generateQRcode($url, $size);
            if(is_null($file)) {
                return;
            }


            // Pass data to view
            $this->set('file', $file);
        }


        /**
         * Action: charactergroupsachievements
         *
         * Display a QR-code for a Character groups Achievement
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @param   string  $seminaryUrl    URL-Title of a Seminary
         * @param   string  $groupsgroupUrl URL-Title of a Character groups-group
         * @param   string  $achievementUrl URL of Achievement
         */
        public function charactergroupsachievements($seminaryUrl, $groupsgroupUrl, $achievementUrl, $size=1)
        {
            // Get seminary
            $seminary = $this->Seminaries->getSeminaryByUrl($seminaryUrl);

            // Get Character groups-group
            $groupsgroup = $this->Charactergroups->getGroupsgroupByUrl($seminary['id'], $groupsgroupUrl);

            // Get Achievement
            $achievement = $this->Charactergroupsachievements->getAchievementByUrl(
                $groupsgroup['id'],
                $achievementUrl
            );

            // Generate QR-code
            $url = $this->linker->link(array('qr', 'cga', $achievement['hash']), 0, true, null, true, null, true);
            $file = $this->generateQRcode($url, $size);
            if(is_null($file)) {
                return;
            }


            // Pass data to view
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


        private function generateQRcode($text, $size)
        {
            \hhu\z\lib\Phpqrcode::load();
            \QRcode::png($text, false, QR_ECLEVEL_L, intval($size), 1);


            return null;
        }


        /**
         * Determine the file for a medium and process it if necessary.
         *
         * @throws  \nre\exceptions\IdNotFoundException
         * @throws  \nre\exceptions\ParamsNotValidException
         * @param   array   $media  Medium to get file for
         * @param   string  $action Action for processing the media
         * @return  object      File for the medium (or null if medium is cached)
         */
        private function getMediaFile($media, $action=null)
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

            // Load and process file
            $file = null;
            if(is_null($action) || !in_array(strtoupper($format), self::getImageTypes()))
            {
                // Do not process the file
                $file = file_get_contents($media['filename']);
            }
            else
            {
                // Process file
                switch($action)
                {
                    case 'questgroup':
                    case 'quest':
                    case 'avatar':
                    case 'charactergroup':
                    case 'charactergroupsquest':
                        $file = self::resizeImage(
                            $media['filename'],
                            $format,
                            \nre\configs\AppConfig::$media[$action]['width'],
                            \nre\configs\AppConfig::$media[$action]['height']
                        );
                    break;
                    default:
                        throw new ParamsNotValidException($action);
                    break;
                }
            }


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
         * @param   string  $fileName   Absolute pathname of image to resize
         * @param   string  $mimeType   Mimetype of target image
         * @param   int $width      Max. width to resize to
         * @param   int $height     Max. height to resize to
         * @return  mixed           Resized image
         */
        private static function resizeImage($fileName, $mimeType, $width, $height)
        {
            // Read image from cache
            $tempFileName = ROOT.DS.\nre\configs\AppConfig::$dirs['temporary'].DS.'media-'.basename($fileName).'-'.$width.'x'.$height;
            if(file_exists($tempFileName))
            {
                // Check age of file
                if(filemtime($fileName) > filemtime($tempFileName)) {
                    // Too old, delete
                    unlink($tempFileName);
                }
                else {
                    // Valid, read and return
                    return file_get_contents($tempFileName);
                }
            }


            // ImageMagick
            $im = new \Imagick($fileName);

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
            $im->setImageFormat($mimeType);

            // Save temporary file
            $im->writeImage($tempFileName);


            // Return resized image
            return $im;
        }

    }

?>
