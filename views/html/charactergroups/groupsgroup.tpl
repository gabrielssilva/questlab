<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>
<h3><?=$seminary['title']?></h3>
<h4><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></h4>
<h5><?=$groupsgroup['name']?></h5>

<ul>
	<?php foreach($groups as &$group) : ?>
	<li><a href="<?=$linker->link(array('group',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=$group['name']?> (<?=$group['xps']?> XPs)</a></li>
	<?php endforeach ?>
</ul>


<h5><?=_('Character Groups Quests')?></h5>
<ul>
	<?php foreach($quests as &$quest) : ?>
	<li><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></li>
	<?php endforeach ?>
</ul>
