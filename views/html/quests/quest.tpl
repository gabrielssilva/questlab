<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','index',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php endif ?>
<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>

<?=$questgroupshierarchypath?>

<h3><?=$quest['title']?></h3>

<?php if(!is_null($queststatustext)) : ?>
<section>
	<?php if($queststatus == 'solved') : ?>
	<h1><?=_('solved')?></h1>
	<?php elseif($queststatus == 'unsolved') : ?>
	<h1><?=_('unsolved')?></h1>
	<?php endif ?>
	<p><?=\hhu\z\Utils::t($queststatustext)?></p>
</section>
<?php endif ?>

<?php if(!is_null($questtext)) : ?>
<section>
	<h1 id="questtext"><?=$questtext['type']?></h1>
	<div id="qtextbox">
		<p class="qtext cf"><?php if(!is_null($media)) : ?><img src="<?=$linker->link(array('media','index',$seminary['url'],$media['url']))?>" /><?php endif ?><?=\hhu\z\Utils::t($questtext['text'])?></p>
	</div>
	
	<ul>
		<?php foreach($questtext['relatedQuestsgroups'] as &$relatedQuestgroup) : ?>
		<li><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$relatedQuestgroup['url']))?>"><?=$relatedQuestgroup['entry_text']?></a></li>
		<?php endforeach ?>
		<?php if(!empty($questtext['abort_text'])) : ?>
		<li><a href="<?=$linker->link(array('quest',$seminary['url'],$questgroup['url'],$relatedquesttext['quest']['url'],$relatedquesttext['type_url'],$relatedquesttext['pos']),1)?>"><?=$questtext['abort_text']?></a></li>
		<?php endif ?>
		<?php if(!empty($questtext['out_text']) && $questtext['pos'] < $questtext['count']) : ?>
		<li><a href="<?=$linker->link(array($questtext['type_url'],$questtext['pos']+1),5,true,null,true,'questtext')?>"><?=$questtext['out_text']?></a></li>
		<?php endif ?>
	</ul>
	
	<?php if(array_key_exists('pos', $questtext)) : ?>
	<?php if($questtext['pos'] > 1) : ?><a href="<?=$linker->link(array($questtext['type_url'],$questtext['pos']-1),5,true,null,true,'questtext')?>">&lt;</a><?php endif ?>
	<?=$questtext['pos']?>/<?=$questtext['count']?>
	<?php if($questtext['pos'] < $questtext['count'] && empty($questtext['out_text'])) : ?><a href="<?=$linker->link(array($questtext['type_url'],$questtext['pos']+1),5,true,null,true,'questtext')?>">&gt;</a><?php endif ?>
	<?php endif ?>
</section>
<?php endif ?>

<?php if(!is_null($task)) : ?>
<section>
	<h1><?=_('Task')?></h1>
	<p><?=\hhu\z\Utils::t($quest['task'])?></p>
	<?=$task?>
</section>
<?php endif ?>

<?php if(!is_null($nextquests) || !is_null($nextquestgroup)) : ?>
<section>
	<p><?=_('Task successfully solved')?> (<a href="<?=$linker->link(null,0,false,array('show-answer'=>'true'))?>"><?=_('Show correct answer')?></a>)</p>
	<h1><?=_('Go on') ?></h1>
	<?php if(count($nextquests) > 0) : ?>
	<ul>
		<?php foreach($nextquests as &$nextquest) : ?>
		<?php if($nextquest['id'] == $relatedquesttext['quest']['id']) : ?>
		<li><?=_('Quest')?>: <a href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url'],$relatedquesttext['type_url'],$relatedquesttext['pos']),3)?>"><?=$nextquest['title']?></a></li>
		<?php else : ?>
		<li><?=_('Quest')?>: <a href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url']),3)?>"><?=$nextquest['title']?></a></li>
		<?php endif ?>
		<?php endforeach ?>
	</ul>
	<?php elseif(!is_null($nextquestgroup)) : ?>
	<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$nextquestgroup['url']))?>"><?=$nextquestgroup['hierarchy']['title_singular']?> <?=$nextquestgroup['hierarchy']['pos']?>: <?=$nextquestgroup['title']?></a>
	<?php else : ?>
	Spiel vorbei
	<?php endif ?>
</section>
<?php endif ?>
