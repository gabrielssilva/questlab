<h1><?=_('Users')?></h1>
<h2><?=$user['username']?></h2>
<nav>
	<li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete user')?></a></li>
</nav>
<p>
	<?=sprintf(_('registered on %s'), $dateFormatter->format(new \DateTime($user['created'])))?>
</p>
