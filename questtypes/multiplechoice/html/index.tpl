<form method="post">
	<ol>
		<?php foreach($questions as $i => &$question) : ?>
		<li>
			<input type="checkbox" id="answers[<?=$i?>]" name="answers[<?=$i?>]" value="true" <?=(array_key_exists($i, $answers)) ? 'checked="checked' : '' ?> />
			<label for="answers[<?=$i?>]"><?=\hhu\z\Utils::t($question['question'])?></label>
		</li>
		<?php endforeach ?>
	</ol>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
