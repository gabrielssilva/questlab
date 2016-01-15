<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
</ul>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('editgroupsgroup',$seminary['url'],$groupsgroup['url']), 1)?>"><?=_('Edit Character groups-group')?></a></li>
    <li><a href="<?=$linker->link(array('deletegroupsgroup',$seminary['url'],$groupsgroup['url']), 1)?>"><?=_('Delete Character groups-group')?></a></li>
    
</nav>
<?php endif ?>

<h1><?=$groupsgroup['name']?></h1>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('creategroup',$seminary['url'],$groupsgroup['url']), 1)?>"><?=sprintf(_('Create new %s Character group'), $groupsgroup['name'])?></a></li>
</nav>
<?php endif ?>
<ol class="cglist rnkng">
    <?php foreach($groups as $index => &$group) : ?>
    <li>
        <?php if($index < 3) : ?>
        <img src="<?=$linker->link(array('media','charactergroup',$seminary['url'],$groupsgroup['url'],$group['url']))?>" class="gbanner">
        <?php endif ?>
        <p><a href="<?=$linker->link(array('group',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=$group['name']?></a><span class="xp"><?=$group['xps']?> XP</span></p>
    </li>
    <?php endforeach ?>
</ol>


<h2><?=sprintf(_('%s-Quests'),$groupsgroup['name'])?></h2>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('charactergroupsquests','create',$seminary['url'],$groupsgroup['url']))?>"><?=sprintf(_('Create new %s-Quest'), $groupsgroup['name'])?></a></li>
</nav>
<?php endif ?>

<ul class="cgqlist cf">
    <?php foreach($quests as &$quest) : ?>
    <li class="cf">
        <img src="<?=$linker->link(array('media','charactergroupsquest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" />
        <p><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></p>
    </li>
    <?php endforeach ?>
</ul>
