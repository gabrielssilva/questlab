<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><?=_('Questgroupshierarchy')?></li>
</ul>

<h1><?=_('Edit Questgroupshierarchy')?></h1>
<?php if($validation !== true) : ?>
<ul>
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
					case 'titleSingular':
						switch($setting) {
							case 'minlength': printf(_('Title (singular) is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Title (singular) is too long (max. %d chars)'), $value);
							break;
							case 'exist': echo _('Title (singular) already exists');
							break;
							default: echo _('Title (singular) invalid');
						}
					break;
					case 'titlePlural':
						switch($setting) {
							case 'minlength': printf(_('Title (plural) is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Title (plural) is too long (max. %d chars)'), $value);
							break;
							case 'exist': echo _('Title (plural) already exists');
							break;
							default: echo _('Title (plural) invalid');
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
<form method="post" class="logreg">
	<fieldset>
		<label for="title_singular"><?=_('Title (singular)')?>:</label>
		<input type="text" name="title_singular" placeholder="<?=_('Title (singular)')?>" value="<?=$titleSingular?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" <?=(array_key_exists('titleSingular', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="title_plural"><?=_('Title (plural)')?>:</label>
		<input type="text" name="title_plural" placeholder="<?=_('Title (plural)')?>" value="<?=$titlePlural?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" <?=(array_key_exists('titlePlural', $validation)) ? 'class="invalid"' : null?> /><br />
	</fieldset>
	<input type="submit" name="edit" value="<?=_('edit')?>" />
</form>
