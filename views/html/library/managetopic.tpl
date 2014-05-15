<?php if(!is_null($seminary['library_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'library'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Library')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('topic',$seminary['url'],$questtopic['url']),1)?>"><?=$questtopic['title']?></a></li>
</ul>
<h1><i class="fa fa-book fa-fw"></i><?=$questtopic['title']?></h1>

<h2>Quests zu diesem Thema:</h2>
<form method="post">
	<ul class="libtop">
		<?php foreach($quests as &$quest) : ?>
		<li>
			<p><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$quest['questgroup']['url'],$quest['url']))?>"><?=$quest['title']?></a></p>
			<?php foreach($questsubtopics as &$subtopic) : ?>
			<input id="subtopic-<?=$quest['id']?>-<?=$subtopic['id']?>" type="checkbox" name="questsubtopics[<?=$quest['id']?>][<?=$subtopic['id']?>]" <?php if(in_array($subtopic['id'], $quest['subtopics'])) : ?>checked="checked"<?php endif ?> />
			<label for="subtopic-<?=$quest['id']?>-<?=$subtopic['id']?>"><?=$subtopic['title']?></label><br />
			<?php endforeach ?>
		</li>
		<?php endforeach ?>
	</ul>
	<input type="submit" value="<?=_('Manage')?>" />
</form>
