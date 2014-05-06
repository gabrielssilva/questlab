<?php if(!is_null($seminary['charactergroups_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'charactergroups'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></li>
</ul>

<h1><?=sprintf(_('Edit %s Character group'), $groupsgroup['name'])?></h1>
<?php if($validation !== true) : ?>
<ul>
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
					case 'icon':
						switch($setting) {
							case 'error': printf(_('Error during icon upload: %s'), $value);
							break;
							case 'mimetype': printf(_('Icon has wrong type “%s”'), $value);
							break;
							case 'size': echo _('Icon exceeds size maximum');
							break;
							default: echo _('Icon invalid');
						}
					break;
					case 'charactergroupname':
						switch($setting) {
							case 'minlength': printf(_('Name is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Name is too long (max. %d chars)'), $value);
							break;
							case 'regex': echo _('Name contains illegal characters');
							break;
							case 'exist': echo _('Name already exists');
							break;
							default: echo _('Name invalid');
						}
					break;
					case 'motto':
						switch($setting) {
							case 'maxlength': printf(_('Motto is too long (max. %d chars)'), $value);
							break;
							default: echo _('Motto invalid');
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
		<legend><?=_('Icon')?></legend>
		<img src="<?=$linker->link(array('media','charactergroup',$seminary['url'],$groupsgroup['url'],$group['url']))?>" class="gbanner"><br />
		<input type="file" name="icon" />
		<p><?=_('Allowed file types')?>:</p>
		<ul>
			<?php foreach($mimetypes as &$mimetype) : ?>
			<li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
			<?php endforeach ?>
		</ul>
	</fieldset>
	<fieldset>
		<label for="charactergroupname"><?=_('Name')?>:</label>
		<?php if(count(array_intersect(array('admin','moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
		<input type="text" id="charactergroupname" name="charactergroupname" placeholder="<?=_('Name')?>" title="<?=_('Name')?>" required="required" maxlength="<?=$validationSettings['charactergroupname']['maxlength']?>" value="<?=$charactergroupname?>" <?=(array_key_exists('charactergroupname', $validation)) ? 'class="invalid"' : null?> /><br />
		<?php else : ?>
		<input type="text" id="charactergroupname" name="charactergroupname" disabled="disabled" value="<?=$charactergroupname?>" <?=(array_key_exists('charactergroupname', $validation)) ? 'class="invalid"' : null?> /><br />
		<input type="hidden" name="charactergroupname" value="<?=$charactergroupname?>" />
		<?php endif ?>
		<label for="motto"><?=_('Motto')?>:</label>
		<input type="text" id="motto" name="motto" placeholder="<?=_('Motto')?>" title="<?=_('Motto')?>" maxlength="<?=$validationSettings['motto']['maxlength']?>" value="<?=$motto?>" <?=(array_key_exists('motto', $validation)) ? 'class="invalid"' : null?> /><br />
	</fieldset>
	<input type="submit" name="edit" value="<?=_('edit')?>" />
</form>
