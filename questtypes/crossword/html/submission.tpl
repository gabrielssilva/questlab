<form method="post">
	<table>
		<tbody>
			<?php foreach(range(0, $maxY) as $y) : ?>
			<tr>
				<?php foreach(range(0, $maxX) as $x) : ?>
				<td>
					<?php if(array_key_exists($x, $matrix) && array_key_exists($y, $matrix[$x]) && !is_null($matrix[$x][$y])) : ?>
					<input type="text" name="answers[<?=$x?>][<?=$y?>]" maxlength="1" size="1" disabled="disabled" style="background-color:<?=($matrix[$x][$y]['right']) ? 'green' : 'red'?>" placeholder="<?=implode('/',$matrix[$x][$y]['indices'])?>" value="<?=(!is_null($matrix[$x][$y]['answer'])) ? $matrix[$x][$y]['answer'] : ''?>" />	
					<?php endif ?>
				</td>
				<?php endforeach ?>
			</tr>
			<?php endforeach ?>
		</tbody>
	</table>
	
	<ul>
		<?php foreach($words as &$word) : ?>
		<li><?=$word['question']?></li>
		<?php endforeach ?>
	</ul>
</form>
