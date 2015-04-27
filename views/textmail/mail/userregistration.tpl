<?=_('A new user has been registered')?>: <?=$user['username']?>

<?php if(!is_null($linker)) : ?><?=$linker->link(array('users','user',$user['url']),0,true,null,false,null,true)?><?php endif ?>
