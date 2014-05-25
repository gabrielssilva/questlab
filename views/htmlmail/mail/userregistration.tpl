<?=_('A new user has been registered')?>:
<?php if(!is_null($linker)) : ?><a href="<?=$linker->link(array('users',$user['url']),0,true,null,false,null,true)?>"><?=$user['username']?></a><?php else : ?><?=$user['username']?><?php endif ?>
