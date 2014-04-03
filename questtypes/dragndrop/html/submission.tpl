<div style="width:<?=$field['width']?>px; height:<?=$field['height']?>px; background-image:url('<?=$linker->link(array('media','index',$seminary['url'],$field['media']['url']))?>')">
	<?php foreach($drops as &$drop) : ?>
	<div id="drop<?=$drop['id']?>" style="position:absolute; width:<?=$drop['width']?>px; height:<?=$drop['height']?>px; margin:<?=$drop['top']?>px 0 0 <?=$drop['left']?>px;">
		<?php if(!is_null($drop['useranswer'])) : ?>
		<img id="drag<?=$drop['useranswer']['id']?>" src="<?=$linker->link(array('media','index',$seminary['url'],$drop['useranswer']['media']['url']))?>" />
		<?php endif ?>
	</div>
	<?php endforeach ?>
</div>

<div style="width:100%; min-height:5em;">
	<?php foreach($drags as &$drag) : ?>
	<img id="drag<?=$drag['id']?>" src="<?=$linker->link(array('media','index',$seminary['url'],$drag['media']['url']))?>" />
	<?php endforeach ?>
</div>
