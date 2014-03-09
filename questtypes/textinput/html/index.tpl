<form method="post">
	<?php for($i=0; $i<count($text); $i++) : ?>
	<?php if($i > 0) : ?>
	<input type="text" name="answer-<?=$i?>" value="" />
	<?php endif ?>
	<?=\hhu\z\Utils::t($text[$i])?>
	<?php endfor ?>
	
	<br /><br />
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
