<h2><?=_('Seminaries')?></h2>
<h3><?=_('Delete seminary')?></h3>

<?=sprintf(_('Should the seminary “%s” really be deleted?'), $seminary['title'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
