<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link('index',1)?>"><?=_('Seminaries')?></a></li>
</ul>

<h1><?=_('Edit seminary')?></h1>
<form method="post" class="logreg">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" placeholder="<?=_('Title')?>" value="<?=$seminary['title']?>" /><br />
	</fieldset>
	<input type="submit" name="save" value="<?=_('save')?>" />
</form>
