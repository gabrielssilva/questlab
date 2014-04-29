<div class="moodpic">
	<img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<h1><?=_('Seminaries')?></h1>
<?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link('create', 1)?>"><?=_('Create new seminary')?></a></li>
</nav>
<?php endif ?>
<ul class="questgroups cf">
	<?php foreach($seminaries as &$seminary) : ?>
	<li>
		<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
		<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>" />
		<?php endif ?>
		<section>
			<p class="fwb">
				<?php if(array_key_exists('usercharacter', $seminary) && count($seminary['usercharacter']['characterroles']) > 0) : ?>
				<a href="<?=$linker->link(array('seminary', $seminary['url']), 1)?>"><?=$seminary['title']?></a>
				<?php else : ?>
				<?=$seminary['title']?>
				<?php endif ?>
			</p>
			<?php if(array_key_exists('usercharacter', $seminary)) : ?>
			<div class="cf">
				<div class="xpbar">
					<span style="width:<?=round($seminary['usercharacter']['xps'] * 100 / $seminary['xps'])?>%"></span>
				</div>
				<p class="xpnumeric"><?=$seminary['usercharacter']['xps']?> / <?=sprintf(_('%d XPs'), $seminary['xps'])?></p>
			</div>
			<?php endif ?>
			<p><?=\hhu\z\Utils::t($seminary['description'])?></p>
			<p><small><?=sprintf(_('created by %s on %s'), $seminary['creator']['username'], $dateFormatter->format(new \DateTime($seminary['created'])))?></small></p>
			<?php if(!array_key_exists('usercharacter', $seminary)) : ?>
			<a href="<?=$linker->link(array('characters','register',$seminary['url']))?>" class="cta orange"><?=_('Create a Character')?></a>
			<?php elseif(count($seminary['usercharacter']['characterroles']) == 0) : ?>
			<p><?=sprintf(_('Your Character “%s” has not been activated yet'), $seminary['usercharacter']['name'])?></p>
			<?php endif ?>
		</section>		
	</li>
	<?php endforeach ?>
</ul>
