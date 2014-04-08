<?php if(array_key_exists('media', $seminary)) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','index',$seminary['media']['url']))?>">
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></h2>
<h3><?=$groupsgroup['name']?></h3>

<ul>
	<?php foreach($groups as &$group) : ?>
	<li><a href="<?=$linker->link(array('group',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=$group['name']?> (<?=$group['xps']?> XPs)</a></li>
	<?php endforeach ?>
</ul>


<h3><?=_('Character Groups Quests')?></h3>
<ul>
	<?php foreach($quests as &$quest) : ?>
	<li><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></li>
	<?php endforeach ?>
</ul>
