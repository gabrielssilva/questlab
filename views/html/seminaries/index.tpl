<ul>
	<?php foreach($seminaries as &$seminary) : ?>
	<li>
		<h2><a href="<?=$linker->link(array('seminary', $seminary['url']), 1)?>"><?=$seminary['title']?></a></h2>
		<details>
			<summary>erstellt von <?=$seminary['creator']['username']?></summary>
		</details>
	</li>
	<?php endforeach ?>
</ul>
