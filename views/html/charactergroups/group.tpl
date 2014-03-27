<!--<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>
<h3><?=$seminary['title']?></h3>
<h4><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></h4>
<h5><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></h5>
-->
<div class="moodpic">
	<img src="http://s1.directupload.net/images/140323/tpzvoy5c.png">
</div>
<section class="gdata cf">
	<div class="gbanner">
		<img src="http://s1.directupload.net/images/140325/3eqybn4i.png">
	</div>
	<div class="gdesc">
		<h1><?=$group['name']?></h1>
		<span>Schweb wie ein Schmetterling! Stich wie eine Biene!</span>
	</div>
	<ul>
		<li><i class="fa fa-th-list fa-fw"></i>7. Platz</li>
		<li><i class="fa fa-lightbulb-o fa-fw"></i><?=$group['xps']?> XP</li>
		<li><i class="fa fa-users fa-fw"></i>6 Mitglieder</li>
	</ul>
</section>

<section>
	<h2><i class="fa fa-users fa-fw"></i><?=_('Characters')?></h2>
	<ul class="gchars cf">
		<?php foreach($characters as &$character) : ?>
		<li>
			<i class="fa fa-star"></i>
			<?php if($character['is_leader'] > 0) : ?><i class="fa fa-star"></i><?php endif ?>
			<img src="http://s7.directupload.net/images/140325/e2wdqhqa.png">
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
		</li>
		<li>
			<img src="http://s7.directupload.net/images/140325/e2wdqhqa.png">
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
			<?php if($character['is_leader'] > 0) : ?><i class="fa fa-star"></i><?php endif ?>
		</li>
		<li>
			<img src="http://s7.directupload.net/images/140325/e2wdqhqa.png">
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
			<?php if($character['is_leader'] > 0) : ?><i class="fa fa-star"></i><?php endif ?>
		</li>
		<li>
			<img src="http://s7.directupload.net/images/140325/e2wdqhqa.png">
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
			<?php if($character['is_leader'] > 0) : ?><i class="fa fa-star"></i><?php endif ?>
		</li>
		<li>
			<img src="http://s7.directupload.net/images/140325/e2wdqhqa.png">
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
			<?php if($character['is_leader'] > 0) : ?><i class="fa fa-star"></i><?php endif ?>
		</li>
		<li>
			<img src="http://s7.directupload.net/images/140325/e2wdqhqa.png">
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
			<p><small><?=$character['xps']?> XP</small></p>
			<?php if($character['is_leader'] > 0) : ?><i class="fa fa-star"></i><?php endif ?>
		</li>
		<?php endforeach ?>
	</ul>
</section>

<section>
	<h2><i class="fa fa-pencil-square-o fa-fw"></i><?=_('Quests')?></h2>
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
