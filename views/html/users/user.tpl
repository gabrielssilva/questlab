<h2><?=$user['username']?></h2>
<p>
	registriert seit <?=date(\hhu\z\Utils::DATEFORMAT, strtotime($user['created']))?>
</p>
