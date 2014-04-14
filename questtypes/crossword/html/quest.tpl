<form method="post" class="crossword">
	<table>
		<tbody>
			<?php foreach(range(0, $maxY) as $y) : ?>
			<tr>
				<?php foreach(range(0, $maxX) as $x) : ?>
				<td>
					<?php if(array_key_exists($x, $matrix) && array_key_exists($y, $matrix[$x]) && !is_null($matrix[$x][$y])) : ?>
					<?php if(count($matrix[$x][$y]['indices']) > 0) : ?><span class="index"><?=implode('/',array_map(function($e) { return $e+1; }, $matrix[$x][$y]['indices']))?></span><?php endif ?>
					<input type="text" name="answers[<?=$x?>][<?=$y?>]" maxlength="1" size="1" value="<?=(!is_null($matrix[$x][$y]['answer'])) ? $matrix[$x][$y]['answer'] : ''?>" />	
					<?php endif ?>
				</td>
				<?php endforeach ?>
			</tr>
			<?php endforeach ?>
		</tbody>
	</table>
	<ol>
		<?php foreach($words as &$word) : ?>
		<li><?=$word['question']?></li>
		<?php endforeach ?>
	</ol>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
<script type="text/javascript">
$('input:text').bind("keyup", function(e) {
	var n = $("input:text").length;
	if(e.which == 8 || e.which == 46) {
		var nextIndex = $('input:text').index(this) - 1;
		var del = 1;
	}
	else {
		var nextIndex = $('input:text').index(this) + 1;
	}
	if(nextIndex < n) {
		$('input:text')[nextIndex].focus();
		if(del == 1) {
			$('input:text')[nextIndex].value = '';
		}
	}
});
</script>
