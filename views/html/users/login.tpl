<div class="moodpic">
    <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<h1><?=_('Users')?></h1>

<h2><?=_('Login')?></h2>
<?php if($failed) : ?>
<p class="invalid"><?=_('Login failed')?>.</p>
<?php endif ?>
<form method="post" class="logreg">
    <fieldset>
        <label for="username"><?=_('Username')?>:</label>
        <input name="username" type="text" placeholder="<?=_('Username')?>" value="<?=$username?>" required="required" autofocus="autofocus" /><br />
        <label for="password"><?=_('Password')?>:</label>
        <input name="password" type="password" placeholder="<?=_('Password')?>" required="required" /><br />
    </fieldset>
    <?php if(!empty($referrer)) : ?>
    <input type="hidden" name="referrer" value="<?=$referrer?>" />
    <?php endif ?>
    <input type="submit" name="login" value="<?=_('Login')?>" />
</form>
