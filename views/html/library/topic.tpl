<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Questtopics')?></a></h2>
<h3><?=$questtopic['title']?></h3>

<div class="cf">
	<div class="xpbar">
		<span style="width:<?=round($questtopic['characterQuestcount']/$questtopic['questcount']*100)?>%"></span>
	</div>
	<p class="xpnumeric"><?=$questtopic['characterQuestcount']?>/<?=$questtopic['questcount']?></p>
</div>

<ul>
	<?php foreach($quests as &$quest) : ?>
	<li>
		<a href="<?=$linker->link(array('quests','quest',$seminary['url'],$quest['questgroup']['url'],$quest['url']))?>"><?=$quest['title']?></a>
		<ul>
			<?php foreach($quest['subtopics'] as &$subtopic) : ?>
			<li><?=$subtopic['title']?></li>
			<?php endforeach ?>
		</ul>
	</li>
	<?php endforeach ?>
</ul>
