<?php if(array_key_exists('media', $seminary)) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','index',$seminary['media']['url']))?>">
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></h2>
<h3><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></h3>
<section class="gdata cf">
	<div class="gbanner">
		<img src="http://s1.directupload.net/images/140325/3eqybn4i.png">
	</div>
	<div class="gdesc">
		<h3><?=$group['name']?></h3>
		<span><?=$group['motto']?></span>
	</div>
	<ul>
		<li><i class="fa fa-th-list fa-fw"></i><?=$group['rank']?>. <?=_('Rank')?></li>
		<li><i class="fa fa-lightbulb-o fa-fw"></i><?=$group['xps']?> XPs</li>
		<li><i class="fa fa-users fa-fw"></i><?=count($group['characters'])?> <?=(count($group['characters']) > 1) ? _('Members') : _('Member')?></li>
	</ul>
</section>

<section>
	<h1><i class="fa fa-users fa-fw"></i><?=_('Characters')?></h1>
	<ul class="gchars cf">
		<?php foreach($group['characters'] as &$character) : ?>
		<li>
			<?php if(array_key_exists('small_avatar', $character)) : ?>
			<p><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['small_avatar']['url']))?>"></p>
			<?php endif ?>
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
