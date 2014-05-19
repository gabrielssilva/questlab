<?php if(!is_null($seminary['library_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'library'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><i class="fa fa-book fa-fw"></i><?=_('Library')?></h1>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('create',$seminary['url']),1)?>"><?=_('Create new Questtopic')?></a></li>
</nav>
<?php endif ?>
<p><?=sprintf(_('Library description, %s, %s'), $seminary['course'], $seminary['title'])?></p>
<div class="libindxpr cf">
	<p><small><?=sprintf(_('Total progress: %d %%'), ($totalQuestcount > 0) ? round($totalCharacterQuestcount/$totalQuestcount*100) : 0) ?></small></p>
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
