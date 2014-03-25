<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>

<?=$questgroupshierarchypath?>
<?=$questgroupspicture?>

<?php if(is_null($relatedquesttext)) : ?>
<h3><?=$quest['title']?></h3>
<?php else : ?>
<h3><a href="<?=$linker->link(array('quest',$seminary['url'],$questgroup['url'],$relatedquesttext['quest']['url'],$relatedquesttext['type_url'],$relatedquesttext['pos']),1)?>"><?=$relatedquesttext['quest']['title']?></a></h3>
<h4><?=$quest['title']?></h4>
<?php endif ?>

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
