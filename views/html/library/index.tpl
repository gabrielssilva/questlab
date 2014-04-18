<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><i class="fa fa-book fa-fw"></i><?=_('Questtopics')?></h1>
<p>Hier findest du alle Themen aus der Vorlesung "Wissensrepräsentation" und die passenden Quests zum Nachschlagen und Wiederholen. Dein Fortschritt in "Die Legende von Zyren" beeinflusst den Umfang der Bibliothek, spiele also regelmäßig weiter und schalte so Quest für Quest alle Inhalte frei.</p>
<div class="libindxpr cf">
	<p><small>Gesamtfortschritt: 77%</small></p>
	<div class="xpbar">
		<span style="width:77%"></span>
	</div>
</div>
<ul class="libindx cf">
	<?php foreach($questtopics as &$topic) : ?>
	<li class="cf">
		<i class="fa fa-file-o"></i>
		<p class="ltopc"><a href="<?=$linker->link(array('library','topic',$seminary['url'],$topic['url']))?>"><?=$topic['title']?></a></p>
		<p><small>Fortschritt: <?=$topic['characterQuestcount']?> / <?=$topic['questcount']?></small></p>
		<div class="xpbar">
			<span style="width:<?=round($topic['characterQuestcount']/$topic['questcount']*100)?>%"></span>
		</div>
	</li>
	<?php endforeach ?>
</ul>
