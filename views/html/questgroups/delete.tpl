<?php if(!is_null($picture)) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$picture['url']))?>" />
</div>
<?php else: ?>
<?=$moodpic?>
<?php endif ?>
<?=$questgroupshierarchypath?>

<?php if(!is_null($questgroup['hierarchy'])) : ?>
<h1><?=$questgroup['hierarchy']['title_singular']?> <?=$questgroup['hierarchy']['questgroup_pos']?>: <?=$questgroup['title']?></h1>
<?php else : ?>
<h1><?=$questgroup['title']?></h1>
<?php endif ?>

<h1><?=_('Delete Questgroup')?></h1>
<?=sprintf(_('Should the Questgroup “%s” really be deleted?'), $questgroup['title'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
