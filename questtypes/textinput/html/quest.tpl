<form method="post">
	<?php foreach($texts as $i => &$text) : ?>
	<?php if($i > 0) : ?>
	<input type="text" name="answers[<?=$i-1?>]" value="<?=$regexs[$i-1]['answer']?>" />
	<?php endif ?>
	<?=$t->t($text)?>
	<?php endforeach ?>
	
	<br /><br />
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
