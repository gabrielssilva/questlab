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
		<tr>
			<td>
				<?=$character['name']?>:
				<?php if($lives['character'] > 0) : ?>
				<?php foreach(range(1,$lives['character']) as $i) : ?>
				♥
				<?php endforeach ?>
				<?php else : ?>
				<?=_('verloren')?>
				<?php endif ?>
			</td>
			<td>
				<?=$fight['bossname']?>:
				<?php if($lives['boss'] > 0) : ?>
				<?php foreach(range(1,$lives['boss']) as $i) : ?>
				♥
				<?php endforeach ?>
				<?php else : ?>
				<?=_('verloren')?>
				<?php endif ?>
			</td>
		</tr>
	</tbody>
</table>

<p><?=\hhu\z\Utils::t($stage['text'])?></p>

<form method="post" action="#task">
	<input type="hidden" name="stage" value="<?=$stage['id']?>" />
	<ul>
		<?php foreach($childStages as &$childStage) : ?>
		<li>
			<?php if(array_key_exists('answer', $childStage) && $childStage['answer']) : ?>
			→
			<?php endif ?>
			<input type="submit" name="submit_stages[<?=$childStage['id']?>]" value="<?=$childStage['question']?>" />
		</li>
		<?php endforeach?>
		<?php if($lives['character'] == 0 || $lives['boss'] == 0) : ?>
		<li>
			<input type="hidden" name="answers" value="" />
			<input type="submit" name="submit" value="<?=_('solve')?>" />
		</li>
		<?php endif ?>
	</ul>
</form>
