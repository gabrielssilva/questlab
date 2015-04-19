<div class="moodpic">
	<img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
</div>
<h1><?=_('Users')?></h1>
<nav class="admin">
	<li><a href="<?=$linker->link('create', 1)?>"><?=_('Create new user')?></a></li>
	<li><a href="<?=$linker->link('manage',1)?>"><?=_('Manage')?></a></li>
</nav>

<form method="get" class="logreg admnqf">
	<fieldset>
		<legend><?=_('Filters')?></legend>
		<small><?=_('Sortorder')?>:</small>
		<select name="sortorder" onchange="this.form.submit();">
			<option value="username" <?php if($sortorder == 'username') : ?>selected="selected"<?php endif ?>><?=_('Username')?></option>
			<option value="role" <?php if($sortorder == 'role') : ?>selected="selected"<?php endif ?>><?=_('Role')?></option>
			<option value="created" <?php if($sortorder == 'created') : ?>selected="selected"<?php endif ?>><?=_('Date of registration')?></option>
		</select>
		<label for="username"><?=_('Username')?>:</label>
		<input id="username" type="text" name="username" placeholder="<?=_('Username')?>" value="<?=$username?>" />
        <label for="name"><?=_('Name')?>:</label>
        <input id="name" type="text" name="name" placeholder="<?=_('Name')?>" value="<?=$name?>" />
        <label for="email"><?=_('E‑mail address')?>:</label>
        <input id="email" type="text" name="email" placeholder="<?=_('E‑mail address')?>" value="<?=$email?>" />
	</fieldset>
	<input type="submit" value="<?=_('Apply filters')?>" />
</form>
<ol id="userlist" class="cglist">
	<?php foreach($users as &$user) : ?>
	<li>
		<p>
			<a href="<?=$linker->link(array('user', $user['username']), 1)?>"><?=$user['username']?></a><span class="xp"><small><?=sprintf(_('registered on %s'),  $dateFormatter->format(new \DateTime($user['created'])))?></small></span>
			<?php if(in_array('admin', $user['roles'])) : ?><small>(<?=_('Admin')?>)</small><?php endif ?>
			<?php if(in_array('moderator', $user['roles'])) : ?><small>(<?=_('Moderator')?>)</small><?php endif ?>
			<?php if(in_array('user', $user['roles'])) : ?><small>(<?=_('User')?>)</small><?php endif ?>
            <br />
            <small>
                <?=$user['prename']?> <?=$user['surname']?>,
                <a href="mailto:<?=$user['email']?>"><?=$user['email']?></a>
            </small>
		</p>
	</li>
	<?php endforeach ?>
</ol>

<?php if(is_null($all) && ($page*$limit) < $usersCount) : ?>
<nav class="admin">
	<li><a id="show-more" href="<?=$linker->link(null,1,true,array('page'=>$page+1,'sortorder'=>$sortorder),false)?>"><?=_('Show more')?></a></li>
	<li><a id="show-all" href="<?=$linker->link('all',1,true,array('sortorder'=>$sortorder))?>"><?=_('Show all')?></a></li>
</nav>
<?php endif ?>

<script>
	var page = 1;
	var request;
	var linkUser = "<?=$linker->link(array('users','user','USER'))?>";
	var linkPage = "<?=$linker->link(null,1,true,array('page'=>'PAGE','sortorder'=>$sortorder),false)?>";
	
	$("#show-more").click(function(event) {
		if(request) {
			request.abort();
		}
		
		page++;
		request = $.getJSON(linkPage.replace('PAGE', page), function(data) {
			$.each(data['users'], function(key, user) {
				var urlUser = linkUser.replace('USER', user['url']);
				$("#userlist").append(
					"<li><p>" +
					"<a href=\"" + urlUser + "\">" + user['username'] + "</a><span class=\"xp\"><small>" + user['created'] + "</small></span>\n" +
					(user['roles'].length > 0 ? "<small>(" + user['roles'].join(', ') + ")</small>" : '') + 

                    "<br /><small>" + user['prename'] + " " + user['surname'] + ", " +
                    "<a href=\"mailto:" + user['email'] + "\">" + user['email'] + "</a></small>" +

					"</p></li>"
				);
			});
			if(data['more']) {
				$("#show-more").attr('href', linkPage.replace('PAGE', page+1));
			}
			else {
				$("#show-more").remove();
				$("#show-all").remove();
			}
		});
		request.fail(function (jqXHR, textStatus, errorThrown) {
			window.location.href = linkPage.replace('PAGE', page);
		});
		
		
		event.preventDefault();
		return false;
	});
</script>
