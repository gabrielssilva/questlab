<?php if(!is_null($seminary['charactergroups_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'charactergroups'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>

<div class="gbanner cf">
	<?php if(!is_null($media)) : ?>
	<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$media['url']))?>" class="grpqimg" />
	<?php else : ?>
	<img src="<?=$linker->link(array('grafics','charactergroup.jpg'))?>" class="gbanner">
	<?php endif ?>
	<h1><?=$quest['title']?></h1>
</div>
<ul class="gdata cf">
	<li><span class="fwb"><?=sprintf(_('%d XPs'), $quest['xps'])?></span></li>
	<li><?php if($questgroup['entered']) : ?><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$questgroup['url']))?>"><?=$questgroup['title']?></a><?php else : ?><?=$questgroup['title']?><?php endif ?></li>
</ul>

<section>
	<h1><i class="fa fa-users fa-fw"></i><?=$groupsgroup['name']?></h1>
	<form method="post">
		<ul class="grpqlist">
			<?php foreach($groups as &$group) : ?>
			<li>
				<span class="group"><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$groupsgroup['url'],$group['url']))?>"><?=$group['name']?></a></span>
				<span class="xp">
					<select name="xps[<?=$group['url']?>]">
						<option value="null" <?php if(is_null($group['quest_group'])) : ?>selected="selected"<?php endif ?>><?=_('Not attended')?></option>
						<?php for($i=0; $i<=$quest['xps']; $i++) : ?>
						<option value="<?=$i?>" <?php if(!is_null($group['quest_group']) && $group['quest_group']['xps'] == $i) : ?>selected="selected"<?php endif ?>><?=sprintf(_('%d XPs'), $i)?></option>
						<?php endfor ?>
					</select>
				</span>
			</li>
			<?php endforeach ?>
		</ul>
		<input type="submit" name="setxps" value="<?=_('Set XPs')?>" />
	</form>
</section>
