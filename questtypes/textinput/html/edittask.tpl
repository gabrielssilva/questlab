<?php if(!empty($validations)) : ?>
<ul>
    <?php foreach($validations as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php
                switch($setting) {
                    case 'regex': echo _('Regex invalid');
                    break;
                    default: echo _('Regex invalid');
                }
                ?>
            </li>
            <?php endforeach ?>
        </ul>
    </li>
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
        <legend><?=_('Fields')?></legend>
        <ul id="fields">
            <?php foreach($fields as $index => &$field) : ?>
            <li>
                <select name="fields[<?=$index?>][size]">
                    <?php foreach($fieldSizes as &$size) : ?>
                    <option value="<?=$size['size']?>" <?php if($fields[$index]['size'] == $size['size']) : ?>selected="selected"<?php endif ?>><?=$size['size']?></option>
                    <?php endforeach ?>
                </select>
                <input type="text" name="fields[<?=$index?>][regex]" required="required" placeholder="/regex/i" value="<?=$field['regex']?>" <?php if(!empty($validations) && array_key_exists($index, $validations)) : ?>class="invalid"<?php endif ?> />
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
    <?php foreach($fields as &$field) : ?>
    <?php $posEnd = mb_strpos($text, '[textinput]', $posStart, 'UTF-8'); ?>
    <?=$t->t(mb_substr($text, $posStart, $posEnd-$posStart, 'UTF-8'))?>
    <input type="text" name="answers[]" value="<?=(array_key_exists('answer', $field)) ? $field['answer'] : ''?>" <?php if($field['size'] != 'default') : ?>class="<?=$field['size']?>"<?php endif ?> />
    <?php $posStart = $posEnd + mb_strlen('[textinput]', 'UTF-8'); ?>
    <?php endforeach ?>
    <?=$t->t(mb_substr($text, $posStart, mb_strlen($text, 'UTF-8')-$posStart, 'UTF-8'))?>
</p>

<script>
    $(function() {
        $("#text").markItUp(mySettings);
    });
    var index = <?=count($fields)?>;
    var selectElement = '<select name="fields[INDEX][size]">' +
        <?php foreach($fieldSizes as &$size) : ?>
        '<option value="<?=$size['size']?>"><?=$size['size']?></option>' +
        <?php endforeach ?>
        '</select>';
    var inputElement = '<input type="text" name="fields[INDEX][regex]" required="required" placeholder="/regex/i" />';
    $("#add-field").click(function(event) {
        event.preventDefault();
        var caret = getCaret("text");
        insertAtCaret("text", caret, "[textinput]");
        updateFields();
    });
    $("#text").on('change keyup paste', function(event) {
        updateFields();
    });

    function updateFields()
    {
        var newCount = $("#text").val().split("[textinput]").length - 1;
        var oldCount = $("#fields > li").length;
        var caret = getCaret("text");
        var pos = $("#text").val().substring(0, caret).split("[textinput]").length - 1;
        if(newCount > oldCount)
        {
            // Add fields
            for(var i=oldCount; i<newCount; i++)
            {
                index++;
                var element = '<li>' + selectElement.replace('INDEX', index) + inputElement.replace('INDEX', index) + '</li>';
                if($("#fields > li").length > 0)
                {
                    if($("#fields > li").length > pos-1) {
                        $($("#fields > li")[pos-1]).before(element);
                    }
                    else {
                        $($("#fields > li")[pos-2]).after(element);
                    }
                }
                else {
                    $("#fields").append(element);
                }
            }
        }
        else if(newCount < oldCount)
        {
            // Remove fields
            for(var i=oldCount; i>newCount; i--) {
                $($("#fields > li")[pos]).remove();
            }
        }
    }
</script>
