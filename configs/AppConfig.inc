<?php

	/**
	 * The Legend of Z
	 *
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 * @copyright	2014 Heinrich-Heine-Universität Düsseldorf
	 * @license	http://www.gnu.org/licenses/gpl.html
	 * @link	https://bitbucket.org/coderkun/the-legend-of-z
	 */
	
	namespace nre\configs;
	
	
	/**
	 * Application configuration.
	 * 
	 * This class contains static variables with configuration values for
	 * the specific application.
	 * 
	 * @author	Oliver Hanraths <oliver.hanraths@uni-duesseldorf.de>
	 */
	final class AppConfig
	{
		
		/**
		 * Application values
		 * 
		 * @static
		 * @var array
		 */
		public static $app = array(
			'name'			=>	'Questlab',
			'genericname'		=>	'The Legend of Z',
			'namespace'		=>	'hhu\\z\\',
			'timeZone'		=>	'Europe/Berlin',
			'mailsender'		=>	'noreply@zyren.inf-d.de'
		);
		
		
		/**
		 * Default values
		 * 
		 * @static
		 * @var array
		 */
		public static $defaults = array(
			'toplevel'		=>	'html',
			'toplevel-error'	=>	'fault',
			'intermediate'		=>	'introduction',
			'intermediate-error'	=>	'error',
			'language'		=>	'de_DE.utf8',
			'locale'		=>	'de-DE'
		);
		
		
		/**
		 * Directories
		 * 
		 * @static
		 * @var array
		 */
		public static $dirs = array(
			'locale'		=> 'locale',
			'media'			=> 'media',
			'seminarymedia'		=> 'seminarymedia',
			'questtypes'		=> 'questtypes',
			'temporary'		=> 'tmp',
			'uploads'		=> 'uploads',
			'seminaryuploads'	=> 'seminaryuploads'
		);
		
		
		/**
		 * Media sizes
		 *
		 * @static
		 * @var array
		 */
		public static $media = array(
			'questgroup' => array(
				'width'		=> 480,
				'height'	=> 5000
			),
			'avatar' => array(
				'width'		=> 500,
				'height'	=> 500
			)
		);
		
		
		/**
		 * Miscellaneous settings
		 * 
		 * @static
		 * @var array
		 */
		public static $misc = array(
			'ranking_range'		=> 2,
			'achievements_range'	=> 3
		);
		
		
		/**
		 * Validation settings for user input
		 * 
		 * @static
		 * @var array
		 */
		public static $validation = array(
			'username' => array(
				'minlength'	=> 5,
				'maxlength'	=> 32,
				'regex'		=> '/^\w*$/'
			),
			'email' => array(
				'regex'		=> '/^\S+@[\w\d.-]{2,}\.[\w]{2,6}$/iU'
			),
			'prename' => array(
				'minlength'	=> 2,
				'maxlength'	=> 32,
				'regex'		=> '/^\S*$/'
			),
			'surname' => array(
				'minlength'	=> 2,
				'maxlength'	=> 32,
				'regex'		=> '/^\S*$/'
			),
			'password' => array(
				'minlength'	=> 5,
				'maxlength'	=> 64
			),
			'charactername' => array(
				'minlength'	=> 5,
				'maxlength'	=> 32,
				'regex'		=> '/^\w*$/'
			)
		);
		
		
		/**
		 * Routes
		 *
		 * @static
		 * @var array
		 */
		public static $routes = array(
			array('^users/([^/]+)/(edit|delete)/?$',				'users/$2/$1',			true),
			array('^users/(?!(index|login|register|logout|create|edit|delete))/?',	'users/user/$1',		true),
			array('^seminaries/([^/]+)/(edit|delete)/?$',				'seminaries/$2/$1',		true),
			array('^seminaries/(?!(index|create|edit|delete))/?',			'seminaries/seminary/$1',	true),
			array('^questgroups/([^/]+)/(create)/?$',				'questgroups/$2/$1',		true),
			array('^questgroups/([^/]+)/([^/]+)/?$',				'questgroups/questgroup/$1/$2',	true),
			array('^quests/([^/]+)/(create|createmedia)/?$',			'quests/$2/$1'	,		true),
			array('^quests/([^/]+)/([^/]+)/([^/]+)/(submissions)/?$',		'quests/$4/$1/$2/$3',		true),
			array('^quests/([^/]+)/([^/]+)/([^/]+)/(submission)/([^/]+)/?$',	'quests/$4/$1/$2/$3/$5',	true),
			array('^quests/(?!(index|create|createmedia))/?',			'quests/quest/$1',		true),
			array('^characters/([^/]+)/(register|manage)/?$',			'characters/$2/$1',		true),
			array('^characters/([^/]+)/?$',						'characters/index/$1',		true),
			array('^characters/([^/]+)/(?!(index|create|register|manage))/?',	'characters/character/$1/$2',	true),
			array('^charactergroups/([^/]+)/?$',					'charactergroups/index/$1',	true),
			array('^charactergroups/([^/]+)/([^/]+)/?$',				'charactergroups/groupsgroup/$1/$2',	true),
			array('^charactergroups/([^/]+)/([^/]+)/(managegroup)/?$',		'charactergroups/$3/$1/$2',	true),
			array('^charactergroups/([^/]+)/([^/]+)/(?!(managegroup))/?',		'charactergroups/group/$1/$2/$3',	true),
			array('^charactergroupsquests/([^/]+)/([^/]+)/([^/]+)/?$',		'charactergroupsquests/quest/$1/$2/$3',	true),
			array('^achievements/([^/]+)/?$',					'achievements/index/$1',	true),
			array('^library/([^/]+)/?$',						'library/index/$1',		true),
			array('^library/([^/]+)/([^/]+)/?$',					'library/topic/$1/$2',		true),
			array('^media/(.*)$',							'media/$1?layout=binary',	false),
			array('^uploads/(.*)$',							'uploads/$1?layout=binary',	false)
		);


		/**
		 * Reverse routes
		 * 
		 * @static
		 * @var array
		 */
		public static $reverseRoutes = array(
			array('^users/user/(.*)$',			'users/$1',			true),
			array('^users/([^/]+)/(.*)$',			'users/$2/$1',			true),
			array('^seminaries/seminary/(.*)$',		'seminaries/$1',		false),
			array('^questgroups/create/(.*)$',		'questgroups/$2/$1',		true),
			array('^questgroups/questgroup/(.*)$',		'questgroups/$1',		true),
			array('^quests/quest/(.*)$',			'quests/$1',			true),
			array('^quests/(create|createmedia)/(.*)$',	'quests/$2/$1'	,		true),
			array('^quests/(submissions|submission)/(.*)$',	'quests/$2/$1',			true),
			array('^characters/(index|character)/(.*)$',	'characters/$2',		true),
			array('^characters/(register|manage)/(.*)$',	'characters/$2/$1',		true),
			array('^charactergroups/(index|group)/(.*)$',	'charactergroups/$2',		true),
			array('^charactergroups/groupsgroup/(.*)$',	'charactergroups/$1',		true),
			array('^charactergroups/(managegroup)/(.*)$',	'charactergroups/$2/$1',	true),
			array('^charactergroupsquests/quest/(.*)$',	'charactergroupsquests/$1',	true),
			array('^achievements/index/(.*)$',		'achievements/$1',		true),
			array('^library/(index|topic)/(.*)$',		'library/$2',			true)
		);
		
		
		/**
		 * Database connection settings
		 * 
		 * @static
		 * @var array
		 */
		public static $database = array(
			'user'		=> 'z',
			'host'		=> 'localhost',
			'password'	=> 'legendofZ',
			'db'		=> 'z'
		);
		
	}

?>
