<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>

<?=$questgroupshierarchypath?>
<?=$questgroupspicture?>

<h3><?=$questgroupshierarchy['title_singular']?> <?=$questgroup['pos']?>: <?=$questgroup['title']?></h3>
<?php foreach($texts as &$text) : ?>
<p><?=\hhu\z\Utils::t($text['text'])?></p>
<?php endforeach ?>

<?php foreach($childquestgroupshierarchy as &$hierarchy) : ?>
<?php if(count($hierarchy['questgroups']) > 0) : ?>
<h3><?=$hierarchy['title_plural']?></h3>
<ul>
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li>
		<?=$hierarchy['title_singular']?> <?=$group['pos']?>:
		<?php if(!array_key_exists('access', $group) || $group['access']) : ?>
		<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a>
		<?php else : ?>
		<?=_('locked')?>
		<?php endif ?>
	</li>
	<?php endforeach?>
</ul>
<?php endif ?>
<?php endforeach ?>

<?php if(isset($quests) && !is_null($quests)) : ?>
<h3><?=_('Quests')?></h3>
<ul>
	<?php foreach($quests as &$quest) : ?>
	<li>
		<?php if(!array_key_exists('access', $quest) || $quest['access']) : ?>
		<a href="<?=$linker->link(array('quests','quest',$seminary['url'],$questgroup['url'],$quest['url']))?>"><?=$quest['title']?></a>
		<br />
		<?=_('containing optional Quests')?>:
		<?php if(count($quest['sidequests']) > 0) : ?>
		<ul>
			<?php foreach($quest['sidequests'] as &$sidequest) : ?>
			<li><?=$sidequest['title']?></li>
			<?php endforeach ?>
		</ul>
		<?php endif ?>
		<?php else : ?>
		<?=_('Locked')?>
		<?php endif ?>
	</li>
	<?php endforeach ?>
</ul>
<?php endif ?>
