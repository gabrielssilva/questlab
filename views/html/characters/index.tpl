<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><?=_('Characters')?></h2>

<ul class="gchars cf">
	<?php foreach($characters as &$character) : ?>
	<li>
		<?php if(array_key_exists('small_avatar', $character)) : ?>
		<p><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['small_avatar']['url']))?>"></p>
		<?php endif ?>
		<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
		<p><small><?=$character['xps']?> XP</small></p>
	</li>
	<?php endforeach ?>
</ul>
