<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>

<?=$questgroupshierarchypath?>
<?=$questgroupspicture?>

<?php if(!is_null($media)) : ?>
<img src="<?=$linker->link(array('media','index',$seminary['url'],$media['url']))?>" />
<?php endif ?>

<h2><?=sprintf(_('Submission of %s'),$character['name'])?></h2>
<section>
	<?=$output?>
</section>
