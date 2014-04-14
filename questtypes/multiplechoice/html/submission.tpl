<ol>
	<?php foreach($questions as $pos => &$question) : ?>
	<li>
		<h1><?=\hhu\z\Utils::t($question['question'])?></h1>
		<ol>
			<?php foreach($question['answers'] as &$answer) : ?>
			<li>
				<?php if($answer['useranswer']) : ?>☑<?php else : ?>☐<?php endif ?>
				<?php if($answer['useranswer'] == $answer['tick']) : ?>✓<?php else : ?>×<?php endif ?>
				<?=$answer['answer']?>
			</li>
			<?php endforeach ?>
		</ol>
	</li>
	<?php endforeach ?>
</ol>
