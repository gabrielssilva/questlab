<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php else : ?>
<?=$moodpic?>
<?php endif ?>
<?=$questgroupshierarchypath?>

<h1><?=_('Delete Quest')?></h1>
<?=sprintf(_('Should the Quest “%s” really be deleted?'), $quest['title'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
