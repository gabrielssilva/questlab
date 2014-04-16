<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2><i class="fa fa-trophy fa-fw"></i><?=_('Achievements')?></h2>

<div class="cf">
	<section class="rare">
		<h3>Die seltensten Errungenschaften</h3>
		<ol>
			<li class="cf">
				<img src="http://legende-von-zyren.de/img/achieve/36b.jpg" />
				<p class="fwb">Des Königs neue Kleider</p>
				<p><small>wurde erst 5 mal gefunden</small></p>
			</li>
			<li class="cf">
				<img src="http://legende-von-zyren.de/img/achieve/1b.jpg" />
				<p class="fwb">Sein oder Sterben</p>
				<p><small>wurde erst 7 mal gefunden</small></p>
			</li>
			<li class="cf">
				<img src="http://legende-von-zyren.de/img/achieve/35b.jpg" />
				<p class="fwb">Hungersnot? Ohne mich.</p>
				<p><small>wurde erst 9 mal gefunden</small></p>
			</li>
		</ol>
	</section>

	<section class="rare hunter">
	<h3>Die erfolgreichsten Sammler</h3>
		<ol>
			<li class="cf">
				<img src="http://zyren.inf-d.de/media/seminary/Die-Legende-von-Zyren/Mensch01-Portrait" />
				<p class="fwb">VHS</p>
				<p><small>hat 15 Errungenschaften gefunden</small></p>
			</li>
			<li class="cf">
				<img src="http://zyren.inf-d.de/media/seminary/Die-Legende-von-Zyren/Mensch01-Portrait" />
				<p class="fwb">Betamax</p>
				<p><small>hat 14 Errungenschaften gefunden</small></p>
			</li>
			<li class="cf">
				<img src="http://zyren.inf-d.de/media/seminary/Die-Legende-von-Zyren/Mensch01-Portrait" />
				<p class="fwb">Laserdisc</p>
				<p><small>hat 12 Errungenschaften gefunden</small></p>
			</li>
		</ol>
	</section>
</div>

<h3>Persönlicher Fortschritt: 75%</h3>
<p><b>12. Platz:</b> Du hast bislang 13 von insgesamt 75 Errungenschaften erreicht.</p>
<ul class="achmnts">
	<li class="cf">
		<img src="http://legende-von-zyren.de/img/achieve/36b.jpg" />
		<p class="fwb">Freigeschaltetes Achievement<span class="unlcked">erreicht am 17.06.104</span></p>
		<p class="desc">Das Bild ist entsprechend farbig, ein eventueller Fortschrittsbalken mit 100% soll entfallen.</p>
	</li>
	<?php foreach($achievements as &$achievement) : ?>
	<li class="cf">
		<?php if(!is_null($achievement[$achievement['media_index']])) : ?>
		<img src="<?=$linker->link(array('media','achievement',$seminary['url'],$achievement['url']))?>" />
		<?php endif ?>
		<p class="fwb"><?=(!$achievement['hidden']) ? $achievement['title'] : _('Secret Achievement')?><span class="unlcked">erreicht am 17.06.104</span></p>
		<?php if(!$achievement['hidden']) : ?>
		<p class="desc"><?=\hhu\z\Utils::t($achievement['description'])?></p>
		<?php else : ?>
		<p class="desc"><?=_('Continue playing to unlock this secret Achievement')?></p>
		<?php endif ?>
		<?php if(array_key_exists('characterProgress', $achievement)) : ?>
		<div class="prgrss cf">
			<div class="xpbar">
				<span style="width:<?=round($achievement['characterProgress']*100)?>%"></span>
			</div>
			<p class="xpnumeric"><?=round($achievement['characterProgress']*100)?>%</p>
		</div>
		<?php endif ?>
	</li>
	<?php endforeach?>
</ul>
