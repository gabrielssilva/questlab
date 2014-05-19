<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<h1><?=$seminary['title']?></h1>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
	<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?><li><a href="<?=$linker->link('edit', 3)?>"><?=_('Edit seminary')?></a></li><?php endif ?>
	<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?><li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete seminary')?></a></li><?php endif ?>
	<?php if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?><li><a href="<?=$linker->link(array('quests','index',$seminary['url']))?>"><?=_('Show Quests')?></a></li><?php endif ?>
	<?php if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?><li><a href="<?=$linker->link(array('calculatexps',$seminary['url']),1)?>"><?=_('Recalculate XPs')?></a></li><?php endif ?>
</nav>
<?php endif ?>
<p><?=\hhu\z\Utils::t($seminary['description'])?></p>
<?php foreach($questgroupshierarchy as &$hierarchy) : ?>
<h2><?=$hierarchy['title_plural']?></h2>
<ul class="questgroups cf">
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li>
		<?php if(!is_null($group['picture'])) : ?>
		<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$group['picture']['url']))?>">
		<?php endif ?>
		<section>
			<p class="fwb"><?=$hierarchy['title_singular']?> <?=$group['pos']?>:
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></p>
			<div class="cf">
				<div class="xpbar">
					<span style="width:<?=round($group['character_xps']*100/$group['achievable_xps'])?>%"></span>
				</div>
				<p class="xpnumeric"><?=$group['character_xps']?> / <?=$group['achievable_xps']?> XP</p>
			</div>
			<?php if(array_key_exists('text', $group)) : ?>
			<p><?=$group['text']?></p>
			<?php endif ?>
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>" class="cta orange"><?=_('Let’s go')?></a>
		</section>
	</li>
	<?php endforeach?>
</ul>
<?php endforeach ?>
