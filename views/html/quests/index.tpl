<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
</div>
<?php endif ?>
<ul class="breadcrumbs">
	<li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><?=_('Quests')?></h1>

<form method="get" class="logreg admnqf">
	<fieldset>
		<legend>Filter</legend>
		<label for="questgroup"><?=_('Questgroup')?>:</label>
		<select id="questgroup" name="questgroup">
			<option value=""><?=_('all')?></option>
			<?php foreach($questgroups as &$questgroup) : ?>
			<option value="<?=$questgroup['id']?>" <?php if($questgroup['id'] == $selectedQuestgroup) : ?>selected="selected"<?php endif ?>><?=$questgroup['title']?></option>
			<?php endforeach ?>
		</select><br />
		<label for="questtype"><?=_('Questtype')?>:</label>
		<select id="questtype" name="questtype">
			<option value=""><?=_('all')?></option>
			<?php foreach($questtypes as &$questtype) : ?>
			<option value="<?=$questtype['id']?>" <?php if($questtype['id'] == $selectedQuesttype) : ?>selected="selected"<?php endif ?>>
				<?php switch($questtype['classname']) {
					case null: echo _('Questtype Empty');
					break;
					case 'bossfight': echo _('Questtype bossfight');
					break;
					case 'choiceinput': echo _('Questtype choiceinput');
					break;
					case 'crossword': echo _('Questtype crossword');
					break;
					case 'dragndrop': echo _('Questtype dragndrop');
					break;
					case 'multiplechoice': echo _('Questtype multiplechoice');
					break;
					case 'submit': echo _('Questtype submit');
					break;
					case 'textinput': echo _('Questtype textinput');
					break;
				} ?>
			</option>
			<?php endforeach ?>
		</select>
	</fieldset>
	<input type="submit" value="<?=_('Apply filters')?>" />
</form>

<ul id="questlist" class="admnql">
	<?php foreach($quests as &$quest) : ?>
	<li>
		<p class="fwb"><a href="<?=$linker->link(array('quest',$seminary['url'],$quest['questgroup_url'],$quest['url']),1)?>"><?=$quest['title']?></a><span><a href="<?=$linker->link(array('submissions',$seminary['url'],$quest['questgroup_url'],$quest['url']),1)?>"><?=$quest['opensubmissionscount']?> <?=_('open submissions')?></a></span></p>
		<p><small>
			<?php switch($quest['questtype']['classname']) {
				case null: echo _('Questtype Empty');
				break;
				case 'bossfight': echo _('Questtype bossfight');
				break;
				case 'choiceinput': echo _('Questtype choiceinput');
				break;
				case 'crossword': echo _('Questtype crossword');
				break;
				case 'dragndrop': echo _('Questtype dragndrop');
				break;
				case 'multiplechoice': echo _('Questtype multiplechoice');
				break;
				case 'submit': echo _('Questtype submit');
				break;
				case 'textinput': echo _('Questtype textinput');
				break;
			} ?>, <?=sprintf(_('%d XPs'), $quest['xps'])?></small></p>
		<p><small><a href="<?=$linker->link(array('questgroups','questgroup',$seminary['url'],$quest['questgroup_url']))?>"><?=$quest['questgroup_title']?></a></small></p>
	</li>
	<?php endforeach ?>
</ul>
<?php if(is_null($all) && ($page*$limit) < $questsCount) : ?>
<nav class="admin">
	<li><a id="show-more" href="<?=$linker->link(null,3,true,array('page'=>$page+1,'questgroup'=>$selectedQuestgroup,'questtype'=>$selectedQuesttype))?>"><?=_('Show more')?></a></li>
	<li><a id="show-all" href="<?=$linker->link('all',3,true,array('questgroup'=>$selectedQuestgroup,'questtype'=>$selectedQuesttype))?>"><?=_('Show all')?></a></li>
</nav>
<?php endif ?>

<script>
	var page = 1;
	var request;
	var linkSubmissions = "<?=$linker->link(array('submissions','SEMINARY','QUESTGROUP','QUEST'),1)?>";
	var linkQuestgroup = "<?=$linker->link(array('questgroups','questgroup','SEMINARY','QUESTGROUP'))?>";
	var linkQuest = "<?=$linker->link(array('quest','SEMINARY','QUESTGROUP','QUEST'),1)?>";
	var linkPage = "<?=$linker->link(null,3,true,array('page'=>'PAGE','questgroup'=>$selectedQuestgroup,'questtype'=>$selectedQuesttype))?>";
	
	$("#show-more").click(function(event) {
		if(request) {
			request.abort();
		}
		
		page++;
		request = $.getJSON(linkPage.replace('PAGE', page), function(data) {
			linkSubmissions = linkSubmissions.replace('SEMINARY', data['seminary']['url']);
			linkQuestgroup = linkQuestgroup.replace('SEMINARY', data['seminary']['url']);
			linkQuest = linkQuest.replace('SEMINARY', data['seminary']['url']);
			$.each(data['quests'], function(key, val) {
				var urlSubmissions = linkSubmissions.replace('QUESTGROUP', val['questgroup_url']).replace('QUEST', val['url']);
				var urlQuestgroup = linkQuestgroup.replace('QUESTGROUP', val['questgroup_url']);
				var urlQuest = linkQuest.replace('QUESTGROUP', val['questgroup_url']).replace('QUEST', val['url']);
				$("#questlist").append(
					"<li>" + 
					"<p class=\"fwb\"><a href=\"" + urlQuest + "\">" + val['title'] + "</a><span><a href=\"" + urlSubmissions + "\">" + val['opensubmissionscount'] + " <?=_('open submissions')?></a></span></p>" +
					"<p><small>" + val['questtype']['title'] + ", " + val['xps'] + "</small></p>" +
					"<p><small><a href=\"" + urlQuestgroup + "\">" + val['questgroup_title'] + "</a></small></p>" +
					"</li>"
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
			alert("fail: " + textStatus + ": " +errorThrown);
		});
		
		
		event.preventDefault();
		return false;
	});
</script>
