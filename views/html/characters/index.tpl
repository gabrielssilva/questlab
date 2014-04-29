<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><?=_('Characters')?></h1>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('manage',$seminary['url']),1)?>"><?=_('Manage')?></a></li>
</nav>
<?php endif ?>

<form method="post">
	<fieldset class="filter">
		<select name="">
			<option value="">Charaktername</option>
			<option value="">XP</option>
			<option value="">Rolle</option>
			<option value="">Matrikelnummer</option>
			<option value="">Studiengang</option>
		</select>
		<input type="submit" name="" value="Liste sortieren" />
	</fieldset>
</form>

<ul class="admnql">
	<?php foreach($characters as &$character) : ?>
	<li class="cf">
		<img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level'],'portrait'))?>">
		<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a><span><?=$character['xps']?> XP</span></p>
		<p><small><a href="<?=$linker->link(array('users','user',$character['user']['url']))?>"><?=$character['user']['username']?></a></small>
		<?php if(in_array('admin', $character['characterroles'])) : ?><small>(<?=_('Admin')?>)</small><?php endif ?>
		<?php if(in_array('moderator', $character['characterroles'])) : ?><small>(<?=_('Moderator')?>)</small><?php endif ?>
		<?php if(in_array('user', $character['characterroles'])) : ?><small>(<?=_('User')?>)</small><?php endif ?>
		</p>
		<?php foreach($character['characterfields'] as &$characterfield) : ?>
		<p class="chrflds"><?=$characterfield['value']?></p>
		<?php endforeach ?>
	</li>
	<?php endforeach ?>
</ul>
