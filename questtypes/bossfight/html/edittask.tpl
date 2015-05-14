<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'bossname':
                        switch($setting) {
                            case 'minlength': printf(_('Name is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Name is too long (max. %d chars)'), $value);
                            break;
                            case 'regex': echo _('Name contains illegal characters');
                            break;
                            default: echo _('Name invalid');
                        }
                    break;
                    case 'bossimage':
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
        <legend><?=sprintf(_('Step %d'), 1)?>: <?=_('Boss-Fight')?></legend>
        <label><?=_('Boss name')?></label>
        <input type="text" name="bossname" value="<?=$bossname?>" maxlength="<?=$validationSettings['bossname']['maxlength']?>" <?=($validation !== true && array_key_exists('bossname', $validation)) ? 'class="invalid"' : null ?> /><br />
        <label><?=_('Boss image')?></label>
        <input type="file" name="bossimage" /><br />
        <p><?=_('Allowed file types')?>:</p>
        <ul>
            <?php foreach($mimetypes as &$mimetype) : ?>
            <li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
            <?php endforeach ?>
        </ul>
        <label><?=_('Character lives')?></label>
        <input type="number" name="lives_character" value="<?=$livesCharacter?>" <?=($validation !== true && array_key_exists('lives_character', $validation)) ? 'class="invalid"' : null ?> /><br />
        <label><?=_('Boss lives')?></label>
        <input type="number" name="lives_boss" value="<?=$livesBoss?>" <?=($validation !== true && array_key_exists('lives_boss', $validation)) ? 'class="invalid"' : null ?> />
    </fieldset>
    <input type="submit" name="next" value="<?=_('next step')?>" />
    <?php elseif($step == 1) : ?>
    <fieldset id="bosstree">
        <legend><?=sprintf(_('Step %d'), 2)?>: <?=_('Stages')?></legend>
        <?php foreach($tree as $i => $v) : ?>
        <div class="bosstreerow">
            <?php foreach($v as $j => $h) : ?>
            <div id="bti-<?=$i?>-<?=$j?>" class="bosstreeitem" style=" width:<?=sprintf('%.3F', 100/count($v))?>%">
                <span class="bosstreelabel">
                    <?php if($h['lives_character'] > 0) : ?>
                    <?php foreach(range(1,$h['lives_character']) as $l) : ?>
                    <i class="fa fa-heart fa-fw char"></i>
                    <?php endforeach ?>
                    <?php endif ?>
                    <?php if($h['lives_boss'] > 0) : ?>
                    <?php foreach(range(1,$h['lives_boss']) as $l) : ?>
                    <i class="fa fa-heart fa-fw boss"></i>
                    <?php endforeach ?>
                    <?php endif ?>
                </span>
                <div id="line-<?=$i?>-<?=$j?>" class="bosstreeline"></div>
            </div>
            <?php endforeach ?>
        </div>
        <?php endforeach ?>
    </fieldset>
    <fieldset id="stages">
        <legend><?=_('Selected stage')?></legend>
        <?php foreach($tree as $i => $v) : ?>
        <?php foreach($v as $j => $h) : ?>
        <div id="stage-<?=$i?>-<?=$j?>" class="bossstage">
            <div class="cf">
                <section class="opponent">
                    <p class="fwb"><?=$character['name']?></p>
                    <p class="portrait"><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']))?>" class="hero" /></p>
                    <p>
                        <?php if($h['lives_character'] > 0) : ?>
                        <?php foreach(range(1,$h['lives_character']) as $l) : ?>
                        <i class="fa fa-heart fa-fw char"></i>
                        <?php endforeach ?>
                        <?php else : ?>
                        <?=_('lost')?>
                        <?php endif ?>
                    </p>
                </section>
                <section class="opponent">
                    <p class="fwb"><?=$fight['bossname']?></p>
                    <p class="portrait"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$fight['bossmedia']['url']))?>" class="boss" /></p>
                    <p>
                        <?php if($h['lives_boss'] > 0) : ?>
                        <?php foreach(range(1,$h['lives_boss']) as $l) : ?>
                        <i class="fa fa-heart fa-fw boss"></i>
                        <?php endforeach ?>
                        <?php else : ?>
                        <b><?=_('lost')?></b>
                        <?php endif ?>
                    </p>
                </section>
            </div>
            <textarea name="stages[<?=$i?>][<?=$j?>][question]"><?=$h['stage']['text']?></textarea>
            <?php if(array_key_exists('childstages', $h)) : ?>
            <ul class="bossfight cf">
                <?php foreach($h['childstages'] as &$childStage) : ?>
                <li class="option">
                    <textarea name="stages[<?=$i?>][<?=$j?>]"><?php if(!empty($childStage)) : ?><?=\hhu\z\Utils::t($childStage['question'])?><?php endif ?></textarea>
                </li>
                <?php endforeach ?>
            </ul>
            <?php endif ?>
        </div>
        <?php endforeach ?>
        <?php endforeach ?>
    </fieldset>
    <input type="submit" name="prev" value="<?=_('previous step')?>" />
    <input type="submit" name="next" value="<?=_('save')?>" />
    <input type="hidden" name="step" value="<?=$step?>" />
    <?php endif ?>
</form>

<script>
    function drawLine(targetItemId, sourceItemId, lineId)
    {
        var sourceItem = $('#'+sourceItemId);
        var targetItem = $('#'+targetItemId);
        var sourcePoint = sourceItem.position();
        sourcePoint.left = sourcePoint.left + sourceItem.width()/2;
        sourcePoint.top = sourcePoint.top + sourceItem.height();
        var targetPoint = targetItem.position();
        targetPoint.left = targetPoint.left + targetItem.width()/2;
        var line = $('#'+lineId);

        var length = Math.sqrt(
            Math.pow(targetPoint.left - sourcePoint.left, 2) +
            Math.pow(targetPoint.top - sourcePoint.top, 2)
        );
        var angle = 180 / Math.PI * Math.acos((targetPoint.left - sourcePoint.left) / length);

        line.css('width', Math.floor(length)+'px');
        line.css('left', sourcePoint.left+'px');
        line.css('top', sourcePoint.top+'px');
        line.css('transform-origin', 'top left');
        line.css('transform', 'rotate('+angle+'deg)');
    }

    function drawLines()
    {
        <?php foreach($tree as $i => $v) : ?>
        <?php foreach($v as $j => $h) : ?>
        <?php if($i > 0) : ?>
        drawLine('bti-<?=$i?>-<?=$j?>', 'bti-<?=$i-1?>-<?=floor($j/2)?>', 'line-<?=$i?>-<?=$j?>');
        <?php endif ?>
        <?php endforeach ?>
        <?php endforeach ?>
    }

    function showSelectedStage()
    {
        $("#bosstree span.ui-selected").each(function(index) {
            var id = 'stage-' + $(this).parent().attr('id').substr(4);
            // hide current stage
            $("#stages div.bossstage").css('display', 'none');
            // show new stage
            $("#"+id).css('display', 'block');
        });
    }

    var resizeTimer;
    $(function()
    {
        $(window).resize(function() {
            clearTimeout(resizeTimer);
            resizeTimer = setTimeout(drawLines, 100);
        });
        drawLines();
        $('#bosstree').selectable({
            filter: " span.bosstreelabel",
            selected: function(event, ui) {
                showSelectedStage();
            }
        });
        $("#bti-0-0 span.bosstreelabel").addClass('ui-selected');
        showSelectedStage();
    });
</script>
