<div class="moodpic">
    <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<?php if(is_null($userId)) : ?>
<form method="post" action="<?=$linker->link(array('users','login'))?>" class="logreg front">
    <fieldset>
        <p>
            <label for="username"><?=_('Username')?>:</label>
            <input id="username" name="username" type="text" placeholder="<?=_('Username')?>" title="<?=_('Username')?>" required="required" autofocus="autofocus" />
        </p>
        <p>
            <label for="password"><?=_('Password')?>:</label>
            <input id="password" name="password" type="password" placeholder="<?=_('Password')?>" title="<?=_('Password')?>" required="required" />
        </p>
        <input type="submit" name="login" class="cta" value="<?=_('Login')?>" />
    </fieldset>
    <p class="register"><?=_('or')?> <a href="<?=$linker->link(array('users','register'))?>"><?=_('register yourself')?></a></p>
</form>
<?php endif ?>
<?php if(!is_null(\hhu\z\controllers\IntermediateController::$user) && in_array('admin',\hhu\z\controllers\IntermediateController::$user['roles'])) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link('edit', 1)?>"><?=_('edit')?></a></li>
</nav>
<?php endif ?>

<h1><?=\nre\configs\AppConfig::$app['name']?></h1>
<?php if(!empty($text)) : ?>
<?=$t->t($text)?>
<?php endif ?>

<hr />
<p><?=sprintf(
    _('This application is powered by %s and is licensed under the %s'),
    '<a href="http://www.questlab.zone">Questlab</a>',
    '<a rel="license" href="http://www.gnu.org/licenses/gpl.html">GPL</a>'
)?>.</p>
