<?php if(count($parentquestgroupshierarchy) > 0) : ?>
<ul class="breadcrumbs">
	<?php foreach($parentquestgroupshierarchy as &$hierarchy) : ?>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$hierarchy['url']))?>"><?=$hierarchy['hierarchy']['title_singular']?> <?=$hierarchy['pos']?>: <?=$hierarchy['title']?></a></li>
	<?php endforeach ?>
</ul>
<?php endif ?>
