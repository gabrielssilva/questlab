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


<h2 id="quests"><?=sprintf(_('%s-Quests'),$groupsgroup['name'])?></h2>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('charactergroupsquests','create',$seminary['url'],$groupsgroup['url']))?>"><?=sprintf(_('Create new %s-Quest'), $groupsgroup['name'])?></a></li>
</nav>
<?php endif ?>

<ul class="cgqlist cf">
    <?php foreach($quests as &$quest) : ?>
<?php if($quest['public'] || count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
    <li class="cf">
        <img src="<?=$linker->link(array('media','charactergroupsquest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" />
        <p><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></p>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
        <p><small>
<?php if($quest['pos'] > 1) : ?>
            <a href="<?=$linker->link(array('charactergroupsquests','moveup',$seminary['url'],$groupsgroup['url'],$quest['url']))?>">↑</a>
<?php endif ?>
<?php if($quest['pos'] < count($quests)) : ?>
            <a href="<?=$linker->link(array('charactergroupsquests','movedown',$seminary['url'],$groupsgroup['url'],$quest['url']))?>">↓</a>
<?php endif ?>
        </small></p>
<?php endif ?>
    </li>
<?php endif ?>
    <?php endforeach ?>
</ul>


<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<h2 id="achievements"><i class="fa fa-trophy fa-fw"></i><?=sprintf(_('%s-Achievements'),$groupsgroup['name'])?></a></h2>
<nav class="admin">
    <li><a href="<?=$linker->link(array('charactergroupsachievements','create',$seminary['url'],$groupsgroup['url']))?>"><?=sprintf(_('Create new %s-Achievement'), $groupsgroup['name'])?></a></li>
    <li><a href="<?=$linker->link(array('charactergroupsachievements','manage',$seminary['url'],$groupsgroup['url']))?>"><?=sprintf(_('Manage %s-Achievements'), $groupsgroup['name'])?></a></li>
</nav>
<ul class="achmnts">
<?php foreach($achievements as &$achievement) : ?>
    <li class="cf">
<?php if(!is_null($achievement['achievementsmedia_id'])) : ?>
        <img src="<?=$linker->link(array('media','charactergroupsachievement',$seminary['url'],$groupsgroup['url'],$achievement['url']))?>" />
<?php endif ?>
        <h3 id="<?=$achievement['url']?>"><?=$achievement['title']?></h3>
        <p class="desc"><?=\hhu\z\Utils::t($achievement['description'])?></p>
    </li>
<?php endforeach?>
</ul>
<?php endif ?>
