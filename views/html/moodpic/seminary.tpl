<div class="moodpic">
    <div>
        <?php if(!is_null($medium)) : ?>
        <img src="<?=$medium['url']?>" <?php if(!empty($medium['title'])) : ?>title="<?=$medium['title']?>"<?php endif ?> <?php if(!empty($medium['description'])) : ?>alt="<?=$medium['description']?>"<?php endif ?>/>
        <?php if(!empty($medium['sourcelabel']) || !empty($medium['sourceurl'])) : ?>
        <?php $label = (!empty($medium['sourcelabel'])) ? $medium['sourcelabel'] : \hhu\z\Utils::urlToLabel($medium['sourceurl']); ?>
        <span class="source">
            <?=_('Image source')?>:
            <?php if(!empty($medium['sourceurl'])): ?>
            <a href="<?=$medium['sourceurl']?>" target="_blank"><?=$label?></a>
            <?php else : ?>
            <?=$label?>
            <?php endif ?>
        </span>
        <?php endif ?>
        <?php else : ?>
        <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
        <?php endif ?>
    </div>
</div>
