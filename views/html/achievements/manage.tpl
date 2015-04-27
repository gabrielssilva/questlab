<?php if(!is_null($seminary['achievements_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'achievements'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('achievements','index',$seminary['url']))?>"><?=_('Achievements')?></a></li>
</ul>

<h1><i class="fa fa-trophy fa-fw"></i><?=_('Manage Achievements')?></h1>
<ul class="achmnts">
	<?php foreach($achievements as $index => &$achievement) : ?>
	<li class="cf">
		<?php if(!is_null($achievement['achieved_achievementsmedia_id'])) : ?>
		<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url']))?>" />
		<?php endif ?>
		<h3 id="<?=$achievement['url']?>"><?=$achievement['title']?></h3>
		<p class="desc"><?=\hhu\z\Utils::t($achievement['description'])?></p>
		<ul class="admin">
			<li><a href="<?=$linker->link(array('edit',$seminary['url'],$achievement['url']),1)?>"><?=_('edit')?></a></li>
			<li><a href="<?=$linker->link(array('delete',$seminary['url'],$achievement['url']),1)?>"><?=_('delete')?></a></li>
			<?php if($index > 0) : ?><li><a href="<?=$linker->link(array('moveup',$seminary['url'],$achievement['url']),1)?>">↑</a></li><?php endif ?>
			<?php if($index < count($achievements)-1) : ?><li><a href="<?=$linker->link(array('movedown',$seminary['url'],$achievement['url']),1)?>">↓</a></li><?php endif ?>
		</ul>
	</li>
	<?php endforeach?>
</ul>
