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
			'name'			=>	'The Legend of Z',
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
			'locale'	=> 'locale',
			'media'		=> 'media',
			'seminarymedia'	=> 'seminarymedia',
			'questtypes'	=> 'questtypes',
			'temporary'	=> 'tmp',
			'uploads'	=> 'uploads'
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
			'ranking_range'			=> 2,
			'seldom_achievements_range'	=> 3
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
				'maxlength'	=> 128,
				'regex'		=> '/^\S*$/'
			),
			'surname' => array(
				'minlength'	=> 2,
				'maxlength'	=> 128,
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
			array('css/?(.*)',						'css/$1?layout=stylesheet',		true),
			array('users/([^/]+)/(edit|delete)',				'users/$2/$1',				true),
			array('users/(?!(index|login|register|logout|create|edit|delete))',	'users/user/$1',		true),
			array('seminaries/([^/]+)/(edit|delete)',			'seminaries/$2/$1',			true),
			array('seminaries/(?!(index|create|edit|delete))',		'seminaries/seminary/$1',		true),
			/*// z/<Seminary>					⇒ z/seminaries/seminary/<Seminary>
			array('^([^/]+)/*$',						'seminaries/seminary/$1',		true),
			// z/<Seminary>/<Questgroup>				⇒ z/questgroups/questgroup/<Seminary>/<Questgroup>
			array('^([^/]+)/([^/]+)/?$',					'questgropus/questgroup/$1/$2',		true),
			// z/<Seminary>/<Questgroup>/<Quest>			⇒ z/quests/quest/<Seminary>/<Questgroup>/<Quest>
			array('^([^/]+)/([^/]+)/([^/]+)/?$',				'quests/quest/$1/$2/3',			true)*/
			array('characters/(?!(index|character|register))',		'characters/index/$1',			true),
			array('charactergroups/(?!(index|groupsgroup|group))',		'charactergroups/index/$1',		true),
			array('charactergroupsquests/(?!(quest))',			'charactergroupsquests/quest/$1',	true),
			array('media/(.*)',						'media/$1?layout=binary',		false),
			array('uploads/(.*)',						'uploads/$1?layout=binary',		false),
			array('uploads/(?!(index))',					'uploads/index/$1',			true)
		);


		/**
		 * Reverse routes
		 * 
		 * @static
		 * @var array
		 */
		public static $reverseRoutes = array(
			array('users/user/(.*)',			'users/$1',			true),
			array('users/([^/]+)/(.*)',			'users/$2/$1',			true),
			array('seminaries/seminary/(.*)',		'seminaries/$1',		false),
			//array('seminaries/seminary/(.*)',		'$1',				false)
			array('characters/index/(.*)',			'characters/$1',		true),
			array('charactergroups/index/(.*)',		'charactergroups/$1',		true),
			array('charactergroupsquests/quest/(.*)',	'charactergroupsquests/$1',	true),
			array('uploads/index/(.*)',			'uploads/$1',			true)
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
