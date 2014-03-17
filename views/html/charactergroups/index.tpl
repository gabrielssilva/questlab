<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>
<h3><?=_('Character Groups')?></h3>

<ul>
	<?php foreach($groupsgroups as &$group) : ?>
	<li><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$group['url']),1)?>"><?=$group['name']?></a></li>
	<?php endforeach ?>
</ul>
