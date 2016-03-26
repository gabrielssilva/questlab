<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Charactertypes')?></a></li>
</ul>

<h1><?=_('Edit Charactertype')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'title_male':
                        switch($setting) {
                            case 'minlength': printf(_('Male title is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Male title is too long (max. %d chars)'), $value);
                            break;
                            case 'exist': echo _('Male title already exists');
                            break;
                            default: echo _('Male title invalid');
                        }
                    break;
                    case 'title_female':
                        switch($setting) {
                            case 'minlength': printf(_('Female title is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Female title is too long (max. %d chars)'), $value);
                            break;
                            case 'exist': echo _('Female title already exists');
                            break;
                            default: echo _('Female title invalid');
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
<form method="post">
    <fieldset>
        <label for="title_male"><?=_('Male title')?>:</label>
        <input id="title_male" type="text" name="title_male" placeholder="<?=_('Male title')?>" title="<?=_('Male title')?>" required="required" maxlength="<?=$validationSettings['title_male']['maxlength']?>" value="<?=$titleMale?>" <?=($validation !== true && array_key_exists('title_male', $validation)) ? 'class="invalid"' : null?> />
        <br />
        <label for="title_female"><?=_('Female title')?>:</label>
        <input id="title_female" type="text" name="title_female" placeholder="<?=_('Female title')?>" title="<?=_('Female title')?>" required="required" maxlength="<?=$validationSettings['title_female']['maxlength']?>" value="<?=$titleFemale?>" <?=($validation !== true && array_key_exists('title_female', $validation)) ? 'class="invalid"' : null?> />
    </fieldset>
    <input type="submit" name="edit" value="<?=_('save')?>" />
</form>
