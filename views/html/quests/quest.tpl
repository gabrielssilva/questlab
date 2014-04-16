<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<?=$questgroupshierarchypath?>
<h2><?=$quest['title']?></h2>

<?php if(count($questtexts) > 0) : ?>
<section>
	<h1 id="questtext"><?=$questtexttype['type']?></h1>
	
	
	
	<div id="qtextbox">
		<?php foreach($questtexts as &$questtext) : ?>
		<p class="qtext cf">
			<?php if(array_key_exists('media', $questtext)) : ?><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questtext['media']['url']))?>" /><?php endif ?>
			<?=\hhu\z\Utils::t($questtext['text'])?>
		</p>
		<?php if(count($questtext['relatedQuestsgroups']) > 0 || !empty($questtext['abort_text'])) : ?>
		<ul>
			<?php foreach($questtext['relatedQuestsgroups'] as &$relatedQuestgroup) : ?>
			<li><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$relatedQuestgroup['url']))?>"><?=$relatedQuestgroup['entry_text']?></a></li>
			<?php endforeach ?>
			<?php if(!empty($questtext['abort_text'])) : ?>
			<li><a href="<?=$linker->link(array('quest',$seminary['url'],$relatedquesttext['quest']['questgroup_url'],$relatedquesttext['quest']['url'],$relatedquesttext['type_url']),1)?>"><?=$questtext['abort_text']?></a></li>
			<?php endif ?>
		</ul>
		<?php endif ?>
		<?php endforeach ?>
	</div>
</section>
<?php endif ?>

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

<?php if($questtexttype['type'] == 'Prolog') : ?>
<section>
	<?php if(!is_null($task)) : ?>
	<h1 id="task"><?=_('Task')?></h1>
	<p><?=\hhu\z\Utils::t($quest['task'])?></p>
	<?=$task?>
	<?php endif ?>
	
	<?php if($solved && !is_null($task)) : ?>
	<p><?=_('Task already successfully solved')?>:</p>
	<?php endif ?>
	<ul>
		<?php if(!is_null($task)) : ?><li><a href="<?=$linker->link(null,0,false,array('show-answer'=>'true'),true,'task')?>"><?=_('Show answer')?></a></li><?php endif ?>
		<li><a href="<?=$linker->link('Epilog',5)?>">Aufgabe Überspringen</a></l>
	</ul>
</section>
<?php endif ?>

<?php if(!is_null($nextquests) || !is_null($nextquestgroup)) : ?>
<section>
	<?php if(count($nextquests) > 0) : ?>
	<ul>
		<?php foreach($nextquests as &$nextquest) : ?>
		<?php if($nextquest['id'] == $relatedquesttext['quest']['id']) : ?>
		<li>
			<?=_('Quest')?>:
			<?php if($nextquest['entered'] || !$charactedHasChoosenNextQuest) : ?>
			<a href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url'],$relatedquesttext['type_url']),3)?>"><?=$nextquest['title']?></a>
			<?php else : ?>
			<?=$nextquest['title']?>
			<?php endif ?>
		</li>
		<?php else : ?>
		<li>
			<?=_('Quest')?>:
			<?php if($nextquest['entered'] || !$charactedHasChoosenNextQuest) : ?>
			<a href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url']),3)?>"><?=$nextquest['title']?></a>
			<?php else : ?>
			<?=$nextquest['title']?>
			<?php endif ?>
		</li>
		<?php endif ?>
		<?php endforeach ?>
	</ul>
	<?php elseif(!is_null($nextquestgroup)) : ?>
	<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$nextquestgroup['url']))?>"><?=$nextquestgroup['hierarchy']['title_singular']?> <?=$nextquestgroup['hierarchy']['questgroup_pos']?>: <?=$nextquestgroup['title']?></a>
	<?php else : ?>
	Spiel vorbei
	<?php endif ?>
</section>
<?php endif ?>
