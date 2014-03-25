<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>
<h3><?=_('Description')?></h3>
<p><?=\hhu\z\Utils::t($seminary['description'])?></p>

<?php foreach($questgroupshierarchy as &$hierarchy) : ?>
<h3><?=$hierarchy['title_plural']?></h3>
<ul class="questgroups cf">
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li>
		<?php if(!is_null($group['picture'])) : ?>
		<img src="<?=$linker->link(array('media','index',$seminary['url'],$group['picture']['url']))?>">
		<?php endif ?>
		<section>
			<p class="fwb"><?=$hierarchy['title_singular']?> <?=$group['pos']?>:
			<?php if(!array_key_exists('access', $group) || $group['access']) : ?>
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></p>
			<div class="cf">
				<div class="xpbar">
					<span style="width:<?=round($group['character_xps']*100/$group['xps'])?>%"></span>
				</div>
				<p class="xpnumeric"><?=$group['character_xps']?> / <?=$group['xps']?> XP</p>
			</div>
			<?php if(array_key_exists('text', $group)) : ?>
			<p><?=$group['text']?></p>
			<?php endif ?>
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
