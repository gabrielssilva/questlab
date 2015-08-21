<?=$moodpic?>
<?=$questgroupshierarchypath?>
<h1><?=$quest['title']?></h1>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link('edit', 5)?>"><?=_('Edit Quest')?></a></li>
    <li><a href="<?=$linker->link('edittexts', 5)?>"><?=_('Edit Quest texts')?></a></li>
    <?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
    <li><a href="<?=$linker->link('delete', 5)?>"><?=_('Delete Quest')?></a></li>
    <?php endif ?>
</nav>
<?php endif ?>
<?php if(array_key_exists('Prolog', $questtexts) && count($questtexts['Prolog']) > 0) : ?>
<section>
    <h1 id="questtext"><?=_('Prolog')?></h1>
    <div class="qtextbox">
        <?php $mediaShown = false; ?>
        <?php foreach($questtexts['Prolog'] as &$questtext) : ?>
        <p class="qtext cf">
            <?php if(array_key_exists('media', $questtext)) : ?>
            <a href="<?=$linker->link(array('media','seminary',$seminary['url'],$questtext['media']['url']))?>">
                <img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questtext['media']['url'], 'quest'))?>" />
            </a>
            <?php if(!empty($questtext['media']['sourceurl'])) : ?>
            <span class="source">
                <a href="<?=$questtext['media']['sourceurl']?>" target="_blank" title="<?=_('Image source')?>" rel="nofollow">
                    <i class="fa fa-external-link"></i>
                </a>
            </span>
            <?php endif ?>
            <?php elseif(!is_null($media) && !$mediaShown) : ?>
            <?php $mediaShown = true; ?>
            <a href="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>">
                <img src="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url'],'quest'))?>" />
            </a>
            <?php if(!empty($media['sourceurl'])) : ?>
            <span class="source">
                <a href="<?=$media['sourceurl']?>" target="_blank" title="<?=_('Image source')?>" rel="nofollow">
                    <i class="fa fa-external-link"></i>
                </a>
            </span>
            <?php endif ?>
            <?php endif ?>
            <?=str_replace('<p>', '', str_replace('</p>', '', $t->t($questtext['text'])))?>
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
        <p><small><?=$t->t($quest['wrong_text'])?></small></p>
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
<section <?php if(count($nextquests) == 0 && is_null($nextquestgroup)) : ?>class="gameover"<?php endif ?>>
    <?php if(count($nextquests) == 0 && is_null($nextquestgroup)) : ?>
    <h1><?=_('Game over')?></h1>
    <?php else : ?>
    <h1 id="questtext"><?=_('Epilog')?></h1>
    <?php endif ?>
    <div class="qtextbox">
        <?php foreach($questtexts['Epilog'] as &$questtext) : ?>
        <p class="qtext cf">
            <?php if(array_key_exists('media', $questtext)) : ?>
            <a href="<?=$linker->link(array('media','seminary',$seminary['url'],$questtext['media']['url']))?>">
                <img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questtext['media']['url'],'quest'))?>" />
            </a>
            <?php if(!empty($questtext['media']['sourceurl'])) : ?>
            <span class="source">
                <a href="<?=$questtext['media']['sourceurl']?>" target="_blank" title="<?=_('Image source')?>" rel="nofollow">
                    <i class="fa fa-external-link"></i>
                </a>
            </span>
            <?php endif ?>
            <?php endif ?>
            <?=str_replace('<p>', '', str_replace('</p>', '', $t->t($questtext['text'])))?>
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

<section>
    <?php if(count($nextquests) > 0 || !is_null($nextquestgroup)) : ?>
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
            <?php if(!empty($nextquest['entry_text'])) : ?>
            <i><?=$nextquest['entry_text']?></i>
            <?php if($nextquest['entered'] || !$charactedHasChoosenNextQuest) : ?>
            <p><a class="cta orange" href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url']),3)?>"><?=_('Choose')?></a></p>
            <?php endif ?>
            <?php else : ?>
            <p><?=_('Quest')?>: <a href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url']),3)?>"><?=$nextquest['title']?></a></p>
            <?php if($nextquest['entered'] || !$charactedHasChoosenNextQuest) : ?>
            <p><a class="cta orange" href="<?=$linker->link(array($nextquest['questgroup_url'],$nextquest['url']),3)?>"><?=_('Go on')?></a></p>
            <?php endif ?>
            <?php endif ?>
        </li>
        <?php endif ?>
        <?php endforeach ?>
    </ul>
    <?php elseif(!is_null($nextquestgroup)) : ?>
    <p><?=$nextquestgroup['hierarchy']['title_singular']?> <?=$nextquestgroup['hierarchy']['questgroup_pos']?>: <a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$nextquestgroup['url']))?>"><?=$nextquestgroup['title']?></a></p>
    <p><a class="cta orange" href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$nextquestgroup['url']))?>"><?=_('Let’s go')?></a></p>
    <?php endif ?>
    <?php endif ?>
</section>
