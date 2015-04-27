<ul>
	<?php foreach($roles as &$role) : ?>
	<li>
		<?php switch($role['name']) {
			case 'admin': echo _('Admin');
			break;
			case 'moderator': echo _('Moderator');
			break;
			case 'user': echo _('User');
			break;
		}
		?>
	</li>
	<?php endforeach ?>
</ul>
