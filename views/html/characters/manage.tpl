<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><?=_('Characters')?></h2>
<h3><?=_('Manage')?></h3>

<form method="post">
	<fieldset>
		<legend><?=_('Selection')?></legend>
		<ul class="gchars cf">
			<?php foreach($characters as &$character) : ?>
			<li>
				<input type="checkbox" name="characters[]" value="<?=$character['id']?>" <?php if($character['id'] == \hhu\z\controllers\SeminaryController::$character['id']) : ?>disabled="disabled"<?php endif ?>/>
				<p><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level'],'portrait'))?>"></p>
				<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
				<p><small><?=$character['xps']?> XP</small></p>
				<p><small><?=implode(', ', $character['characterroles'])?></small></p>
			</li>
			<?php endforeach ?>
		</ul>
	</fieldset>
	<fieldset>
		<legend><?=_('Add role')?></legend>
		<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
		<input type="submit" name="actions[addrole]" value="<?=_('Admin')?>" />
		<input type="submit" name="actions[addrole]" value="<?=_('Moderator')?>" />
		<?php endif ?>
		<input type="submit" name="actions[addrole]" value="<?=_('User')?>" />
	</fieldset>
	<fieldset>
		<legend><?=_('Remove role')?></legend>
		<?php if(in_array('admin', \hhu\z\controllers\SeminaryController::$character['characterroles'])) : ?>
		<input type="submit" name="actions[removerole]" value="<?=_('Admin')?>" />
		<input type="submit" name="actions[removerole]" value="<?=_('Moderator')?>" />
		<?php endif ?>
		<input type="submit" name="actions[removerole]" value="<?=_('User')?>" />
	</fieldset>
</form>
