<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php endif ?>
<?=$questgroupshierarchypath?>

<h1><?=_('Edit Quest task')?></h1>
<?php if(!is_null($task)) : ?>
<?=$task?>
<?php endif ?>
