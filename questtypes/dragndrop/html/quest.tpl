<form method="post">
	<div id="dropZone" style="width:<?=$field['width']?>px; height:<?=$field['height']?>px; background-image:url('<?=$linker->link(array('media','seminary',$seminary['url'],$field['media']['url']))?>')">
		<?php foreach($drops as &$drop) : ?>
		<div id="drop<?=$drop['id']?>" ondragenter="onDragEnter(event)" ondragover="onDragOver(event)" ondragleave="onDragLeave(event)" ondrop="onDrop(event)" style="position:absolute; width:<?=$drop['width']?>px; height:<?=$drop['height']?>px; margin:<?=$drop['top']?>px 0 0 <?=$drop['left']?>px;"><?php if(array_key_exists('answer', $drop) && !is_null($drop['answer'])) : ?><img id="drag<?=$drop['answer']['id']?>" draggable="true" ondragstart="onDragStart(event)" ondragend="onDragEnd(event)" src="<?=$linker->link(array('media','seminary',$seminary['url'],$drop['answer']['media']['url']))?>" /><?php endif ?></div>
		<input type="hidden" id="dnd_drop<?=$drop['id']?>" name="answers[<?=$drop['id']?>]" value="<?=(array_key_exists('answer', $drop)) ? 'drag'.$drop['answer']['id'] : null ?>" />
		<?php endforeach ?>
	</div>
	
	<div id="dragZone" ondragenter="onDragEnter(event)" ondragover="onDragOver(event)" ondragleave="onDragLeave(event)" ondrop="onDrop(event, false)" style="width:100%; min-height:5em;">
		<?php foreach($drags as &$drag) : ?>
		<img id="drag<?=$drag['id']?>" draggable="true" ondragstart="onDragStart(event)" ondragend="onDragEnd(event)" src="<?=$linker->link(array('media','seminary',$seminary['url'],$drag['media']['url']))?>" />
		<?php endforeach ?>
	</div>
	
	<br />
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
