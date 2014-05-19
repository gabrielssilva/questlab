<p>
	<?php
		$text = $t->t($task['text']);
		
		// Insert comboboxes
		foreach(array_reverse($choiceLists) as &$list)
		{
			// Get positions
			$posStart = mb_strrpos($text, '[choiceinput]', 0, 'UTF-8');
			$posEnd = $posStart + mb_strlen('[choiceinput]', 'UTF-8');
			
			// Create combobox
			$combobox = '<select name="answers[]" disabled="disabled">';
			foreach($list['values'] as &$choice) {
				$combobox .= sprintf(
					'<option value="%s" %s>%s</option>',
					$choice['id'],
					(array_key_exists('answer', $list) && $list['answer'] == $choice['id']) ? 'selected="selected"' : null,
					$choice['text']
				);
			}
			$combobox .= '</select>';
			
			// Insert input field
			$text = mb_substr($text, 0, $posStart, 'UTF-8') . $combobox . mb_substr($text, $posEnd, mb_strlen($text)-$posEnd, 'UTF-8');
		}
	?>
	<?=$text?>
</p>
