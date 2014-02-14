<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>

<?=$questgroupshierarchypath?>
<?=$questgroupspicture?>

<h3><a href="<?=$linker->link(array('quest',$seminary['url'],$questgroup['url'],$quest['url'],$questtext['type_url'],$questtext['pos']),1)?>"><?=$quest['title']?></a></h3>
<h4><?=$sidequest['title']?></h4>
<p><?=_('This Quest is optional')?>.</p>
<?php if(!is_null($media)) : ?>
<img src="<?=$linker->link(array('media','index',$seminary['url'],$media['url']))?>" />
<?php endif ?>
<section>
	<h1><?=$sidequesttext['type']?></h1>
	<p><?=$sidequesttext['text']?></p>
	
	<?php if($sidequesttext['pos'] > 1) : ?><a href="<?=$linker->link(array($sidequesttext['type_url'],$sidequesttext['pos']-1),6)?>">&lt;</a><?php endif ?>
	<?=$sidequesttext['pos']?>/<?=$sidequesttext['count']?>
	<?php if($sidequesttext['pos'] < $sidequesttext['count'] && empty($sidequesttext['out_text'])) : ?><a href="<?=$linker->link(array($sidequesttext['type_url'],$sidequesttext['pos']+1),6)?>">&gt;</a><?php endif ?>
</section>

<?php if($showtask) : ?>
<section>
	<h1><?=_('Task')?></h1>
	<p><?=$sidequest['task']?></p>
</section>
<?php endif ?>
