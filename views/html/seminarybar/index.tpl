<section class="cf">
	<h1><?=$character['name']?></h1>
	<img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level']))?>" class="char">
	<ul class="charstats">
		<li><i class="fa fa-caret-right fa-fw"></i><?=('Level')?> <?=$character['xplevel']['level']?></li>
		<li><i class="fa fa-caret-right fa-fw"></i><?=$character['xps']?> XPs</li>
		<li><i class="fa fa-caret-right fa-fw"></i><?=$character['rank']?>. <?=_('Rank')?></li>
		<li><i class="fa fa-caret-right fa-fw"></i><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>">Zum Profil</a></li>
	</ul>
</section>

<?php if(!is_null($lastQuest)) : ?>
<section>
	<h1><?=_('Last Quest')?></h1>
	<p><i class="fa fa-pencil-square-o fa-fw"></i><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$lastQuest['questgroup']['url'],$lastQuest['url']))?>"><?=$lastQuest['title']?></a></p>
</section>
<?php endif ?>

<?php if(!is_null($lastAchievement)) : ?>
<section>
	<h1><?=('Last Achievement')?></h1>
	<ul class="cranks">
		<li>
			<?php if(!is_null($lastAchievement['achieved_achievementsmedia_id'])) : ?>
			<a href="<?=$linker->link(array('achievements','index',$seminary['url']),0,true,null,true,$lastAchievement['url'])?>" title="Achievement-Titel"><img src="<?=$linker->link(array('media','achievement',$seminary['url'],$lastAchievement['url']))?>"></a>
			<?php endif ?>
			<p><a href="<?=$linker->link(array('achievements','index',$seminary['url']),0,true,null,true,$lastAchievement['url'])?>"><?=$lastAchievement['title']?></a></p>
			<p><small><?=sprintf(_('achieved at: %s'), $dateFormatter->format(new \DateTime($lastAchievement['created'])))?></small></p>
		</li>
	</ul>
</section>
<?php endif ?>

<section>
	<?php foreach($characterGroups as &$group) : ?>
	<h1><?=$group['name']?></h1>
	<ul class="cranks">
		<?php foreach($group['members'] as &$member) : ?>
		<li>
			<a href="#" title="Achievement-Titel"><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$member['charactertype_url'],$member['xplevel'],'portrait'))?>"></a>
			<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$member['url']))?>"><?=$member['name']?></a></p>
			<p><small><?=_('Level')?> <?=$member['xplevel']?> (<?=$member['xps']?> XPs)</small></p>
		</li>
		<?php endforeach ?>
	</ul>
	<p><i class="fa fa-users fa-fw"></i><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$group['charactergroupsgroup_url'],$group['url']))?>"><?=sprintf(_('Show %s-Profile'),$group['charactergroupsgroup_name'])?></a></p>
	<?php endforeach ?>
</section>
