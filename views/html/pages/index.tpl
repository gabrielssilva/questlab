<div class="moodpic">
    <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>

<h1><?=_('Pages')?></h1>
<ul>
    <?php foreach($pages as &$page) : ?>
    <li>
        <a href="<?=$linker->link(array('page',$page['url']),1)?>">
            <?=$page['title']?>
        </a>
    </li>
    <?php endforeach ?>
    <li>
        <form method="post" action="<?=$linker->link('create',1)?>">
            <input type="text" name="title" placeholder="<?=_('New page')?>" />
            <input type="submit" name="create" value="<?=_('create')?>" />
        </form>
    </li>
</ul>
