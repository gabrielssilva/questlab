<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><i class="fa fa-trophy fa-fw"></i><?=_('Achievements')?></h1>
<p><?=_('Achievement description')?></p>
<div class="cf">
	<section class="rare">
		<h2><?=_('Seldom Achievements')?></h2>
		<ol>
			<?php foreach($seldomAchievements as &$achievement) : ?>
			<li class="cf">
				<?php if($achievement['achieved'] !== false) : ?>
				<?php if(!is_null($achievement['achieved_achievementsmedia_id'])) : ?>
				<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url']))?>" />
				<?php endif ?>
				<?php else : ?>
				<?php if(!is_null($achievement['unachieved_achievementsmedia_id'])) : ?>
				<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url']))?>" />
				<?php endif ?>
				<?php endif ?>
				<p class="fwb"><?=$achievement['title']?></p>
				<p><small><?=sprintf(_('Achievement has been achieved only %d times'), $achievement['c'])?></small></p>
			</li>
			<?php endforeach ?>
		</ol>
	</section>
	<section class="rare hunter">
		<h2><?=_('Most successful collectors')?></h2>
		<ol>
			<?php foreach($successfulCharacters as $successfulCharacter) : ?>
			<li class="cf">
				<img src="<?=$linker->link(array('media','avatar',$seminary['url'],$successfulCharacter['charactertype_url'],$successfulCharacter['xplevel'],'portrait'))?>" />
				<p class="fwb"><?=$successfulCharacter['name']?></p>
				<p><small><?=sprintf(_('Character has achieved %d Achievements'), $successfulCharacter['c'])?></small></p>
			</li>
			<?php endforeach ?>
		</ol>
	</section>
</div>
<h2><?=_('Personal Achievements')?></h2>
<div class="libindxpr cf">
	<p><small><?=sprintf(_('Own progress: %d %%'), round(count($achievedAchievements) / (count($achievedAchievements)+count($unachievedAchievements)) * 100))?></small></p>
	<div class="xpbar">
		<span style="width:<?=round(count($achievedAchievements) / (count($achievedAchievements)+count($unachievedAchievements)) * 100)?>%"></span>
	</div>
</div>
<p><small><b><?=$character['rank']?>. <?=_('Rank')?>:</b> <?=sprintf(_('You achieved %d of %d Achievements so far'), count($achievedAchievements), count($achievedAchievements)+count($unachievedAchievements))?>.</small></p>
<ul class="achmnts">
	<?php foreach($achievedAchievements as &$achievement) : ?>
	<li class="cf">
		<?php if(!is_null($achievement['achieved_achievementsmedia_id'])) : ?>
		<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url']))?>" />
		<?php endif ?>
		<h3 id="<?=$achievement['url']?>"><?=$achievement['title']?><span class="unlcked"><?=sprintf(_('achieved at: %s'), $dateFormatter->format(new \DateTime($achievement['created'])))?></span></h3>
		<p class="desc"><?=\hhu\z\Utils::t($achievement['description'])?></p>
	</li>
	<?php endforeach?>
	<?php foreach($unachievedAchievements as &$achievement) : ?>
	<li class="cf">
		<?php if(!is_null($achievement['unachieved_achievementsmedia_id'])) : ?>
		<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url'],'locked'))?>" />
		<?php endif ?>
		<h3 id="<?=$achievement['url']?>"><?=(!$achievement['hidden']) ? $achievement['title'] : _('Secret Achievement')?></h3>
		<?php if(!$achievement['hidden']) : ?>
		<p class="desc"><?=\hhu\z\Utils::t($achievement['description'])?></p>
		<?php else : ?>
		<p class="desc"><?=_('Continue playing to unlock this secret Achievement')?></p>
		<?php endif ?>
		<?php if(array_key_exists('characterProgress', $achievement)) : ?>
		<div class="prgrss cf">
			<div class="xpbar">
				<span style="width:<?=round($achievement['characterProgress']*100)?>%"></span>
			</div>
			<p class="xpnumeric"><?=round($achievement['characterProgress']*100)?>%</p>
		</div>
		<?php endif ?>
	</li>
	<?php endforeach?>
</ul>
