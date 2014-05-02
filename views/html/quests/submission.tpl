<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php endif ?>
<?=$questgroupshierarchypath?>
<h1><?=$quest['title']?></h1>

<h3><?=sprintf(_('Submission of %s'),$character['name'])?></h3>
<section>
	<?=$output?>
</section>
