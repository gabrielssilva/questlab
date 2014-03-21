<h1><?=_('Seminaries')?></h1>
<h2><?=$seminary['title']?></h2>
<h3><?=_('Character Groups Quests')?></h3>
<h4><?=$quest['title']?></h4>

<?php if(!is_null($media)) : ?>
<img src="<?=$linker->link(array('media','index',$seminary['url'],$media['url']))?>" />
<?php endif ?>

<section>
	<p>XPs: <?=$quest['xps']?></p>
	<h1><?=_('Description')?></h1>
	<p><?=\hhu\z\Utils::t($quest['description'])?></p>
	<?php if(!empty($quest['rules'])) : ?>
	<h1><?=_('Rules')?></h1>
	<p><?=\hhu\z\Utils::t($quest['rules'])?></p>
	<?php endif ?>
</section>

<?php if(!empty($quest['von_text'])) : ?>
<section>	
	<h1><?=_('Won Quest')?></h1>
	<p><?=\hhu\z\Utils::t($quest['won_text'])?></p>
</section>
<?php endif ?>
<?php if(!empty($quest['lost_text'])) : ?>
<section>
	<h1><?=_('Lost Quest')?></h1>
	<p><?=\hhu\z\Utils::t($quest['lost_text'])?></p>
</section>
<?php endif ?>

<section>
	<h1><?=$groupsgroup['name']?></h1>
	<table>
		<tbody>
			<?php foreach($groups as &$group) : ?>
			<tr>
				<td><?=$dateFormatter->format(new \DateTime($group['created']))?></td>
				<td><a href="<?=$linker->link(array('charactergroups','group',$seminary['url'],$groupsgroup['url'],$group['url']))?>"><?=$group['name']?></a></td>
				<td><?=$group['xps']?>/<?=$quest['xps']?> XPs</td>
			</tr>
			<?php endforeach ?>
		</tbody>
	</table>
</section>
