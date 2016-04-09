<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Library')?></a></li>
</ul>
<h1><i class="fa fa-book fa-fw"></i><?=$questtopic['title']?></h1>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('edit',$seminary['url'],$questtopic['url']),1)?>"><?=_('Edit Questtopic')?></a></li>
    <li><a href="<?=$linker->link(array('delete',$seminary['url'],$questtopic['url']),1)?>"><?=_('Delete Questtopic')?></a></li>
    <li><a href="<?=$linker->link(array('manage',$seminary['url'],$questtopic['url']),1)?>"><?=_('Manage Questtopic')?></a></li>
</nav>
<?php endif ?>
<div class="libindxpr cf">
    <p><small>Themenfortschritt: <?=$questtopic['characterQuestcount']?> / <?=$questtopic['questcount']?></small></p>
    <div class="xpbar">
        <span style="width:<?=($questtopic['questcount'] > 0) ? round($questtopic['characterQuestcount']/$questtopic['questcount']*100) : 0?>%"></span>
    </div>
</div>

<h2>Quests zu diesem Thema:</h2>
<ul class="libtop">
    <?php foreach($quests as &$quest) : ?>
    <li>
        <p><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$quest['questgroup_url'],$quest['url']))?>"><?=$quest['title']?></a></p>
        <ul class="addon">
            <?php foreach($quest['subtopics'] as &$subtopic) : ?>
            <li><?=$subtopic['title']?></li>
            <?php endforeach ?>
        </ul>
    </li>
    <?php endforeach ?>
</ul>
