<section class="cf">
	<h1><?=$character['name']?></h1>
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['avatar_url']))?>" class="char">
	<ul class="charstats">
		<li><i class="fa fa-caret-right fa-fw"></i><?=('Level')?> <?=$character['xplevel']['level']?></li>
		<li><i class="fa fa-caret-right fa-fw"></i><?=$character['xps']?> XPs</li>
		<li><i class="fa fa-caret-right fa-fw"></i><?=$character['rank']?>. <?=_('Rank')?></li>
		<li><i class="fa fa-caret-right fa-fw"></i><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>">Zum Profil</a></li>
	</ul>
</section>

<?php if(!is_null($lastQuest)) : ?>
<section>
	<h1><?=_('Last Quest')?></h1>
	<p><i class="fa fa-pencil-square-o fa-fw"></i><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$lastQuest['questgroup']['url'],$lastQuest['url']))?>"><?=$lastQuest['title']?></a></p>
</section>
<?php endif ?>

<section>
	<h1><?=('Last Achievement')?></h1>
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
