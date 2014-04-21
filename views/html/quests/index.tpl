<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><?=_('Quests')?></h2>

<form method="post">
	<table>
		<thead>
			<tr>
				<th>
					<select name="filters[questgroup]">
						<option value="0"><?=_('Questgroup')?></option>
						<?php foreach($filters['questgroups'] as &$filter) : ?>
						<option value="<?=$filter['id']?>" <?php if($filter['id'] == $selectedFilters['questgroup']) : ?>selected="selected"<?php endif ?>><?=$filter['title']?></option>
						<?php endforeach ?>
					</select>
				</th>
				<th><?=_('Questname')?></th>
				<th>
					<select name="filters[questtype]">
						<option value=""><?=_('Questtype')?></option>
						<?php foreach($filters['questtypes'] as &$filter) : ?>
						<option value="<?=$filter['classname']?>" <?php if($filter['classname'] == $selectedFilters['questtype']) : ?>selected="selected"<?php endif ?>><?=$filter['title']?></option>
						<?php endforeach ?>
					</select>
				</th>
				<th>XPs</th>
				<th><?=('Submissions')?></th>
			</tr>
		</thead>
		<tbody>
			<?php foreach($quests as &$quest) : ?>
			<tr>
				<td><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$quest['questgroup']['url']))?>"><?=$quest['questgroup']['title']?></a></td>
				<td><a href="<?=$linker->link(array('quests','quest',$seminary['url'],$quest['questgroup']['url'],$quest['url']))?>"><?=$quest['title']?></a></td>
				<td><?=$quest['questtype']['title']?></td>
				<td><?=$quest['xps']?></td>
				<td><?=$quest['opensubmissionscount']?></td>
			</tr>
			<?php endforeach ?>
		</tbody>
	</table>
	
	<input type="submit" name="filter" value="<?=_('Apply filters')?>" />
	<input type="submit" name="reset" value="<?=_('Reset filters')?>" />
</form>
