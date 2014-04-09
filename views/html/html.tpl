<!DOCTYPE html>
<html>

<head>
	<meta charset="utf-8" />
	<title>The Legend of Z</title>
	<meta name="viewport" content="width=device-width,initial-scale=1.0">
	<link href="http://fonts.googleapis.com/css?family=Open+Sans:400,700" rel="stylesheet" type="text/css">
	<link href="//netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css" rel="stylesheet">
	<link rel="stylesheet" type="text/css" href="<?=$linker->link(array('css','desktop.css'))?>" media="all" />
	<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js"></script>
	<script type="text/javascript" src="/js/jquery.nicescroll.min.js"></script>
	<script type="text/javascript">
	$(document).ready(
	function() {
		$("#qtextbox").niceScroll({autohidemode:false,cursorcolor:"#c2beb9"});
	}
	);
	</script>
	<!--[if lt IE 9]>
	<script type="text/javascript" src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
	<script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/respond.js/1.4.2/respond.js"></script>
	<![endif]-->
	<script type="text/javascript" src="/js/dnd.js"></script>
	<meta name="description" content="">
	<meta name="robots" content="noindex,follow">
</head>

<body>
	<header>
		<nav>
			<input type="checkbox" id="toggle">
			<label for="toggle" class="toggle" onclick><a id="navicon"><i class="fa fa-bars"></i>Menü</a></label>
			<?php if(!is_null($loggedUser)) : ?>
			<?php if(!is_null($loggedCharacter)) : ?>
			<a href="<?=$linker->link(array('characters','character',$loggedSeminary['url'],$loggedCharacter['url']))?>" id="profile"><i class="fa fa-user fa-fw"></i><?=$loggedCharacter['name']?><span class="circlenote"><?=$loggedCharacter['xplevel']?></span></a>
			<?php else : ?>
			<a href="<?=$linker->link(array('users',$loggedUser['url']))?>" id="profile"><i class="fa fa-user fa-fw"></i><?=$loggedUser['username']?></a>
			<?php endif ?>
			<?php endif ?>
			<menu>
				<?=$menu?>
			</menu>
		</nav>
	</header>
	<article class="wrap">
		<?=$intermediate?>
	</article>
	<aside>
		<section class="cf">
			<h1>Zyrendaniel</h1>
			<img src="http://legende-von-zyren.de/img/avatars/Goblin7.png" class="char">
			<ul class="charstats">
				<li><i class="fa fa-caret-right fa-fw"></i>Level 1</li>
				<li><i class="fa fa-caret-right fa-fw"></i>1500 XP</li>
				<li><i class="fa fa-caret-right fa-fw"></i>11. Platz</li>
				<li><i class="fa fa-caret-right fa-fw"></i><a href="#">Zum Profil</a></li>
			</ul>
		</section>
		<section>
			<h1>Letzter Speicherpunkt</h1>
			<p><i class="fa fa-pencil-square-o fa-fw"></i><a href="#">Die verwunschene Stadt</a></p>
		</section>
		<section>
			<h1>Letzte Errungenschaft</h1>
			<ul class="cranks">
				<li>
					<a href="#" title="Achievement-Titel"><img src="http://legende-von-zyren.de/img/achieve/1b.jpg"></a>
					<p><a href="#">Des Königs neue Quests</a></p>
					<p><small>erreicht am: 14.07.2014</small></p>
				</li>
			</ul>
		</section>
		<section>
			<h1>Wille und die Majas</h1>
			<ul class="cranks">
				<li>
					<a href="#" title="Achievement-Titel"><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></a>
					<p><a href="#">Anduin</a></p>
					<p><small>Level 27 (1500 XP)</small></p>
				</li>
				<li>
					<a href="#" title="Achievement-Titel"><img src="http://s1.directupload.net/images/140325/upv2dg2r.png"></a>
					<p><a href="#">Jaina</a></p>
					<p><small>Level 26 (1400 XP)</small></p>
				</li>
				<li>
					<a href="#" title="Achievement-Titel"><img src="http://s14.directupload.net/images/140325/x9ny5kgu.png"></a>
					<p><a href="#">Uther</a></p>
					<p><small>Level 25 (1300 XP)</small></p>
				</li>
				<li>
					<a href="#" title="Achievement-Titel"><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></a>
					<p><a href="#">Lothar</a></p>
					<p><small>Level 24 (1200 XP)</small></p>
				</li>
				<li>
					<a href="#" title="Achievement-Titel"><img src="http://s1.directupload.net/images/140325/whre34td.png"></a>
					<p><a href="#">Morris</a></p>
					<p><small>Level 23 (1100 XP)</small></p>
				</li>
			</ul>
			<p><i class="fa fa-users fa-fw"></i><a href="#">Gildenprofil ansehen</a></p>
		</section>
	</aside>
</body>

</html>
