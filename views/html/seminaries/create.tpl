<h2><?=_('Seminaries')?></h2>
<h3><?=_('New seminary')?></h3>

<form method="post" action="<?=$linker->link('create', 1)?>">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" placeholder="<?=_('Title')?>" /><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
