<form method="post">
	<a href="<?=$linker->link(array('uploads','index',$submission['url']))?>"><?=$submission['name']?></a> (<?=sprintf(_('submitted at %s on %s h'), $dateFormatter->format(new \DateTime($submission['created'])), $timeFormatter->format(new \DateTime($submission['created'])))?>)
	<br /><br />
	
	<?php if($solved) : ?>
	<?=_('solved')?>
	<?php else : ?>
	<input type="submit" name="submit" value="<?=_('solved')?>" />
	<input type="submit" name="submit" value="<?=_('unsolved')?>" />
	<?php endif ?>
</form>
