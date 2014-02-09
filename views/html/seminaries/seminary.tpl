<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>
<nav>
	<li><a href="<?=$linker->link('edit', 3)?>"><?=_('Edit seminary')?></a></li>
	<li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete seminary')?></a></li>
</nav>
<p>
	<?=sprintf(_('created by %s on %s'), $seminary['creator']['username'],  $dateFormatter->format(new \DateTime($seminary['created'])))?>
</p>
<h3>Beschreibung</h3>
<p><?=$seminary['description']?></p>

<?php foreach($questgroupshierarchy as &$hierarchy) : ?>
<h3><?=$hierarchy['title_plural']?></h3>
<ul>
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li><?=$hierarchy['title_singular']?> <?=$group['pos']?>: <a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></li>
	<?php endforeach?>
</ul>
<?php endforeach ?>
