<form method="post">
	<fieldset>
		<legend><?=sprintf(_('Question %d of %d'), $pos, $count)?>:</legend>
		<p class="fwb"><?=\hhu\z\Utils::t($question['question'])?></p>
		<ol class="mchoice">
			<?php foreach($question['answers'] as $i => &$answer) : ?>
			<li class="cf">
				<input type="checkbox" id="answers[<?=$i?>]" name="answers[<?=$i?>]" value="true" <?=(array_key_exists('useranswer', $answer) && $answer['useranswer']) ? 'checked="checked"' : '' ?> />
				<label for="answers[<?=$i?>]"><?=$t->t($answer['answer'])?></label>
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
