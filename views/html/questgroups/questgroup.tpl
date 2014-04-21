<?php if(!is_null($picture)) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$picture['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>

<?=$questgroupshierarchypath?>

<?php if(!is_null($questgroup['hierarchy'])) : ?>
<h2><?=$questgroup['hierarchy']['title_singular']?> <?=$questgroup['hierarchy']['questgroup_pos']?>: <?=$questgroup['title']?></h2>
<?php else : ?>
<h2><?=$questgroup['title']?></h2>
<?php endif ?>
<?php foreach($texts as &$text) : ?>
<p><?=\hhu\z\Utils::t($text['text'])?></p>
<?php endforeach ?>

<?php if(!is_null($childquestgroupshierarchy)) : ?>
<?php foreach($childquestgroupshierarchy as &$hierarchy) : ?>
<?php if(count($hierarchy['questgroups']) > 0) : ?>
<h3><?=$hierarchy['title_plural']?></h3>
<ul class="qg">
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li class="cf">
		<span class="qgicon"><i class="fa fa-check-square-o"></i></span>
		<div class="qgtitle"><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><?=$group['title']?></a></div>
		<div class="qgprogress cf">
			<p class="xpinfo">Fortschritt:</p>
			<div class="xpbar">
				<span style="width:<?=round($group['character_xps']/$group['xps']*100)?>%"></span>
			</div>
			<p class="xpnumeric"><?=$group['character_xps']?> / <?=$group['xps']?> XP</p>
		</div>
	</li>
	<?php endforeach?>
</ul>
<?php endif ?>
<?php endforeach ?>
<?php endif ?>

<?php if(isset($quests) && !is_null($quests) && count($quests) > 0) : ?>
<h3><?=_('Quests')?></h3>
<ul class="qglist">
	<?php foreach($quests as &$quest) : ?>
	<li class="qgtitle">
		<a href="<?=$linker->link(array('quests','quest',$seminary['url'],$questgroup['url'],$quest['url']))?>" <?php if($quest['solved']) : ?>class="solved"<?php endif ?>><i class="fa <?=($quest['solved']) ? 'fa-check-square-o' : 'fa-share-square-o'?> fa-fw"></i><?=$quest['title']?></a>
	</li>
	<?php if(count($quest['relatedQuestgroups']) > 0) : ?>
		<?php foreach($quest['relatedQuestgroups'] as &$relatedQuestgroup) : ?>
		<li class="qgtitle">
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$relatedQuestgroup['url']))?>" class="bonus"><i class="fa fa-share-square-o fa-fw"><?=$relatedQuestgroup['title']?></i></a>
		</li>
		<?php endforeach ?>
	<?php endif ?>
	<?php endforeach ?>
</ul>
<?php endif ?>
