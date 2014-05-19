<form method="post" class="textinput">
	<p>
		<?php
			$text = $t->t($task['text']);
			
			// Insert input fields
			foreach(array_reverse($fields) as &$field)
			{
				// Get positions
				$posStart = mb_strrpos($text, '[textinput]', 0, 'UTF-8');
				$posEnd = $posStart + mb_strlen('[textinput]', 'UTF-8');
				
				// Create input field
				$class = ($field['size'] != 'default') ? $field['size'] : null;
				$value = (array_key_exists('answer', $field)) ? $field['answer'] : null;
				$inputField = '<input type="text" name="answers[]" value="'.$value.'" class="'.$class.'" />';
				
				// Insert input field
				$text = mb_substr($text, 0, $posStart, 'UTF-8') . $inputField . mb_substr($text, $posEnd, mb_strlen($text)-$posEnd, 'UTF-8');
			}
		?>
		<?=$text?>
	</p>
	<input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
