<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('achievements','index',$seminary['url']))?>"><?=_('Achievements')?></a></li>
</ul>

<h1><?=_('Delete Achievement')?></h1>
<?=sprintf(_('Should the Achievement “%s” really be deleted?'), $achievement['title'])?>
<form method="post">
    <input type="submit" name="delete" value="<?=_('delete')?>" />
    <input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
