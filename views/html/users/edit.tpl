<h1><?=_('Users')?></h1>
<h2><?=_('Edit user')?></h2>

<form method="post" class="logreg">
	<fieldset>
		<label for="username"><?=_('Username')?>:</label>
		<input type="text" name="username" placeholder="<?=_('Username')?>" value="<?=$user['username']?>" /><br />
		<label for="prename"><?=_('Prename')?>:</label>
		<input name="prename" type="text" placeholder="<?=_('Prename')?>" value="<?=$user['prename']?>" /><br />
		<label for="surname"><?=_('Surname')?>:</label>
		<input name="surname" type="text" placeholder="<?=_('Surname')?>" value="<?=$user['surname']?>" /><br />
		<label for="email"><?=_('E‑mail address')?>:</label>
		<input type="email" name="email" placeholder="<?=_('E‑mail address')?>" value="<?=$user['email']?>" /><br />
		<label for="password"><?=_('Password')?>:</label>
		<input type="password" name="password" placeholder="<?=_('Password')?>" /><br />
	</fieldset>
	<input type="submit" name="save" value="<?=_('save')?>" />
</form>
