<form method="post">
	<div id="dnd" style="width:<?=$field['width']?>px; height:<?=$field['height']?>px; background-image:url('<?=$linker->link(array('media','index',$seminary['url'],$field['media']['url']))?>')">
		<?php foreach($drops as &$drop) : ?>
		<div id="drop<?=$drop['id']?>" style="position:absolute; width:<?=$drop['width']?>px; height:<?=$drop['height']?>px; margin:<?=$drop['top']?>px 0 0 <?=$drop['left']?>px;"></div>
		<input type="hidden" id="dnd_drop<?=$drop['id']?>" name="dnd[<?=$drop['id']?>]" value="" />
		<?php endforeach ?>
	</div>
	
	<div>
		<?php foreach($drags as &$drag) : ?>
		<img id="drag<?=$drag['id']?>" src="<?=$linker->link(array('media','index',$seminary['url'],$drag['media']['url']))?>" />
		<?php endforeach ?>
	</div>
	
	<br />
	<input type="submit" name="submit" value="<?=_('solve')?>" <?=($solved) ? 'disabled="disabled"' : '' ?> />
</form>
