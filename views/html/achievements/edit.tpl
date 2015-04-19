<?php if(!is_null($seminary['achievements_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'achievements'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('achievements','index',$seminary['url']))?>"><?=_('Achievements')?></a></li>
</ul>

<h1><?=_('Edit Achievement')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
					case 'media':
						switch($setting) {
							case 'error': printf(_('Error during picture upload: %s'), $value);
							break;
							case 'mimetype': printf(_('Picture has wrong type “%s”'), $value);
							break;
							case 'size': echo _('Picture exceeds size maximum');
							break;
							default: echo _('Picture invalid');
						}
					break;
					case 'title':
						switch($setting) {
							case 'minlength': printf(_('Title is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Title is too long (max. %d chars)'), $value);
							break;
							case 'regex': echo _('Title contains illegal characters');
							break;
							case 'exist': echo _('Title already exists');
							break;
							default: echo _('Title invalid');
						}
					break;
					case 'deadline':
						switch($setting) {
							case 'regex': echo _('Deadline has wrong format');
							break;
							default: echo _('Deadline invalid');
						}
					break;
				} ?>
			</li>
			<?php endforeach ?>
		</ul>
	</li>
	<?php endforeach ?>
</ul>
<?php endif ?>
<form method="post" class="logreg" enctype="multipart/form-data">
	<fieldset>
		<legend><?=_('Images')?></legend>
		<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url'],'locked'))?>" />
		<label for="unachievedImage"><?=_('Unachieved')?></label>
		<input id="unachievedImage" type="file" name="unachieved_image" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" /><br />
		<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url']))?>" />
		<label for="achievedImage"><?=_('Achieved')?></label>
		<input id="achievedImage" type="file" name="achieved_image" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" /><br />
		<p><?=_('Allowed file types')?>:</p>
		<ul>
			<?php foreach($mimetypes as &$mimetype) : ?>
			<li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
			<?php endforeach ?>
		</ul>
	</fieldset>
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input id="title" type="text" name="title" placeholder="<?=_('Title')?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=(array_key_exists('title', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="description"><?=_('Description')?>:</label>
		<textarea id="description" name="description"><?=$description?></textarea><br />
		<input id="progress" type="checkbox" name="progress" <?php if($progress) : ?>checked="checked"<?php endif ?> />
		<label for="progress"><?=_('Show progress')?></label><br />
		<input id="hidden" type="checkbox" name="hidden" <?php if($hidden) : ?>checked="checked"<?php endif ?> />
		<label for="hidden"><?=_('Secret Achievement')?></label><br />
		<input id="onlyOnce" type="checkbox" name="only_once" <?php if($onlyOnce) : ?>checked="checked"<?php endif ?> />
		<label for="onlyOnce"><?=_('Only achieveable by one Character')?></label><br />
		<input id="allConditions" type="checkbox" name="all_conditions" <?php if($allConditions) : ?>checked="checked"<?php endif ?> />
		<label for="allConditions"><?=_('All conditions')?></label><br />
		<label for="deadline"><?=_('Deadline')?>:</label>
		<input id="deadline" type="datetime" name="deadline" placeholder="YYYY-MM-DD HH:MM:SS" pattern="<?=substr($validationSettings['deadline']['regex'],1,strrpos($validationSettings['deadline']['regex'],$validationSettings['deadline']['regex'][0])-1)?>" value="<?=$deadline?>" <?=(array_key_exists('deadline', $validation)) ? 'class="invalid"' : null?> />
	</fieldset>
	<fieldset>
		<legend><?=_('Condition')?></legend>
		<select name="condition">
			<?php foreach($conditions as &$c) : ?>
			<option value="<?=$c['condition']?>" <?php if($c['condition'] == $condition) : ?>selected="selected"<?php endif ?>>
				<?php switch($c['condition']) {
					case 'date': echo _('Achievement conditions date');
					break;
					case 'character': echo _('Achievement conditions Character');
					break;
					case 'quest': echo _('Achievement conditions Quest');
					break;
					case 'achievement': echo _('Achievement conditions Achievement');
					break;
				} ?>
			</option>
			<?php endforeach ?>
		</select>
		<i><?=_('Changing the condition will delete all current conditions')?>.</i>
	</fieldset>
	<input type="submit" name="edit-conditions" value="<?=_('edit conditions')?>" />
	<input type="submit" name="edit" value="<?=_('save')?>" />
</form>
