<menu>
	<li><a href="<?=$linker->link("users")?>"><?=_('Users')?></a></li>
	<li><a href="<?=$linker->link("seminaries")?>"><?=_('Seminaries')?></a></li>
	<?php if(is_null($loggedUser)) : ?>
	<li><a href="<?=$linker->link(array('users','login'))?>"><?=_('Login')?></a></li>
	<?php else : ?>
	<li><a href="<?=$linker->link(array('users','logout'))?>"><?=_('Logout')?></a></li>
	<?php endif ?>
</menu>
