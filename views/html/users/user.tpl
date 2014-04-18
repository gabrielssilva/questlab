<h1><?=_('Users')?></h1>
<h2><?=$user['username']?></h2>
<?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) : ?>
<nav>
	<li><a href="<?=$linker->link('edit', 3)?>"><?=_('Edit user')?></a></li>
	<li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete user')?></a></li>
</nav>
<?php endif ?>
<p>
	<?=sprintf(_('registered on %s'), $dateFormatter->format(new \DateTime($user['created'])))?><br />
	<?=_('Name')?>: <?=$user['prename']?> <?=$user['surname']?><br />
	<?=_('E‑mail address')?>: <a href="mailto:<?=$user['email']?>"><?=$user['email']?></a>
</p>

<h2><?=_('Characters')?></h2>
<ul class="gchars cf">
	<?php foreach($characters as &$character) : ?>
	<li>
		<?php if(array_key_exists('small_avatar', $character)) : ?>
		<p><img src="<?=$linker->link(array('media','seminary',$character['seminary_url'],$character['small_avatar']['url']))?>"></p>
		<?php endif ?>
		<p>
			<?php if(count($character['user_seminaryroles']) > 0) : ?>
			<a href="<?=$linker->link(array('characters','character',$character['seminary_url'],$character['url']))?>"><?=$character['name']?></a>
			<?php else : ?>
			<?=$character['name']?>
			<?php endif ?>
		</p>
		<p><small><?=_('Level')?> <?=$character['xplevel']['level']?></small></p>
	</li>
	<?php endforeach ?>
</ul>

<h2><?=_('Roles')?></h2>
<?=$userroles?>
