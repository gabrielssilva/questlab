<?=$moodpic?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('edit',$seminary['url'],$groupsgroup['url'],$quest['url']),1)?>"><?=sprintf(_('Edit %s-Quest'), $groupsgroup['name'])?></a></li>
	<li><a href="<?=$linker->link(array('delete',$seminary['url'],$groupsgroup['url'],$quest['url']),1)?>"><?=sprintf(_('Delete %s-Quest'), $groupsgroup['name'])?></a></li>
	<li><a href="<?=$linker->link(array('manage',$seminary['url'],$groupsgroup['url'],$quest['url']),1)?>"><?=sprintf(_('Manage %s-Quest'), $groupsgroup['name'])?></a></li>
</nav>
<?php endif ?>

<div class="gbanner cf">
	<img src="<?=$linker->link(array('media','charactergroupsquest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" class="grpqimg" />
	<h1><?=$quest['title']?></h1>
</div>
<ul class="gdata cf">
	<li><span class="fwb"><?=sprintf(_('%d XPs'), $quest['xps'])?></span></li>
	<li><?php if($questgroup['entered']) : ?><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$questgroup['url']))?>"><?=$questgroup['title']?></a><?php else : ?><?=$questgroup['title']?><?php endif ?></li>
</ul>

<?php if(count($uploads) > 0) : ?>
<section>
	<h1><i class="fa fa-picture-o fa-fw"></i><?=_('Media')?></h1>
	<ul class="gqgllry">
		<?php foreach($uploads as &$upload) : ?>
		<li>
			<a href="<?=$linker->link(array('uploads','seminary',$seminary['url'],$upload['upload']['url']))?>">
				<img src="<?=$linker->link(array('uploads','seminary',$seminary['url'],$upload['upload']['url'],'thumbnail'))?>" />
			</a>
		</li>
		<?php endforeach ?>
	</ul>
</section>
<?php endif ?>

<section>
	<h1><i class="fa fa-envelope fa-fw"></i><?=_('Description')?></h1>
	<p><?=\hhu\z\Utils::t($quest['description'])?></p>
	<?php if(!empty($quest['rules'])) : ?>
	<h1><i class="fa fa-exclamation-triangle fa-fw"></i><?=_('Rules')?></h1>
	<p><?=\hhu\z\Utils::t($quest['rules'])?></p>
	<?php endif ?>
</section>

<?php if(!empty($quest['won_text'])) : ?>
<section>	
	<h1><i class="fa fa-thumbs-up fa-fw"></i><?=_('Won Quest')?></h1>
	<p><?=\hhu\z\Utils::t($quest['won_text'])?></p>
</section>
<?php endif ?>
<?php if(!empty($quest['lost_text'])) : ?>
<section>
	<h1><i class="fa fa-thumbs-down fa-fw"></i><?=_('Lost Quest')?></h1>
	<p><?=\hhu\z\Utils::t($quest['lost_text'])?></p>
</section>
<?php endif ?>

<section>
	<h1><i class="fa fa-users fa-fw"></i><?=$groupsgroup['name']?></h1>
	<ol class="grpqlist">
		<?php foreach($groups as &$group) : ?>
		<li>
			<span class="date"><?=$dateFormatter->format(new \DateTime($group['created']))?></span>
			<span class="group"><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$groupsgroup['url'],$group['url']))?>"><?=$group['name']?></a></span>
			<span class="xp"><?=sprintf(_('%d XPs'), $group['xps'])?></span>
		</li>
		<?php endforeach ?>
	</ol>
</section>
