<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Charactertypes')?></a></li>
</ul>

<h1><?=_('Create new Charactertype')?></h1>
<?php if($validation !== true && !empty($validation)) : ?>
<ul class="validation">
    <?php foreach($validation as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
                    case 'charactertypename':
                        switch($setting) {
                            case 'minlength': printf(_('Name is too short (min. %d chars)'), $value);
                            break;
                            case 'maxlength': printf(_('Name is too long (max. %d chars)'), $value);
                            break;
                            case 'exist': echo _('Name already exists');
                            break;
                            default: echo _('Name invalid');
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
        <label for="name"><?=_('Name')?>:</legend>
        <input id="name" type="text" name="charactertypename" placeholder="<?=_('Name')?>" title="<?=_('Name')?>" required="required" maxlength="<?=$validationSettings['charactertypename']['maxlength']?>" value="<?=$name?>" <?=($validation !== true && array_key_exists('name', $validation)) ? 'class="invalid"' : null?> />
    </fieldset>
    <input type="submit" name="create" value="<?=_('create')?>" />
</form>
