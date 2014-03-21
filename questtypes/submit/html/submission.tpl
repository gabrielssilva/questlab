<form method="post">
	<?=\hhu\z\Utils::t($submission['text'])?>
	<br /><br />
	
	<?php if($solved) : ?>
	<?=_('solved')?>
	<?php else : ?>
	<input type="submit" name="submit" value="<?=_('solved')?>" />
	<input type="submit" name="submit" value="<?=_('unsolved')?>" />
	<?php endif ?>
</form>
