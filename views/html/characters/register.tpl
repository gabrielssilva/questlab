<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<h1><?=$seminary['title']?></h1>
<h2><?=_('Create Character')?></h2>

<form method="post" action="">
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
								default: echo _('Character name invalid');
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
		<legend><?=_('Character properties')?></legend>
		<label for="charactername"><?=_('Character name')?>:</label>
		<input type="text" name="charactername" placeholder="<?=_('Character name')?>" required="required" value="<?=$charactername?>" /><br />
		<label for="type"><?=_('Character type')?>:</label>
		<select name="type" required="required">
			<?php foreach($types as &$type) : ?>
			<option value="<?=$type['url']?>" <?php if(array_key_exists('selected', $type) && $type['selected']) : ?>selected="selected"<?php endif ?>><?=$type['name']?></option>
			<?php endforeach ?>
		</select>
	</fieldset>
	
	<?php if($fieldsValidation !== true) : ?>
	<ul>
		<?php foreach($fieldsValidation as $field => &$settings) : ?>
		<li><?=sprintf(_('The Seminary field “%s” is invalid'), $field)?></li>
		<?php endforeach ?>
	</ul>
	<?php endif ?>
	<fieldset>
		<legend><?=_('Seminary fields')?></legend>
		<?php foreach($fields as &$field) : ?>
		<label for="fields[<?=$field['url']?>]"><?=$field['title']?>:</label>
		<?php switch($field['type_title']) {
			case 'Number':
			case 'Varchar': ?>
				<input type="text" name="fields[<?=$field['url']?>]" pattern="<?=(!empty($field['regex'])) ? substr($field['regex'],1,strrpos($field['regex'],$field['regex'][0])-1) : ''?>" <?php if($field['required']) : ?>required="required"<?php endif ?>/>
			<?php break;
			case 'Text': ?>
				<textarea name="fields[<?=$field['url']?>]"></textarea>
			<?php break;
			case 'List': ?>
				<select name="fields[<?=$field['url']?>]">
					<?php foreach(explode('|', substr($field['regex'],1,strrpos($field['regex'],$field['regex'][0])-1)) as $option) : ?>
					<option value="<?=mb_eregi_replace('\\\\','',$option)?>"><?=mb_eregi_replace('\\\\','',$option)?></option>
					<?php endforeach?>
				</select>
			<?php break;
		} ?>
		<br />
		<?php endforeach ?>
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
