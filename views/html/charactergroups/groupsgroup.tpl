<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
</ul>

<h1><?=$groupsgroup['name']?></h1>

<ol class="cglist">
	<?php foreach($groups as &$group) : ?>
	<li><a href="<?=$linker->link(array('group',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=$group['name']?></a><span class="xp"><?=$group['xps']?> XP</span></li>
	<?php endforeach ?>
</ol>


<h2><?=sprintf(_('%s-Quests'),$groupsgroup['name'])?></h2>
<ul class="cgqlist">
	<?php foreach($quests as &$quest) : ?>
	<li><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></li>
	<?php endforeach ?>
</ul>
