<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','index',$seminary['url']))?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>

<h1><?=sprintf(_('Edit %s-Quest'), $groupsgroup['name'])?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'icon':
                        switch($setting) {
                            case 'error': printf(_('Error during icon upload: %s'), $value);
                            break;
                            case 'mimetype': printf(_('Icon has wrong type “%s”'), $value);
                            break;
                            case 'size': echo _('Icon exceeds size maximum');
                            break;
                            default: echo _('Icon invalid');
                        }
                    break;
                    case 'title':
                        switch($setting) {
                            case 'minlength': printf(_('Title is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Title is too long (max. %d chars)'), $value);
                            break;
                            case 'regex': echo _('Title contains illegal characters');
                            break;
                            case 'exist': echo _('Title already exists');
                            break;
                            default: echo _('Title invalid');
                        }
                    break;
                    case 'xps':
                        switch($setting) {
                            case 'minlength': printf(_('XPs not set'), $value);
                            break;
                            case 'regex': echo _('XPs contain illegal characters');
                            break;
                            default: echo _('XPs invalid');
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
<form method="post" action="" class="logreg" enctype="multipart/form-data">
    <fieldset>
        <legend><?=_('Icon')?></legend>
        <img src="<?=$linker->link(array('media','charactergroupsquest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" /><br />
        <input type="file" name="icon" />
        <p><?=_('Allowed file types')?>:</p>
        <ul>
            <?php foreach($mimetypes as &$mimetype) : ?>
            <li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
            <?php endforeach ?>
        </ul>
    </fieldset>
    <fieldset>
        <input type="checkbox" id="public" name="public" <?php if($public) : ?>checked="checked"<?php endif ?> />
        <label for="public"><?=_('public')?></label>
        <label for="title"><?=_('Title')?>:</label>
        <input type="text" id="title" name="title" placeholder="<?=_('Title')?>" title="<?=_('Title')?>" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=(array_key_exists('title', $validation)) ? 'class="invalid"' : null?> />
        <label for="xps"><?=_('XPs')?>:</label>
        <input type="number" id="xps" name="xps" placeholder="<?=_('XPs')?>" title="<?=_('XPs')?>" pattern="<?=substr($validationSettings['xps']['regex'],1,strrpos($validationSettings['xps']['regex'],$validationSettings['xps']['regex'][0])-1)?>" value="<?=$xps?>" <?=(array_key_exists('xps', $validation)) ? 'class="invalid"' : null?> />
        <label for="questgroup"><?=_('Questgroup')?></label>
        <select id="questgroup" name="questgroup">
            <?php foreach($questgroups as &$questgroup) : ?>
            <option value="<?=$questgroup['url']?>" <?php if(array_key_exists('selected', $questgroup) && $questgroup['selected']) : ?>selected="selected"<?php endif ?>><?=$questgroup['title']?></option>
            <?php endforeach ?>
        </select>
        <label for="description"><?=_('Description')?>:</label>
        <textarea id="description" name="description" placeholder="<?=_('Description')?>"><?=$description?></textarea>
        <label for="rules"><?=_('Rules')?>:</label>
        <textarea id="rules" name="rules" placeholder="<?=_('Rules')?>"><?=$rules?></textarea>
        <label for="wonText"><?=_('Won-text')?>:</label>
        <textarea id="wonText" name="wonText" placeholder="<?=_('Won-text')?>"><?=$wonText?></textarea>
        <label for="lostText"><?=_('Lost-text')?>:</label>
        <textarea id="lostText" name="lostText" placeholder="<?=_('Lost-text')?>"><?=$lostText?></textarea>
    </fieldset>
    <input type="submit" name="edit" value="<?=_('edit')?>" />
</form>
<script>
    $(function() {
        $("#description").markItUp(mySettings);
        $("#rules").markItUp(mySettings);
        $("#wonText").markItUp(mySettings);
        $("#lostText").markItUp(mySettings);
    });
</script>
