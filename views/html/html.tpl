<!DOCTYPE html>
<html>

<head>
	<meta charset="utf-8" />
	<title>The Legend of Z</title>
	<meta name="viewport" content="width=device-width,initial-scale=1.0">
	<link href="http://fonts.googleapis.com/css?family=Open+Sans:400,700" rel="stylesheet" type="text/css">
	<link href="//netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css" rel="stylesheet">
	<link rel="stylesheet" type="text/css" href="<?=$linker->link(array('css','desktop.css'))?>" media="all" />
	<!--[if lt IE 9]>
	<script type="text/javascript" src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
	<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/respond.js/1.4.2/respond.js"></script>
	<![endif]-->
	<meta name="description" content="">
	<meta name="robots" content="noindex,follow">
</head>

<body>
	<header>
		<nav class="wrap">
			<input type="checkbox" id="toggle">
			<label for="toggle" class="toggle" onclick><a id="navicon"><i class="fa fa-bars"></i>Menü</a></label>
			<?php if(!is_null($loggedUser)) : ?>
			<a href="<?=$linker->link(array('users',$loggedUser['url']))?>" id="profile"><i class="fa fa-user fa-fw"></i><?=$loggedUser['username']?></a>
			<?php endif ?>
			<?=$menu?>
		</nav>
	</header>
	<article class="wrap">
		<h1><a href="<?=$linker->link(array(), 0, true, array(), true)?>">The Legend of Z</a></h1>
		<?php if(!is_null($loggedUser)) : ?>
		<div id="user">
			<a href="<?=$linker->link(array('users',$loggedUser['url']))?>"><?=$loggedUser['username']?></a>
			<?php if(!is_null($loggedCharacter)) : ?>
			<?=_('as')?> <a href="<?=$linker->link(array('characters','character',$loggedSeminary['url'],$loggedCharacter['url']))?>"><?=$loggedCharacter['name']?></a> (<?=$loggedCharacter['xps']?> XPs, <?=$loggedCharacter['xplevel']?>)
			<?php endif ?>
		</div>
		<?php endif ?>
		<?=$intermediate?>
	</article>
</body>

</html>
