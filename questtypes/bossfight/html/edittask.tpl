<form method="post" enctype="multipart/form-data">
    <fieldset>
        <legend><?=_('Boss-Fight')?></legend>
        <label><?=_('Boss name')?></label>
        <input type="text" name="bossname" value="<?=$fight['bossname']?>" /><br />
        <label><?=_('Boss image')?></label>
        <input type="file" name="bossimage" /><br />
        <label><?=_('Boss lives')?></label>
        <input type="number" name="lives_boss" value="<?=$fight['lives_boss']?>" /><br />
        <label><?=_('Character lives')?></label>
        <input type="number" name="lives_character" value="<?=$fight['lives_character']?>" />
    </fieldset>
    <fieldset>
        <legend><?=_('Stages')?></legend>
        <?php renderStage($stages, $fight['lives_boss'], $fight['lives_character']); ?>
    </fieldset>
    <input type="submit" name="save" value="<?=_('save')?>" />
</form>

<?php function renderStage($stage, $livesBoss, $livesCharacter, $level=0, $indices=array()) { ?>
    <div style="margin-left:<?=$level?>em">
        <h2><?=implode('.', $indices)?></h2>
        <?php if(!empty($stage['question'])) : ?>
        <p><?=$stage['question']?></p>
        <?php endif ?>
        <p><?=_('Character')?> <?=$livesCharacter?> vs. <?=$livesBoss?> <?=_('Boss')?></p>
        <p><?=$stage['text']?></p>
        <?php foreach($stage['childs'] as $index => &$childStage) : ?>
            <?php $childIndices = $indices; ?>
            <?php $childIndices[] = $index+1; ?>
            <?php renderStage($childStage, $livesBoss+$childStage['livedrain_boss'], $livesCharacter+$childStage['livedrain_character'], $level+1, $childIndices); ?>
        <?php endforeach ?>
        <?php if($livesBoss == 0 && $livesCharacter == 0) : ?>
        Bedie verloren
        <?php elseif($livesBoss == 0) : ?>
        Boss verloren, Character gewonnen
        <?php elseif($livesCharacter == 0) : ?>
        Boss gewonnen, Character verloren
        <?php endif ?>
    </div>
<?php } ?>
