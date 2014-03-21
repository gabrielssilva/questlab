<form method="post">
	<ol>
		<?php foreach($questions as $i => &$question) : ?>
		<li>
			<input type="checkbox" id="answers[<?=$i?>]" name="answers[<?=$i?>]" value="true" <?=($question['answer']) ? 'checked="checked"' : '' ?> <?=($solved) ? 'disabled="disabled"' : '' ?>/>
			<label for="answers[<?=$i?>]"><?=\hhu\z\Utils::t($question['question'])?></label>
		</li>
		<?php endforeach ?>
	</ol>
	<input type="submit" name="submit" value="<?=_('solve')?>" <?=($solved) ? 'disabled="disabled"' : '' ?> />
</form>
