<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
</ul>
<h1><?=_('Delete Character groups-group')?></h1>

<?=sprintf(_('Should the Character groups-group “%s” really be deleted?'), $groupsgroup['name'])?>
<form method="post">
    <input type="submit" name="delete" value="<?=_('delete')?>" />
    <input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
