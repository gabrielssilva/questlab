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
			'mailsender'		=>	'questlab@hhu.de'
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
			'toplevel-mail'		=>	'textmail',
			'toplevel-htmlmail'	=>	'htmlmail',
			'intermediate'		=>	'introduction',
			'intermediate-error'	=>	'error',
			'intermediate-mail'	=>	'mail',
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
			),
			'charactergroup' => array(
				'width'		=> 80,
				'height'	=> 80
			),
			'charactergroupsquest' => array(
				'width'		=> 80,
				'height'	=> 80
			)
		);
		
		
		/**
		 * Allowed mimetypes with sizes
		 * 
		 * @static
		 * @var array
		 */
		public static $mimetypes = array(
			'icons' => array(
				array(
					'mimetype'	=> 'image/jpeg',
					'size'		=> 102400
				),
				array(
					'mimetype'	=> 'image/png',
					'size'		=> 204800
				)
			),
			'moodpics' => array(
				array(
					'mimetype'	=> 'image/jpeg',
					'size'		=> 524288
				),
				array(
					'mimetype'	=> 'image/png',
					'size'		=> 1048576
				)
			),
			'charactergroupsquests' => array(
				array(
					'mimetype'	=> 'image/jpeg',
					'size'		=> 1048576
				)
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
			'achievements_range'	=> 3,
			'title_delimiter'	=> ' – ',
			'lists_limit'		=> 10
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
				'maxlength'	=> 12,
				'regex'		=> '/^\w*$/'
			),
			'email' => array(
				'regex'		=> '/^\S+@[\w\d.-]{2,}\.[\w]{2,6}$/iU'
			),
			'prename' => array(
				'minlength'	=> 2,
				'maxlength'	=> 32,
				'regex'		=> '/^(\S| )*$/'
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
				'maxlength'	=> 12,
				'regex'		=> '/^\w*$/'
			),
			'charactergroupsgroupname' => array(
				'minlength'	=> 4,
				'maxlength'	=> 32,
				'regex'		=> '/^(\S| )*$/'
			),
			'preferred' => array(
				'regex'		=> '/^(0|1)$/'
			),
			'charactergroupname' => array(
				'minlength'	=> 4,
				'maxlength'	=> 32,
				'regex'		=> '/^(\S| )*$/'
			),
			'motto' => array(
				'maxlength'	=> 128
			),
			'title' => array(
				'minlength'	=> 4,
				'maxlength'	=> 32,
				'regex'		=> '/^(\S| )*$/'
			),
			'xps' => array(
				'minlength'	=> 1,
				'regex'		=> '/^(\d*)$/'
			),
			'course' => array(
				'maxlength'	=> 128
			),
			'charactertypename' => array(
				'minlength'	=> 1,
				'maxlength'	=> 32
			),
			'questgroupshierarchytitle' => array(
				'minlength'	=> 1,
				'maxlength'	=> 64
			),
			'deadline' => array(
				'regex'		=> '/^(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})?$/'
			),
			'choice' => array(
				'minlength'	=> 1,
				'maxlength'	=> 128
			),
			'answer' => array(
				'minlength'	=> 1,
				'maxlength'	=> 255
			)
		);
		
		
		/**
		 * Routes
		 *
		 * @static
		 * @var array
		 */
		public static $routes = array(
			array('^users/all/?$',								'users/index/all',		true),
			array('^users/([^/]+)/(edit|delete)/?$',					'users/$2/$1',			true),
			array('^users/(?!(index|login|register|logout|manage|create|edit|delete))/?',	'users/user/$1',		true),
			array('^seminaries/([^/]+)/(edit|delete)/?$',				'seminaries/$2/$1',			true),
			array('^seminaries/(?!(index|create|edit|delete|calculatexps))/?',	'seminaries/seminary/$1',		true),
			array('^xplevels/([^/]+)/(manage)/?$',					'xplevels/$2/$1',			true),
			array('^questgroupshierarchy/([^/]+)/create/?$',				'questgroupshierarchy/create/$1',	true),
			array('^questgroupshierarchy/([^/]+)/([^/]+)/(edit|delete|moveup|movedown)/?$',	'questgroupshierarchy/$3/$1/$2',	true),
			array('^questgroups/([^/]+)/create/?$',							'questgroups/create/$1',		true),
			array('^questgroups/([^/]+)/([^/]+)/(edit|edittexts|delete|moveup|movedown)/?$',	'questgroups/$3/$1/$2',			true),
			array('^questgroups/([^/]+)/([^/]+)/?$',						'questgroups/questgroup/$1/$2',		true),
			array('^quests/([^/]+)/?$',									'quests/index/$1',		true),
			array('^quests/([^/]+)/all/?$',									'quests/index/$1/all',		true),
			array('^quests/([^/]+)/([^/]+)/(create|createmedia)/?$',					'quests/$3/$1/$2',		true),
			array('^quests/([^/]+)/([^/]+)/([^/]+)/(submissions|edit|edittask|edittexts|delete)/?$',	'quests/$4/$1/$2/$3',		true),
			array('^quests/([^/]+)/([^/]+)/([^/]+)/(submission)/([^/]+)/?$',				'quests/$4/$1/$2/$3/$5',	true),
			array('^quests/(?!(index|create|createmedia))/?',						'quests/quest/$1',		true),
			array('^characters/([^/]+)/(register|manage)/?$',			'characters/$2/$1',			true),
			array('^characters/([^/]+)/?$',						'characters/index/$1',			true),
			array('^characters/([^/]+)/all/?$',					'characters/index/$1/all',		true),
			array('^characters/([^/]+)/([^/]+)/(edit|delete)/?$',			'characters/$3/$1/$2',			true),
			array('^characters/([^/]+)/(?!(index|register|manage))/?',		'characters/character/$1/$2',		true),
			array('^charactertypes/([^/]+)/?$',				'charactertypes/index/$1',	true),
			array('^charactertypes/([^/]+)/create/?$',			'charactertypes/create/$1',	true),
			array('^charactertypes/([^/]+)/([^/]+)/(edit|delete)/?$',	'charactertypes/$3/$1/$2',	true),
			array('^charactergroups/([^/]+)/?$',						'charactergroups/index/$1',			true),
			array('^charactergroups/([^/]+)/(create)/?$',					'charactergroups/creategroupsgroup/$1/$2',	true),
			array('^charactergroups/([^/]+)/([^/]+)/?$',					'charactergroups/groupsgroup/$1/$2',		true),
			array('^charactergroups/([^/]+)/([^/]+)/(edit|delete)/?$',			'charactergroups/$3groupsgroup/$1/$2',		true),
			array('^charactergroups/([^/]+)/([^/]+)/(create)/?$',				'charactergroups/creategroup/$1/$2/$3',		true),
			array('^charactergroups/([^/]+)/([^/]+)/([^/]+)/?$',				'charactergroups/group/$1/$2/$3',		true),
			array('^charactergroups/([^/]+)/([^/]+)/([^/]+)/(manage|edit|delete)/?$',	'charactergroups/$4group/$1/$2/$3',		true),
			array('^charactergroupsquests/([^/]+)/([^/]+)/create/?$',			'charactergroupsquests/create/$1/$2',	true),
			array('^charactergroupsquests/([^/]+)/([^/]+)/([^/]+)/?$',			'charactergroupsquests/quest/$1/$2/$3',	true),
			array('^charactergroupsquests/([^/]+)/([^/]+)/([^/]+)/(edit|delete|manage)/?$',	'charactergroupsquests/$4/$1/$2/$3',	true),
			array('^achievements/([^/]+)/(create|manage)/?$',					'achievements/$2/$1',		true),
			array('^achievements/([^/]+)/([^/]+)/(edit|conditions|moveup|movedown|delete)/?$',	'achievements/$3/$1/$2',	true),
			array('^achievements/([^/]+)/?$',							'achievements/index/$1',	true),
			array('^library/([^/]+)/?$',						'library/index/$1',		true),
			array('^library/([^/]+)/create/?$',					'library/create/$1',		true),
			array('^library/([^/]+)/([^/]+)/?$',					'library/topic/$1/$2',		true),
			array('^library/([^/]+)/([^/]+)/(edit|delete|manage)/?$',		'library/$3/$1/$2',		true),
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
			array('^users/index/all$',			'users/all',			true),
			array('^users/user/(.*)$',			'users/$1',			true),
			array('^users/([^/]+)/(.*)$',			'users/$2/$1',			true),
			array('^seminaries/seminary/(.*)$',		'seminaries/$1',		false),
			array('^xplevels/(manage)/(.*)$',		'xplevels/$2/$1',		false),
			array('^questgroupshierarchy/create/(.*)$',	'questgroupshierarchy/$1/create',		true),
			array('^questgroupshierarchy/([^/]+)/(.*)$',	'questgroupshierarchy/$2/$1',			true),
			array('^questgroups/create/(.*)$',					'questgroups/$1/create',	true),
			array('^questgroups/questgroup/(.*)$',					'questgroups/$1',		true),
			array('^questgroups/(edit|edittexts|delete|moveup|movedown)/(.*)$',	'questgroups/$2/$1',		true),
			array('^quests/index/(.+)$',								'quests/$1',			true),
			array('^quests/quest/(.*)$',								'quests/$1',			true),
			array('^quests/(create|createmedia)/(.*)$',						'quests/$2/$1'	,		true),
			array('^quests/(submissions|edit|edittask|edittexts|delete)/([^/]+)/([^/]+)/([^/]+)$',	'quests/$2/$3/$4/$1',		true),
			array('^quests/(submission)/([^/]+)/([^/]+)/([^/]+)/([^/]+)$',				'quests/$2/$3/$4/$1/$5',	true),
			array('^characters/(index|character)/(.*)$',			'characters/$2',		true),
			array('^characters/(register|manage)/([^/]+)$',			'characters/$2/$1',		true),
			array('^characters/(edit|delete)/([^/]+)/([^/]+)$',		'characters/$2/$3/$1',		true),
			array('^charactertypes/index/([^/]+)$',			'charactertypes/$1',		true),
			array('^charactertypes/create/([^/]+)$',		'charactertypes/$1/create',	true),
			array('^charactertypes/(edit|delete)/([^/]+)/([^/]+)$',	'charactertypes/$2/$3/$1',	true),
			array('^charactergroups/index/([^/]+)$',					'charactergroups/$1',		true),
			array('^charactergroups/creategroupsgroup/([^/]+)$',				'charactergroups/$1/create',	true),
			array('^charactergroups/groupsgroup/([^/]+)/([^/]+)$',				'charactergroups/$1/$2',	true),
			array('^charactergroups/(edit|delete)groupsgroup/([^/]+)/([^/]+)$',		'charactergroups/$2/$3/$1',	true),
			array('^charactergroups/creategroup/([^/]+)/([^/]+)$',				'charactergroups/$1/$2/create',	true),
			array('^charactergroups/group/([^/]+)/([^/]+)/([^/]+)$',			'charactergroups/$1/$2/$3',	true),
			array('^charactergroups/(manage|edit|delete)group/([^/]+)/([^/]+)/([^/]+)$',	'charactergroups/$2/$3/$4/$1',	true),
			array('^charactergroupsquests/create/([^/]+)/([^/]+)/?$',			'charactergroupsquests/$1/$2/create',	true),
			array('^charactergroupsquests/quest/(.*)$',					'charactergroupsquests/$1',		true),
			array('^charactergroupsquests/(edit|delete|manage)/([^/]+)/([^/]+)/([^/]+)$',	'charactergroupsquests/$2/$3/$4/$1',	true),
			array('^achievements/index/(.*)$',					'achievements/$1',		true),
			array('^achievements/(create|manage)/(.*)$',				'achievements/$2/$1',		true),
			array('^achievements/(edit|conditions|moveup|movedown|delete)/(.*)$',	'achievements/$2/$1',		true),
			array('^library/index/([^/]+)/?$',					'library/$1',		true),
			array('^library/create/([^/]+)/?$',					'library/$1/create',	true),
			array('^library/topic/([^/]+)/([^/]+)/?$',				'library/$1/$2',	true),
			array('^library/(edit|delete|manage)/([^/]+)/([^/]+)/?$',		'library/$2/$3/$1',	true)
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
		
		
		/**
		 * Mailserver connection settings
		 * 
		 * @static
		 * @var array
		 */
		public static $mail = array(
			'host'		=> '',
			'port'		=> 465,
			'username'	=> '',
			'password'	=> '',
			'secure'	=> '',
			'charset'	=> 'UTF-8'
		);
		
	}

?>
