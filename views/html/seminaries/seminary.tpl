<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<h1><?=$seminary['title']?></h1>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link('edit', 3)?>"><?=_('Edit seminary')?></a></li>
	<li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete seminary')?></a></li>
</nav>
<nav class="admin">
	<li><a href="<?=$linker->link(array('charactertypes','manage',$seminary['url']))?>"><?=_('Manage Charactertypes')?></a></li>
	<li><a href="<?=$linker->link(array('questgroups','manage',$seminary['url']))?>"><?=_('Manage Questgroups')?></a></li>
</nav>
<?php endif ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('quests','index',$seminary['url']))?>"><?=_('Show Quests')?></a></li>
	<li><a href="<?=$linker->link(array('calculatexps',$seminary['url']),1)?>"><?=_('Recalculate XPs')?></a></li>
</nav>
<?php endif ?>
<p><?=\hhu\z\Utils::t($seminary['description'])?></p>
<?php foreach($questgroupshierarchy as $hierarchyIndex => &$hierarchy) : ?>
<h2 id="<?=$hierarchy['url']?>"><?=$hierarchy['title_plural']?></h2>
<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('questgroupshierarchy','edit',$seminary['url'],$hierarchy['url']))?>"><?=_('Edit Questgroupshierarchy')?></a></li>
	<li><a href="<?=$linker->link(array('questgroupshierarchy','delete',$seminary['url'],$hierarchy['url']))?>"><?=_('Delete Questgroupshierarchy')?></a></li>
	<?php if($hierarchyIndex > 0) : ?><li><a href="<?=$linker->link(array('questgroupshierarchy','moveup',$seminary['url'],$hierarchy['url']))?>">↑</a></li><?php endif ?>
	<?php if($hierarchyIndex < count($questgroupshierarchy)-1) : ?><li><a href="<?=$linker->link(array('questgroupshierarchy','movedown',$seminary['url'],$hierarchy['url']))?>">↓</a></li><?php endif ?>
</nav>
<?php endif ?>
<ul class="questgroups cf">
	<?php foreach($hierarchy['questgroups'] as $questgroupIndex => &$group) : ?>
	<li>
		<?php if(!is_null($group['picture'])) : ?>
		<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$group['picture']['url']))?>">
		<?php endif ?>
		<section>
			<p class="fwb"><?=$hierarchy['title_singular']?> <?=$group['pos']?>:
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></p>
			<div class="cf">
				<div class="xpbar">
					<span style="width:<?=($group['achievable_xps'] > 0) ? round($group['character_xps']*100/$group['achievable_xps']) : 0?>%"></span>
				</div>
				<p class="xpnumeric"><?=$group['character_xps']?> / <?=$group['achievable_xps']?> XP</p>
			</div>
			<?php if(array_key_exists('text', $group)) : ?>
			<p><?=$group['text']?></p>
			<?php endif ?>
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>" class="cta orange"><?=_('Let’s go')?></a>
			<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
			<div>
				<?php if($questgroupIndex > 0) : ?><a href="<?=$linker->link(array('questgroups','moveup',$seminary['url'],$group['url']))?>">↑</a><?php endif ?>
				<?php if($questgroupIndex < count($hierarchy['questgroups'])-1) : ?><a href="<?=$linker->link(array('questgroups','movedown',$seminary['url'],$group['url']))?>">↓</a><?php endif ?>
			</div>
			<?php endif ?>
		</section>
	</li>
	<?php endforeach?>
	<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
	<li>
		<section>
			<form method="post" action="<?=$linker->link(array('questgroups','create',$seminary['url']))?>" enctype="multipart/form-data">
				<input type="hidden" name="questgroupshierarchy" value="<?=$hierarchy['url']?>" />
				<input type="file" name="moodpic" />
				<?=$hierarchy['title_singular']?> <?=count($hierarchy['questgroups'])+1?>:
				<input type="text" name="title" value="" placeholder="<?=_('Title')?>" />
				<input type="submit" name="create" value="<?=_('Add new Questgroup')?>" />
			</form>
		</section>
	</li>
	<?php endif ?>
</ul>
<?php endforeach ?>

<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
<form method="post" action="<?=$linker->link(array('questgroupshierarchy','create',$seminary['url']))?>">
	<h2><?=_('New Questgroupshierarchy')?></h2>
	<?=_('Title (singular)')?>: <input type="text" name="title_singular" placeholder="<?=_('Title (singular)')?>" />
	<?=_('Title (plural)')?>: <input type="text" name="title_plural" placeholder="<?=_('Title (plural)')?>" />
	<input type="submit" name="create" value="<?=_('Add new Questgroupshierarchy')?>" />
</form>
<?php endif ?>
