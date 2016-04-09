<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>

<h1><?=sprintf(_('Edit %s-Achievement'), $groupsgroup['name'])?></h1>
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
                } ?>
            </li>
            <?php endforeach ?>
        </ul>
    </li>
    <?php endforeach ?>
</ul>
<?php endif ?>
<form method="post" class="logreg" enctype="multipart/form-data">
    <fieldset>
        <legend><?=_('Icon')?></legend>
        <?php if(!is_null($achievement['achievementsmedia_id'])) : ?>
        <img src="<?=$linker->link(array('media','charactergroupsachievement',$seminary['url'],$groupsgroup['url'],$achievement['url']))?>" />
        <?php endif ?>
        <input type="file" name="icon" />
        <p><?=_('Allowed file types')?>:</p>
        <ul>
            <?php foreach($mimetypes as &$mimetype) : ?>
            <li><?=sprintf(_('%s-files'), strtoupper(explode('/',$mimetype['mimetype'])[1]))?> <?php if($mimetype['size'] > 0) : ?>(<?=_('max.')?> <?=round($mimetype['size']/(1024*1024),2)?> MiB)<?php endif ?></li>
            <?php endforeach ?>
        </ul>
    </fieldset>
    <fieldset>
        <label for="title"><?=_('Title')?>:</label>
        <input id="title" type="text" name="title" placeholder="<?=_('Title')?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=(array_key_exists('title', $validation)) ? 'class="invalid"' : null?> /><br />
        <label for="description"><?=_('Description')?>:</label>
        <textarea id="description" name="description"><?=$description?></textarea><br />
    </fieldset>
    <input type="submit" name="edit" value="<?=_('save')?>" />
</form>
