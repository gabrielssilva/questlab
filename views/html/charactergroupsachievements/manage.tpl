<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>
<nav class="admin">
    <li><a href="<?=$linker->link(array('create', $seminary['url'], $groupsgroup['url']), 1)?>"><?=sprintf(_('Create new %s-Achievement'), $groupsgroup['name'])?></a></li>
</nav>

<h1><i class="fa fa-trophy fa-fw"></i><?=sprintf(_('Manage %s-Achievements'), $groupsgroup['name'])?></h1>
<ul class="achmnts">
<?php foreach($achievements as $index => &$achievement) : ?>
    <li class="cf">
<?php if(!is_null($achievement['achievementsmedia_id'])) : ?>
        <img src="<?=$linker->link(array('media','charactergroupsachievement',$seminary['url'],$groupsgroup['url'],$achievement['url']))?>" />
<?php endif ?>
        <h3 id="<?=$achievement['url']?>"><?=$achievement['title']?></h3>
        <p class="desc"><?=\hhu\z\Utils::t($achievement['description'])?></p>
        <ul class="admin">
            <li><a href="<?=$linker->link(array('edit',$seminary['url'],$groupsgroup['url'],$achievement['url']),1)?>"><?=_('edit')?></a></li>
            <li><a href="<?=$linker->link(array('delete',$seminary['url'],$groupsgroup['url'],$achievement['url']),1)?>"><?=_('delete')?></a></li>
            <?php if($index > 0) : ?><li><a href="<?=$linker->link(array('moveup',$seminary['url'],$groupsgroup['url'],$achievement['url']),1)?>">↑</a></li><?php endif ?>
            <?php if($index < count($achievements)-1) : ?><li><a href="<?=$linker->link(array('movedown',$seminary['url'],$groupsgroup['url'],$achievement['url']),1)?>">↓</a></li><?php endif ?>
            <li>
                <a href="<?=$linker->link(array('achievement',$seminary['url'],$groupsgroup['url'],$achievement['hash']),1)?>"><?=_('assign manually')?></a>
            </li>
            <li>
                <a href="<?=$linker->link(array('qrcodes','charactergroupsachievements',$seminary['url'],$groupsgroup['url'],$achievement['url'],'50'))?>">
                    <i class="fa fa-qrcode"></i>
                </a>
            </li>
        </ul>
    </li>
<?php endforeach?>
</ul>
