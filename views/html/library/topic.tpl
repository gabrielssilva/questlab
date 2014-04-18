<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Questtopics')?></a></li>
</ul>
<h1><i class="fa fa-book fa-fw"></i><?=$questtopic['title']?></h1>
<div class="libindxpr cf">
	<p><small>Themenfortschritt: <?=$questtopic['characterQuestcount']?> / <?=$questtopic['questcount']?></small></p>
	<div class="xpbar">
		<span style="width:<?=round($questtopic['characterQuestcount']/$questtopic['questcount']*100)?>%"></span>
	</div>
</div>

<h2>Quests zu diesem Thema:</h2>
<ul class="libtop">
	<?php foreach($quests as &$quest) : ?>
	<li class="cf">
		<p><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$quest['questgroup']['url'],$quest['url']))?>">Die vielen Facetten des Orden des<?=$quest['title']?></a></p>
		<?php foreach($quest['subtopics'] as &$subtopic) : ?>
		<p class="addon"><?=$subtopic['title']?></p>
		<?php endforeach ?>
	</li>
	<?php endforeach ?>
</ul>
