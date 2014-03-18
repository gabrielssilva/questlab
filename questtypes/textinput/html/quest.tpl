<form method="post">
	<?php foreach($texts as $i => &$text) : ?>
	<?php if($i > 0) : ?>
	<input type="text" name="answers[<?=$i-1?>]" value="<?=(array_key_exists($i-1, $answers)) ? $answers[$i-1] : '' ?>" />
	<?php endif ?>
	<?=\hhu\z\Utils::t($text)?>
	<?php endforeach ?>
	
	<br /><br />
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
