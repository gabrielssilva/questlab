<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>
<h3><?=_('Character Groups')?></h3>
<h4><?=$groupsgroup['name']?></h4>

<ul>
	<?php foreach($groups as &$group) : ?>
	<li><a href="<?=$linker->link(array('group',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=$group['name']?></a></li>
	<?php endforeach ?>
</ul>
