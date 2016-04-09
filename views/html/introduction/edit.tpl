<div class="moodpic">
    <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>

<h1><?=\nre\configs\AppConfig::$app['name']?></h1>
<form method="post">
    <fieldset>
        <legend><?=_('Introduction text')?></legend>
        <textarea id="text" name="text" placeholder="<?=_('Please enter an introduction text')?>"><?=$text?></textarea>
    </fieldset>
    <input type="submit" name="edit" value="<?=_('save')?>" />
    <input type="submit" name="cancel" value="<?=_('cancel')?>" />
</form>
<script>
    $(function() {
        $("#text").markItUp(mySettings);
    });
</script>
