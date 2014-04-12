<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><?=_('Character Groups')?></h2>

<ul>
	<?php foreach($groupsgroups as &$group) : ?>
	<li><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$group['url']),1)?>"><?=$group['name']?></a></li>
	<?php endforeach ?>
</ul>
