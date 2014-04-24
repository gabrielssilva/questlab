<form method="post" class="textinput">
	<p>
	<?php foreach($texts as $i => &$text) : ?>
	<?php if($i > 0) : ?>
	<input type="text" name="answers[<?=$i-1?>]" value="<?=$regexs[$i-1]['answer']?>" />
	<?php endif ?>
	<?=$t->t($text)?>
	<?php endforeach ?>
	</p>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
