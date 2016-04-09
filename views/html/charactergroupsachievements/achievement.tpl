<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
    <li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('charactergroups','groupsgroup',$seminary['url'],$groupsgroup['url']))?>"><?=$groupsgroup['name']?></a></li>
</ul>

<h1><?=$achievement['title']?></h1>
<ul class="achmnts">
    <li class="cf">
<?php if(!is_null($achievement['achievementsmedia_id'])) : ?>
        <img src="<?=$linker->link(array('media','charactergroupsachievement',$seminary['url'],$groupsgroup['url'],$achievement['url']))?>" />
<?php endif ?>
        <p class="desc"><?=\hhu\z\Utils::t($achievement['description'])?></p>
    </li>
</ul>

<form method="post" action="<?=$linker->link(null, 5, true)?>">
    <fieldset>
        <label for="charactergroup"><?=sprintf(_('%s-Group to show'), $groupsgroup['name'])?>:</label>
        <br />
        <select id="charactergroup" name="charactergroup">
            <?php foreach($charactergroups as &$group) : ?>
            <option value="<?=$group['id']?>"><?=$group['name']?></option>
            <?php endforeach ?>
        </select>
    </fieldset>
    <input type="submit" value="<?=_('proceed')?>" />
</form>
