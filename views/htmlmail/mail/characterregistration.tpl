<?=sprintf(_('User “%s” has registered a new Character for the Seminary “%s”'), $user['username'], $seminary['title'])?>:
<?php if(!is_null($linker)) : ?><a href="<?=$linker->link(array('characters',$seminary['url'],$user['url']),0,false,null,false,null,true)?>"><?=$character['name']?></a><?php else : ?><?=$character['name']?><?php endif ?>
