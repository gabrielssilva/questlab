<h1><?=_('Users')?></h1>
<nav class="admin">
	<li><a href="<?=$linker->link('create', 1)?>"><?=_('Create new user')?></a></li>
</nav>
<ol class="cglist">
	<?php foreach($users as &$user) : ?>
	<li><a href="<?=$linker->link(array('user', $user['username']), 1)?>"><?=$user['username']?></a><span class="xp"><small><?=sprintf(_('registered on %s'),  $dateFormatter->format(new \DateTime($user['created'])))?></small></span></li>
	<?php endforeach ?>
</ol>
