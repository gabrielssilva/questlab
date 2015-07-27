<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Library')?></a></li>
</ul>
<h1><i class="fa fa-book fa-fw"></i><?=$questtopic['title']?></h1>

<h2>Quests zu diesem Thema:</h2>
<form method="post">
    <ul class="libtop">
        <?php foreach($quests as &$quest) : ?>
        <li>
            <p><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$quest['questgroup_url'],$quest['url']))?>"><?=$quest['title']?></a></p>
            <?php foreach($questsubtopics as &$subtopic) : ?>
            <input id="subtopic-<?=$quest['id']?>-<?=$subtopic['id']?>" type="checkbox" name="questsubtopics[<?=$quest['id']?>][<?=$subtopic['id']?>]" <?php if(in_array($subtopic['id'], $quest['subtopics'])) : ?>checked="checked"<?php endif ?> />
            <label for="subtopic-<?=$quest['id']?>-<?=$subtopic['id']?>"><?=$subtopic['title']?></label><br />
            <?php endforeach ?>
        </li>
        <?php endforeach ?>
        <li>
            <p>
                <select name="addquest">
                    <option value=""><?=_('Add Quest')?></option>
                    <?php foreach($allQuests as &$quest) : ?>
                    <option value="<?=$quest['id']?>"><?=$quest['title']?></opiton>
                    <?php endforeach ?>
                </select>
            </p>
            <?php foreach($questsubtopics as &$subtopic) : ?>
            <input id="subtopic-new-<?=$subtopic['id']?>" type="checkbox" name="questsubtopics[addquest][<?=$subtopic['id']?>]" />
            <label for="subtopic-new-<?=$subtopic['id']?>"><?=$subtopic['title']?></label><br />
            <?php endforeach ?>
        </li>
    </ul>
    <input type="submit" value="<?=_('Manage')?>" />
</form>
