<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><?=_('Manage Charactertypes')?></h1>




<h2><?=_('Edit Charactertypes')?></h2>
<form method="post">
	<ul>
		<?php foreach($charactertypesNames as $charactertypeId => &$name) : ?>
		<li>
			<?php if($validations['edit-charactertypes'] !== true && array_key_exists($charactertypeId, $validations['edit-charactertypes']) && $validations['edit-charactertypes'][$charactertypeId] !== true) : ?>
			<ul>
				<?php foreach($validations['edit-charactertypes'][$charactertypeId] as $field => &$settings) : ?>
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
			<input id="charactertype-<?=$charactertypeId?>" type="text" name="charactertypes[<?=$charactertypeId?>]" placeholder="<?=$name?>" title="<?=$name?>" required="required" maxlength="<?=$validationSettings['charactertype']['maxlength']?>" value="<?=$name?>" <?=($validations['edit-charactertypes'] !== true && array_key_exists($charactertypeId, $validations['edit-charactertypes']) && $validations['edit-charactertypes'][$charactertypeId] !== true && array_key_exists('charactertypename', $validations['edit-charactertypes'][$charactertypeId])) ? 'class="invalid"' : null?>/>
			<input id="charactertype-<?=$charactertypeId?>-delete" type="checkbox" name="delete-charactertypes[<?=$charactertypeId?>]" <?php if(!is_null($deleteCharactertypes) && array_key_exists($charactertypeId, $deleteCharactertypes)) : ?>checked="checked"<?php endif ?> />
			<label for="charactertype-<?=$charactertypeId?>-delete"><?=_('delete')?></label><br />
		</li>
		<?php endforeach ?>
	</ul>
	<input type="submit" name="edit-charactertypes" value="<?=_('save')?>" />
</form>




<h2><?=_('Create new Charactertype')?></h2>
<?php if($validations['create-charactertype'] !== true) : ?>
<ul>
	<?php foreach($validations['create-charactertype'] as $field => &$settings) : ?>
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
<form method="post">
	<fieldset>
		<label for="charactertypename"><?=_('Name')?>:</legend>
		<input id="charactertypename" type="text" name="charactertypename" placeholder="<?=_('Name')?>" title="<?=_('Name')?>" required="required" maxlength="<?=$validationSettings['charactertypename']['maxlength']?>" value="<?=$charactertypeName?>" <?=($validations['create-charactertype'] !== true && array_key_exists('title', $validations['create-charactertype'])) ? 'class="invalid"' : null?> />
	</fieldset>
	<input type="submit" name="create-charactertype" value="<?=_('create')?>" />
</form>
