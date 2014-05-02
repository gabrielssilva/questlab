<div class="moodpic">
	<img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link('index',1)?>"><?=_('Users')?></a></li>
</ul>

<h1><?=_('Manage')?></h1>

<form method="post">
	<fieldset class="filter">
		<p><small>Sortierung:</small></p>
		<select name="sortorder" onchange="this.form.submit();">
			<option value="username" <?php if($sortorder == 'username') : ?>selected="selected"<?php endif ?>><?=_('Username')?></option>
			<option value="role" <?php if($sortorder == 'role') : ?>selected="selected"<?php endif ?>><?=_('Role')?></option>
			<option value="date" <?php if($sortorder == 'date') : ?>selected="selected"<?php endif ?>><?=_('Date of registration')?></option>
		</select>
		<noscript><input type="submit" value="<?=_('Sort list')?>" /></noscript>
	</fieldset>
	<fieldset>
		<ul class="admnql">
			<?php foreach($users as &$user) : ?>
			<li class="cf">
				<input type="checkbox" id="users-<?=$user['id']?>" name="users[]" value="<?=$user['id']?>" <?php if(in_array($user['id'], $selectedUsers)) : ?>checked="checked"<?php endif ?> <?php if($user['id'] == \hhu\z\controllers\SeminaryController::$user['id']) : ?>disabled="disabled"<?php endif ?>/>
				<label for="users-<?=$user['id']?>">
					<p>
					<a href="<?=$linker->link(array('users','user',$user['url']))?>"><?=$user['username']?></a>
					<?php if(in_array('admin', $user['roles'])) : ?><small>(<?=_('Admin')?>)</small><?php endif ?>
					<?php if(in_array('moderator', $user['roles'])) : ?><small>(<?=_('Moderator')?>)</small><?php endif ?>
					<?php if(in_array('user', $user['roles'])) : ?><small>(<?=_('User')?>)</small><?php endif ?>
					<span class="xp"><small><?=sprintf(_('registered on %s'),  $dateFormatter->format(new \DateTime($user['created'])))?></small></span>
					</p>
				</label>
			</li>
			<?php endforeach ?>
		</ul>
	</fieldset>
	<fieldset>
		<legend><?=_('Add role')?></legend>
		<?php if(in_array('admin', \hhu\z\controllers\IntermediateController::$user['roles'])) : ?>
		<input type="submit" name="actions[addrole]" value="<?=_('Admin')?>" />
		<input type="submit" name="actions[addrole]" value="<?=_('Moderator')?>" />
		<?php endif ?>
		<input type="submit" name="actions[addrole]" value="<?=_('User')?>" />
	</fieldset>
	<fieldset>
		<legend><?=_('Remove role')?></legend>
		<?php if(in_array('admin', \hhu\z\controllers\IntermediateController::$user['roles'])) : ?>
		<input type="submit" name="actions[removerole]" value="<?=_('Admin')?>" />
		<input type="submit" name="actions[removerole]" value="<?=_('Moderator')?>" />
		<?php endif ?>
		<input type="submit" name="actions[removerole]" value="<?=_('User')?>" />
	</fieldset>
</form>
