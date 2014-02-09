<h1><?=_('Seminaries')?></h2>
<h2><?=$seminary['title']?></h3>

<?=$questgroupshierarchypath?>

<h3><?=$questgroupshierarchy['title_singular']?> <?=$questgroup['pos']?>: <?=$questgroup['title']?></h3>
<?php foreach($texts as &$text) : ?>
<p><?=$text['text']?></p>
<?php endforeach ?>

<?php foreach($childquestgroupshierarchy as &$hierarchy) : ?>
<?php if(count($hierarchy['questgroups']) > 0) : ?>
<h3><?=$hierarchy['title_plural']?></h3>
<ul>
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li><?=$hierarchy['title_singular']?> <?=$group['pos']?>: <a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></li>
	<?php endforeach?>
</ul>
<?php endif ?>
<?php endforeach ?>

<?php if(isset($quests) && !is_null($quests)) : ?>
<h3>Quests</h3>
<ul>
	<?php foreach($quests as &$quest) : ?>
	<li><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$questgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></li>
	<?php endforeach ?>
</ul>
<?php endif ?>
