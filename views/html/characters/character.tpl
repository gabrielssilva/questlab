<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><i class="fa fa-user fa-fw"></i><?=$character['name']?></h2>

<section class="cf">
	<div class="cinfo">
		<div class="cdata">
			<div class="xpbar">
				<span style="width:85%"></span>
			</div>
			<p><small>Gesamtfortschritt: 85%</small></p>
		</div>
		<div class="cdata square">
			<p class="value"><?=$character['xplevel']['level']?></p>
			<p><small><?=_('Level')?></small></p>
		</div>
		<div class="cdata square">
			<p class="value">500</p>
			<p><small>XP</small></p>
		</div>
		<div class="cdata square blue">
			<p class="value">7.</p>
			<p><small>Platz</small></p>
		</div>

		<h2><i class="fa fa-certificate fa-fw"></i>Belohnungen</h2>
		<ul class="crewards">
			<li>
				<p class="unlocked"><i class="fa fa-check-circle fa-fw"></i>Aktive Beteiligung</p>
			</li>
			<li>
				<p class="unlocked"><i class="fa fa-check-circle fa-fw"></i>+ 0,3 Notenbonus</p>
			</li>
			<li>
				<p><i class="fa fa-lock fa-fw"></i>+ 0,7 Notenbonus <span class="locked">(noch 300 XP)</span></p>
			</li>
			<li>
				<p><i class="fa fa-lock fa-fw"></i>+ 1,0 Notenbonus <span class="locked">(noch 500 XP)</span></p>
			</li>
		</ul>
	</div>
	<div class="cportrait">
		<img src="http://legende-von-zyren.de/img/avatars/Goblin7.png"><br>
		<?php if(!is_null($character['avatar_url'])) : ?>
		<img src="<?=$linker->link(array('media','index',$seminary['url'],$character['avatar_url']))?>" alt="<?=$character['avatar_description']?>" />
		<?php endif ?>
	</div>
</section>

<section>
	<h2><i class="fa fa-users fa-fw"></i><?=_('Character Groups')?></h2>
	<ul class="cgroups cf">
		<li class="cf">
			<img src="http://s1.directupload.net/images/140325/3eqybn4i.png">
			<a href="#">Super wilde Arbeits Gruppe [SWAG]</a><p><span>500 XP</span></p>
		</li>
		<li class="cf">
			<img src="http://s1.directupload.net/images/140325/3eqybn4i.png">
			<a href="#">Mit Herz und Seele</a><p><span>500 XP</span></p>
		</li>
		<?php foreach($groups as &$group) : ?>
		<li><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$group['charactergroupsgroup_url'],$group['url']))?>"><?=$group['name']?></a> (<?=$group['xps']?> XPs)</li>
		<?php endforeach ?>
	</ul>
</section>

<div class="cf">
<section class="fll48">
	<h2><i class="fa fa-trophy fa-fw"></i>Neue Achievements</h2>
	<ul class="cranks">
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://legende-von-zyren.de/img/achieve/1b.jpg"></a>
			<p><a href="#">Des Königs neue Quests</a></p>
			<p><small>erreicht am: 14.07.2014</small></p>
		</li>
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://legende-von-zyren.de/img/achieve/2b.jpg"></a>
			<p><a href="#">Des Königs neue Quests</a></p>
			<p><small>erreicht am: 14.07.2014</small></p>
		</li>
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://legende-von-zyren.de/img/achieve/3b.jpg"></a>
			<p><a href="#">Des Königs neue Quests</a></p>
			<p><small>erreicht am: 14.07.2014</small></p>
		</li>
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://legende-von-zyren.de/img/achieve/4b.jpg"></a>
			<p><a href="#">Des Königs neue Quests</a></p>
			<p><small>erreicht am: 14.07.2014</small></p>
		</li>
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://legende-von-zyren.de/img/achieve/5b.jpg"></a>
			<p><a href="#">Des Königs neue Quests</a></p>
			<p><small>erreicht am: 14.07.2014</small></p>
		</li>
	</ul>
</section>

<section class="flr48">
	<h2><i class="fa fa-list fa-fw"></i>Ranking</h2>
	<ul class="cranks">
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></a>
			<p>7. <a href="#">Anduin</a></p>
			<p><small>Level 27 (1500 XP)</small></p>
		</li>
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://s1.directupload.net/images/140325/upv2dg2r.png"></a>
			<p>8. <a href="#">Jaina</a></p>
			<p><small>Level 26 (1400 XP)</small></p>
		</li>
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://s14.directupload.net/images/140325/x9ny5kgu.png"></a>
			<p class="fwb">9. <a href="#">Uther</a></p>
			<p><small>Level 25 (1300 XP)</small></p>
		</li>
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></a>
			<p>10. <a href="#">Lothar</a></p>
			<p><small>Level 24 (1200 XP)</small></p>
		</li>
		<li>
			<a href="#" title="Achievement-Titel"><img src="http://s1.directupload.net/images/140325/whre34td.png"></a>
			<p>11. <a href="#">Morris</a></p>
			<p><small>Level 23 (1100 XP)</small></p>
		</li>
	</ul>
</section>
</div>

<section>
	<h2><i class="fa fa-book fa-fw"></i>Thematischer Fortschritt</h2>
	<ul class="ctopics cf">
		<li>
			<p><small><a href="#">Klassifikation</a> (3/5)</small></p>
			<div class="xpbar">
				<span style="width:60%"></span>
			</div>
		</li>
		<li>
			<p><small><a href="#">Thesauri</a> (1/10)</small></p>
			<div class="xpbar">
				<span style="width:10%"></span>
			</div>
		</li>
		<li>
			<p><small><a href="#">Indexierung</a> (3/5)</small></p>
			<div class="xpbar">
				<span style="width:20%"></span>
			</div>
		</li>
		<li>
			<p><small><a href="#">Recherche</a> (3/5)</small></p>
			<div class="xpbar">
				<span style="width:80%"></span>
			</div>
		</li>
		<li>
			<p><small><a href="#">Folksonomies</a> (3/5)</small></p>
			<div class="xpbar">
				<span style="width:70%"></span>
			</div>
		</li>
	</ul>
</section>

