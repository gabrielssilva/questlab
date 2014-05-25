<?=sprintf(_('User “%s” has registered a new Character for the Seminary “%s”'), $user['username'], $seminary['title'])?>: <?=$character['name']?>

<?php if(!is_null($linker)) : ?><?=$linker->link(array('characters',$seminary['url'],$user['url']),0,false,null,false,null,true)?><?php endif ?>
