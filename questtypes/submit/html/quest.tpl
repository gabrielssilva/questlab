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
<?php if(!$solved && (is_null($lastStatus) || count($submissions) == 0 || $lastStatus['created'] > $submissions[count($submissions)-1]['created'])) : ?>
<form method="post" enctype="multipart/form-data" class="submit">
	<input type="file" name="answers" required="required" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" />
	<p><?=_('Allowed file types')?>:</p>
	<ul>
		<?php foreach($mimetypes as &$mimetype) : ?>
		<li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
		<?php endforeach ?>
	</ul>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
<?php endif ?>

<?php if(count($submissions) > 0) : ?>
<h2><?=_('Past submissions')?></h2>
<ol>
	<?php foreach($submissions as &$submission) : ?>
	<li>
		<a href="<?=$linker->link(array('uploads','seminary',$seminary['url'], $submission['upload']['url']))?>"><?=$submission['upload']['name']?></a><br />
		<?=sprintf(_('submitted at %s on %s h'), $dateFormatter->format(new \DateTime($submission['created'])), $timeFormatter->format(new \DateTime($submission['created'])))?><br />
		<?php if($lastStatus['status'] == 1) : ?>
		<?=_('This submission is waiting for approval')?>
		<?php endif ?>
		<?php if(count($submission['comments']) >  0) : ?>
		<ol>
			<?php foreach($submission['comments'] as &$comment) : ?>
			<li>
				<?php if(array_key_exists('user', $comment) && array_key_exists('character', $comment['user'])) : ?>
				<?=sprintf(_('Comment from %s on %s at %s'), $comment['user']['character']['name'], $dateFormatter->format(new \DateTime($comment['created'])), $timeFormatter->format(new \DateTime($comment['created'])))?>:<br />
				<?php endif ?>
				<?=\hhu\z\Utils::t($comment['comment'])?>
			</li>
			<?php endforeach ?>
		</ol>
		<?php endif ?>
	</li>
	<?php endforeach ?>
</ol>
<?php endif ?>
