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
        <label for="keyword"><?=_('Keyword')?>:</label>
        <input type="text" name="keyword" value="<?=$keyword?>" placeholder="/regex/i" />
    </fieldset>
    <input type="submit" name="save" value="<?=_('save')?>" />
</form>
