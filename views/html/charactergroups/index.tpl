<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><?=_('Character Groups')?></h1>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('creategroupsgroup',$seminary['url']),1)?>"><?=_('Create new Character groups-group')?></a></li>
</nav>
<?php endif ?>

<ul class="cglist">
    <?php foreach($groupsgroups as &$group) : ?>
    <li><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$group['url']),1)?>"><?=$group['name']?></a></li>
    <?php endforeach ?>
</ul>
