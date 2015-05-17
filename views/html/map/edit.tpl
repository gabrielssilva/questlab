<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'map'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Map')?></a></li>
</ul>

<h1><i class="fa fa-map-marker fa-fw"></i><?=_('Map')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
	<?php foreach($validation as $field => &$settings) : ?>
	<li>
		<ul>
			<?php foreach($settings as $setting => $value) : ?>
			<li>
				<?php switch($field) {
					case 'media':
						switch($setting) {
							case 'error': printf(_('Error during file upload: %s'), $value);
							break;
							case 'mimetype': printf(_('File has wrong type “%s”'), $value);
							break;
							case 'size': echo _('File exceeds size maximum');
							break;
							default: echo _('File invalid');
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
		<input type="file" name="media" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" />
		<p><?=_('Allowed file types')?>:</p>
		<ul>
			<?php foreach($mimetypes as &$mimetype) : ?>
			<li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
			<?php endforeach ?>
		</ul>
    </fieldset>
	<input type="submit" name="edit" value="<?=_('save')?>" />
</form>
