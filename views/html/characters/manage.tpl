<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('characters','index',$seminary['url']))?>"><?=_('Characters')?></a></li>
</ul>
<h1><?=_('Manage')?></h1>

<form method="post">
	<fieldset>
		<legend><?=_('Selection')?>:</legend>
		<ul class="gchars cf">
			<?php foreach($characters as &$character) : ?>
			<li>
				<input type="checkbox" id="characters-<?=$character['id']?>" name="characters[]" value="<?=$character['id']?>" <?php if(in_array($character['id'], $selectedCharacters)) : ?>checked="checked"<?php endif ?> <?php if($character['id'] == \hhu\z\controllers\SeminaryController::$character['id']) : ?>disabled="disabled"<?php endif ?>/>
				<label for="characters-<?=$character['id']?>">
					<p><img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level'],'portrait'))?>"></p>
					<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
					<p><small><?=$character['xps']?> XP</small></p>
					<?php if(in_array('admin', $character['characterroles'])) : ?><p><small><?=_('Admin')?></small></p><?php endif ?>
					<?php if(in_array('moderator', $character['characterroles'])) : ?><p><small><?=_('Moderator')?></small></p><?php endif ?>
					<?php if(in_array('user', $character['characterroles'])) : ?><p><small><?=_('User')?></small></p><?php endif ?>
				</label>
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
