<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></li>
</ul>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0 || in_array(\hhu\z\controllers\SeminaryController::$character['id'], array_map(function($c) { return $c['id']; }, $group['characters']))) : ?>
<nav class="admin">
    <?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0 || in_array(\hhu\z\controllers\SeminaryController::$character['id'], array_map(function($c) { return $c['id']; }, $group['characters']))) : ?>
    <li><a href="<?=$linker->link(array('editgroup',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=sprintf(_('Edit %s Character group'), $groupsgroup['name'])?></a></li>
    <?php endif ?>
    <?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
    <li><a href="<?=$linker->link(array('deletegroup',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=sprintf(_('Delete %s Character group'), $groupsgroup['name'])?></a></li>
    <li><a href="<?=$linker->link(array('managegroup',$seminary['url'],$groupsgroup['url'],$group['url']),1)?>"><?=sprintf(_('Manage %s Character group'), $groupsgroup['name'])?></a></li>
    <?php endif ?>
</nav>
<?php endif ?>

<div class="gbanner cf">
    <img src="<?=$linker->link(array('media','charactergroup',$seminary['url'],$groupsgroup['url'],$group['url']))?>" class="gbanner">
    <h1><?=$group['name']?></h1>
    <?php if(!empty($group['motto'])) : ?>
    <p>"<?=$group['motto']?>"</p>
    <?php endif ?>
</div>
<ul class="gdata cf">
    <li><?=$group['rank']?>. <?=_('Rank')?></li>
    <li><?=sprintf(_('%d XPs'), $group['xps'])?></li>
    <li><?=count($group['characters'])?> <?=(count($group['characters']) == 0 || count($group['characters']) > 1) ? _('Members') : _('Member')?></li>
</ul>

<section>
    <h1><i class="fa fa-users fa-fw"></i><?=_('Characters')?></h1>
    <ul class="gchars cf">
        <?php foreach($group['characters'] as &$character) : ?>
        <li>
            <?php if(array_key_exists('small_avatar', $character)) : ?>
            <p><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['small_avatar']['url']))?>"></p>
            <?php endif ?>
            <p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
            <p><small><?=sprintf(_('%d XPs'), $character['xps'])?></small></p>
        </li>
        <?php endforeach ?>
    </ul>
</section>

<section>
    <h1><i class="fa fa-pencil-square-o fa-fw"></i><?=sprintf(_('%s-Quests'),$groupsgroup['name'])?></h1>
    <ul class="gquests">
        <?php foreach($quests as &$quest) : ?>
        <li class="cf">
            <p>
                <span class="date"><?=$dateFormatter->format(new \DateTime($quest['created']))?></span>
                <a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" class="fwb"><?=$quest['title']?></a>
                <span class="xp"><?=$quest['group_xps']?> / <?=$quest['xps']?> <?=_('XPs')?></span>
            </p>
        </li>
        <?php endforeach ?>
    </ul>
</section>

<?php if(!empty($achievements) || count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<section>
    <h1 id="achievements"><i class="fa fa-trophy fa-fw"></i><?=_('Achievements')?></a></h1>
<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
    <nav class="admin">
        <li><a href="<?=$linker->link(array('charactergroupsachievements','manage',$seminary['url'],$groupsgroup['url']))?>"><?=sprintf(_('Manage %s-Achievements'), $groupsgroup['name'])?></a></li>
    </nav>
<?php endif ?>
    <ul class="achmnts">
<?php foreach($achievements as &$achievement) : ?>
        <li class="cf">
<?php if(!is_null($achievement['achievementsmedia_id'])) : ?>
            <img src="<?=$linker->link(array('media','charactergroupsachievement',$seminary['url'],$groupsgroup['url'],$achievement['url']))?>" />
<?php endif ?>
            <h3 id="<?=$achievement['url']?>">
                <?=$achievement['title']?>
                <span class="unlcked"><?=sprintf(_('achieved at: %s'), $dateFormatter->format(new \DateTime($achievement['created'])))?></span>
            </h3>
            <p class="desc"><?=\hhu\z\Utils::t($achievement['description'])?></p>
        </li>
<?php endforeach?>
    </ul>
</section>
<?php endif ?>
