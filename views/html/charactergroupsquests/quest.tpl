<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><?=_('Character Groups Quests')?></li>
</ul>

<h1><?=$quest['title']?></h1>
<small>Maximale Belohnung: <span class="fwb"><?=$quest['xps']?> XP</span></small>

<section>
	<h1><i class="fa fa-envelope fa-fw"></i><?=_('Description')?></h1>
	<p>
	<?php if(!is_null($media)) : ?>
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>" class="grpqimg" />
	<?php endif ?>
	<?=\hhu\z\Utils::t($quest['description'])?>
	</p>
	<?php if(!empty($quest['rules'])) : ?>
	<h1><i class="fa fa-exclamation-triangle fa-fw"></i><?=_('Rules')?></h1>
	<p><?=\hhu\z\Utils::t($quest['rules'])?></p>
	<?php endif ?>
</section>

<?php if(!empty($quest['von_text'])) : ?>
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
	<ul class="grpqlist">
		<?php foreach($groups as &$group) : ?>
		<li>
			<span class="date"><?=$dateFormatter->format(new \DateTime($group['created']))?></span>
			<span class="group"><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$groupsgroup['url'],$group['url']))?>"><?=$group['name']?></a></span>
			<span class="xp"><?=$group['xps']?> XP</span>
		</li>
		<?php endforeach ?>
	</ul>
</section>
