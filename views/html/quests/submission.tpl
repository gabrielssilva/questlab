<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<?=$questgroupshierarchypath?>
<h2><?=$quest['title']?></h2>

<?php if(!is_null($media)) : ?>
<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>" />
<?php endif ?>

<h2><?=sprintf(_('Submission of %s'),$character['name'])?></h2>
<section>
	<?=$output?>
</section>
