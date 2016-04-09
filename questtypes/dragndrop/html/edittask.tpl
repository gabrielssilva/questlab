<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'zone':
                        switch($setting) {
                            case 'error': printf(_('Error during file upload: %s'), $value);
                            break;
                            case 'mimetype': printf(_('File has wrong type “%s”'), $value);
                            break;
                            case 'size': echo _('File exceeds size maximum');
                            break;
                            default: echo _('File invalid');
                        }
                    break;
                } ?>
            </li>
            <?php endforeach ?>
        </ul>
    </li>
    <?php endforeach ?>
</ul>
<?php endif ?>
<form method="post" enctype="multipart/form-data">
    <?php if($step == 0) : ?>
    <fieldset>
        <legend><?=sprintf(_('Step %d'), 1)?>: <?=_('Field')?>:</legend>
        <?php if(!is_null($zone)) : ?>
        <div id="dropZone" style="width:<?=$zone['width']?>px; height:<?=$zone['height']?>px; background-image:url('<?=$linker->link(array('media','seminary',$seminary['url'],$zone['media']['url']))?>')">
        </div>
        <?php endif ?>
        <label for="zone"><?=_('Upload background image')?>:</label>
        <input type="file" id="zone" name="zone" />
        <p><?=_('Allowed file types')?>:</p>
        <ul>
            <?php foreach($mimetypes as &$mimetype) : ?>
            <li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
            <?php endforeach ?>
        </ul>
    </fieldset>
    <input type="submit" name="next" value="<?=_('next step')?>" />
    <?php elseif($step == 1) : ?>
    <fieldset>
        <legend><?=sprintf(_('Step %d'), 2)?>: <?=_('Drop-items')?></legend>
        <div id="dropZone" class="dev" style="position:relative; width:<?=$zone['width']?>px; height:<?=$zone['height']?>px; background-image:url('<?=$linker->link(array('media','seminary',$seminary['url'],$zone['media']['url']))?>')">
            <?php foreach($drops as $index => &$drop) : ?>
            <div id="drop<?=$index?>" ondragenter="onDragEnter(event)" ondragover="onDragOver(event)" ondragleave="onDragLeave(event)" ondrop="onDrop(event)" style="position:absolute; width:<?=$drop['width']?>px; height:<?=$drop['height']?>px; top:<?=$drop['top']?>px; left:<?=$drop['left']?>px;">
                <?=$index+1?>
                <i class="fa fa-arrows move"></i>
                <i class="fa fa-expand resize"></i>
            </div>
            <?php endforeach ?>
        </div>
        <ol id="drops">
            <?php foreach($drops as $index => &$drop) : ?>
            <li id="drop<?=$index?>-p">
                <span class="lstidx"><?=$index+1?></span>
                <input type="hidden" name="drops[<?=$index?>][id]" value="<?=$drop['id']?>" />
                <label><?=_('Size')?>:</label>
                <input type="number" id="drop<?=$index?>-w" name="drops[<?=$index?>][width]" value="<?=$drop['width']?>" min="45" max="<?=$zone['width']?>" /> x
                <input type="number" id="drop<?=$index?>-h" name="drops[<?=$index?>][height]" value="<?=$drop['height']?>" min="25" max="<?=$zone['height']?>" /> px
                <br />
                <label><?=_('Position')?>:</label>
                <input type="number" id="drop<?=$index?>-x" name="drops[<?=$index?>][x]" value="<?=$drop['left']?>" min="0" max="<?=$zone['width']?>" /> x
                <input type="number" id="drop<?=$index?>-y" name="drops[<?=$index?>][y]" value="<?=$drop['top']?>" min="0" max="<?=$zone['height']?>" /> px
                <br />
                <input type="button" class="remove-drop" value="−" />
            </li>
            <?php endforeach ?>
            <li>
                <input type="button" class="add-drop" value="+" />
            </li>
        </ol>
    </fieldset>
    <input type="submit" name="prev" value="<?=_('previous step')?>" />
    <input type="submit" name="next" value="<?=_('next step')?>" />
    <?php elseif($step == 2) : ?>
    <fieldset>
        <legend><?=sprintf(_('Step %d'), 3)?>: <?=_('Drag-items')?></legend>
        <div id="dropZone" class="dev" style="position:relative; width:<?=$zone['width']?>px; height:<?=$zone['height']?>px; background-image:url('<?=$linker->link(array('media','seminary',$seminary['url'],$zone['media']['url']))?>')">
            <?php foreach($drops as $index => &$drop) : ?>
            <div id="drop<?=$index?>" ondragenter="onDragEnter(event)" ondragover="onDragOver(event)" ondragleave="onDragLeave(event)" ondrop="onDrop(event)" style="position:absolute; width:<?=$drop['width']?>px; height:<?=$drop['height']?>px; top:<?=$drop['top']?>px; left:<?=$drop['left']?>px;">
                <?=$index+1?>
            </div>
            <?php endforeach ?>
        </div>
        <ul id="drags">
            <?php foreach($drags as $dragIndex => &$drag) : ?>
            <li id="drag<?=$dragIndex?>">
                <?php if($dragsValidation !== true && array_key_exists($dragIndex, $dragsValidation) && $dragsValidation[$dragIndex] !== true) : ?>
                <ul class="validation">
                    <?php foreach($dragsValidation[$dragIndex] as $field => &$settings) : ?>
                    <li>
                        <ul>
                            <?php foreach($settings as $setting => $value) : ?>
                            <li>
                                <?php switch($field) {
                                    case 'file':
                                        switch($setting) {
                                            case 'error': printf(_('Error during file upload: %s'), $value);
                                            break;
                                            case 'mimetype': printf(_('File has wrong type “%s”'), $value);
                                            break;
                                            case 'size': echo _('File exceeds size maximum');
                                            break;
                                            default: echo _('File invalid');
                                        }
                                    break;
                                } ?>
                            </li>
                            <?php endforeach ?>
                        </ul>
                    </li>
                    <?php endforeach ?>
                </ul>
                <?php endif ?>
                <input type="hidden" name="drags[<?=$dragIndex?>][id]" value="<?=$drag['id']?>" />
                <img id="drag<?=$dragIndex?>" src="<?=$linker->link(array('media','seminary',$seminary['url'],$drag['media']['url']))?>" />
                <input type="file" name="drags[<?=$dragIndex?>]" />
                <?php foreach($drops as $dropIndex => &$drop) : ?>
                <input type="checkbox" id="drag<?=$dragIndex?>-drop<?=$dropIndex?>" name="drags[<?=$dragIndex?>][drops][<?=$drop['id']?>]" <?php if(in_array($drop['id'], $drag['drops'])) : ?>checked="checked"<?php endif ?> />
                <label for="drag<?=$dragIndex?>-drop<?=$dropIndex?>"><?=$dropIndex+1?></label>
                <?php endforeach ?>
                <br />
                <input type="button" class="remove-drag" value="−" />
            </li>
            <?php endforeach?>
            <li>
                <input type="button" class="add-drag" value="+" />
            </li>
        </ul>
        <p><?=_('Allowed file types')?>:</p>
        <ul>
            <?php foreach($mimetypes as &$mimetype) : ?>
            <li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
            <?php endforeach ?>
        </ul>
    </fieldset>
    <input type="submit" name="prev" value="<?=_('previous step')?>" />
    <input type="submit" name="next" value="<?=_('save')?>" />
    <?php endif ?>
    <input type="hidden" name="step" value="<?=$step?>" />
</form>

<script>
    var dropIndex = <?=count($drops)?>;
    var dragIndex = <?=count($drags)?>;
    var cssProps = {w: "width", h: "height", x: "left", y: "top"};
    var draggable = {
        containment: "parent",
        handle: 'i.move',
        drag: function(event, ui) {
            var id = ui.helper.prop('id').substr(4);
            $('#drop' + id + '-x').prop('value', ui.position.left);
            $('#drop' + id + '-y').prop('value', ui.position.top);
        }
    };
    var resizable = {
        minWidth: 45,
        minHeight: 25,
        handles: {
            se: 'i.resize'
        },
        resize: function(event, ui) {
            var id = ui.helper.prop('id').substr(4);
            $('#drop' + id + '-w').prop('value', ui.size.width);
            $('#drop' + id + '-h').prop('value', ui.size.height);
        }
    };
    var dropElement =
        '<div id="dropDROPINDEX" style="position:absolute; width:75px; height:50px; top:0; left:0;">' +
        'DROPINDEX1' +
        '<i class="fa fa-arrows move"></i>' +
        '<i class="fa fa-expand resize"></i>' +
        '</div>';
    var dropPropElement =
        '<li id="dropDROPINDEX-p">' +
        '<span class="lstidx">DROPINDEX1</span>' +
        "<label><?=_('Size')?>:</label>" +
        '<input type="number" id="dropDROPINDEX-w" name="drops[DROPINDEX][width]" value="45" min="45" max="<?=$zone['width']?>" /> x' +
        '<input type="number" id="dropDROPINDEX-h" name="drops[DROPINDEX][height]" value="25" min="25" max="<?=$zone['height']?>" /> px' +
        '<br />' +
        "<label><?=_('Position')?>:</label>" +
        '<input type="number" id="dropDROPINDEX-x" name="drops[DROPINDEX][x]" value="0" min="0" max="<?=$zone['width']?>" /> x' +
        '<input type="number" id="dropDROPINDEX-y" name="drops[DROPINDEX][y]" value="0" min="0" max="<?=$zone['height']?>" /> px' +
        '<br /><input type="button" class="remove-drop" value="−" />' +
        '</li>';
    var dragElement =
        '<li id="dragDRAGINDEX">' +
        '<input type="file" name="drags[DRAGINDEX]" />' +
        <?php foreach($drops as $dropIndex => &$drop) : ?>
        '<input type="checkbox" id="dragDRAGINDEX-drop<?=$dropIndex?>" name="drags[DRAGINDEX][drops][<?=$drop['id']?>]" />\n' +
        '<label for="dragDRAGINDEX-drop<?=$dropIndex?>"><?=$dropIndex+1?></label>\n' +
        <?php endforeach ?>
        '<br /><input type="button" class="remove-drag" value="−" /></li>';

    function addDrop(event) {
        var element = dropElement.replace(/DROPINDEX1/g, dropIndex+1).replace(/DROPINDEX/g, dropIndex);
        $("#dropZone").append(element);
        var propElement =  dropPropElement.replace(/DROPINDEX1/g, dropIndex+1).replace(/DROPINDEX/g, dropIndex);
        $(event.target).parent().before(propElement);

        $("#drop"+dropIndex).draggable(draggable);
        $("#drop"+dropIndex).resizable(resizable);
        $("#drop"+dropIndex+"-p").change(changeDrop);
        $("#drop"+dropIndex+"-p .remove-drop").click(removeDrop);

        event.preventDefault();
        dropIndex++;
    }
    function changeDrop(event) {
        var id = event.target.id.substring(4, event.target.id.length-2);
        var type = event.target.id.substr(event.target.id.length-1);
        $("#drop" + id).css(cssProps[type], $(event.target).val()+'px');
    }
    function removeDrop(event) {
        var element = $(event.target).parent();
        var id = element.attr('id').substring(4, element.attr('id').length-2);
        $("#drop" + id).remove();
        element.remove();

        event.preventDefault();
    }
    function addDrag(event) {
        var element = dragElement.replace(/DRAGINDEX/g, dragIndex);
        $(event.target).parent().before(element);

        $("#drag"+dragIndex+" .remove-drag").click(removeDrag);

        event.preventDefault();
        dragIndex++;
    }
    function removeDrag(event) {
        var element = $(event.target).parent();
        element.remove();

        event.preventDefault();
    }

    $(function() {
        $("#dropZone.dev div").draggable(draggable);
        $("#dropZone.dev div").resizable(resizable);
        $("#drops li").change(changeDrop);
        $(".add-drop").click(addDrop);
        $(".remove-drop").click(removeDrop);
        $(".add-drag").click(addDrag);
        $(".remove-drag").click(removeDrag);
    });
</script>
