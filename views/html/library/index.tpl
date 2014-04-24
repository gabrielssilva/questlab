<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><i class="fa fa-book fa-fw"></i><?=_('Questtopics')?></h1>
<p><?=sprintf(_('Library description, %s, %s'), $seminary['course'], $seminary['title'])?></p>
<div class="libindxpr cf">
	<p><small><?=sprintf(_('Total progress: %d %%'), ($totalQuestcount > 0) ? $numberFormatter->format(round($totalCharacterQuestcount/$totalQuestcount*100)) : 0) ?></small></p>
	<div class="xpbar">
		<span style="width:<?=($totalQuestcount > 0) ? round($totalCharacterQuestcount/$totalQuestcount*100) : 0 ?>%"></span>
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
