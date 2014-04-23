<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><?=_('Characters')?></h2>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('manage',$seminary['url']),1)?>"><?=_('Manage')?></li>
</nav>
<?php endif ?>

<ul class="gchars cf">
	<?php foreach($characters as &$character) : ?>
	<li>
		<p><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level'],'portrait'))?>"></p>
		<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
		<p><small><?=$character['xps']?> XP</small></p>
	</li>
	<?php endforeach ?>
</ul>
