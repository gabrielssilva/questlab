<menu>
	<?php if(is_null($loggedUser)) : ?><li><a href="<?=$linker->link(null)?>"><i class="fa fa-users fa-fw"></i><?=_('Introduction')?></a></li><?php endif ?>
	<?php if(!is_null($loggedUser)) : ?><li><a href="<?=$linker->link('users')?>"><i class="fa fa-users fa-fw"></i><?=_('Users')?></a></li><?php endif ?>
	<?php if(!is_null($loggedUser)) : ?><li><a href="<?=$linker->link('seminaries')?>"><i class="fa fa-users fa-fw"></i><?=_('Seminaries')?></a></li><?php endif ?>
	<?php if(is_null($loggedUser)) : ?>
	<li><a href="<?=$linker->link(array('users','login'))?>"><i class="fa fa-sign-in fa-fw"></i><?=_('Login')?></a></li>
	<?php else : ?>
	<li><a href="<?=$linker->link(array('users','logout'))?>"><i class="fa fa-sign-out fa-fw"></i><?=_('Logout')?></a></li>
	<?php endif ?>
</menu>
