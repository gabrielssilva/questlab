<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>
<h3>Beschreibung</h3>
<p><?=\hhu\z\Utils::t($seminary['description'])?></p>

<?php foreach($questgroupshierarchy as &$hierarchy) : ?>
<h3><?=$hierarchy['title_plural']?></h3>
<ul>
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li class="questgroup">
		<section>
			<p class="fwb"><?=$hierarchy['title_singular']?> <?=$group['pos']?>:
			<?php if(!array_key_exists('access', $group) || $group['access']) : ?>
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></p>
			<div class="xpbar">
				<span style="width:25%"></span>
			</div>
			<p class="xpnumeric">350 / 450 XP</p>
			<p>Einleitungstext: Mit völlig verseuchtem Tagewerk machst du dich an die Arbeit und stellst schnell fest...</p>
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>" class="cta orange">Auf ins Abenteuer!</a>
			<?php else : ?>
			<?=_('locked')?></p>
			<?php endif ?>
		</section>
	</li>
	<?php endforeach?>
</ul>
<?php endforeach ?>

<nav>
	<li><a href="<?=$linker->link('edit', 3)?>"><?=_('Edit seminary')?></a></li>
	<li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete seminary')?></a></li>
</nav>
<nav>
	<li><a href="<?=$linker->link(array('characters',$seminary['url']))?>"><?=_('Characters')?></a></li>
	<li><a href="<?=$linker->link(array('charactergroups',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
</nav>
<p>
	<?=sprintf(_('created by %s on %s'), $seminary['creator']['username'],  $dateFormatter->format(new \DateTime($seminary['created'])))?>
</p>