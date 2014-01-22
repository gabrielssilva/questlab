<h1><?=_('Users')?></h1>
<h2><?=$user['username']?></h2>
<nav>
	<li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete user')?></a></li>
</nav>
<p>
	<?=_('registered on')?> <?=date(\hhu\z\Utils::DATEFORMAT, strtotime($user['created']))?>
</p>
