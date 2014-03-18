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
<ul class="qg">
	<?php foreach($hierarchy['questgroups'] as &$group) : ?>
	<li>
		<div class="qgtitle">
			<?php if(!array_key_exists('access', $group) || $group['access']) : ?>
			<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$group['url']))?>"><i class="fa fa-square-o fa-fw"></i><?=$group['title']?></a></div>
			<div class="qgprogress cf">
				<div class="xpbar">
					<span style="width:25%"></span>
				</div>
				<p class="xpnumeric">50 / 200 XP</p>
			</div>
			<div class="qghidden">
				<p>Versteckte Questline gefunden:</p>
				<p><a href="#"><i class="fa fa-star-o fa-fw"></i>Hier der Titel der entsprechenden Side-Questline</a></p>
			<?php else : ?>
			<?=$hierarchy['title_singular']?> <?=_('locked')?>
			<?php endif ?>
		</div>
	</li>
	<?php endforeach?>
</ul>
<?php endif ?>
<?php endforeach ?>

<?php if(isset($quests) && !is_null($quests)) : ?>
<h3><?=_('Quests')?></h3>
<ul class="qglist">
	<li>
		<div class="qgtitle">
			<a href="#" class="solved"><i class="fa fa-check-square-o fa-fw"></i>Beispiel für eine gelöste Quest</a>
		</div>
	</li>
	<li>
		<div class="qgtitle">
			<a href="#" class="bonus"><i class="fa fa-share-square-o fa-fw"></i>Beispiel für eine gefunde Side-Questline</a>
		</div>
	</li>
	<?php foreach($quests as &$quest) : ?>
	<li>
		<?php if(!array_key_exists('access', $quest) || $quest['access']) : ?>
		<div class="qgtitle">
			<a href="<?=$linker->link(array('quests','quest',$seminary['url'],$questgroup['url'],$quest['url']))?>"><i class="fa fa-square-o fa-fw"></i><?=$quest['title']?></a>
		</div>
		<?php if(count($quest['sidequests']) > 0) : ?>
		<br />
		<?=_('containing optional Quests')?>:
		<ul>
			<?php foreach($quest['sidequests'] as &$sidequest) : ?>
			<li><?=$sidequest['title']?></li>
			<?php endforeach ?>
		</ul>
		<?php endif ?>
		<?php else : ?>
		<?=_('locked')?>
		<?php endif ?>
	</li>
	<?php endforeach ?>
</ul>
<?php endif ?>
