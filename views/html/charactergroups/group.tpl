<h2><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h2>
<h3><?=$seminary['title']?></h3>
<h4><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></h4>
<h5><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></h5>
<h6><?=$group['name']?></h6>

<section>
	XPs: <?=$group['xps']?>
</section>

<section>
	<h1><?=_('Characters')?></h1>
	<ul>
		<?php foreach($characters as &$character) : ?>
		<li><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a> (<?=$character['xps']?> XPs) <?php if($character['is_leader'] > 0) : ?>(<?=_('Group Leader')?>)<?php endif ?></li>
		<?php endforeach ?>
	</ul>
</section>

<section>
	<h1><?=_('Quests')?></h1>
	<table>
		<tbody>
			<?php foreach($quests as &$quest) : ?>
			<tr>
				<td><?=$dateFormatter->format(new \DateTime($quest['created']))?></td>
				<td><a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>"><?=$quest['title']?></a></td>
				<td><?=$quest['group_xps']?>/<?=$quest['xps']?> XPs</td>
			</tr>
			<?php endforeach ?>
		</tbody>
	</table>
</section>
