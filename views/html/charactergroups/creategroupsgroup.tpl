<?=$moodpic?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
</ul>

<h1><?=_('New Character groups-group')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
					case 'charactergroupsgroupname':
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
					default:
						echo $exception->getMessage();
					break;
				} ?>
			</li>
			<?php endforeach ?>
		</ul>
	</li>
	<?php endforeach ?>
</ul>
<?php endif ?>
<form method="post" action="" class="logreg">
	<fieldset>
		<label for="charactergroupsgroupname"><?=_('Name')?>:</label>
		<input type="text" name="charactergroupsgroupname" placeholder="<?=_('Name')?>" title="<?=_('Name')?>" required="required" maxlength="<?=$validationSettings['charactergroupsgroupname']['maxlength']?>" value="<?=$charactergroupsgroupname?>" <?=(array_key_exists('charactergroupsgroupname', $validation)) ? 'class="invalid"' : null?> /><br />
		<div class="inlbl"><input type="checkbox" id="preferred" name="preferred" <?php if($preferred) : ?>checked="checked"<?php endif ?> /><label for="preferred"><?=_('preferred')?></label></div>
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
