<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>

<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Quests')?></a></li>
</ul>
<h1><?=_('Create Quest')?></h1>

<form method="post" enctype="multipart/form-data">
	<fieldset>
		<label for="name"><?=_('Name')?>:</label>
		<input type="text" name="name" value="" placeholder="<?=_('Name')?>" /><br />
		<label for="questgroup"><?=_('Questgroup')?>:</label>
		<select name="questgroup">
			<?php foreach($questgroups as &$questgroup) : ?>
			<option value="<?=$questgroup['url']?>"><?=$questgroup['title']?></option>
			<?php endforeach ?>
		</select><br />
		<label for="questtype"><?=('Questtype')?>:</label>
		<select name="questtype">
			<?php foreach($questtypes as &$questtype) : ?>
			<option value="<?=$questtype['url']?>"><?=$questtype['title']?></option>
			<?php endforeach ?>
		</select><br />
		<label for="name"><?=_('XPs')?>:</label>
		<input type="number" name="xps" value="" placeholder="<?=_('XPs')?>" /><br />
		<input type="file" name="questmedia" /><br />
	</fieldset>
	<fieldset>
		<label for="prolog">Prolog:</label><br />
		<textarea name="prolog" placeholder="Prolog" style="width:100%; height:10em;"></textarea><br />
		<label for="entrytext"><?=('Entry text')?>:</label><br />
		<textarea name="entrytext" placeholder="<?=_('Entry text')?>" style="width:100%; height:10em;"></textarea><br />
		<label for="wrongtext"><?=('Wrong text')?>:</label><br />
		<textarea name="wrongtext" placeholder="<?=_('Wrong text')?>" style="width:100%; height:10em;"></textarea><br />
		<label for="task"><?=_('Task')?>:</label><br />
		<textarea name="task" placeholder="<?=('Task')?>" style="width:100%; height:10em;"></textarea><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('Create')?>" />
</form>
