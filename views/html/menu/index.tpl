<li><a href="<?=$linker->link(array(), 0, true, array(), true)?>"><?=\nre\configs\AppConfig::$app['name']?></a></li>
<?php if(!is_null($loggedUser) && count(array_intersect(array('admin','moderator'),$loggedUser['roles'])) > 0) : ?><li><a href="<?=$linker->link('users')?>"><?=_('Users')?></a></li><?php endif ?>
<?php if(!is_null($loggedUser)) : ?><li><a href="<?=$linker->link('seminaries')?>"><?=_('Seminaries')?></a></li><?php endif ?>
<?php if(!is_null($loggedCharacter) && count($loggedCharacter['characterroles']) > 0) : ?><?=$seminarymenu?><?php endif ?>
<?php if(is_null($loggedUser)) : ?>
<li><a href="<?=$linker->link(array('users','login'))?>"><?=_('Login')?></a></li>
<?php else : ?>
<li><a href="<?=$linker->link(array('users','logout'))?>"><?=_('Logout')?></a></li>
<?php endif ?>
