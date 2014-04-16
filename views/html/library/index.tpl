<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><?=_('Questtopics')?></h2>

<ul>
	<?php foreach($questtopics as &$topic) : ?>
	<li>
		<h3><a href="<?=$linker->link(array('library','topic',$seminary['url'],$topic['url']))?>"><?=$topic['title']?></a></h3>
		<div class="cf">
			<div class="xpbar">
				<span style="width:<?=round($topic['characterQuestcount']/$topic['questcount']*100)?>%"></span>
			</div>
			<p class="xpnumeric"><?=$topic['characterQuestcount']?>/<?=$topic['questcount']?></p>
		</div>
	</li>
	<?php endforeach ?>
</ul>
