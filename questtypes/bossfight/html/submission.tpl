<table>
	<tbody>
		<tr>
			<td>
				<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['avatar_url']))?>" />
			</td>
			<td>
				<?php if(array_key_exists('bossmedia', $fight)) : ?>
				<img src="<?=$linker->link(array('media','seminary',$seminary['url'],$fight['bossmedia']['url']))?>" />
				<?php endif ?>
			</td>
		</tr>
		<?php foreach($stages as &$stage) : ?>
		<tr>
			<td colspan="2">
				<?=$stage['question']?>
			</td>
		</tr>
		<tr>
			<td>
				<?=$character['name']?>:
				<?php if($stage['lives']['character'] > 0) : ?>
				<?php foreach(range(1,$stage['lives']['character']) as $i) : ?>
				♥
				<?php endforeach ?>
				<?php else : ?>
				<?=_('lost')?>
				<?php endif ?>
			</td>
			<td>
				<?=$fight['bossname']?>:
				<?php if($stage['lives']['boss'] > 0) : ?>
				<?php foreach(range(1,$stage['lives']['boss']) as $i) : ?>
				♥
				<?php endforeach ?>
				<?php else : ?>
				<?=_('lost')?>
				<?php endif ?>
			</td>
		</tr>
		<?php endforeach ?>
	</tbody>
</table>
