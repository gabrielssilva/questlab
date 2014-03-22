<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>
<h3><?=_('Characters')?></h3>

<ul>
	<?php foreach($characters as &$character) : ?>
	<li><a href="<?=$linker->link(array('character',$seminary['url'],$character['url']),1)?>"><?=$character['name']?></a> (<?=$character['xps']?> XPs, <?=_('Level')?> <?=$character['xplevel']['level']?><?php if(!is_null($character['xplevel']['name'])) : ?>: <?=$character['xplevel']['name']?><?php endif ?>)</li>
	<?php endforeach ?>
</ul>
