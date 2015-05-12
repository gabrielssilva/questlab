<p>
    <?php $posStart = 0; ?>
    <?php foreach($fields as &$field) : ?>
    <?php $posEnd = mb_strpos($task['text'], '[textinput]', $posStart, 'UTF-8'); ?>
    <?=$t->t(mb_substr($task['text'], $posStart, $posEnd-$posStart, 'UTF-8'))?>
    <span style="background-color:grey"><?=$field['answer']?></span><?=($field['right']) ? '✓' : '✕'?>
    <?php $posStart = $posEnd + mb_strlen('[textinput]', 'UTF-8'); ?>
    <?php endforeach ?>
    <?=$t->t(mb_substr($task['text'], $posStart, mb_strlen($task['text'], 'UTF-8')-$posStart, 'UTF-8'))?>
</p>
