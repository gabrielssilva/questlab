<?php

    foreach($users as &$user)
    {
        // Role translation
        foreach($user['roles'] as &$role)
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

        // Date formattieng
        $user['created'] = sprintf(_('registered on %s'),  $dateFormatter->format(new \DateTime($user['created'])));
    }

?>
<?=json_encode(array(
    'users' => $users,
    'more'  => (($page*$limit) < $usersCount)
))?>
