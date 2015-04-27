<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php endif ?>
<?=$questgroupshierarchypath?>

<h1><?=_('Edit Quest texts')?></h1>
<form method="post" enctype="multipart/form-data">
	<?php foreach($questtexttypes as &$type) : ?>
	<fieldset>
		<legend><?=$type['type']?></legend>
		<?php if(array_key_exists($type['url'], $validations)) : ?>
		<ul class="validation">
			<?php foreach($validations[$type['url']] as $textId => &$validation) : ?>
			<?php if($validation !== true) : ?>
				<?php foreach($validation as $field => &$settings) : ?>
				<li>
					<ul>
						<?php foreach($settings as $setting => $value) : ?>
						<li>
							<?php switch($field) {
								case 'media':
									switch($setting) {
										case 'error': printf(_('Error during picture upload: %s'), $value);
										break;
										case 'mimetype': printf(_('Picture has wrong type “%s”'), $value);
										break;
										case 'size': echo _('Picture exceeds size maximum');
										break;
										default: echo _('Picture invalid');
									}
								break;
							} ?>
						</li>
						<?php endforeach ?>
					</ul>
				</li>
				<?php endforeach ?>
			<?php endif ?>
			<?php endforeach ?>
		</ul>
		<?php endif ?>
		<ul class="admnql">
			<?php foreach($type['texts'] as &$text) : ?>
			<li class="cf">
				<?php if(array_key_exists('media', $text)) : ?>
				<a href="<?=$linker->link(array('media','seminary',$seminary['url'],$text['media']['url']))?>"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$text['media']['url']))?>" /></a><br />
				<?php endif ?>
				<input type="file" name="media[<?=$type['url']?>][<?=$text['id']?>]" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" /><br />
				<textarea name="questtexts[<?=$type['url']?>][<?=$text['id']?>]"><?=$text['text']?></textarea><br />
				<input id="deletes[<?=$type['url']?>][<?=$text['id']?>]" type="checkbox" name="deletes[<?=$type['url']?>][<?=$text['id']?>]" />
				<label for="deletes[<?=$type['url']?>][<?=$text['id']?>]"><?=_('delete')?></label>
			</li>
			<?php endforeach ?>
			<li class="cf">
				<input type="file" name="media[<?=$type['url']?>][new]" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" /><br />
				<textarea name="questtexts[<?=$type['url']?>][new]" placeholder="<?=_('New Questgroup text')?>"></textarea>
			</li>
		</ul>
	</fieldset>
	<?php endforeach ?>
	<input type="submit" name="edit" value="<?=_('edit')?>" />
</form>
