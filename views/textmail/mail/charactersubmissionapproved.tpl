<?=sprintf(_('Your submission for the Quest “%s” of the Seminary “%s” has been approved'), $quest['title'], $seminary['title'])?>.
<?php if(!is_null($linker)) : ?><?=$linker->link(array('quests','quest',$seminary['url'],$questgroup['url'],$quest['url']),0,true,null,false,null,true)?><?php endif ?>
