<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Charactertitles')?></a></li>
</ul>

<h1><?=_('Delete Charactertitle')?></h1>
<?=sprintf(_('Should the Charactertitle “%s/%s” really be deleted?'), $title['title_male'], $title['title_female'])?>
<form method="post">
    <input type="submit" name="delete" value="<?=_('delete')?>" />
    <input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
