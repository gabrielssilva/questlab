<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>" />
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><?=_('Questgroups')?></li>
</ul>

<h1><?=_('Create Questgroup')?></h1>
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
		<legend><?=_('Context')?></legend>
		<?=_('Questgroupshierarchy')?>: <?=$questgroupshierarchy['title_singular']?><br />
		<input type="hidden" name="questgroupshierarchy" value="<?=$questgroupshierarchy['url']?>" />
		<?php if(!is_null($questgroup)) : ?>
		<?=_('Questgroup')?>: <?=$questgroup['title']?>
		<input type="hidden" name="questgroup" value="<?=$questgroup['url']?>" />
		<?php endif ?>
	</fieldset>
	<fieldset>
		<legend><?=_('Moodpic')?></legend>
		<input type="file" name="moodpic" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" />
		<p><?=_('Allowed file types')?>:</p>
		<ul>
			<?php foreach($mimetypes as &$mimetype) : ?>
			<li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
			<?php endforeach ?>
		</ul>
	</fieldset>
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input type="text" name="title" placeholder="<?=_('Title')?>" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=(array_key_exists('title', $validation)) ? 'class="invalid"' : null?> /><br />
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
