<!DOCTYPE html>
<html>

<head>
	<meta charset="utf-8" />
	<title>The Legend of Z</title>
	
	<link rel="stylesheet" type="text/css" href="<?=$linker->link(array('css','desktop'))?>" media="all" />
</head>

<body>
	<header>
		<h1><a href="<?=$linker->link(array(), 0, true, array(), true)?>">The Legend of Z</a></h1>
		<nav>
			<?=$menu?>
		</nav>
	</header>
	<article>
		<?=$intermediate?>
	</article>
</body>

</html>
