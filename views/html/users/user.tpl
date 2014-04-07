<h1><?=_('Users')?></h1>
<h2><?=$user['username']?></h2>
<?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) : ?>
<nav>
	<li><a href="<?=$linker->link('edit', 3)?>"><?=_('Edit user')?></a></li>
	<li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete user')?></a></li>
</nav>
<?php endif ?>
<p>
	<?=sprintf(_('registered on %s'), $dateFormatter->format(new \DateTime($user['created'])))?>
</p>

<h2><?=_('Characters')?></h2>
<ul>
	<?php foreach($characters as &$character) : ?>
	<li><a href="<?=$linker->link(array('characters','character',$character['seminary_url'],$character['url']))?>"><?=$character['name']?></a> (<?=$character['xps']?> XPs, <?=_('Level')?> <?=$character['xplevel']['level']?><?php if(!is_null($character['xplevel']['name'])) : ?>: <?=$character['xplevel']['name']?><?php endif ?>) (<a href="<?=$linker->link(array('seminaries',$character['seminary_url']))?>"><?=$character['seminary_title']?></a>)</li>
	<?php endforeach ?>
</ul>

<h2><?=_('Roles')?></h2>
<?=$userroles?>
