<form method="post" class="multiplechoice">
    <ol class="mchoice">
        <?php foreach($answers as $i => &$answer) : ?>
        <li class="cf">
            <input type="checkbox" id="answer[<?=$i?>]" name="answer[<?=$i?>]" value="true" <?php if(array_key_exists('submission', $answer) && $answer['submission'] === true) : ?>checked="checked"<?php endif ?> <?php if($tried) : ?>disabled="disabled"<?php endif ?>/>
            <label for="answer[<?=$i?>]"><?=$t->t($answer['answer'])?></label>
        </li>
        <?php endforeach ?>
    </ol>
<?php if(!$tried) : ?>
    <input type="submit" name="submit" value="<?=_('solve')?>" />
<?php endif ?>
</form>
