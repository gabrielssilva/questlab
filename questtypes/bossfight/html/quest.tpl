<div class="cf">
<section class="opponent">
	<p class="fwb"><?=$character['name']?></p>
	<p class="portrait"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['avatar_url']))?>" class="hero" /></p>
	<p>
		<?php if($lives['character'] > 0) : ?>
		<?php foreach(range(1,$lives['character']) as $i) : ?>
		<i class="fa fa-heart fa-fw"></i>
		<?php endforeach ?>
		<?php else : ?>
		<?=_('lost')?>
		<?php endif ?>
	</p>
</section>
<section class="opponent">
	<p class="fwb"><?=$fight['bossname']?></p>
	<p class="portrait"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$fight['bossmedia']['url']))?>" class="boss" /></p>
	<p>
		<?php if($lives['boss'] > 0) : ?>
		<?php foreach(range(1,$lives['boss']) as $i) : ?>
		<i class="fa fa-heart fa-fw"></i>
		<?php endforeach ?>
		<?php else : ?>
		<?=_('lost')?>
		<?php endif ?>
	</p>
</section>
</div>

<p><?=\hhu\z\Utils::t($stage['text'])?></p>

<form method="post" action="#task">
	<input type="hidden" name="stage" value="<?=$stage['id']?>" />
	<ul>
		<?php foreach($childStages as &$childStage) : ?>
		<li>
			<p>
				<?php if(array_key_exists('answer', $childStage) && $childStage['answer']) : ?>→<?php endif ?>
				<?=\hhu\z\Utils::t($childStage['question'])?>
			</p>
			<input type="submit" name="submit_stages[<?=$childStage['id']?>]" value="<?=_('Choose')?>" />
		</li>
		<?php endforeach?>
		<?php if($lives['character'] == 0 || $lives['boss'] == 0) : ?>
		<li>
			<input type="hidden" name="answers" value="" />
			<input type="submit" name="submit" value="<?=_('solve')?>" />
		</li>
		<?php endif ?>
	</ul>
</form>
