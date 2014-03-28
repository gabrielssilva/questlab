<?php if(count($parentquestgroupshierarchy) > 0) : ?>
<ul class="breadcrumbs">
	<?php foreach($parentquestgroupshierarchy as &$hierarchy) : ?>
	<li>
		<i class="fa fa-chevron-right fa-fw"></i>
		<?php if(array_key_exists('hierarchy', $hierarchy)) : ?>
		<a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$hierarchy['url']))?>">
			<?php if(!is_null($hierarchy['hierarchy'])) : ?>
			<?=$hierarchy['hierarchy']['title_singular']?> <?=$hierarchy['hierarchy']['questgroup_pos']?>:
			<?php endif ?>
			<?=$hierarchy['title']?>
		</a>
		<?php else : ?>
		<a href="<?=$linker->link(array('quests','quest',$seminary['url'],$hierarchy['questgroup']['url'],$hierarchy['url']))?>">
			<?=$hierarchy['title']?>
		</a>
		<?php endif ?>
	</li>
	<?php endforeach ?>
</ul>
<?php endif ?>
