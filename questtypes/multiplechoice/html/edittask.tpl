<?php if(!empty($validations)) : ?>
<ul>
    <?php foreach($validations as &$question) : ?>
    <li>
        <?php if(!empty($question['answers'])) : ?>
        <?php foreach($question['answers'] as &$answer) : ?>
        <ul>
            <?php foreach($answer as $setting => $value) : ?>
            <li>
                <?php
                switch($setting) {
                    case 'minlength': printf(_('Answer input is too short (min. %d chars)'), $value);
                    break;
                    case 'maxlength': printf(_('Answer input is too long (max. %d chars)'), $value);
                    break;
                    default: echo _('Answer input invalid');
                }
                ?>
            </li>
            <?php endforeach ?>
        </ul>
        <?php endforeach ?>
        <?php endif ?>
    </li>
    <?php endforeach ?>
</ul>
<?php endif ?>
<form method="post">
    <fieldset>
        <legend><?=_('Questions')?></legend>
        <ol id="questions">
            <?php foreach($questions as $questionIndex => &$question) : ?>
            <li id="question-<?=$questionIndex?>">
                <?=_('Question')?>:
                <textarea id="question-<?=$questionIndex?>-question" name="questions[<?=$questionIndex?>][question]"><?=$question['question']?></textarea>
                <script>
                    $(function() {
                        $("#question-<?=$questionIndex?>-question").markItUp(mySettings);
                    });
                </script>

                <?php if(!empty($validations) && array_key_exists($questionIndex, $validations) && !empty($validations[$questionIndex]) && $validations[$questionIndex]['answers'] !== true) : ?>
                <ul>
                    <?php foreach($validations[$questionIndex]['answers'] as &$answer) : ?>
                    <?php foreach($answer as $setting => $value) : ?>
                    <li>
                        <?php
                        switch($setting) {
                            case 'minlength': printf(_('Answer input is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Answer input is too long (max. %d chars)'), $value);
                            break;
                            default: echo _('Answer input invalid');
                        }
                        ?>
                    </li>
                    <?php endforeach ?>
                    <?php endforeach ?>
                </ul>
                <?php endif ?>

                <ul>
                    <?php foreach($question['answers'] as $answerIndex => &$answer) : ?>
                    <li>
                        <input id="question-<?=$questionIndex?>-answer-<?=$answerIndex?>-tick" type="checkbox" name="questions[<?=$questionIndex?>][answers][<?=$answerIndex?>][tick]" <?php if(array_key_exists('tick', $answer) && $answer['tick']) : ?>checked="checked"<?php endif ?> />
                        <label for="questions[<?=$questionIndex?>][answers][<?=$answerIndex?>][tick]">
                            <input id="question-<?=$questionIndex?>-answer-<?=$answerIndex?>" type="text" name="questions[<?=$questionIndex?>][answers][<?=$answerIndex?>][answer]" value="<?=$answer['answer']?>" <?php if(!empty($validations) && array_key_exists($questionIndex, $validations) && !empty($validations[$questionIndex]) && array_key_exists($answerIndex, $validations[$questionIndex]['answers']) && $validations[$questionIndex]['answers'][$answerIndex] !== true) : ?>class="invalid"<?php endif ?> />
                        </label>
                        <button class="remove-answer" type="button">−</button>
                    </li>
                    <?php endforeach ?>
                    <li>
                        <button class="add-answer" type="button">+</button>
                    </li>
                </ul>
                <button class="remove-question" type="button"><?=_('Remove question')?></button>
            </li>
            <?php endforeach ?>
            <li>
                <button class="add-question" type="button"><?=_('Add question')?></button>
            </li>
        </ol>
    </fieldset>
    <input type="submit" name="save" value="<?=_('save')?>" />
</form>

<script>
    var questionIndex = <?=count($questions)?>;
    var answerIndices = new Array(<?=count($questions)?>);
    <?php foreach($questions as $index => &$question) : ?>
    answerIndices[<?=$index?>] = <?=count($question['answers'])?>;
    <?php endforeach?>
    var questionElement =   '<?=_('Question')?>: <textarea id="questions-QUESTIONINDEX-question" name="questions[QUESTIONINDEX][question]"></textarea>' +
                '<ul><li><button class="add-answer" type="button">+</button></li></ul>' +
                '<button class="remove-question" type="button"><?=_('Remove question')?></button>';
    var answerElement = '<input id="question-QUESTIONINDEX-answer-ANSWERINDEX-tick" type="checkbox" name="questions[QUESTIONINDEX][answers][ANSWERINDEX][tick]" />' +
                '<label for="questions[QUESTIONINDEX][answers][ANSWERINDEX][tick]">' +
                '<input id="question-QUESTIONINDEX-answer-ANSWERINDEX" type="text" name="questions[QUESTIONINDEX][answers][ANSWERINDEX][answer]" value="" />' +
                '</label>' +
                '<button class="remove-answer" type="button">−</button>';

    $(".add-question").click(addQuestion);
    $(".remove-question").click(removeQuestion);
    $(".add-answer").click(addAnswer);
    $(".remove-answer").click(removeAnswer);

    function addQuestion(event)
    {
        event.preventDefault();

        answerIndices.push(0);
        var element = '<li id="question-'+questionIndex+'">' + questionElement.replace(/QUESTIONINDEX/g, questionIndex) + '</li>';
        $(event.target).parent().before(element);
        $("#question-"+questionIndex+" .remove-question").click(removeQuestion);
        $("#question-"+questionIndex+" .add-answer").click(addAnswer);
        $("#question-"+questionIndex+" .remove-answer").click(removeAnswer);
        $("#questions-"+questionIndex+"-question").markItUp(mySettings);

        questionIndex++;
    }
    function removeQuestion(event)
    {
        event.preventDefault();
        $(event.target).parent().remove();
    }
    function addAnswer(event)
    {
        event.preventDefault();

        var parent = $(event.target).parent();
        var index = parent.parent().parent().attr('id').substring(9);
        var element = '<li>' + answerElement.replace(/QUESTIONINDEX/g, index).replace(/ANSWERINDEX/g, answerIndices[index]) + '</li>';
        $(event.target).parent().before(element);
        $(".remove-answer").click(removeAnswer);

        answerIndices[index]++;
    }
    function removeAnswer(event)
    {
        event.preventDefault();
        $(event.target).parent().remove();
    }
</script>
