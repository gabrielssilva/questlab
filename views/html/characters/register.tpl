<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><?=$seminary['title']?></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><?=_('Characters')?></li>
</ul>
<h1><?=_('Create Character')?></h1>
<form method="post" action="" class="logreg">
	<?php if($validation !== true) : ?>
	<ul>
		<?php foreach($validation as $field => &$settings) : ?>
		<li>
			<ul>
				<?php foreach($settings as $setting => $value) : ?>
				<li>
					<?php switch($field) {
						case 'charactername':
							switch($setting) {
								case 'minlength': printf(_('Character name is too short (min. %d chars)'), $value);
								break;
								case 'maxlength': printf(_('Character name is too long (max. %d chars)'), $value);
								break;
								case 'regex': echo _('Character name contains illegal characters');
								break;
								case 'exist': echo _('Character name already exists');
								break;
								default: echo _('Character name invalid');
							}
						break;
						case 'type':
							switch($setting) {
								case 'exist': echo _('Please choose an avatar');
								break;
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
	<fieldset>
		<legend class="fwb"><?=_('Character properties')?></legend>
		<label for="charactername"><?=_('Character name')?>:</label>
		<input type="text" name="charactername" placeholder="<?=_('Character name')?>" required="required" value="<?=$charactername?>" /><br />
		<ul class="avatar">
			<?php foreach($types as &$type) : ?>
			<li>
				<label for="type-<?=$type['id']?>">
					<p><?=$type['name']?></p>
					<?php if(array_key_exists('avatar', $type) && !is_null($type['avatar']['small_avatarpicture_id'])) : ?>
					<img id="avatar" src="<?=$linker->link(array('media','avatar',$seminary['url'],$type['url'],$xplevels[0]['level'],'portrait'))?>" />
					<?php endif ?>
				</label>
				<input id="type-<?=$type['id']?>" name="type" type="radio" value="<?=$type['url']?>" <?php if(array_key_exists('selected', $type) && $type['selected']) : ?>checked="checked"<?php endif ?> />
			</li>
			<?php endforeach ?>
		</ul>
	</fieldset>
	
	<?php if($fieldsValidation !== true) : ?>
	<ul>
		<?php foreach($fieldsValidation as $field => &$settings) : ?>
		<li><?=sprintf(_('The Seminary field “%s” is invalid'), $field)?></li>
		<?php endforeach ?>
	</ul>
	<?php endif ?>
	<fieldset>
		<legend class="fwb"><?=_('Seminary fields')?></legend>
		<?php foreach($fields as &$field) : ?>
		<label for="fields[<?=$field['url']?>]"><?=$field['title']?>:</label>
		<?php switch($field['type_title']) {
			case 'Number':
			case 'Varchar': ?>
				<input type="text" name="fields[<?=$field['url']?>]" pattern="<?=(!empty($field['regex'])) ? substr($field['regex'],1,strrpos($field['regex'],$field['regex'][0])-1) : ''?>" <?php if(array_key_exists('uservalue', $field)) : ?>value="<?=$field['uservalue']?>"<?php endif ?> <?php if($field['required']) : ?>required="required"<?php endif ?>/>
			<?php break;
			case 'Text': ?>
				<textarea name="fields[<?=$field['url']?>]"><?=(array_key_exists('uservalue', $field) ? $field['uservalue'] : null)?></textarea>
			<?php break;
			case 'List': ?>
				<select name="fields[<?=$field['url']?>]">
					<?php foreach(explode('|', substr($field['regex'],1,strrpos($field['regex'],$field['regex'][0])-1)) as $option) : ?>
					<option value="<?=mb_eregi_replace('\\\\','',$option)?>" <?php if(array_key_exists('uservalue', $field) && $field['uservalue'] == mb_eregi_replace('\\\\','',$option)) : ?>selected="selected"<?php endif ?>><?=mb_eregi_replace('\\\\','',$option)?></option>
					<?php endforeach?>
				</select>
			<?php break;
		} ?>
		<br />
		<?php endforeach ?>
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
