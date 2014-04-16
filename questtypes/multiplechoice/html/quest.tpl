<form method="post">
	<fieldset>
		<legend><?=sprintf(_('Question %d of %d'), $pos, $count)?></legend>
		<p><?=\hhu\z\Utils::t($question['question'])?></p>
		<ol>
			<?php foreach($question['answers'] as $i => &$answer) : ?>
			<li>
				<input type="checkbox" id="answers[<?=$i?>]" name="answers[<?=$i?>]" value="true" <?=(array_key_exists('useranswer', $answer) && $answer['useranswer']) ? 'checked="checked"' : '' ?> />
				<label for="answers[<?=$i?>]"><?=\hhu\z\Utils::t($answer['answer'])?></label>
			</li>
			<?php endforeach ?>
		</ol>
	</fieldset>
	
	<input type="hidden" name="question" value="<?=$pos?>" />
	<?php if($pos < $count) : ?>
	<input type="submit" name="submit-answer" value="<?=_('solve Question')?>" />
	<?php else : ?>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
	<?php endif ?>
</form>
