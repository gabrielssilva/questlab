<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><?=_('Questgroups')?></li>
</ul>
<h1><?=_('Create Questgroup')?></h1>

<form method="post">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" value="" placeholder="<?=_('Title')?>" /><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('Create')?>" />
</form>
