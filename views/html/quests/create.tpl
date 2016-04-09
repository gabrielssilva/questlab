<?=$moodpic?>
<?=$questgroupshierarchypath?>

<h1><?=_('Create Quest')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'media':
                        switch($setting) {
                            case 'error': printf(_('Error during picture upload: %s'), $value);
                            break;
                            case 'mimetype': printf(_('Picture has wrong type “%s”'), $value);
                            break;
                            case 'size': echo _('Picture exceeds size maximum');
                            break;
                            default: echo _('Picture invalid');
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
<form method="post" enctype="multipart/form-data">
    <fieldset>
        <legend><?=_('Picture')?></legend>
        <input type="file" name="media" accept="<?=implode(',', array_map(function($m) { return $m['mimetype']; }, $mimetypes))?>" />
        <p><?=_('Allowed file types')?>:</p>
        <ul>
            <?php foreach($mimetypes as &$mimetype) : ?>
            <li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
            <?php endforeach ?>
        </ul>
    </fieldset>
    <fieldset>
        <label for="title"><?=_('Title')?>:</label>
        <input id="title" type="text" name="title" value="<?=$title?>" placeholder="<?=_('Title')?>" maxlength="<?=$validationSettings['title']['maxlength']?>" <?=(array_key_exists('title', $validation)) ? 'class="invalid"' : null?> /><br />
        <label for="xps"><?=_('XPs')?>:</label>
        <input id="xps" type="number" name="xps" placeholder="<?=_('XPs')?>" title="<?=_('XPs')?>" pattern="<?=substr($validationSettings['xps']['regex'],1,strrpos($validationSettings['xps']['regex'],$validationSettings['xps']['regex'][0])-1)?>" value="<?=$xps?>" <?=(array_key_exists('xps', $validation)) ? 'class="invalid"' : null?> /><br />
        <label for="questtype"><?=('Questtype')?>:</label>
        <select id="questtype" name="questtype">
            <?php foreach($questtypes as &$questtype) : ?>
            <option value="<?=$questtype['url']?>" <?php if($questtype['selected']) : ?>selected="selected"<?php endif ?>>
                <?php switch($questtype['classname']) {
                    case null: echo _('Questtype Empty');
                    break;
                    case 'bossfight': echo _('Questtype bossfight');
                    break;
                    case 'choiceinput': echo _('Questtype choiceinput');
                    break;
                    case 'crossword': echo _('Questtype crossword');
                    break;
                    case 'dragndrop': echo _('Questtype dragndrop');
                    break;
                    case 'multiplechoice': echo _('Questtype multiplechoice');
                    break;
                    case 'submit': echo _('Questtype submit');
                    break;
                    case 'textinput': echo _('Questtype textinput');
                    break;
                } ?>
            </option>
            <?php endforeach ?>
        </select>
    </fieldset>
    <fieldset>
        <label for="entrytext"><?=_('Entry text')?>:</label><br />
        <textarea id="entrytext" name="entrytext" placeholder="<?=_('Entry text')?>"><?=$entryText?></textarea><br />
        <label for="task"><?=_('Task')?>:</label><br />
        <textarea id="task" name="task" placeholder="<?=('Task')?>"><?=$task?></textarea><br />
        <label for="wrongtext"><?=_('Wrong text')?>:</label><br />
        <textarea id="wrongtext" name="wrongtext" placeholder="<?=_('Wrong text')?>"><?=$wrongText?></textarea><br />
    </fieldset>
    <input type="submit" name="create" value="<?=_('create')?>" />
</form>
<script>
    $(function() {
        $("#entrytext").markItUp(mySettings);
        $("#task").markItUp(mySettings);
        $("#wrongtext").markItUp(mySettings);
    });
</script>
