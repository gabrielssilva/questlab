<h1><?=_('Users')?></h1>
<h2><?=$user['username']?></h2>
<p>
	<?=_('registered on')?> <?=date(\hhu\z\Utils::DATEFORMAT, strtotime($user['created']))?>
</p>
