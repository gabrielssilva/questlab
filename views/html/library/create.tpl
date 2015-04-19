<?php if(!is_null($seminary['library_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'library'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Library')?></a></li>
</ul>
<h1><i class="fa fa-book fa-fw"></i><?=_('New Questtopic')?></h1>

<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
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
<form method="post">
	<fieldset>
		<label for="title"><?=_('Title')?>:</label>
		<input id="title" type="text" name="title" placeholder="<?=_('Title')?>" title="<?=_('Title')?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=(array_key_exists('title', $validation)) ? 'class="invalid"' : null?> />
	</fieldset>
	<input type="submit" name="create" value="<?=_('create')?>" />
</form>
