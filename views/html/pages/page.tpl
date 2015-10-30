<div class="moodpic">
    <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<?php if(in_array('admin', \hhu\z\controllers\IntermediateController::$user['roles'])) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('edit',$page['url']),1)?>"><?=_('Edit page')?></a></li>
    <li><a href="<?=$linker->link(array('delete',$page['url']),1)?>"><?=_('Delete page')?></a></li>
</nav>
<?php endif ?>

<h1><?=$page['title']?></h1>
<?=$t->t($page['text'])?>
