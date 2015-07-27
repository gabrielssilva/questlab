<?php if(!is_null($picture)) : ?>
<div class="moodpic">
    <img src="<?=$linker->link(array('media','seminary',$seminary['url'],$picture['url']))?>" />
</div>
<?php else: ?>
<?=$moodpic?>
<?php endif ?>
<?=$questgroupshierarchypath?>

<h1><?=_('Edit Questgroup texts')?></h1>
<form method="post">
    <fieldset>
        <ul class="admnql">
            <?php foreach($questgrouptexts as &$text) : ?>
            <li class="cf">
                <textarea id="questgrouptexts-<?=$text['id']?>" name="questgrouptexts[<?=$text['id']?>]"><?=$text['text']?></textarea><br />
                <input id="deletes[<?=$text['id']?>]" type="checkbox" name="deletes[<?=$text['id']?>]" />
                <label for="deletes[<?=$text['id']?>]"><?=_('delete')?></label>
                <script>
                    $(function() {
                        $("#questgrouptexts-<?=$text['id']?>").markItUp(mySettings);
                    });
                </script>
            </li>
            <?php endforeach ?>
            <li class="cf">
                <textarea id="questgrouptexts-new" name="questgrouptexts[]" placeholder="<?=_('New Questgroup text')?>"></textarea>
            </li>
        </ul>
    </fieldset>
    <input type="submit" name="edit" value="<?=_('edit')?>" />
</form>
<script>
    $(function() {
        $("#questgrouptexts-new").markItUp(mySettings);
    });
</script>
