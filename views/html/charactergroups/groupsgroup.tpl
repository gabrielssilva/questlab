<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>
<h3><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></h3>
<h4><?=$groupsgroup['name']?></h4>

<ul>
	<?php foreach($groups as &$group) : ?>
	<li><a href="<?=$linker->link(array('group',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=$group['name']?> (<?=$group['xps']?> XPs)</a></li>
	<?php endforeach ?>
</ul>


<h4><?=_('Character Groups Quests')?></h4>
<ul>
	<?php foreach($quests as &$quest) : ?>
	<li><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></li>
	<?php endforeach ?>
</ul>
