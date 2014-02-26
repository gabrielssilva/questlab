<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>

<?=$questgroupshierarchypath?>
<?=$questgroupspicture?>

<h3><?=$quest['title']?></h3>
<?php if(!is_null($media)) : ?>
<img src="<?=$linker->link(array('media','index',$seminary['url'],$media['url']))?>" />
<?php endif ?>
<section>
	<?php if($questtext['type'] == 'solved') : ?>
	<h1><?=_('solved')?></h1>
	<?php elseif($questtext['type'] == 'unsolved') : ?>
	<h1><?=_('unsolved')?></h1>
	<?php else : ?>
	<h1><?=$questtext['type']?></h1>
	<?php endif ?>
	<p><?=\hhu\z\Utils::t($questtext['text'])?></p>
	
	<?php if(array_key_exists('sidequests', $questtext) && !empty($questtext['sidequests'])) : ?>
	<ul>
		<?php foreach($questtext['sidequests'] as &$sidequest) : ?>
		<li><a href="<?=$linker->link(array('sidequest',$seminary['url'],$questgroup['url'],$quest['url'],$sidequest['url']),1)?>"><?=$sidequest['entry_text']?></a></li>
		<?php endforeach ?>
		<?php if(!empty($questtext['out_text'])) : ?>
		<li><a href="<?=$linker->link($questtext['pos']+1, 6)?>"><?=$questtext['out_text']?></a></li>
		<?php endif ?>
	</ul>	
	<?php endif ?>
	
	<?php if(array_key_exists('out_text', $questtext) && !empty($questtext['out_text']) && array_key_exists('sidequests', $questtext) && empty($questtext['sidequests'])) : ?>
	<a href="<?=$linker->link($questtext['pos']+1, 6)?>"><?=$questtext['out_text']?></a>
	<?php endif ?>
	
	<?php if(array_key_exists('pos', $questtext)) : ?>
	<?php if($questtext['pos'] > 1) : ?><a href="<?=$linker->link(array($questtext['type_url'],$questtext['pos']-1),5)?>">&lt;</a><?php endif ?>
	<?=$questtext['pos']?>/<?=$questtext['count']?>
	<?php if($questtext['pos'] < $questtext['count'] && empty($questtext['out_text'])) : ?><a href="<?=$linker->link(array($questtext['type_url'],$questtext['pos']+1),5)?>">&gt;</a><?php endif ?>
	<?php endif ?>
</section>

<?php if(!is_null($task)) : ?>
<section>
	<h1><?=_('Task')?></h1>
	<p><?=\hhu\z\Utils::t($quest['task'])?></p>
	<p><?=$task?></p>
</section>
<?php endif ?>
