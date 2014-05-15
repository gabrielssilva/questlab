<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace hhu\z;
	
	
	/**
	 * Class for implementing utility methods.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class Utils
	{
		
		
		/**
		 * Mask HTML-chars for save output.
		 * 
		 * @static
		 * @param	string	$string	String to be masked
		 * @return	string		Masked string
		 */
		public static function t($string)
		{
			return nl2br(htmlspecialchars($string));
		}
		
		
		/**
		 * ‚htmlspecialchars‘ with support for UTF-8.
		 * 
		 * @static
		 * @param	string	$string	String to be masked
		 * @return	string		Masked string
		 */
		public static function htmlspecialchars_utf8($string)
		{
			return htmlspecialchars($string, ENT_COMPAT, 'UTF-8');
		}
		
		
		/**
		 * Cut a string to the given length but only word boundaries.
		 * 
		 * @static
		 * @param	string	$string	String to cut
		 * @param	int	$length	Length to cut string
		 * @param	int	$scope	Maximum length to cut string regardless word boundaries
		 * @return	string		Cutted string
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
		 * @param	string	$from		Sender of mail
		 * @param	mixed	$to		One (string) or many (array) receivers
		 * @param	string	$subject	Subject of mail
		 * @param	string	$message	Message of mail
		 * @param	boolean	$html		Whether mail should be formatted as HTML or not
		 * @return				Whether mail has been send or not
		 */
		public static function sendMail($from, $to, $subject, $message, $html=false)
		{
			// Set receivers
			$to = is_array($to) ? implode(',', $to) : $to;
			
			// Set header
			$headers = array();
			$headers[] = 'Content-type: text/'.($html ? 'html' : 'plain').'; charset=UTF-8';
			if(!is_null($from)) {
				$headers[] = "From: $from";
			}
			$header = implode("\r\n", $headers)."\r\n";
			
			
			// Send mail
			return mail($to, $subject, $message, $header);
		}
		
		
		/**
		 * Detect Mimetype of a file.
		 * 
		 * @param	string	$filename		Name of file to detect Mimetype of
		 * @param	string	$defaultMimetype	Default Mimetype to use
		 * @return	string				Detected Mimetype of file
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
		
	}

?>
