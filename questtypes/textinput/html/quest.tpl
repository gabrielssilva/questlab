<form method="post" class="textinput">
	<p>
		<?php $posStart = 0; ?>
		<?php foreach($fields as &$field) : ?>
		<?php $posEnd = mb_strpos($task['text'], '[textinput]', $posStart, 'UTF-8'); ?>
		<?=$t->t(mb_substr($task['text'], $posStart, $posEnd-$posStart, 'UTF-8'))?>
		<input type="text" name="answers[]" value="<?=(array_key_exists('answer', $field)) ? $field['answer'] : ''?>" <?php if($field['size'] != 'default') : ?>class="<?=$field['size']?>"<?php endif ?> />
		<?php $posStart = $posEnd + mb_strlen('[textinput]', 'UTF-8'); ?>
		<?php endforeach ?>
		<?=$t->t(mb_substr($task['text'], $posStart, mb_strlen($task['text'], 'UTF-8')-$posStart, 'UTF-8'))?>
	</p>
    <?php if($showcount) : ?>
    <p><?=sprintf(_('You filled %d of %d fields correctly'), $count, count($fields))?>.</p>
    <?php endif ?>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
