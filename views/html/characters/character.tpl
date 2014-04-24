<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><i class="fa fa-user fa-fw"></i><?=$character['name']?></h1>
<section class="cf">
	<div class="cinfo">
		<div class="cdata">
			<div class="xpbar">
				<span style="width:<?=round($character['quest_xps']*100/$seminary['achievable_xps'])?>%"></span>
			</div>
			<p><small><?=_('Total progress')?>: <?=round($character['quest_xps']*100/$seminary['achievable_xps'])?> %</small></p>
		</div>
		<div class="cdata square">
			<p class="value"><?=$character['xplevel']['level']?></p>
			<p><small><?=_('Level')?></small></p>
		</div>
		<div class="cdata square">
			<p class="value"><?=$character['xps']?></p>
			<p><small>XP</small></p>
		</div>
		<div class="cdata square blue">
			<p class="value"><?=$character['rank']?>.</p>
			<p><small><?=_('Rank')?></small></p>
		</div>
		<h2><i class="fa fa-bookmark fa-fw"></i><?=_('Milestones')?></h2>
		<ul class="crewards">
			<?php foreach($milestones as &$milestone) : ?>
			<li>
				<?php if($milestone['achieved']) : ?>
				<p class="unlocked fwb"><i class="fa fa-check-circle fa-fw"></i><?=$milestone['title']?></p>
				<?php elseif($milestone['deadline'] < date('Y-m-d H:i:s')) : ?>
				<i class="fa fa-times-circle fa-fw"></i><?=$milestone['title']?></p>
				<?php else : ?>
				<p class="fwb"><i class="fa fa-lock fa-fw"></i><?=$milestone['title']?></p>
				<?php endif ?>
				<p><?=\hhu\z\Utils::t($milestone['description'])?></p>
			</li>
			<?php endforeach ?>
		</ul>
	</div>
	<div class="cportrait">
		<img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level']))?>" />
	</div>
</section>

<div class="cf">
	<section class="fll48">
		<h2><i class="fa fa-users fa-fw"></i><?=_('Character Groups')?></h2>
		<ul class="cgroups cf">
			<?php foreach($groups as &$group) : ?>
			<li class="cf">
				<img src="http://s1.directupload.net/images/140325/3eqybn4i.png">
				<a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$group['charactergroupsgroup_url'],$group['url']))?>"><?=$group['name']?></a><p><span><?=$group['xps']?> XPs</span></p>
			</li>
			<?php endforeach ?>
		</ul>
	</section>
	<section class="flr48">
		<h2><i class="fa fa-list fa-fw"></i><?=_('Ranking')?></h2>
		<ul class="cranks">
			<?php foreach($ranking['superior'] as $index => &$rankCharacter) : ?>
			<li>
				<a href="#" title="Achievement-Titel"><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$rankCharacter['charactertype_url'],$rankCharacter['xplevel'],'portrait'))?>"></a>
				<p><?=$character['rank']-count($ranking['superior'])+$index?>. <a href="#"><?=$rankCharacter['name']?></a></p>
				<p><small><?=_('Level')?> <?=$rankCharacter['xplevel']?> (<?=$rankCharacter['xps']?> XPs)</small></p>
			</li>
			<?php endforeach ?>
			<li>
				<a href="#" title="Achievement-Titel"><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level'],'portrait'))?>"></a>
				<p class="fwb"><?=$character['rank']?>. <a href="#"><?=$character['name']?></a></p>
				<p><small><?=_('Level')?> <?=$character['xplevel']['level']?> (<?=$character['xps']?> XPs)</small></p>
			</li>
			<?php foreach($ranking['inferior'] as $index => &$rankCharacter) : ?>
			<li>
				<a href="#" title="Achievement-Titel"><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$rankCharacter['charactertype_url'],$rankCharacter['xplevel'],'portrait'))?>"></a>
				<p><?=$character['rank']+$index+1?>. <a href="#"><?=$rankCharacter['name']?></a></p>
				<p><small><?=_('Level')?> <?=$rankCharacter['xplevel']?> (<?=$rankCharacter['xps']?> XPs)</small></p>
			</li>
			<?php endforeach ?>
		</ul>
	</section>
</div>

<section>
	<h2><i class="fa fa-book fa-fw"></i><?=_('Topic progress')?></h2>
	<ul class="ctopics cf">
		<?php foreach($questtopics as &$topic) : ?>
		<li>
			<p><small><a href="<?=$linker->link(array('library','topic',$seminary['url'],$topic['url']))?>"><?=$topic['title']?></a> (<?=$topic['characterQuestcount']?>/<?=$topic['questcount']?>)</small></p>
			<div class="xpbar">
				<span style="width:<?=round($topic['characterQuestcount']/$topic['questcount']*100)?>%"></span>
			</div>
		</li>
		<?php endforeach ?>
	</ul>
</section>


<?php if(!is_null($lastQuest)) : ?>
<section>
	<h2><?=_('Last Quest')?></h2>
	<p><i class="fa fa-pencil-square-o fa-fw"></i><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$lastQuest['questgroup']['url'],$lastQuest['url']))?>"><?=$lastQuest['title']?></a></p>
</section>
<?php endif ?>

