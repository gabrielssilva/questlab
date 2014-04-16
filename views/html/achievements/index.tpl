<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><?=_('Achievements')?></h2>

<ul>
	<?php foreach($achievements as &$achievement) : ?>
	<li>
		<?php if(!is_null($achievement[$achievement['media_index']])) : ?>
		<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url']))?>" />
		<?php endif ?>
		<h3><?=(!$achievement['hidden']) ? $achievement['title'] : _('Secret Achievement')?></h3>
		<?php if(!$achievement['hidden']) : ?>
		<?=\hhu\z\Utils::t($achievement['description'])?>
		<?php else : ?>
		<?=_('Continue playing to unlock this secret Achievement')?>
		<?php endif ?>
		<br />
		
		<?php if(array_key_exists('characterProgress', $achievement)) : ?>
		<div class="cf">
			<div class="xpbar">
				<span style="width:<?=round($achievement['characterProgress']*100)?>%"></span>
			</div>
			<p class="xpnumeric"><?=round($achievement['characterProgress']*100)?> %</p>
		</div>
		<?php endif ?>
	</li>
	<?php endforeach?>
</ul>
