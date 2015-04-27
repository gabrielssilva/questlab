<?php
	
	foreach($characters as &$character)
	{
		// Role translation
		foreach($character['characterroles'] as &$role)
		{
			switch($role)
			{
				case 'admin': $role = _('Admin');
				break;
				case 'moderator': $role = _('Moderator');
				break;
				case 'user': $role = _('User');
				break;
			}
		}
	}
	
?>
<?=json_encode(array(
	'seminary'	=> $seminary,
	'characters'	=> $characters,
	'more'		=> (($page*$limit) < $charactersCount)
))?>
