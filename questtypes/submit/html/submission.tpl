<?php if(count($submissions) > 0) : ?>
<ol>
	<?php foreach($submissions as &$submission) : ?>
	<li>
		<a href="<?=$linker->link(array('uploads','seminary',$seminary['url'], $submission['upload']['url']))?>"><?=$submission['upload']['name']?></a><br />
		<?=sprintf(_('submitted at %s on %s h'), $dateFormatter->format(new \DateTime($submission['created'])), $timeFormatter->format(new \DateTime($submission['created'])))?><br />
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

<form method="post">
	<?php $submission = array_pop($submissions); ?>
	<?php if(!$solved) : ?>
	<?=_('Comment')?><br />
	<textarea name="characterdata[comment]"></textarea><br />
	<input type="hidden" name="characterdata[submission_id]" value="<?=$submission['id']?>" />
	<input type="submit" name="submit" value="<?=_('solved')?>" />
	<input type="submit" name="submit" value="<?=_('unsolved')?>" />
	<?php endif ?>
</form>
