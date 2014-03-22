<ul>
	<?php foreach($questions as &$question) : ?>
	<li>
		<?php if($question['answer']) : ?>☑<?php else : ?>☐<?php endif ?>
		<?php if($question['answer'] == $question['tick']) : ?>✓<?php else : ?>×<?php endif ?>
		<?=$question['question']?>
	</li>
	<?php endforeach ?>
</ul>
