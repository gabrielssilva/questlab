<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Quests')?></a></h2>
<h3><?=_('Create')?></h3>

<form method="post">
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
		<label for="name">XPs:</label>
		<input type="number" name="xps" value="" placeholder="<?=_('XPs')?>" /><br />
		<label for="entrytext"><?=('Entry text')?>:</label><br />
		<textarea name="entrytext" placeholder="<?=_('Entry text')?>"></textarea><br />
		<label for="wrongtext"><?=('Wrong text')?>:</label><br />
		<textarea name="wrongtext" placeholder="<?=_('Wrong text')?>"></textarea><br />
		<label for="task"><?=_('Task')?>:</label><br />
		<textarea name="task" placeholder="<?=('Task')?>"></textarea><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('Create')?>" />
</form>
