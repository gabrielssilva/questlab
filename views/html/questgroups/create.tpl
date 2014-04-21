<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><?=_('Questgroups')?></h2>
<h3><?=_('Create')?></h3>

<form method="post">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" value="" placeholder="<?=_('Title')?>" /><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('Create')?>" />
</form>
