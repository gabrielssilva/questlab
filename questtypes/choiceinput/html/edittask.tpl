<?php if(!empty($validations)) : ?>
<ul>
    <?php foreach($validations as &$list) : ?>
    <?php foreach($list as $part => &$choices) : ?>
    <li>
        <?php if($part == 'choices') : ?>
        <?php foreach($choices as $field => &$settings) : ?>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php
                switch($setting) {
                    case 'minlength': printf(_('Choice input is too short (min. %d chars)'), $value);
                    break;
                    case 'maxlength': printf(_('Choice input is too long (max. %d chars)'), $value);
                    break;
                    default: echo _('Choice input invalid');
                }
                ?>
            </li>
            <?php endforeach ?>
        </ul>
        <?php endforeach ?>
        <?php elseif($part == 'answer') : ?>
        <?php foreach($choices as $setting => &$value) : ?>
            <li>
                <?php
                switch($setting) {
                    case 'exist': printf(_('Please select correct choice'));
                    break;
                }
                ?>
            </li>
        <?php endforeach ?>
        <?php endif ?>
    </li>
    <?php endforeach ?>
    <?php endforeach ?>
</ul>
<?php endif ?>
<form method="post">
    <fieldset>
        <legend><?=_('Text')?></legend>
        <button id="add-field" type="button"><?=_('Add field')?></button><br />
        <textarea id="text" name="text"><?=$text?></textarea>
    </fieldset>
    <fieldset>
        <legend><?=_('Choice inputs')?></legend>
        <ul id="lists">
            <?php foreach($choiceLists as $listIndex => &$list) : ?>
            <li id="list-<?=$listIndex?>">
                <?php if(!empty($validations) && array_key_exists($listIndex, $validations) && !empty($validations[$listIndex]) && array_key_exists('answer', $validations[$listIndex]) && $validations[$listIndex]['answer'] !== true) : ?>
                <ul>
                    <?php foreach($validations[$listIndex]['answer'] as $setting => $value) : ?>
                    <li>
                        <?php
                        switch($setting) {
                            case 'exist': printf(_('Please select correct choice'));
                            break;
                        }
                        ?>
                    </li>
                    <?php endforeach ?>
                </ul>
                <?php endif ?>
                <ul>
                    <?php foreach($list['choices'] as $choiceIndex => &$choice) : ?>
                    <li>
                        <input type="radio" name="lists[<?=$listIndex?>][answer]" value="<?=$choiceIndex?>" <?php if($choiceIndex == $list['answer']) : ?>checked="checked"<?php endif ?> />
                        <input type="text" name="lists[<?=$listIndex?>][choices][<?=$choiceIndex?>]" required="required" value="<?=$choice?>" <?php if(!empty($validations) && array_key_exists($listIndex, $validations) && !empty($validations[$listIndex]) && array_key_exists($choiceIndex, $validations[$listIndex]['choices']) && $validations[$listIndex]['choices'][$choiceInput] !== true) : ?>class="invalid"<?php endif ?> />
                        <button class="remove-choice" type="button">−</button>
                    </li>
                    <?php endforeach ?>
                    <li>
                        <button class="add-choice" type="button">+</button>
                    </li>
                </ul>
            </li>
            <?php endforeach ?>
        </ul>
    </fieldset>
    <input type="submit" name="preview" value="<?=_('Preview')?>" />
    <input type="submit" name="save" value="<?=_('save')?>" />
</form>
<h2><?=_('Preview')?></h2>
<p>
    <?php $posStart = 0; ?>
    <?php foreach($choiceLists as &$list) : ?>
    <?php $posEnd = mb_strpos($text, '[choiceinput]', $posStart, 'UTF-8'); ?>
    <?=$t->t(mb_substr($text, $posStart, $posEnd-$posStart, 'UTF-8'))?>
    <select name="answers[]">
        <?php foreach($list['choices'] as &$choice) : ?>
        <option><?=$choice?></option>
        <?php endforeach ?>
    </select>
    <?php $posStart = $posEnd + mb_strlen('[choiceinput]', 'UTF-8'); ?>
    <?php endforeach ?>
    <?=$t->t(mb_substr($text, $posStart, mb_strlen($text, 'UTF-8')-$posStart, 'UTF-8'))?>
</p>

<script>
    var listIndex = <?=count($choiceLists)?>;
    var choiceIndices = new Array(<?=count($choiceLists)?>);
    <?php foreach($choiceLists as $index => &$list) : ?>
    choiceIndices[<?=$index?>] = <?=count($list)?>;
    <?php endforeach?>
    var listElement = '<ul><li><button class="add-choice" type="button">+</button></li></ul>';
    var inputElement =  '<input type="radio" name="lists[LISTINDEX][answer]" value="CHOICEINDEX" />' +
                '<input type="text" name="lists[LISTINDEX][choices][CHOICEINDEX]" required="required" />' +
                '<button class="remove-choice" type="button">−</button>';
    $("#add-field").click(function(event) {
        event.preventDefault();
        var caret = getCaret("text");
        insertAtCaret("text", caret, "[choiceinput]");
        updateFields();
    });
    $("#text").on('change keyup paste', function(event) {
        updateFields();
    });
    $(".add-choice").click(addChoice);
    $(".remove-choice").click(removeChoice);

    function updateFields()
    {
        var newCount = $("#text").val().split("[choiceinput]").length - 1;
        var oldCount = $("#lists > li").length;
        var caret = getCaret("text");
        var pos = $("#text").val().substring(0, caret).split("[choiceinput]").length - 1;
        if(newCount > oldCount)
        {
            // Add lists
            for(var i=oldCount; i<newCount; i++)
            {
                choiceIndices.push(0);
                var element = '<li id="list-'+listIndex+'">' + listElement + '</li>';
                if($("#lists > li").length > 0)
                {
                    if($("#lists > li").length > pos-1) {
                        $($("#lists > li")[pos-1]).before(element);
                    }
                    else {
                        $($("#lists > li")[pos-2]).after(element);
                    }
                }
                else {
                    $("#lists").append(element);
                }
                $("#list-"+listIndex+" .add-choice").click(addChoice);

                listIndex++;
            }
        }
        else if(newCount < oldCount)
        {
            // Remove lists
            for(var i=oldCount; i>newCount; i--) {
                $($("#lists > li")[pos]).remove();
            }
        }
    }

    function addChoice(event)
    {
        event.preventDefault();

        var parent = $(event.target).parent();
        var index = parent.parent().parent().attr('id').substring(5);
        var element = '<li>' + inputElement.replace(/LISTINDEX/g, index).replace(/CHOICEINDEX/g, choiceIndices[index]) + '</li>';
        $(event.target).parent().before(element);
        $(".remove-choice").click(removeChoice);

        choiceIndices[index]++;
    }
    function removeChoice(event)
    {
        event.preventDefault();
        $(event.target).parent().remove();
    }
</script>
