<ul>
	<?php foreach($users as &$user) : ?>
	<li>
		<h2><a href="<?=$linker->link(array('user', $user['username']), 1)?>"><?=$user['username']?></a></h2>
		<details>
			<summary>registriert seit <?=date(\hhu\z\Utils::DATEFORMAT, strtotime($user['created']))?></summary>
		</details>
	</li>
	<?php endforeach ?>
</ul>
