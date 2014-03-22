<h2><?=_('Users')?></h2>
<h3><?=$user['username']?></h3>
<nav>
	<li><a href="<?=$linker->link('edit', 3)?>"><?=_('Edit user')?></a></li>
	<li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete user')?></a></li>
</nav>
<p>
	<?=sprintf(_('registered on %s'), $dateFormatter->format(new \DateTime($user['created'])))?>
</p>

<h3><?=_('Characters')?></h3>
<ul>
	<?php foreach($characters as &$character) : ?>
	<li><a href="<?=$linker->link(array('characters','character',$character['seminary_url'],$character['url']))?>"><?=$character['name']?></a> (<?=$character['xps']?> XPs, <?=_('Level')?> <?=$character['xplevel']['level']?><?php if(!is_null($character['xplevel']['name'])) : ?>: <?=$character['xplevel']['name']?><?php endif ?>) (<a href="<?=$linker->link(array('seminaries',$character['seminary_url']))?>"><?=$character['seminary_title']?></a>)</li>
	<?php endforeach ?>
</ul>

<h3><?=_('Roles')?></h3>
<?=$userroles?>
