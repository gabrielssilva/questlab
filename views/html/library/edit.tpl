<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Library')?></a></li>
</ul>

<h1><i class="fa fa-book fa-fw"></i><?=_('Edit Questtopic')?></h1>
<?php if($validations['edit'] !== true) : ?>
<ul class="validation">
    <?php foreach($validations['edit'] as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
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
<form method="post">
    <fieldset>
        <label for="title"><?=_('Title')?>:</label>
        <input id="title" type="text" name="title" placeholder="<?=_('Title')?>" title="<?=_('Title')?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$questtopicTitle?>" <?=($validations['edit'] !== true && array_key_exists('title', $validations['edit'])) ? 'class="invalid"' : null?> />
    </fieldset>
    <input type="submit" name="edit" value="<?=_('save')?>" />
</form>

<h2><?=_('Edit Questsubtopics')?></h2>
<form method="post">
    <?php foreach($subtopicsTitles as $subtopicId => &$title) : ?>
    <?php if($validations['edit-subtopics'] !== true && array_key_exists($subtopicId, $validations['edit-subtopics']) && $validations['edit-subtopics'][$subtopicId] !== true) : ?>
    <ul class="validation">
        <?php foreach($validations['edit-subtopics'][$subtopicId] as $field => &$settings) : ?>
        <li>
            <ul>
                <?php foreach($settings as $setting => $value) : ?>
                <li>
                    <?php switch($field) {
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
    <input id="subtopic-<?=$subtopicId?>" type="text" name="subtopics[<?=$subtopicId?>]" placeholder="<?=$title?>" title="<?=$title?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$title?>" <?=($validations['edit-subtopics'] !== true && array_key_exists($subtopicId, $validations['edit-subtopics']) && $validations['edit-subtopics'][$subtopicId] !== true && array_key_exists('title', $validations['edit-subtopics'][$subtopicId])) ? 'class="invalid"' : null?>/>
    <input id="subtopic-<?=$subtopicId?>-delete" type="checkbox" name="delete-subtopics[<?=$subtopicId?>]" <?php if(!is_null($deleteSubtopics) && array_key_exists($subtopicId, $deleteSubtopics)) : ?>checked="checked"<?php endif ?> />
    <label for="subtopic-<?=$subtopicId?>-delete"><?=_('delete')?></label><br />
    <?php endforeach ?>
    
    <input type="submit" name="edit-subtopics" value="<?=_('save')?>" />
</form>

<h2><?=_('Create new Questsubtopic')?></h2>
<?php if($validations['create-subtopic'] !== true) : ?>
<ul class="validation">
    <?php foreach($validations['create-subtopic'] as $field => &$settings) : ?>
    <li>
        <ul>
            <?php foreach($settings as $setting => $value) : ?>
            <li>
                <?php switch($field) {
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
<form method="post">
    <fieldset>
        <label for="subtopictitle"><?=_('Title')?>:</legend>
        <input id="subtopictitle" type="text" name="title" placeholder="<?=_('Title')?>" title="<?=_('Title')?>" required="required" maxlength="<?=$validationSettings['title']['maxlength']?>" value="<?=$subtopicTitle?>" <?=($validations['create-subtopic'] !== true && array_key_exists('title', $validations['create-subtopic'])) ? 'class="invalid"' : null?> />
    </fieldset>
    <input type="submit" name="create-subtopic" value="<?=_('create')?>" />
</form>
