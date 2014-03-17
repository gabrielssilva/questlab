<h1><?=_('Users')?></h1>
<h2><?=_('Delete user')?></h2>

<?=sprintf(_('Should the user “%s” (%s) really be deleted?'), $user['username'], $user['email'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
