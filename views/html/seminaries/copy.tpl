<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link('index',1)?>"><?=_('Seminaries')?></a></li>
</ul>

<h1><?=_('Copy seminary')?></h1>
<?php if(!is_null($exception)) : ?>
<p class="error">
	<?php if($exception instanceof \hhu\z\exceptions\FileCopyException) : ?>
	<?=sprintf(_('Copying of files failed: “%s”'), $exception->getNestedError()['message'])?>
    <?php elseif($exception instanceof \Exception) : ?>
    <?=sprintf(_('Copying of Seminary failed: “%s”'), $exception->getMessage())?>
	<?php endif ?>
</p>
<?php endif ?>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
					case 'moodpic':
						switch($setting) {
							case 'error': printf(_('Error during moodpic upload: %s'), $value);
							break;
							case 'mimetype': printf(_('Moodpic has wrong type “%s”'), $value);
							break;
							case 'size': echo _('Moodpic exceeds size maximum');
							break;
							default: echo _('Moodpic invalid');
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
					case 'course':
						switch($setting) {
							case 'maxlength': printf(_('Course is too long (max. %d chars)'), $value);
							break;
							default: echo _('Course invalid');
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
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" id="title" name="title" placeholder="<?=_('Title')?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=($validation !== true && array_key_exists('title', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="course"><?=_('Course')?>:</label>
		<input type="text" id="course" name="course" placeholder="<?=_('Course')?>" maxlength="<?=$validationSettings['course']['maxlength']?>" value="<?=$course?>" <?=($validation !== true && array_key_exists('course', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="description"><?=_('Description')?>:<br />
		<textarea id="description" name="description" placeholder="<?=_('Description')?>"><?=$description?></textarea><br />
	</fieldset>
    <fieldset>
        <legend><?=_('Elements')?></legend>
        <input type="checkbox" id="elements_seminaryfields" name="elements[seminaryfields]" <?php if(array_key_exists('seminaryfields', $elements)) : ?>checked="checked"<?php endif ?> />
        <label for="elements_seminaryfields"><?=_('Seminary fields')?></label>
        <input type="checkbox" id="elements_media" name="elements[media]" <?php if(array_key_exists('media', $elements)) : ?>checked="checked"<?php endif ?> />
        <label for="elements_media"><?=_('Media')?></label>
        <input type="checkbox" id="elements_questgroupshierarchy" name="elements[questgroupshierarchy]" <?php if(array_key_exists('questgroupshierarchy', $elements)) : ?>checked="checked"<?php endif ?> />
        <label for="elements_questgroupshierarchy"><?=_('Questgroupshierarchy')?></label>
        <div class="cond">
            <input type="checkbox" id="elements_questgroups" name="elements[questgroups]" <?php if(array_key_exists('questgroups', $elements)) : ?>checked="checked"<?php endif ?> />
            <label for="elements_questgroups"><?=_('Questgroups')?></label>
            <div class="cond">
                <input type="checkbox" id="elements_quests" name="elements[quests]" <?php if(array_key_exists('quests', $elements)) : ?>checked="checked"<?php endif ?> />
                <label for="elements_quests"><?=_('Quests')?></label>
                <div class="cond">
                    <input type="checkbox" id="elements_questtopics" name="elements[questtopics]" <?php if(array_key_exists('questtopics', $elements)) : ?>checked="checked"<?php endif ?> />
                    <label for="elements_questtopics"><?=_('Library')?></label>
                </div>
            </div>
        </div>
        <input type="checkbox" id="elements_charactertypes" name="elements[charactertypes]" <?php if(array_key_exists('charactertypes', $elements)) : ?>checked="checked"<?php endif ?> />
        <label for="elements_charactertypes"><?=_('Charactertypes')?></label>
        <div class="cond">
            <input type="checkbox" id="elements_xplevels" name="elements[xplevels]" <?php if(array_key_exists('xplevels', $elements)) : ?>checked="checked"<?php endif ?> />
            <label for="elements_xplevels"><?=_('XP-Levels')?></label>
            <div class="cond">
                <input type="checkbox" id="elements_avatars" name="elements[avatars]" <?php if(array_key_exists('avatars', $elements)) : ?>checked="checked"<?php endif ?> />
                <label for="elements_avatars"><?=_('Avatars')?></label>
            </div>
        </div>
        <input type="checkbox" id="elements_achievements" name="elements[achievements]" <?php if(array_key_exists('achievements', $elements)) : ?>checked="checked"<?php endif ?> />
        <label for="elements_achievements"><?=_('Achievements')?></label>
        <input type="checkbox" id="elements_charactergroupsgroups" name="elements[charactergroupsgroups]" <?php if(array_key_exists('charactergroupsgroups', $elements)) : ?>checked="checked"<?php endif ?> />
        <label for="elements_charactergroupsgroups"><?=_('Character Groups')?></label>
        <div class="cond">
            <input type="checkbox" id="elements_charactergroupsquests" name="elements[charactergroupsquests]" <?php if(array_key_exists('charactergroupsquests', $elements)) : ?>checked="checked"<?php endif ?> />
            <label for="elements_charactergroupsquests"><?=_('Character Groups Quests')?></label>
        </div>
        <input type="checkbox" id="elements_map" name="elements[map]" <?php if(array_key_exists('map', $elements)) : ?>checked="checked"<?php endif ?>  />
        <label for="elements_map"><?=_('Map')?></label>
    </fieldset>
	<input type="submit" name="edit" value="<?=_('copy')?>" />
</form>
