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

<form method="get">
	<fieldset class="filter">
		<p><small>Sortierung:</small></p>
		<select name="sortorder" onchange="this.form.submit();">
			<option value="charactername" <?php if($sortorder == 'charactername') : ?>selected="selected"<?php endif ?>><?=_('Character name')?></option>
			<option value="xps" <?php if($sortorder == 'xps') : ?>selected="selected"<?php endif ?>><?=_('XPs')?></option>
			<option value="role" <?php if($sortorder == 'role') : ?>selected="selected"<?php endif ?>><?=_('Role')?></option>
			<option value="date" <?php if($sortorder == 'date') : ?>selected="selected"<?php endif ?>><?=_('Date of registration')?></option>
			<?php foreach($characterfields as &$characterfield) : ?>
			<option value="<?=$characterfield['url']?>" <?php if($sortorder == $characterfield['url']) : ?>selected="selected"<?php endif ?>><?=$characterfield['title']?></option>
			<?php endforeach ?>
		</select>
		<noscript><input type="submit" value="<?=_('Sort list')?>" /></noscript>
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
