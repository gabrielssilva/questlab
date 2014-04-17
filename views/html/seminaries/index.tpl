<h1><?=_('Seminaries')?></h1>
<?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) : ?>
<nav>
	<li><a href="<?=$linker->link('create', 1)?>"><?=_('Create new seminary')?></a></li>
</nav>
<?php endif ?>
<ul class="questgroups cf">
	<?php foreach($seminaries as &$seminary) : ?>
	<li>
		<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
		<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
		<?php endif ?>
		<section>
			<p class="fwb">
			<?php if(count($seminary['userroles']) > 0) : ?>
			<a href="<?=$linker->link(array('seminary', $seminary['url']), 1)?>"><?=$seminary['title']?></a>
			<?php else : ?>
			<?=$seminary['title']?>
			<?php endif ?>
			</p>
			<p><small><?=sprintf(_('created by %s on %s'), $seminary['creator']['username'], $dateFormatter->format(new \DateTime($seminary['created'])))?></small></p>
			<p><?=\hhu\z\Utils::t($seminary['description'])?></p>
			<?php if(!array_key_exists('usercharacter', $seminary)) : ?>
			<a href="<?=$linker->link(array('characters','register',$seminary['url']))?>" class="cta orange"><?=_('Create a Character')?></a>
			<?php elseif(count($seminary['userroles']) == 0) : ?>
			<p><?=sprintf(_('Your Character “%s” has not been activated yet'), $seminary['usercharacter']['name'])?></p>
			<?php endif ?>
		</section>		
	</li>
	<?php endforeach ?>
</ul>
