<div class="moodpic">
	<img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<ul class="breadcrumbs">
	<?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) : ?>
	<li><a href="<?=$linker->link('index',1)?>"><?=_('Users')?></a></li>
	<?php else : ?>
	<li><?=_('Users')?></li>
	<?php endif ?>
</ul>

<h1><?=_('Edit user')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
					case 'username':
						switch($setting) {
							case 'minlength': printf(_('Username is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Username is too long (max. %d chars)'), $value);
							break;
							case 'regex': echo _('Username contains illegal characters');
							break;
							case 'exist': echo _('Username already exists');
							break;
							default: echo _('Username invalid');
						}
					break;
					case 'prename':
						switch($setting) {
							case 'minlength': printf(_('Prename is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Prename is too long (max. %d chars)'), $value);
							break;
							case 'regex': printf(_('Prename contains illegal characters'));
							break;
							default: echo _('Prename invalid');
						}
					break;
					case 'surname':
						switch($setting) {
							case 'minlength': printf(_('Surname is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Surname is too long (max. %d chars)'), $value);
							break;
							case 'regex': printf(_('Surname contains illegal characters'));
							break;
							default: echo _('Surname invalid');
						}
					break;
					case 'email':
						switch($setting) {
							case 'regex': echo _('E‑mail address invalid');
							break;
							case 'exist': echo _('E‑mail address already exists');
							break;
							default: echo _('E‑mail address invalid');
						}
					break;
					case 'password':
						switch($setting) {
							case 'minlength': printf(_('Password is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Password is too long (max. %d chars)'), $value);
							break;
                            case 'repeat': printf(_('Passwords does not match'));
                            break;
							default: echo _('Password invalid');
						}
					break;
					default:
						echo $exception->getMessage();
					break;
				} ?>
			</li>
			<?php endforeach ?>
		</ul>
	</li>
	<?php endforeach ?>
</ul>
<?php endif ?>
<form method="post" class="logreg">
	<fieldset>
		<label for="username"><?=_('Username')?>:</label>
		<?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) : ?>
		<input name="username" type="text" placeholder="<?=_('Username')?>" title="<?=_('Username')?>" value="<?=$username?>" required="required" maxlength="<?=$validationSettings['username']['maxlength']?>" <?=(array_key_exists('username', $validation)) ? 'class="invalid"' : null ?> />
		<?php else : ?>
		<input name="username" type="text" placeholder="<?=_('Username')?>" title="<?=_('Username')?>" value="<?=$username?>" disabled="disabled" />
		<input type="hidden" name="username" value="<?=$username?>" />
		<?php endif ?><br />
		<label for="prename"><?=_('Prename')?>:</label>
		<input name="prename" type="text" placeholder="<?=_('Prename')?>" title="<?=_('Prename')?>" required="required" maxlength="<?=$validationSettings['prename']['maxlength']?>" value="<?=$prename?>" <?=(array_key_exists('prename', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="surname"><?=_('Surname')?>:</label>
		<input name="surname" type="text" placeholder="<?=_('Surname')?>" title="<?=_('Surname')?>" required="required" maxlength="<?=$validationSettings['surname']['maxlength']?>" value="<?=$surname?>" <?=(array_key_exists('surname', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="email"><?=_('E‑mail address')?>:</label>
		<input name="email" type="email" placeholder="<?=_('E‑mail address')?>" title="<?=_('E‑mail address')?>" required="required" value="<?=$email?>" <?=(array_key_exists('email', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="password"><?=_('Password')?>:</label>
		<input name="password" type="password" placeholder="<?=_('Password')?>" title="<?=_('Password')?>" maxlength="<?=$validationSettings['password']['maxlength']?>" <?=(array_key_exists('password', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="passwordrepeat"><?=_('Repeat password')?>:</label>
		<input name="passwordrepeat" type="password" placeholder="<?=_('Password')?>" title="<?=_('Password')?>" required="required" maxlength="<?=$validationSettings['password']['maxlength']?>" <?=(array_key_exists('password', $validation)) ? 'class="invalid"' : null?> /><br />
		<input id="mailing" type="checkbox" name="mailing" <?php if($mailing) : ?>checked="checked"<?php endif ?> /> 
		<label for="mailing"><?=_('Mail notifications')?></label>
	</fieldset>
	<input type="submit" name="save" value="<?=_('save')?>" />
</form>
