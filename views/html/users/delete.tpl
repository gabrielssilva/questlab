<h2><?=_('Users')?></h2>
<h3><?=_('Delete user')?></h3>

<?=sprintf(_('Should the user “%s” (%s) really be deleted?'), $user['username'], $user['email'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
