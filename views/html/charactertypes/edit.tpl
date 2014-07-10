<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Charactertypes')?></a></li>
</ul>

<h1><?=_('Edit Charactertype')?></h1>
<?php if($validation !== true) : ?>
<ul>
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
					case 'charactertypename':
						switch($setting) {
							case 'minlength': printf(_('Name is too short (min. %d chars)'), $value);
							break;
							case 'maxlength': printf(_('Name is too long (max. %d chars)'), $value);
							break;
							case 'exist': echo _('Name already exists');
							break;
							default: echo _('Name invalid');
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
<form method="post" enctype="multipart/form-data">
	<fieldset>
		<label for="name"><?=_('Name')?>:</label>
		<input id="name" type="text" name="charactertypename" placeholder="<?=_('Name')?>" title="<?=_('Name')?>" required="required" maxlength="<?=$validationSettings['charactertypename']['maxlength']?>" value="<?=$name?>" <?=($validation !== true && array_key_exists('name', $validation)) ? 'class="invalid"' : null?> />
	</fieldset>
	<fieldset>
		<legend><?=_('Avatars')?></legend>
		<ul>
			<?php foreach($xplevels as &$xplevel) : ?>
			<li>
				<?php if($avatarsValidation !== true && array_key_exists($xplevel['id'], $avatarsValidation)) : ?>
				<ul>
					<?php if(array_key_exists('portrait', $avatarsValidation[$xplevel['id']])) : ?>
					<?php foreach($avatarsValidation[$xplevel['id']]['portrait'] as $field => &$settings) : ?>
					<li>
						<ul>
							<?php foreach($settings as $setting => $value) : ?>
							<li>
								<?php switch($field) {
									case 'avatar':
										switch($setting) {
											case 'error': printf(_('Error during avatar portrait upload: %s'), $value);
											break;
											case 'mimetype': printf(_('Avatar portrait has wrong type “%s”'), $value);
											break;
											case 'size': echo _('Avatar portrait exceeds size maximum');
											break;
											default: echo _('Avatar portrait invalid');
										}
									break;
								} ?>
							</li>
							<?php endforeach ?>
						</ul>
					</li>
					<?php endforeach ?>
					<?php endif ?>
					<?php if(array_key_exists('avatar', $avatarsValidation[$xplevel['id']])) : ?>
					<?php foreach($avatarsValidation[$xplevel['id']]['avatar'] as $field => &$settings) : ?>
					<li>
						<ul>
							<?php foreach($settings as $setting => $value) : ?>
							<li>
								<?php switch($field) {
									case 'avatar':
										switch($setting) {
											case 'error': printf(_('Error during avatar upload: %s'), $value);
											break;
											case 'mimetype': printf(_('Avatar has wrong type “%s”'), $value);
											break;
											case 'size': echo _('Avatar exceeds size maximum');
											break;
											default: echo _('Avatar invalid');
										}
									break;
								} ?>
							</li>
							<?php endforeach ?>
						</ul>
					</li>
					<?php endforeach ?>
					<?php endif ?>
				</ul>
				<?php endif ?>
				<?=_('Level')?> <?=$xplevel['level']?>:<br />
				<?php if(array_key_exists('avatar', $xplevel) && !is_null($xplevel['avatar']['small_avatarpicture_id'])) : ?>
				<img id="avatar" src="<?=$linker->link(array('media','avatar',$seminary['url'],$charactertype['url'],$xplevel['level'],'portrait'))?>" />
				<?php endif ?>
				<label for="avatar-<?=$xplevel['id']?>-portrait"><?=_('Protrait')?>:</label>
				<input id="avatar-<?=$xplevel['id']?>-portrait" type="file" name="avatars[<?=$xplevel['id']?>][portrait]" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" /><br />
				<?php if(array_key_exists('avatar', $xplevel) && !is_null($xplevel['avatar']['avatarpicture_id'])) : ?>
				<img id="avatar" src="<?=$linker->link(array('media','avatar',$seminary['url'],$charactertype['url'],$xplevel['level']))?>" />
				<?php endif ?>
				<label for="avatar-<?=$xplevel['id']?>-avatar"><?=_('Avatar')?>:</label>
				<input id="avatar-<?=$xplevel['id']?>-avatar" type="file" name="avatars[<?=$xplevel['id']?>][avatar]" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" />
			</li>
			<?php endforeach ?>
		</ul>
		<p><?=_('Allowed file types')?>:</p>
		<ul>
			<?php foreach($mimetypes as &$mimetype) : ?>
			<li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
			<?php endforeach ?>
		</ul>
	</fieldset>
	<input type="submit" name="edit" value="<?=_('save')?>" />
</form>
