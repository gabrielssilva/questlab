<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>

<?=$questgroupshierarchypath?>
<?=$questgroupspicture?>

<h3><?=$quest['title']?></h3>
<?php if(!is_null($media)) : ?>
<img src="<?=$linker->link(array('media','index',$seminary['url'],$media['url']))?>" />
<?php endif ?>
<section>
	<h1><?=$questtext['type']?></h1>
	<p><?=$questtext['text']?></p>
	
	<?php if(!empty($questtext['sidequests'])) : ?>
	<ul>
		<?php foreach($questtext['sidequests'] as &$sidequest) : ?>
		<li><a href="<?=$linker->link(array('sidequest',$seminary['url'],$questgroup['url'],$quest['url'],$sidequest['url']),1)?>"><?=$sidequest['entry_text']?></a></li>
		<?php endforeach ?>
		<?php if(!empty($questtext['out_text'])) : ?>
		<li><a href="<?=$linker->link($questtext['pos']+1, 6)?>"><?=$questtext['out_text']?></a>
		<?php endif ?>
	</ul>	
	<?php endif ?>
	
	<?php if(!empty($questtext['out_text']) && empty($questtext['sidequests'])) : ?>
	<a href="<?=$linker->link($questtext['pos']+1, 6)?>"><?=$questtext['out_text']?></a>
	<?php endif ?>
	
	<?php if($questtext['pos'] > 1) : ?><a href="<?=$linker->link(array($questtext['type_url'],$questtext['pos']-1),5)?>">&lt;</a><?php endif ?>
	<?=$questtext['pos']?>/<?=$questtext['count']?>
	<?php if($questtext['pos'] < $questtext['count'] && empty($questtext['out_text'])) : ?><a href="<?=$linker->link(array($questtext['type_url'],$questtext['pos']+1),5)?>">&gt;</a><?php endif ?>
</section>

<?php if($showtask) : ?>
<section>
	<h1><?=_('Task')?></h1>
	<p><?=$quest['task']?></p>
</section>
<?php endif ?>
