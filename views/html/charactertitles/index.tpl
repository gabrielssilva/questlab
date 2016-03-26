<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>

<h1><?=_('Charactertitles')?></h1>
<?php if($seminary['created_user_id'] == \hhu\z\controllers\IntermediateController::$user['id'] || (!is_null(\hhu\z\controllers\SeminaryController::$character) && in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles']))) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('create',$seminary['url']),1)?>"><?=_('Create new Character titles')?></a></li>
</nav>
<?php endif ?>
<ul>
    <?php foreach($titles as &$title) : ?>
    <li>
        <p><?=$title['title_male']?>/<?=$title['title_female']?></p>
        <ul class="admin">
            <li><a href="<?=$linker->link(array('edit',$seminary['url'],$title['hash']),1)?>"><?=_('edit')?></a></li>
            <li><a href="<?=$linker->link(array('delete',$seminary['url'],$title['hash']),1)?>"><?=_('delete')?></a></li>
        </ul>
    </li>
    <?php endforeach ?>
</ul>
