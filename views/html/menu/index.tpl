<li><a href="<?=$linker->link(array(), 0, true, array(), true)?>"><i class="fa fa-home fa-fw"></i>Questlab</a></li>
<?php if(!is_null($loggedUser) && count(array_intersect(array('admin','moderator'),$loggedUser['roles'])) > 0) : ?><li><a href="<?=$linker->link('users')?>"><i class="fa fa-users fa-fw"></i><?=_('Users')?></a></li><?php endif ?>
<?php if(!is_null($loggedUser)) : ?><li><a href="<?=$linker->link('seminaries')?>"><i class="fa fa-pencil-square-o fa-fw"></i><?=_('Seminaries')?></a></li><?php endif ?>
<?php if(!is_null($loggedCharacter) && count($loggedCharacter['characterroles']) > 0) : ?><?=$seminarymenu?><?php endif ?>
<?php if(is_null($loggedUser)) : ?>
<li><a href="<?=$linker->link(array('users','login'))?>"><i class="fa fa-sign-in fa-fw"></i><?=_('Login')?></a></li>
<?php else : ?>
<li><a href="<?=$linker->link(array('users','logout'))?>"><i class="fa fa-sign-out fa-fw"></i><?=_('Logout')?></a></li>
<?php endif ?>
