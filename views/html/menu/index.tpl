<menu>
	<?php if(is_null($loggedUser)) : ?><li><a href="<?=$linker->link(null)?>"><i class="fa fa-users fa-fw"></i><?=_('Introduction')?></a></li><?php endif ?>
	<li><a href="<?=$linker->link(array(), 0, true, array(), true)?>"><i class="fa fa-users fa-fw"></i>The Legend of Z</a></li>
	<?php if(!is_null($loggedUser)) : ?><li><a href="<?=$linker->link('users')?>"><i class="fa fa-users fa-fw"></i><?=_('Users')?></a></li><?php endif ?>
	<?php if(!is_null($loggedUser)) : ?><li><a href="<?=$linker->link('seminaries')?>"><i class="fa fa-pencil-square-o fa-fw"></i><?=_('Seminaries')?></a></li><?php endif ?>
	<?php if(!is_null($loggedUser)) : ?><li><a href="#"><i class="fa fa-users fa-fw"></i>Gilden</a></li><?php endif ?>
	<?php if(!is_null($loggedUser)) : ?><li><a href="#"><i class="fa fa-trophy fa-fw"></i>Achievements</a></li><?php endif ?>
	<?php if(!is_null($loggedUser)) : ?><li><a href="#"><i class="fa fa-picture-o fa-fw"></i>Karte</a></li><?php endif ?>
	<?php if(!is_null($loggedUser)) : ?><li><a href="#"><i class="fa fa-book fa-fw"></i>Bibliothek</a></li><?php endif ?>
	<?php if(is_null($loggedUser)) : ?>
	<li><a href="<?=$linker->link(array('users','login'))?>"><i class="fa fa-sign-in fa-fw"></i><?=_('Login')?></a></li>
	<?php else : ?>
	<li><a href="<?=$linker->link(array('users','logout'))?>"><i class="fa fa-sign-out fa-fw"></i><?=_('Logout')?></a></li>
	<?php endif ?>
</menu>
