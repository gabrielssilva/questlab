<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><?=_('Characters')?></h1>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
	<li><a href="<?=$linker->link(array('manage',$seminary['url']),1)?>"><?=_('Manage')?></a></li>
</nav>
<?php endif ?>

<form method="post">
	<fieldset class="filter">
		<ul>
			<li><input type="checkbox" id="username" name="properties[]" value="username" <?php if(in_array('username', $properties)) : ?>checked="checked"<?php endif ?> /><label for="username"><?=_('Username')?></label></li>
			<li><input type="checkbox" id="xps" name="properties[]" value="xps" <?php if(in_array('xps', $properties)) : ?>checked="checked"<?php endif ?> /><label for="xps"><?=_('XPs')?></label></li>
			<li><input type="checkbox" id="roles" name="properties[]" value="roles" <?php if(in_array('roles', $properties)) : ?>checked="checked"<?php endif ?> /><label for="roles"><?=_('Roles')?></label></li>
			<?php foreach($characterfields as &$characterfield) : ?>
			<li><input type="checkbox" id="characterfield-<?=$characterfield['url']?>" name="properties[characterfields][]" value="<?=$characterfield['url']?>" <?php if(array_key_exists('characterfields', $properties) && in_array($characterfield['url'], $properties['characterfields'])) : ?>checked="checked"<?php endif ?> /><label for="characterfield-<?=$characterfield['url']?>"><?=$characterfield['url']?></label></li>
			<?php endforeach ?>
		</ul>
		<input class="cta" type="submit" name="set-properties" value="<?=_('Set properties')?>" />
	</fieldset>
</form>

<ul class="gchars cf">
	<?php foreach($characters as &$character) : ?>
	<li>
		<p><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level'],'portrait'))?>"></p>
		<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
		<?php if(in_array('username', $properties)) : ?><p><small><a href="<?=$linker->link(array('users','user',$character['user']['url']))?>"><?=$character['user']['username']?></a></small></p><?php endif ?>
		<?php if(in_array('xps', $properties)) : ?><p><small><?=$character['xps']?> XP</small></p><?php endif ?>
		<?php if(in_array('roles', $properties)) : ?>
		<?php if(in_array('admin', $character['characterroles'])) : ?><p><small><?=_('Admin')?></small></p><?php endif ?>
		<?php if(in_array('moderator', $character['characterroles'])) : ?><p><small><?=_('Moderator')?></small></p><?php endif ?>
		<?php if(in_array('user', $character['characterroles'])) : ?><p><small><?=_('User')?></small></p><?php endif ?>
		<?php endif ?>
		<?php foreach($character['characterfields'] as &$characterfield) : ?>
		<?php if(array_key_exists('characterfields', $properties) && in_array($characterfield['url'], $properties['characterfields'])) : ?>
		<p><small><?=$characterfield['value']?></small></p>
		<?php endif ?>
		<?php endforeach ?>
	</li>
	<?php endforeach ?>
</ul>
