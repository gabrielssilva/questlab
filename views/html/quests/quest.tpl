<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>

<?=$questgroupshierarchypath?>

<h3><?=$quest['title']?></h3>
<section>
	<p><?=$questtext['text']?></p>
	<?php if(!empty($questtext['out_text'])) : ?>
	<a href=""><?=$questtext['out_text']?></a>
	<?php endif ?>
</section>

<?php if($showtask) : ?>
<section>
	<p><?=$quest['task']?></p>
</section>
<?php endif ?>
