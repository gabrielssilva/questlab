<div class="moodpic">
    <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link('index',1)?>"><?=_('Users')?></a></li>
</ul>

<h1><?=_('Delete user')?></h1>
<?=sprintf(_('Should the user “%s” (%s) really be deleted?'), $user['username'], $user['email'])?>
<form method="post">
    <input type="submit" name="delete" value="<?=_('delete')?>" />
    <input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
