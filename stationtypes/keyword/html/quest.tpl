<form method="post" class="keyword">
    <input type="text" id="keyword" name="answer" <?php if(!is_null($submission)) : ?>value="<?=$submission?>"<?php endif ?> <?php if($tried) : ?>disabled="disabled"<?php endif ?>/>
<?php if(!$tried) : ?>
    <input type="submit" name="submit" value="<?=_('solve')?>" />
<?php endif ?>
</form>
