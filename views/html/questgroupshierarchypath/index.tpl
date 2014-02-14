<?php if(count($parentquestgroupshierarchy) > 0) : ?>
Pfad:
<ul>
	<?php foreach($parentquestgroupshierarchy as &$hierarchy) : ?>
	<li><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$hierarchy['url']))?>"><?=$hierarchy['hierarchy']['title_singular']?> <?=$hierarchy['pos']?>: <?=$hierarchy['title']?></a></li>
	<?php endforeach ?>
</ul>
<?php endif ?>
