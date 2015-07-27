<div class="moodpic">
    <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<ul class="breadcrumbs">
    <?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) : ?>
    <li><a href="<?=$linker->link('index',1)?>"><?=_('Users')?></a></li>
    <?php else : ?>
    <li><?=_('Users')?></li>
    <?php endif ?>
</ul>

<h1><?=$user['username']?></h1>
<nav class="admin">
    <?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0 || $user['id'] == \hhu\z\controllers\IntermediateController::$user['id']) : ?>
    <li><a href="<?=$linker->link('edit', 3)?>"><?=_('Edit user')?></a></li>
    <?php endif ?>
    <?php if(count(array_intersect(array('admin','moderator'),\hhu\z\controllers\IntermediateController::$user['roles'])) > 0) : ?>
    <li><a href="<?=$linker->link('delete', 3)?>"><?=_('Delete user')?></a></li>
    <?php endif ?>
</nav>
<p>
    <?=sprintf(_('registered on %s'), $dateFormatter->format(new \DateTime($user['created'])))?><br />
    <?=_('Name')?>: <?=$user['prename']?> <?=$user['surname']?><br />
    <?=_('E‑mail address')?>: <a href="mailto:<?=$user['email']?>"><?=$user['email']?></a>
</p>

<h2><?=_('Characters')?></h2>
<ul class="gchars cf">
    <?php foreach($characters as &$character) : ?>
    <li>
        <?php if(array_key_exists('small_avatar', $character)) : ?>
        <p><img src="<?=$linker->link(array('media','seminary',$character['seminary_url'],$character['small_avatar']['url']))?>"></p>
        <?php endif ?>
        <p>
            <?php if(count($character['characterroles']) > 0) : ?>
            <a href="<?=$linker->link(array('characters','character',$character['seminary_url'],$character['url']))?>"><?=$character['name']?></a>
            <?php else : ?>
            <?=$character['name']?>
            <?php endif ?>
        </p>
        <?php if(array_key_exists('xplevel', $character) && !is_null($character['xplevel'])) : ?>
        <p><small><?=_('Level')?> <?=$character['xplevel']['level']?></small></p>
        <?php endif ?>
    </li>
    <?php endforeach ?>
</ul>

<h2><?=_('Roles')?></h2>
<?=$userroles?>
