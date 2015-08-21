<div class="moodpic">
    <div>
        <?php if(!is_null($medium)) : ?>
        <img src="<?=$medium['url']?>" <?php if(!empty($medium['title'])) : ?>title="<?=$medium['title']?>"<?php endif ?> <?php if(!empty($medium['description'])) : ?>alt="<?=$medium['description']?>"<?php endif ?>/>
        <?php if(!empty($medium['sourceurl'])) : ?>
        <span class="source">
            <a href="<?=$medium['sourceurl']?>" target="_blank" title="<?=_('Image source')?>" rel="nofollow">
                <i class="fa fa-external-link"></i>
            </a>
        </span>
        <?php endif ?>
        <?php else : ?>
        <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
        <?php endif ?>
    </div>
</div>
