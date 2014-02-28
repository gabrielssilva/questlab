<h1><?=$seminary['title']?></h1>
<h2><?=_('Characters')?></h2>
<h3><?=$character['name']?></h3>

<section>
	<p>
		XPs: <?=$character['xps']?> (<?=$character['xplevel']?>)<br />
		<?=_('User')?>: <a href="<?=$linker->link(array('users','user',$user['url']))?>"><?=$user['username']?></a><br />
		<?php foreach($characterfields as &$field) : ?>
		<?=$field['title']?>: <?=$field['value']?><br />
		<?php endforeach ?>
	</p>
</section>

<section>
	<h1><?=_('Character Groups')?></h1>
	<ul>
		<?php foreach($groups as &$group) : ?>
		<li><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$group['charactergroupsgroup_url'],$group['url']))?>"><?=$group['name']?></a> (<?=$group['xps']?> XPs)</li>
		<?php endforeach ?>
	</ul>
</section>
