<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li>
		<i class="fa fa-chevron-right fa-fw"></i>
		<a href="<?=$linker->link(array('characters','index',$seminary['url']))?>"><?=_('Characters')?></a>
	</li>
</ul>

<h1><?=_('Delete Character')?></h1>
<?=sprintf(_('Should the Character “%s” of user “%s” (%s) really be deleted?'), $character['name'], $user['username'], $user['email'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
