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
		<label for="charactergroupname"><?=_('Name')?>:</label>
		<input type="text" id="charactergroupname" name="charactergroupname" placeholder="<?=_('Name')?>" title="<?=_('Name')?>" required="required" maxlength="<?=$validationSettings['charactergroupname']['maxlength']?>" value="<?=$charactergroupname?>" <?=(array_key_exists('charactergroupname', $validation)) ? 'class="invalid"' : null?> /><br />
		<label for="motto"><?=_('Motto')?>:</label>
		<input type="text" id="motto" name="motto" placeholder="<?=_('Motto')?>" title="<?=_('Motto')?>" maxlength="<?=$validationSettings['motto']['maxlength']?>" value="<?=$motto?>" <?=(array_key_exists('motto', $validation)) ? 'class="invalid"' : null?> /><br />
	</fieldset>
	<input type="submit" name="edit" value="<?=_('edit')?>" />
</form>
