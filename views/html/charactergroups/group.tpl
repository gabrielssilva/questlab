<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>
<h3><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></h3>
<h4><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></h4>
<h5><?=$group['name']?></h5>

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
