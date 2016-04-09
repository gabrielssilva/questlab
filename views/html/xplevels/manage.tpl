<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><?=_('Manage XP-levels')?></h1>

<h2><?=_('Edit XP-levels')?></h2>
<form method="post">
    <ul>
        <?php foreach($xplevels as &$xplevel) : ?>
        <li>
            <?php if($validations['edit'] !== true && array_key_exists($xplevel['id'], $validations['edit']) && $validations['edit'][$xplevel['id']] !== true) : ?>
            <ul class="validation">
                <?php foreach($validations['edit'][$xplevel['id']] as $field => &$settings) : ?>
                <li>
                    <ul>
                        <?php foreach($settings as $setting => $value) : ?>
                        <li>
                            <?php switch($field) {
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
            <?=_('Level')?> <?=$xplevel['level']?>:
            <input id="xplevel-<?=$xplevel['id']?>-xps" type="number" name="xplevels[<?=$xplevel['id']?>][xps]" value="<?=$xplevelsValues[$xplevel['id']]['xps']?>" <?=($validations['edit'] !== true && array_key_exists($xplevel['id'], $validations['edit']) && $validations['edit'][$xplevel['id']] !== true && array_key_exists('xps', $validations['edit'][$xplevel['id']])) ? 'class="invalid"' : null?> />
            <label for="xplevel-<?=$xplevel['id']?>-xps"><?=_('XPs')?></label>
            <input id="xplevel-<?=$xplevel['id']?>-delete" type="checkbox" name="deletes[<?=$xplevel['id']?>]" <?php if(array_key_exists($xplevel['id'], $deletes)) : ?>checked="checked"<?php endif ?> />
            <label for="xplevel-<?=$xplevel['id']?>-delete"><?=_('delete')?></label><br />
        </li>
        <?php endforeach ?>
    </ul>
    <input type="submit" name="edit" value="<?=_('save')?>" />
</form>

<h2><?=_('Create new XP-level')?></h2>
<?php if($validations['create'] !== true) : ?>
<ul class="validation">
    <?php foreach($validations['create'] as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
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
<form method="post">
    <fieldset>
        <input id="xplevel-new-xps" type="number" name="xplevelnew[xps]" value="<?=(count($xplevels) > 0) ? $xplevels[count($xplevels)-1]['xps']+1 : 0 ?>" min="<?=(count($xplevels) > 0) ? $xplevels[count($xplevels)-1]['xps']+1 : 0 ?>" <?=($validations['create'] !== true && array_key_exists('xps', $validations['create'])) ? 'class="invalid"' : null?> />
        <label for="xplevel-new-xps"><?=_('XPs')?></label>
    </fieldset>
    <input type="submit" name="create" value="<?=_('create')?>" />
</form>
