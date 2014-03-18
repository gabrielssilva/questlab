<form method="post">
	<textarea name="answers[]" <?=(!is_null($submission)) ? 'disabled="disabled"' : ''?>><?=!is_null($submission) ? $submission['text'] : ''?></textarea><br />
	
	<?php if(!is_null($submission)) : ?>
	<?php if($wordcount > 1) : ?>
	<?=$wordcount?> <?=_('Words')?><br />
	<?php else : ?>
	<?=$wordcount?> <?=_('Word')?><br />
	<?php endif ?>
	(<?=sprintf(_('submitted at %s on %s h'), $dateFormatter->format(new \DateTime($submission['created'])), $timeFormatter->format(new \DateTime($submission['created'])))?>)
	<?php else : ?>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
	<?php endif ?>
</form>
