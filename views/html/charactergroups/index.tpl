<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>
<h3><?=$seminary['title']?></h3>
<h4><?=_('Character Groups')?></h4>

<ul>
	<?php foreach($groupsgroups as &$group) : ?>
	<li><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$group['url']),1)?>"><?=$group['name']?></a></li>
	<?php endforeach ?>
</ul>
