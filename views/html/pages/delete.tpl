<div class="moodpic">
    <img src="<?=$linker->hardlink('/grafics/questlab.jpg')?>" />
</div>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(null,3)?>"><?=$page['title']?></a></li>
</ul>

<h1><?=_('Delete page')?></h1>
<?=sprintf(_('Should the page “%s” really be deleted?'), $page['title'])?>
<form method="post">
	<input type="submit" name="delete" value="<?=_('delete')?>" />
	<input type="submit" name="not-delete" value="<?=_('cancel')?>" />
</form>
