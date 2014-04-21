<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Characters')?></a></h2>
<h3><i class="fa fa-user fa-fw"></i><?=$character['name']?></h3>

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

		<h1><i class="fa fa-trophy fa-fw"></i><?=_('Achievements')?></h1>
		<ul class="cranks">
			<?php foreach($achievements as &$achievement) : ?>
			<li>
				<?php if(!is_null($achievement['achieved_achievementsmedia_id'])) : ?>
				<a href="<?=$linker->link(array('achievements','index',$seminary['url']),0,true,null,true,$achievement['url'])?>" title="Achievement-Titel"><img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url']))?>"></a>
				<?php endif ?>
				<p><a href="<?=$linker->link(array('achievements','index',$seminary['url']),0,true,null,true,$achievement['url'])?>"><?=$achievement['title']?></a></p>
				<p><small><?=sprintf(_('achieved at: %s'), $dateFormatter->format(new \DateTime($achievement['created'])))?></small></p>
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
		<h1><i class="fa fa-users fa-fw"></i><?=_('Character Groups')?></h1>
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
		<h1><i class="fa fa-list fa-fw"></i><?=_('Ranking')?></h1>
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
	<h1><i class="fa fa-book fa-fw"></i><?=_('Topic progress')?></h1>
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

