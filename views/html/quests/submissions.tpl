<?php if(!is_null($questgroup['picture'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$questgroup['picture']['url']))?>" />
</div>
<?php endif ?>
<?=$questgroupshierarchypath?>
<h1><?=$quest['title']?></h1>

<section>
	<h1><?=_('submitted')?></h1>
	<ul>
		<?php foreach($submittedSubmissionCharacters as &$character) : ?>
		<li>
			<a href="<?=$linker->link(array('submission',$seminary['url'],$questgroup['url'],$quest['url'],$character['url']),1)?>"><?=$character['name']?></a>
		</li>
		<?php endforeach?>
	</ul>
	
	<h1><?=_('unsolved')?></h1>
	<ul>
		<?php foreach($unsolvedSubmissionCharacters as &$character) : ?>
		<li>
			<a href="<?=$linker->link(array('submission',$seminary['url'],$questgroup['url'],$quest['url'],$character['url']),1)?>"><?=$character['name']?></a>
		</li>
		<?php endforeach?>
	</ul>

	<h1><?=_('solved')?></h1>
	<ul>
		<?php foreach($solvedSubmissionCharacters as &$character) : ?>
		<li>
			<a href="<?=$linker->link(array('submission',$seminary['url'],$questgroup['url'],$quest['url'],$character['url']),1)?>"><?=$character['name']?></a>
		</li>
		<?php endforeach?>
	</ul>
</section>
