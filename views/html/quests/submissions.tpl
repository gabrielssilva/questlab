<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>

<?=$questgroupshierarchypath?>
<?=$questgroupspicture?>

<h3><?=$quest['title']?></h3>

<?php if(!is_null($media)) : ?>
<img src="<?=$linker->link(array('media','index',$seminary['url'],$media['url']))?>" />
<?php endif ?>

<section>
	<h1><?=_('unsolved')?></h1>
	<ul>
		<?php foreach($unsolvedsubmissions as &$submission) : ?>
		<li>
			<a href="<?=$linker->link(array('submission',$seminary['url'],$questgroup['url'],$quest['url'],$submission['character']['url']),1)?>"><?=$submission['character']['name']?></a>
		</li>
		<?php endforeach?>
	</ul>

	<h1><?=_('solved')?></h1>
	<ul>
		<?php foreach($solvedsubmissions as &$submission) : ?>
		<li>
			<a href="<?=$linker->link(array('submission',$seminary['url'],$questgroup['url'],$quest['url'],$submission['character']['url']),1)?>"><?=$submission['character']['name']?></a>
		</li>
		<?php endforeach?>
	</ul>
</section>
