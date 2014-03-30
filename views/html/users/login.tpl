<h1><?=_('Users')?></h1>
<h2><?=_('Login')?></h2>

<form method="post" action="<?=$linker->link(array(), 2)?>">
	<fieldset>
		<label for="username"><?=_('Username')?></label>
		<input name="username" type="text" placeholder="<?=_('Username')?>" value="<?=$username?>" /><br />
		<label for="password"><?=_('Password')?></label>
		<input name="password" type="password" placeholder="<?=_('Password')?>" /><br />
	</fieldset>
	<input type="submit" name="login" value="<?=_('Login')?>" />
</form>
