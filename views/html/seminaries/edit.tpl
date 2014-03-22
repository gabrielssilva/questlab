<h2><?=_('Seminaries')?></h2>
<h3><?=_('Edit seminary')?></h3>

<form method="post">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" placeholder="<?=_('Title')?>" value="<?=$seminary['title']?>" /><br />
	</fieldset>
	<input type="submit" name="save" value="<?=_('save')?>" />
</form>
