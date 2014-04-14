<li><a href="<?=$linker->link(array('seminaries',$loggedSeminary['url']))?>" class="smnry"><i class="fa fa-chevron-right fa-fw"></i><?=$loggedSeminary['title']?></a></li>
<?php if(count(array_intersect(array('admin','moderator'),$loggedUser['roles'])) > 0) : ?><li><a href="<?=$linker->link(array('characters',$loggedSeminary['url']))?>" class="smnry"><i class="fa fa-users fa-fw"></i><?=_('Characters')?></a></li><?php endif ?>
<li><a href="<?=$linker->link(array('charactergroups','index',$loggedSeminary['url']))?>" class="smnry"><i class="fa fa-users fa-fw"></i><?=_('Character Groups')?></a></li>
<li><a href="<?=$linker->link(array('achievements','index',$loggedSeminary['url']))?>" class="smnry"><i class="fa fa-trophy fa-fw"></i><?=_('Achievements')?></a></li>
<li><a href="<?=$linker->link(array('library','index',$loggedSeminary['url']))?>" class="smnry"><i class="fa fa-book fa-fw"></i><?=_('Library')?></a></li>

