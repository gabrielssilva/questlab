<h1><?=_('Seminaries')?></h1>
<h2><?=_('Edit seminary')?></h2>

<form method="post">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" placeholder="<?=_('Title')?>" value="<?=$seminary['title']?>" /><br />
	</fieldset>
	<input type="submit" name="save" value="<?=_('save')?>" />
</form>
