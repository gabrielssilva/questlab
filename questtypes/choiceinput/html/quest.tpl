<form method="post">
    <p>
        <?php $posStart = 0; ?>
        <?php foreach($choiceLists as &$list) : ?>
        <?php $posEnd = mb_strpos($task['text'], '[choiceinput]', $posStart, 'UTF-8'); ?>
        <?=$t->t(mb_substr($task['text'], $posStart, $posEnd-$posStart, 'UTF-8'))?>
        <select name="answers[]">
            <?php foreach($list['values'] as &$choice) : ?>
            <option value="<?=$choice['id']?>" <?php if(array_key_exists('answer', $list) && $list['answer'] == $choice['id']) : ?>selected="selected"<?php endif ?>><?=$choice['text']?></option>
            <?php endforeach ?>
        </select>
        <?php $posStart = $posEnd + mb_strlen('[choiceinput]', 'UTF-8'); ?>
        <?php endforeach ?>
        <?=$t->t(mb_substr($task['text'], $posStart, mb_strlen($task['text'], 'UTF-8')-$posStart, 'UTF-8'))?>
    </p>
    <input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
