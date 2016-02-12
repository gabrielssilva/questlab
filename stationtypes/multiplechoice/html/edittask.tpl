<form method="post">
    <fieldset>
        <legend><?=_('Question')?></legend>
        <?=$t->t($task)?>
    </fieldset>
    <fieldset>
        <legend><?=_('Answers')?></legend>
        <ol id="answers">
            <?php foreach($answers as $answerIndex => &$answer) : ?>
            <li>
                <?=_('Answer')?>:<br />
                <label>
                    <input id="answer-<?=$answerIndex?>-tick" type="checkbox" name="answers[<?=$answerIndex?>][tick]" <?php if(array_key_exists('tick', $answer) && $answer['tick']) : ?>checked="checked"<?php endif ?> />
                    <?=_('correct')?>
                </label>
                <textarea id="answer-<?=$answerIndex?>" name="answers[<?=$answerIndex?>][answer]" class="answer">
<?=$answer['answer']?>
                </textarea>
                <button class="remove-answer" type="button">−</button>
                <hr />
            </li>
            <?php endforeach ?>
            <li>
                <button class="add-answer" type="button">+</button>
            </li>
        </ol>
    </fieldset>
    <input type="submit" name="save" value="<?=_('save')?>" />
</form>

<script>
    // Text editors
    $('textarea.answer').markItUp(mySettings);

    // Answers
    var answerIndex = <?=count($answers)?>;
    var answerElement = '<label><input id="answer-ANSWERINDEX-tick" type="checkbox" name="answers[ANSWERINDEX][tick]" /> <?=_('correct answer')?></label>' +
                        '<textarea id="answer-ANSWERINDEX" name="answers[ANSWERINDEX][answer]" class="answer"></textarea>' +
                        '<button class="remove-answer" type="button">−</button>' +
                        '<hr />';
    $(".add-answer").click(addAnswer);
    $(".remove-answer").click(removeAnswer);
    function addAnswer(event)
    {
        event.preventDefault();

        var parent = $(event.target).parent();
        var element = '<li>' + answerElement.replace(/ANSWERINDEX/g, answerIndex) + '</li>';
        parent.before(element);
        $("#answers li:nth-last-child(2) .remove-answer").click(removeAnswer);
        $('#answers li:nth-last-child(2) textarea.answer').markItUp(mySettings);

        answerIndex++;
    }
    function removeAnswer(event)
    {
        event.preventDefault();
        $(event.target).parent().remove();
    }
</script>
