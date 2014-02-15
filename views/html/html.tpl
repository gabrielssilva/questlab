<!DOCTYPE html>
<html>

<head>
	<meta charset="utf-8" />
	<title>The Legend of Z</title>
	
	<link rel="stylesheet" type="text/css" href="<?=$linker->link(array('css','desktop.css'))?>" media="all" />
</head>

<body>
	<header>
		<h1><a href="<?=$linker->link(array(), 0, true, array(), true)?>">The Legend of Z</a></h1>
		<nav>
			<?=$menu?>
		</nav>
		<?php if(!is_null($loggedUser)) : ?>
		<div id="user">
			<a href="<?=$linker->link(array('users',$loggedUser['url']))?>"><?=$loggedUser['username']?></a>
		</div>
		<?php endif ?>
	</header>
	<article>
		<?=$intermediate?>
	</article>
</body>

</html>
