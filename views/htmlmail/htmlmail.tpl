<!DOCTYPE html>
<html>

<head>
	<meta charset="utf-8" />
</head>

<body>
	<p><?=$mailreceiver?>,</p>
	<p>
		<?=$intermediate?>
	</p>
	
	<p>–
		<?php if(!is_null($linker)) : ?><a href="<?=$linker->link(array(),0,true,null,false,null,true)?>"><?=$appname?></a><?php else : ?><?=$appname?><?php endif ?>
	</p>
</body>

</html>
