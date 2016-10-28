<?php

    /**
     * Questlab
     *
     * @author      Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     * @copyright   2014 – 2016 Heinrich-Heine-Universität Düsseldorf
     * @license     http://www.gnu.org/licenses/gpl.html
     * @link        https://github.com/coderkun/questlab
     */

    namespace hhu\z;


    /**
     * Class for implementing utility methods.
     *
     * @author  Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
     */
    class Utils
    {
        /**
         * String length for hashes
         *
         * @var int
         */
        const HASH_LENGTH = 10;




        /**
         * Mask HTML-chars for save output.
         *
         * @static
         * @param   string  $string String to be masked
         * @return  string      Masked string
         */
        public static function t($string)
        {
            return nl2br(htmlspecialchars($string));
        }


        /**
         * ‚htmlspecialchars‘ with support for UTF-8.
         *
         * @static
         * @param   string  $string String to be masked
         * @return  string      Masked string
         */
        public static function htmlspecialchars_utf8($string)
        {
            return htmlspecialchars($string, ENT_COMPAT, 'UTF-8');
        }


        /**
         * Cut a string to the given length but only word boundaries.
         *
         * @static
         * @param   string  $string String to cut
         * @param   int $length Length to cut string
         * @param   int $scope  Maximum length to cut string regardless word boundaries
         * @return  string      Cutted string
         */
        public static function shortenString($string, $length, $scope)
        {
            // Determine length
            $length = min($length, strlen($string));

            // Look for word boundary
            if(($pos = strpos($string, ' ', $length)) !== false)
            {
                // Check if boundary is outside of scope
                if($pos > $length + $scope) {
                    $pos = strrpos(substr($string, 0, $pos), ' ');
                }
            }
            else {
                $pos = strlen($string);
            }


            // Cut string and return it
            return substr($string, 0, $pos);
        }


        /**
         * Send an e‑mail.
         *
         * @throws  \hhu\z\exceptions\MailingException
         * @param   mixed           $to     One (string) or many (array) receivers
         * @param   string          $messageAction  Message Action
         * @param   boolean         $html       Whether mail should be formatted as HTML or not
         * @param   array           $params     Parameters to pass
         * @param   \nre\core\Linker    $linker     Linker instance
         */
        public static function sendMail($to, $messageAction, $html=false, $params=null, $linker=null)
        {
            // Check configuration
            if(
                empty(\nre\configs\AppConfig::$mail['host']) ||
                empty(\nre\configs\AppConfig::$mail['port']) ||
                empty(\nre\configs\AppConfig::$mail['username'])
            ) {
                return;
            }

            // Load classes
            \hhu\z\lib\PHPMailerAutoload::load();
            \hhu\z\lib\PHPMailer::load();
            \hhu\z\lib\SMTP::load();

            // Create mailer
            $mail = new \PHPMailer();

            // Configure mailer
            $mail->isSMTP();
            $mail->Host = \nre\configs\AppConfig::$mail['host'];
            $mail->Port = \nre\configs\AppConfig::$mail['port'];
            $mail->SMTPAuth = true;
            $mail->Username = \nre\configs\AppConfig::$mail['username'];
            $mail->Password = \nre\configs\AppConfig::$mail['password'];
            $mail->SMTPSecure = \nre\configs\AppConfig::$mail['secure'];

            // Set properties
            $mail->CharSet = 'UTF-8';
            $mail->From = \nre\configs\AppConfig::$app['mailsender'];
            $mail->FromName = \nre\configs\AppConfig::$app['name'];
            if(!is_array($to)) {
                $to = array($to);
            }
            foreach($to as &$receiver) {
                $mail->addAddress($receiver);
            }
            if($html) {
                $mail->isHTML(true);
            }

            // Create message
            try {
                // Create MailApi
                $mailApi = new \hhu\z\apis\MailApi();
                if(!is_null($linker)) {
                    $mailApi->setLinker($linker);
                }
                $mailApi->setMessage($messageAction);
                $mailApi->setParams($params);
                if($html) {
                    $mailApi->setHTML();
                }

                // Render message
                $exception = $mailApi->run();
                if(!is_null($exception)) {
                    return $exception;
                }
                $mail->Subject = $mailApi->getSubject();
                $mail->Body = $mailApi->render();

                // Try to render alternativ plaintext message
                if($html)
                {
                    $mailApi->setHTML(false);

                    // Render message
                    $exception = $mailApi->run();
                    if(is_null($exception))
                    {
                        try {
                            $mail->AltBody = $mailApi->render();
                        }
                        catch(\nre\core\Exception $e) {
                            // No alternative plaintext available
                        }
                    }
                }
            }
            catch(\nre\core\Exception $e) {
                throw new \hhu\z\exceptions\MailingException($e->getMessage());
            }


            // Return status
            if(!$mail->send()) {
                throw new \hhu\z\exceptions\MailingException($mail->ErrorInfo);
            }
        }


        /**
         * Detect Mimetype of a file.
         *
         * @param   string  $filename       Name of file to detect Mimetype of
         * @param   string  $defaultMimetype    Default Mimetype to use
         * @return  string              Detected Mimetype of file
         */
        public static function getMimetype($filename, $defaultMimetype=null)
        {
            $mimetype = (!is_null($defaultMimetype)) ? $defaultMimetype : 'application/octet-stream';
            // Use Fileinfo
            if(class_exists('\finfo'))
            {
                $finfo = new \finfo(FILEINFO_MIME_TYPE);
                if(!is_null($finfo)) {
                    $mimetype = $finfo->file($filename);
                }
            }
            // Use deprecated mime_content_type()
            elseif(function_exists('mime_content_type')) {
                $mimetype = mime_content_type($filename);
            }


            return $mimetype;
        }


        /**
         * Create a random hash string.
         *
         * @param   int     Length of string
         * @return  string  String with random characters
         */
        public static function createRandomHash($length=self::HASH_LENGTH)
        {
            // Length of URL
            $length = max(0, min(32, $length));


            // Create and return random string
            return substr(md5(microtime()), rand(0, 32-$length), $length);
        }

    }

?>
