<h1><?=_('Introduction')?></h1>
<p>Ein Projekt zum Thema „Gamification im Lehrumfeld“ – basierend auf <a href="http://legende-von-zyren.de">Die Legende von Zyren</a>.</p>

<?php if(is_null($userId)) : ?>
<h2><?=_('Login')?></h2>
<form method="post" action="<?=$linker->link(array('users','login'))?>">
	<fieldset>
		<label for="username"><?=_('Username')?>:</label>
		<input name="username" type="text" placeholder="<?=_('Username')?>" title="<?=_('Username')?>" required="required" /><br />
		<label for="password"><?=_('Password')?>:</label>
		<input name="password" type="password" placeholder="<?=_('Password')?>" title="<?=_('Password')?>" required="required" /><br />
	</fieldset>
	<input type="submit" name="login" value="<?=_('Login')?>" />
	<?=_('or')?> <a href="<?=$linker->link(array('users','register'))?>"><?=_('register yourself')?></a>
</form>
<?php endif ?>

<h2>Entwickler</h2>
<ul>
	<li itemscope itemtype="http://schema.org/Person">
		<span itemprop="name">Oliver Hanraths</span><br />
		Programmierung und Datenbank
	</li>
	<li itemscope itemtype="http://schema.org/Person">
		<span itemprop="name">Daniel Miskovic</span><br />
		GUI und Webdesign
	</li>
	<li itemscope itemtype="http://schema.org/Person">
		<span itemprop="name">Kathrin Knautz</span>, <span itemprop="honorificSuffix">B.A., M.A.</span><br />
		Leitung
	</li>
</ul>

<p itemscope itemtype="http://schema.org/CollegeOrUniversity">
	<a itemprop="name" href="http://www.uni-duesseldorf.de">Heinrich-Heine-Universität Düsseldorf</a>
</p>
