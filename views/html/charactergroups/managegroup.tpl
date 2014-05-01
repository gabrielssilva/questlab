<?php if(!is_null($seminary['charactergroups_seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'], 'charactergroups'))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('index',$seminary['url']),1)?>"><?=_('Character Groups')?></a></li>
	<li><i class="fa fa-chevron-right fa-fw"></i><a href="<?=$linker->link(array('groupsgroup',$seminary['url'],$groupsgroup['url']),1)?>"><?=$groupsgroup['name']?></a></li>
</ul>

<h1><?=_('Manage Character group')?></h1>
<div class="gbanner cf">
	<?php if(!is_null($group['seminaryupload_id'])) : ?>
	<img src="<?=$linker->link(array('uploads','charactergroup',$seminary['url'],$groupsgroup['url'],$group['url']))?>" class="gbanner">
	<?php else : ?>
	<img src="<?=$linker->link(array('grafics','charactergroup.jpg'))?>" class="gbanner">
	<?php endif ?>
	<h1><?=$group['name']?></h1>
	<p>"<?=$group['motto']?>"</p>
</div>
<ul class="gdata cf">
	<li><?=$group['rank']?>. <?=_('Rank')?></li>
	<li><?=$group['xps']?> XP</li>
	<li><?=count($group['characters'])?> <?=(count($group['characters']) > 1) ? _('Members') : _('Member')?></li>
</ul>

<section>
	<h1><i class="fa fa-users fa-fw"></i><?=_('Characters')?></h1>
	<form method="post">
		<fieldset>
			<ul class="gchars cf">
				<?php foreach($group['characters'] as &$character) : ?>
				<li>
					<input type="checkbox" id="characters-<?=$character['id']?>" name="characters[]" value="<?=$character['id']?>" <?php if($character['id'] == \hhu\z\controllers\SeminaryController::$character['id']) : ?>disabled="disabled"<?php endif ?>/>
					<label for="characters-<?=$character['id']?>">
						<?php if(array_key_exists('small_avatar', $character)) : ?>
						<p><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['small_avatar']['url']))?>"></p>
						<?php endif ?>
						<p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a></p>
						<p><small><?=$character['xps']?> XP</small></p>
					</label>
				</li>
				<?php endforeach ?>
			</ul>
			<input type="submit" name="actions[removecharacters]" value="<?=_('Remove Characters')?>" />
		</fieldset>
		<fieldset class="filter add">
			<p class="fwb"><small>Charaktere der Gruppe hinzufügen:</small></p>
			<input type="text" placeholder="<?=_('Filter Characters')?>" onkeyup="filter_characters(this)" />
			<select id="characters" name="characters[]" size="5" multiple="multiple">
				<?php foreach($characters as &$character) : ?>
				<option value="<?=$character['id']?>"><?=$character['name']?></option>
				<?php endforeach ?>
			</select>
			<input type="submit" name="actions[addcharacters]" value="<?=_('Add Characters')?>" />
		</fieldset>
	</form>
</section>

<section>
	<h1><i class="fa fa-pencil-square-o fa-fw"></i><?=_('Quests')?></h1>
	<ul class="gquests">
		<?php foreach($quests as &$quest) : ?>
		<li class="cf">
			<p>
				<span class="date"><?=$dateFormatter->format(new \DateTime($quest['created']))?></span>
				<a href="<?=$linker->link(array('charactergroupsquests','quest',$seminary['url'],$groupsgroup['url'],$quest['url']))?>" class="fwb"><?=$quest['title']?></a>
				<span class="xp"><?=$quest['group_xps']?> / <?=$quest['xps']?> XP</span>
			</p>
		</li>
		<?php endforeach ?>
	</ul>
</section>




<script>
	/**
	 * Hide select elements that include the value string from the given input
	 * element.
	 */
	function filter_characters(input)
	{
		text = input.value.toLowerCase();
		$('#characters option').each(function() {
			if(this.text.toLowerCase().indexOf(text) !== -1) {
				jQuery(this).removeAttr('hidden');
			}
			else {
				jQuery(this).attr('hidden', "hidden");
			}
		});
	}
</script>
