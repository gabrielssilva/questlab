<div class="cf">
<section class="opponent">
	<p class="portrait"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$character['avatar_url']))?>" class="hero" /></p>
</section>
<section class="opponent">
	<p class="portrait"><img src="<?=$linker->link(array('media','seminary',$seminary['url'],$fight['bossmedia']['url']))?>" class="boss" /></p>
</section>
</div>

<?php foreach($stages as &$stage) : ?>
<p><?=$stage['question']?></p>
<div class="cf">
	<section class="opponent">
		<p class="fwb"><?=$character['name']?></p>
		<p>
			<?php if($stage['lives']['character'] > 0) : ?>
			<?php foreach(range(1,$stage['lives']['character']) as $i) : ?>
			<i class="fa fa-heart fa-fw"></i>
			<?php endforeach ?>
			<?php else : ?>
			<?=_('lost')?>
			<?php endif ?>
		</p>
	</section>
	<section class="opponent">
		<p class="fwb"><?=$fight['bossname']?></p>
		<p>
			<?php if($stage['lives']['boss'] > 0) : ?>
			<?php foreach(range(1,$stage['lives']['boss']) as $i) : ?>
			<i class="fa fa-heart fa-fw"></i>
			<?php endforeach ?>
			<?php else : ?>
			<b><?=_('lost')?></b>
			<?php endif ?>
		</p>
	</section>
</div>
<?php endforeach ?>
