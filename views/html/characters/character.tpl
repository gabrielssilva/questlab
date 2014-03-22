<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>
<h3><?=_('Characters')?></h3>
<h4><?=$character['name']?></h4>

<section>
	<p>
		XPs: <?=$character['xps']?> (<?=_('Level')?> <?=$character['xplevel']['level']?><?php if(!is_null($character['xplevel']['name'])) : ?>: <?=$character['xplevel']['name']?><?php endif ?>)<br />
		<?=_('User')?>: <a href="<?=$linker->link(array('users','user',$user['url']))?>"><?=$user['username']?></a><br />
		<?php foreach($characterfields as &$field) : ?>
		<?=$field['title']?>: <?=$field['value']?><br />
		<?php endforeach ?>
	</p>
	<?php if(!is_null($character['avatar_url'])) : ?>
	<img src="<?=$linker->link(array('media','index',$seminary['url'],$character['avatar_url']))?>" alt="<?=$character['avatar_description']?>" />
	<?php endif ?>
</section>

<section>
	<h1><?=_('Character Groups')?></h1>
	<ul>
		<?php foreach($groups as &$group) : ?>
		<li><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$group['charactergroupsgroup_url'],$group['url']))?>"><?=$group['name']?></a> (<?=$group['xps']?> XPs)</li>
		<?php endforeach ?>
	</ul>
</section>
