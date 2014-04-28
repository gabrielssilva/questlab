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
	<fieldset>
		<legend><?=_('Properties')?></legend>
		<input type="checkbox" id="username" name="properties[]" value="username" <?php if(in_array('username', $properties)) : ?>checked="checked"<?php endif ?> /><label for="username"><?=_('Username')?></label><br />
		<input type="checkbox" id="xps" name="properties[]" value="xps" <?php if(in_array('xps', $properties)) : ?>checked="checked"<?php endif ?> /><label for="xps"><?=_('XPs')?></label><br />
		<input type="checkbox" id="roles" name="properties[]" value="roles" <?php if(in_array('roles', $properties)) : ?>checked="checked"<?php endif ?> /><label for="roles"><?=_('Roles')?></label><br />
		<?php foreach($characterfields as &$characterfield) : ?>
		<input type="checkbox" id="characterfield-<?=$characterfield['url']?>" name="properties[characterfields][]" value="<?=$characterfield['url']?>" <?php if(array_key_exists('characterfields', $properties) && in_array($characterfield['url'], $properties['characterfields'])) : ?>checked="checked"<?php endif ?> /><label for="characterfield-<?=$characterfield['url']?>"><?=$characterfield['url']?></label><br />
		<?php endforeach ?>
		<input type="submit" name="set-properties" value="<?=_('Set properties')?>" />
	</fieldset>
	<fieldset>
		<legend><?=_('Selection')?>:</legend>
		<ul class="gchars cf">
			<?php foreach($characters as &$character) : ?>
			<li>
				<input type="checkbox" id="characters-<?=$character['id']?>" name="characters[]" value="<?=$character['id']?>" <?php if(in_array($character['id'], $selectedCharacters)) : ?>checked="checked"<?php endif ?> <?php if($character['id'] == \hhu\z\controllers\SeminaryController::$character['id']) : ?>disabled="disabled"<?php endif ?>/>
				<label for="characters-<?=$character['id']?>">
					<p><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level'],'portrait'))?>"></p>
					<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
					<?php if(in_array('username', $properties)) : ?><p><small><a href="<?=$linker->link(array('users','user',$character['user']['url']))?>"><?=$character['user']['username']?></a></small></p><?php endif ?>
					<?php if(in_array('xps', $properties)) : ?><p><small><?=$character['xps']?> XP</small></p><?php endif ?>
					<?php if(in_array('roles', $properties)) : ?>
					<?php if(in_array('admin', $character['characterroles'])) : ?><p><small><?=_('Admin')?></small></p><?php endif ?>
					<?php if(in_array('moderator', $character['characterroles'])) : ?><p><small><?=_('Moderator')?></small></p><?php endif ?>
					<?php if(in_array('user', $character['characterroles'])) : ?><p><small><?=_('User')?></small></p><?php endif ?>
					<?php endif ?>
					<?php foreach($character['characterfields'] as &$characterfield) : ?>
					<?php if(array_key_exists('characterfields', $properties) && in_array($characterfield['url'], $properties['characterfields'])) : ?>
					<p><small><?=$characterfield['value']?></small></p>
					<?php endif ?>
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
