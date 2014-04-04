<?php if(!is_null($exception)) : ?>
<p class="error">
	<?php if($exception->getNestedException() instanceof \hhu\z\exceptions\WrongFiletypeException) : ?>
	<?=sprintf(_('File has wrong type “%s”'), $exception->getNestedException()->getType())?>
	<?php elseif($exception->getNestedException() instanceof \hhu\z\exceptions\WrongFiletypeException) : ?>
	<?=_('File exceeds size maximum')?>
	<?php elseif($exception->getNestedException() instanceof \hhu\z\exceptions\FileUploadException) : ?>
	<?=sprintf(_('Error during file upload: %s'), $exception->getNestedException()->getNestedMessage())?>
	<?php else : ?>
	<?=$exception->getNestedException()->getMessage()?>	
	<?php endif ?>
</p>
<?php endif ?>
<?php if(is_null($submission)) : ?>
<form method="post" enctype="multipart/form-data">
	<input type="file" name="answers" /><br />
	<?=_('Allowed file types')?>:
	<ul>
		<?php foreach($mimetypes as &$mimetype) : ?>
		<li><?=$mimetype['mimetype']?> (<?=_('max.')?> <?=$numberFormatter->format(round($mimetype['size']/(1024*1024),2))?> MiB)</li>
		<?php endforeach ?>
	</ul>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
<?php else : ?>
<a href="<?=$linker->link(array('uploads','index',$submission['url']))?>"><?=$submission['name']?></a> (<?=sprintf(_('submitted at %s on %s h'), $dateFormatter->format(new \DateTime($submission['created'])), $timeFormatter->format(new \DateTime($submission['created'])))?>)
<?php endif ?>
