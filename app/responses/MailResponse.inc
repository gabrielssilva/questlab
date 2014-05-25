<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	 
	namespace hhu\z\responses;
	
	
	/**
	 * Representation of a mail-response.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	class MailResponse extends \nre\core\Response
	{
		/**
		 * Mail subject
		 * 
		 * @var string
		 */
		private $subject = null;
		
		
		
		
		/**
		 * Set subject.
		 * 
		 * @param	string	$subject	Subject to set
		 */
		public function setSubject($subject)
		{
			$this->subject = $subject;
		}
		
		
		/**
		 * Get subject.
		 * 
		 * @return	string	Subject
		 */
		public function getSubject()
		{
			return $this->subject;
		}
		
	}

?>
