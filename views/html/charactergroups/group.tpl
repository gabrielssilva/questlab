<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></li>
</ul>
<div class="gbanner cf">
	<img src="http://s1.directupload.net/images/140325/3eqybn4i.png" class="gbanner">
	<h1><?=$group['name']?></h1>
	<p>"<?=$group['motto']?>"</p>
</div>
<ul class="gdata cf">
	<li><?=$group['rank']?>. <?=_('Rank')?></li>
	<li><?=$group['xps']?> XP</li>
	<li><?=count($group['characters'])?> <?=(count($group['characters']) > 1) ? _('Members') : _('Member')?></li>
</ul>

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
