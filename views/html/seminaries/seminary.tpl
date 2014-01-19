<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>
<p>
	<?=sprintf(_('created by %s on %s'), $seminary['creator']['username'], date(\hhu\z\Utils::DATEFORMAT, strtotime($seminary['created'])))?>
</p>
