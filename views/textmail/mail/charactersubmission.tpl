<?=sprintf(_('Character “%s” has submitted a new submission for the Quest “%s” of the Seminary “%s”'), $character['name'], $quest['title'], $seminary['title'])?>.
<?php if(!is_null($linker)) : ?><?=$linker->link(array('quests','submission',$seminary['url'],$questgroup['url'],$quest['url'],$character['url']),0,true,null,false,null,true)?><?php endif ?>
