<p>
	<?php
		$text = $t->t($task['text']);
		
		// Insert Character answers
		foreach(array_reverse($fields) as &$field)
		{
			// Get positions
			$posStart = mb_strrpos($text, '[textinput]', 0, 'UTF-8');
			$posEnd = $posStart + mb_strlen('[textinput]', 'UTF-8');
			
			// Create field for Character answer
			$answerField = sprintf(
				'<span style="background-color:grey">%s</span>%s',
				$field['answer'],
				($field['right']) ? '✓' : '✕'
			);
			
			// Insert input field
			$text = mb_substr($text, 0, $posStart, 'UTF-8') . $answerField . mb_substr($text, $posEnd, mb_strlen($text)-$posEnd, 'UTF-8');
		}
	?>
	<?=$text?>
</p>
