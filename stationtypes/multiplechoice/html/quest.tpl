<form method="post" class="multiplechoice">
    <ol class="mchoice">
        <?php foreach($answers as $i => &$answer) : ?>
        <li class="cf">
            <input type="checkbox" id="answer[<?=$i?>]" name="answer[<?=$i?>]" value="true" />
            <label for="answer[<?=$i?>]"><?=$t->t($answer['answer'])?></label>
        </li>
        <?php endforeach ?>
    </ol>
    <input type="submit" name="submit" value="<?=_('solve')?>" />
</form>
