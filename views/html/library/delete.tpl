<?=$moodpic?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Library')?></a></li>
</ul>

<h1><i class="fa fa-book fa-fw"></i><?=_('Delete Questtopic')?></h1>
<?=sprintf(_('Should the Questtopic “%s” really be deleted?'), $questtopic['title'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
