<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php endif ?>
<?=$questgroupshierarchypath?>
<h1><?=$quest['title']?></h1>

<?php if(array_key_exists('Prolog', $questtexts) && count($questtexts['Prolog']) > 0) : ?>
<section>
	<h1 id="questtext"><?=_('Prolog')?></h1>
	<div class="qtextbox">
		<?php $mediaShown = false; ?>
		<?php foreach($questtexts['Prolog'] as &$questtext) : ?>
		<p class="qtext cf">
			<?php if(array_key_exists('media', $questtext)) : ?>
			<a href="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questtext['media']['url']))?>" /></a>
			<?php elseif(!is_null($media) && !$mediaShown) : ?>
			<?php $mediaShown = true; ?>
			<a href="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>" /></a>
			<?php endif ?>
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

<?php if(!is_null($task)) : ?>
<section class="task">
	<h1 id="task"><?=_('Task')?></h1>
	<?php if(!is_null($queststatus)) : ?>
	<?php if($queststatus == 'solved') : ?>
	<div class="success">
		<p class="fwb"><i class="fa fa-check-circle fa-fw"></i><?=_('solved')?></p>
		<p><small><?=_('Quest completed.')?> <?php if($quest['xps'] > 0): ?><?=sprintf(_('You have earned %d XPs.'), $quest['xps'])?><?php endif ?></small></p>
	</div>
	<?php elseif($queststatus == 'unsolved') : ?>
	<div class="error">
		<p class="fwb"><i class="fa fa-times-circle fa-fw"></i><?=_('unsolved')?></p>
		<p><small><?=\hhu\z\Utils::t($quest['wrong_text'])?></small></p>
	</div>
	<?php endif ?>
	<?php endif ?>
	
	<?php if($queststatus != 'solved') : ?>
	<p><?=$t->t($quest['task'])?></p>
	<?=$task?>
	
	<?php if($solved && empty($queststatus)) : ?>
	<div class="solvdmsg">
		<p><?=_('Task already successfully solved')?>:
		<nav class="admin">
			<li><a href="<?=$linker->link(null,0,false,array('show-answer'=>'true'),true,'task')?>"><?=_('Show answer')?></a></li>
		</nav>
	</div>
	<?php endif ?>
	<?php endif ?>
</section>
<?php endif ?>

<?php if(array_key_exists('Epilog', $questtexts) && count($questtexts['Epilog']) > 0) : ?>
<section>
	<h1 id="questtext"><?=_('Epilog')?></h1>
	<div class="qtextbox">
		<?php foreach($questtexts['Epilog'] as &$questtext) : ?>
		<p class="qtext cf">
			<?php if(array_key_exists('media', $questtext)) : ?>
			<a href="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questtext['media']['url']))?>" /></a>
			<?php endif ?>
			<?=\hhu\z\Utils::t($questtext['text'])?>
		</p>
		<?php if(count($questtext['relatedQuestsgroups']) > 0 || !empty($questtext['abort_text'])) : ?>
		<ul>
			<?php foreach($questtext['relatedQuestsgroups'] as &$relatedQuestgroup) : ?>
			<li><p><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$relatedQuestgroup['url']))?>"><?=$relatedQuestgroup['entry_text']?></a></p></li>
			<?php endforeach ?>
			<?php if(!empty($questtext['abort_text'])) : ?>
			<li><p><a href="<?=$linker->link(array('quest',$seminary['url'],$relatedquesttext['quest']['questgroup_url'],$relatedquesttext['quest']['url'],$relatedquesttext['type_url']),1)?>"><?=$questtext['abort_text']?></a></p></li>
			<?php endif ?>
		</ul>
		<?php endif ?>
		<?php endforeach ?>
	</div>
</section>
<?php endif ?>

<?php if(!is_null($nextquests) || !is_null($nextquestgroup)) : ?>
<section>
	<h1><?=_('Continuation')?></h1>
	<?php if(count($nextquests) > 0) : ?>
	<ul>
		<?php foreach($nextquests as &$nextquest) : ?>
		<?php if($nextquest['id'] == $relatedquesttext['quest']['id']) : ?>
		<li>
			<p>
			<?=_('Quest')?>:
			<?php if($nextquest['entered'] || !$charactedHasChoosenNextQuest) : ?>
			<a href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url'],$relatedquesttext['type_url']),3)?>"><?=$nextquest['title']?></a>
			<?php else : ?>
			<?=$nextquest['title']?>
			<?php endif ?>
			</p>
		</li>
		<?php else : ?>
		<li>
			<p>
			<?php if($nextquest['entered'] || !$charactedHasChoosenNextQuest) : ?>
			<?php if(!empty($nextquest['entry_text'])) : ?>
			<a href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url']),3)?>"><?=$nextquest['entry_text']?></a>
			<?php else : ?>
			<?=_('Quest')?>:
			<a href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url']),3)?>"><?=$nextquest['title']?></a>
			<?php endif ?>
			<?php else : ?>
			<?php if(!empty($nextquest['entry_text'])) : ?>
			<?=$nextquest['entry_text']?>
			<?php else : ?>
			<?=$nextquest['title']?>
			<?php endif ?>
			<?php endif ?>
			</p>
		</li>
		<?php endif ?>
		<?php endforeach ?>
	</ul>
	<?php elseif(!is_null($nextquestgroup)) : ?>
	<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$nextquestgroup['url']))?>"><?=$nextquestgroup['hierarchy']['title_singular']?> <?=$nextquestgroup['hierarchy']['questgroup_pos']?>: <?=$nextquestgroup['title']?></a>
	<?php endif ?>
</section>
<?php endif ?>
