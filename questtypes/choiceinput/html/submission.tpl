<form method="post">
	<?php foreach($texts as $i => &$text) : ?>
	<?php if($i > 0) : ?>
	<select name="answers[<?=$i-1?>]" disabled="disabled">
		<?php foreach($choiceLists[$i-1]['values'] as &$choice) : ?>
		<option value="<?=$choice['id']?>" <?php if(array_key_exists('answer', $choiceLists[$i-1]) && $choiceLists[$i-1]['answer'] == $choice['id']) : ?>selected="selected"<?php endif ?>><?=$choice['text']?></option>
		<?php endforeach ?>
	</select>
	<?php endif ?>
	<?=\hhu\z\Utils::t($text)?>
	<?php endforeach ?>
</form>
