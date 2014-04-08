<h1><?=_('Seminaries')?></h1>
<h2><?=_('New seminary')?></h2>

<form method="post" action="<?=$linker->link('create', 1)?>">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" placeholder="<?=_('Title')?>" /><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
