<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
    <?php foreach($parentquestgroupshierarchy as &$hierarchy) : ?>
    <li>
        <i class="fa fa-chevron-right fa-fw"></i>
        <?php if(array_key_exists('hierarchy', $hierarchy)) : ?>
        <?php if(!is_null($hierarchy['hierarchy'])) : ?>
        <?=$hierarchy['hierarchy']['title_singular']?><?php if(array_key_exists('questgroup_pos', $hierarchy['hierarchy'])) : ?> <?=$hierarchy['hierarchy']['questgroup_pos']?><?php endif ?>:
        <?php endif ?>
        <a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$hierarchy['url']))?>"><?=$hierarchy['title']?></a>
        <?php else : ?>
        <a href="<?=$linker->link(array('quests','quest',$seminary['url'],$hierarchy['questgroup']['url'],$hierarchy['url']))?>"><?=$hierarchy['title']?></a>
        <?php endif ?>
    </li>
    <?php endforeach ?>
</ul>
