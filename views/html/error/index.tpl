<h1><?=_('Error')?></h1>
<p class="error"><?=$code?>: <?=$string?></p>

<?php if($code == 403 && $userId <= 0) : ?>
<h2><?=_('Login')?></h2>
<form method="post" action="<?=$linker->link(array('users','login'))?>" class="logreg">
	<fieldset>
		<label for="username"><?=_('Username')?>:</label>
		<input name="username" type="text" placeholder="<?=_('Username')?>" title="<?=_('Username')?>" required="required" autofocus="autofocus" /><br />
		<label for="password"><?=_('Password')?>:</label>
		<input name="password" type="password" placeholder="<?=_('Password')?>" title="<?=_('Password')?>" required="required" /><br />
	</fieldset>
	<input type="hidden" name="referrer" value="<?=$linker->link(null, null, false)?>" />
	<input type="submit" name="login" class="cta" value="<?=_('Login')?>" />
	<?=_('or')?> <a href="<?=$linker->link(array('users','register'))?>"><?=_('register yourself')?></a>
</form>
<?php endif ?>
