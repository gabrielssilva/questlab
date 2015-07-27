<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link('index',1)?>"><?=_('Seminaries')?></a></li>
</ul>

<h1><?=_('Delete seminary')?></h1>
<?=sprintf(_('Should the seminary “%s” really be deleted?'), $seminary['title'])?>
<form method="post">
    <input type="submit" name="delete" value="<?=_('delete')?>" />
    <input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
