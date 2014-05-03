<div class="moodpic">
	<img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link('index',1)?>"><?=_('Seminaries')?></a></li>
</ul>

<h1><?=_('New seminary')?></h1>
<form method="post" action="<?=$linker->link('create', 1)?>" class="logreg">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" placeholder="<?=_('Title')?>" /><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
