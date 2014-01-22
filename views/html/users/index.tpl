<h1><?=_('Users')?></h1>
<nav>
	<li><a href="<?=$linker->link('create', 1)?>"><?=_('Create new user')?></a></li>
</nav>
<ul>
	<?php foreach($users as &$user) : ?>
	<li>
		<h2><a href="<?=$linker->link(array('user', $user['username']), 1)?>"><?=$user['username']?></a></h2>
		<details>
			<summary><?=_('registered on')?> <?=date(\hhu\z\Utils::DATEFORMAT, strtotime($user['created']))?></summary>
		</details>
	</li>
	<?php endforeach ?>
</ul>
