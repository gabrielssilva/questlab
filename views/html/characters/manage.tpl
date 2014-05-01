<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('characters','index',$seminary['url']))?>"><?=_('Characters')?></a></li>
</ul>
<h1><?=_('Manage')?></h1>

<form method="post">
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
	<fieldset>
		<ul class="admnql">
			<?php foreach($characters as &$character) : ?>
			<li class="cf">
				<input type="checkbox" id="characters-<?=$character['id']?>" name="characters[]" value="<?=$character['id']?>" <?php if(in_array($character['id'], $selectedCharacters)) : ?>checked="checked"<?php endif ?> <?php if($character['id'] == \hhu\z\controllers\SeminaryController::$character['id']) : ?>disabled="disabled"<?php endif ?>/>
				<label for="characters-<?=$character['id']?>">
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
				</label>
			</li>
			<?php endforeach ?>
		</ul>
	</fieldset>
	<fieldset>
		<legend><?=_('Add role')?></legend>
		<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) > 0 || !in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
		<input type="submit" name="actions[addrole]" value="<?=_('Admin')?>" />
		<input type="submit" name="actions[addrole]" value="<?=_('Moderator')?>" />
		<?php endif ?>
		<input type="submit" name="actions[addrole]" value="<?=_('User')?>" />
	</fieldset>
	<fieldset>
		<legend><?=_('Remove role')?></legend>
		<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\IntermediateController::$user['roles'])) > 0 || !in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
		<input type="submit" name="actions[removerole]" value="<?=_('Admin')?>" />
		<input type="submit" name="actions[removerole]" value="<?=_('Moderator')?>" />
		<?php endif ?>
		<input type="submit" name="actions[removerole]" value="<?=_('User')?>" />
	</fieldset>
</form>
