<h2><?=_('Seminaries')?></h2>
<nav>
	<li><a href="<?=$linker->link('create', 1)?>"><?=_('Create new seminary')?></a></li>
</nav>
<ul>
	<?php foreach($seminaries as &$seminary) : ?>
	<li>
		<h2><a href="<?=$linker->link(array('seminary', $seminary['url']), 1)?>"><?=$seminary['title']?></a></h2>
		<details>
			<summary><?=sprintf(_('created by %s on %s'), $seminary['creator']['username'], $dateFormatter->format(new \DateTime($seminary['created'])))?></summary>
		</details>
	</li>
	<?php endforeach ?>
</ul>
