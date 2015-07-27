<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>

<h1><?=_('Charactertypes')?></h1>
<?php if($seminary['created_user_id'] == \hhu\z\controllers\IntermediateController::$user['id'] || (!is_null(\hhu\z\controllers\SeminaryController::$character) && in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles']))) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('create',$seminary['url']),1)?>"><?=_('Create new Character type')?></a></li>
</nav>
<?php endif ?>
<ul class="avatar">
    <?php foreach($charactertypes as &$type) : ?>
    <li>
        <p><?=$type['name']?></p>
        <?php if(array_key_exists('avatar', $type) && !is_null($type['avatar']['small_avatarpicture_id'])) : ?>
        <img id="avatar" src="<?=$linker->link(array('media','avatar',$seminary['url'],$type['url'],$xplevels[0]['level'],'portrait'))?>" />
        <?php endif ?>
        <ul class="admin">
            <li><a href="<?=$linker->link(array('edit',$seminary['url'],$type['url']),1)?>"><?=_('edit')?></a></li>
            <li><a href="<?=$linker->link(array('delete',$seminary['url'],$type['url']),1)?>"><?=_('delete')?></a></li>
        </ul>
    </li>
    <?php endforeach ?>
</ul>
