<div class="moodpic">
	<img src="http://s1.directupload.net/images/140323/tpzvoy5c.png">
</div>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></h2>
<section class="gdata cf">
	<div class="gbanner">
		<img src="http://s1.directupload.net/images/140325/3eqybn4i.png">
	</div>
	<div class="gdesc">
		<h3><?=$group['name']?></h3>
		<span>Schweb wie ein Schmetterling! Stich wie eine Biene!</span>
	</div>
	<ul>
		<li><i class="fa fa-th-list fa-fw"></i>7. Platz</li>
		<li><i class="fa fa-lightbulb-o fa-fw"></i><?=$group['xps']?> XP</li>
		<li><i class="fa fa-users fa-fw"></i>6 Mitglieder</li>
	</ul>
</section>

<section>
	<h1><i class="fa fa-users fa-fw"></i><?=_('Characters')?></h1>
	<ul class="gchars cf">
		<?php foreach($characters as &$character) : ?>
		<li>
			<p><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></p>
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
		</li>
		<li>
			<p><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></p>
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
		</li>
		<li>
			<p><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></p>
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
		</li>
		<li>
			<p><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></p>
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
		</li>
		<li>
			<p><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></p>
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
		</li>
		<li>
			<p><img src="http://s7.directupload.net/images/140325/e2wdqhqa.png"></p>
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
		</li>
		<?php endforeach ?>
	</ul>
</section>

<section>
	<h1><i class="fa fa-pencil-square-o fa-fw"></i><?=_('Quests')?></h1>
	<ul class="gquests">
		<?php foreach($quests as &$quest) : ?>
		<li class="cf">
			<p>
				<span class="date"><?=$dateFormatter->format(new \DateTime($quest['created']))?></span>
				<a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" class="fwb"><?=$quest['title']?></a>
				<span class="xp"><?=$quest['group_xps']?> / <?=$quest['xps']?> XP</span>
			</p>
		</li>
		<?php endforeach ?>
	</ul>
</section>
