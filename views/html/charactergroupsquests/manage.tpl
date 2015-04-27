<?php if(!is_null($seminary['charactergroups_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'charactergroups'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>

<div class="gbanner cf">
	<?php if(!is_null($media)) : ?>
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>" class="grpqimg" />
	<?php else : ?>
	<img src="<?=$linker->link(array('grafics','charactergroup.jpg'))?>" class="gbanner">
	<?php endif ?>
	<h1><?=$quest['title']?></h1>
</div>
<ul class="gdata cf">
	<li><span class="fwb"><?=sprintf(_('%d XPs'), $quest['xps'])?></span></li>
	<li><?php if($questgroup['entered']) : ?><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$questgroup['url']))?>"><?=$questgroup['title']?></a><?php else : ?><?=$questgroup['title']?><?php endif ?></li>
</ul>

<section>
	<h1><i class="fa fa-picture-o fa-fw"></i><?=_('Media')?></h1>
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
	<form class="mng" method="post" enctype="multipart/form-data">
        <ul class="gqgllry mnglst">
            <?php foreach($uploads as &$upload) : ?>
            <li>
                <input type="checkbox" id="upload_<?=$upload['upload']['id']?>" name="uploads[]" value="<?=$upload['upload']['id']?>" />
                <br />
                <label for="upload_<?=$upload['upload']['id']?>">
                    <a href="<?=$linker->link(array('uploads','seminary',$seminary['url'],$upload['upload']['url']))?>">
                        <img src="<?=$linker->link(array('uploads','seminary',$seminary['url'],$upload['upload']['url'],'thumbnail'))?>" />
                    </a>
                <label>
            </li>
            <?php endforeach ?>
        </ul>
        <input type="submit" name="deletemedia" value="<?=_('delete selected')?>" />
    </form>
	<form class="mng" method="post" enctype="multipart/form-data">
		<input type="file" name="media" /><br />
        <p><?=_('Allowed file types')?>: <?php foreach($mimetypes as &$mimetype) : ?><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB) <?php endif ?><?php endforeach ?></p>
		<input type="submit" name="setmedia" value="<?=_('upload')?>" />
	</form>
</section>

<section>
	<h1><i class="fa fa-users fa-fw"></i><?=$groupsgroup['name']?></h1>
	<form method="post">
		<ul class="grpqlist">
			<?php foreach($groups as &$group) : ?>
			<li>
				<span class="group"><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$groupsgroup['url'],$group['url']))?>"><?=$group['name']?></a></span>
				<span class="xp">
					<select name="xps[<?=$group['url']?>]">
						<option value="null" <?php if(is_null($group['quest_group'])) : ?>selected="selected"<?php endif ?>><?=_('Not attended')?></option>
						<?php for($i=0; $i<=$quest['xps']; $i++) : ?>
						<option value="<?=$i?>" <?php if(!is_null($group['quest_group']) && $group['quest_group']['xps'] == $i) : ?>selected="selected"<?php endif ?>><?=sprintf(_('%d XPs'), $i)?></option>
						<?php endfor ?>
					</select>
				</span>
			</li>
			<?php endforeach ?>
		</ul>
		<input type="submit" name="setxps" value="<?=_('Set XPs')?>" />
	</form>
</section>
