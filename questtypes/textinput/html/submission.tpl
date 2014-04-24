<?php foreach($texts as $i => &$text) : ?>
<?php if($i > 0) : ?>
<span style="background-color:grey"><?=$regexs[$i-1]['answer']?></span>
<?php if($regexs[$i-1]['right']) : ?>✓<?php else: ?>✕<?php endif ?>
<?php endif ?>
<?=$t->t($text)?>
<?php endforeach ?>
