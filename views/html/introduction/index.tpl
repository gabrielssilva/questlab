<h1><?=_('Introduction')?></h1>
<?php if(is_null($userId)) : ?>
<h2><?=_('Login')?></h2>
<form method="post" action="<?=$linker->link(array('users','login'))?>" class="logreg">
	<fieldset>
		<label for="username"><?=_('Username')?>:</label>
		<input name="username" type="text" placeholder="<?=_('Username')?>" title="<?=_('Username')?>" required="required" autofocus="autofocus" /><br />
		<label for="password"><?=_('Password')?>:</label>
		<input name="password" type="password" placeholder="<?=_('Password')?>" title="<?=_('Password')?>" required="required" /><br />
	</fieldset>
	<input type="submit" name="login" class="cta" value="<?=_('Login')?>" />
	<?=_('or')?> <a href="<?=$linker->link(array('users','register'))?>"><?=_('register yourself')?></a>
</form>
<?php endif ?>

<p itemscope itemtype="http://schema.org/CollegeOrUniversity">Bereits im Sommersemester 2013 wurde das Projekt „Die Legende von Zyren“ unterstützt durch den Lehrförderungsfond der <a itemprop="name" href="http://www.uni-duesseldorf.de">Heinrich-Heine-Universität Düsseldorf</a> ins Leben gerufen, um die Inhalte der Vorlesung „Wissensrepräsentation“ den Studierenden des Faches Informationswissenschaft mit Hilfe von Spielelementen und -modellen zu vermitteln. Die innovative Lernumgebung besteht aus einem virtuellen Textadventure, dass über eine webbasierte Plattform zugänglich ist und realen Spielen in einer Präsenzveranstaltung, in denen die Studierenden unmittelbar in das Abenteuer eintauchen und in Teams spielerisch gegeneinander antreten.</p>
<p>Auf der Plattform spielt sich jeder der Studierenden mit seinem virtuellen Avatar durch das Reich von Zyren und erlernt und vertieft auf spielerische Weise die Inhalte der Vorlesung „Wissensrepräsentation“, die in Form von Herausforderungen oder Rätseln in das Abenteuer eingebunden wurden und über den Fortlauf und den Erfolg des Spiels entscheiden.</p>
<p>In der zusätzlichen Präsenzveranstaltung tauchen die Studierenden direkt in das Abenteuer ein und die vertiefen die Inhalte spielerisch. Hier schließen sich die Studierenden in Teams (Gilden) zusammen, müssen eigenverantwortlich Lerninhalte erarbeiten, Probleme lösen und in speziellen Gildenaufgaben gegen andere Teams antreten, um ihr kollaborativ erarbeitetes Wissen auf die Probe zu stellen.</p>
<p>Für jede erfolgreiche absolvierte Herausforderung auf der Plattform oder in der Übung erhalten die Studierenden Erfahrungspunkte und Belohnungen.</p>
<p>Um das Konzept auch anderen Fachbereichen und Lehrveranstaltungen zugänglich zu machen, wurde im Frühjahr 2014 das Projekt Questlab (Arbeitstitel „The Legend of Z“) gestartet um das Konzept zu generalisieren. Lehrende können die Plattform nun nutzen um eigene Aufgaben (Quests) zu kreieren und hochzuladen und sie optional in eine Geschichte einzubinden, die sie selbst gestalten können. Zudem wurde das Responsive Design überarbeitet und bietet nun optimalen Zugriff auf die Plattform über alle mobilen Endgeräte.</p>

<h2>Die Legende von Zyren in der Presse</h2>
<ul>
	<li><a href="http://www.uni-duesseldorf.de/home/nc/startseite/news-detailansicht/article/erstmals-an-einer-deutschen-hochschule-gamification-und-interaktive-textadventures.html">Pressemitteilung der Heinrich-Heine-Universität Düsseldorf vom 12.7.13</a></li>
	<li><a href="">Artikel in der Rheinischen Post (Print-Version) vom 23.7.13</a></li>
	<li><a href="http://www.welt.de/regionales/duesseldorf/article120340979/Mit-Computer-spielend-zum-Uni-Abschluss.html">Artikel in der Zeitschrift Welt (Print- und Online-Version) vom 24.9.13</a></li>
	<li><a href="http://www.heise.de/tp/artikel/40/40838/1.html">Artikel auf Heise Online</a></li>
	<li><a href="http://www.faz.net/aktuell/beruf-chance/fantasy-an-der-uni-spielend-durchs-studium-12735331.html">Artikel in der Frankfurter Allgemeinen Zeitung</a></li>
	<li><a href="http://www.wdr5.de/sendungen/leonardo/rollenspieluniduesseldorf100.html">Radiobeitrag im Deutschlandfunk vom 5.8.13</a></li>
	<li>Diverse Beiträge in Blogs, Wikis und anderen sozialen Plattformen, wie beispielweise <a href="http://www.mittelstandswiki.de/wissen/Gamification,_Teil_1">www.mittelstandswiki.de</a> oder <a href="http://www.scoop.it/t/digitale-spiel-und-lernwelten/p/4005676096/2013/08/05/die-legende-von-zyren">www.scoop.it</a></li>
	<li>Teilnahme am Finale des studentischen Video-Wettbewerb der DINI „Study Fiction – Videoclips zur Zukunft von Studium und Lehre“ mit dem Beitrag <a href="http://dini.de/wettbewerbe/study-fiction/preisverleihung/">„Always Online – Die Zukunft des Lernens“</a></li>
</ul>

<h2>Das Team</h2>
<h3>Projektleitung:</h3>
<ul>
	<li itemscope itemtype="http://schema.org/Person"><span itemprop="name">Kathrin Knautz</span></li>
</ul>
<h3>Entwicklung und Evaluation des Prototypens:</h3>
<ul>
	<li itemscope itemtype="http://schema.org/Person"><span itemprop="name">Lisa Orszullok</span></li>
	<li itemscope itemtype="http://schema.org/Person"><span itemprop="name">Simone Soubusta</span></li>
	<li itemscope itemtype="http://schema.org/Person"><span itemprop="name">Julia Göretz</span></li>
	<li itemscope itemtype="http://schema.org/Person"><span itemprop="name">Anja Wintermeyer</span></li>
</ul>
<h3>Entwicklung „The Legend of Z“:</h3>
<ul>
	<li itemscope itemtype="http://schema.org/Person"><span itemprop="name">Oliver Hanraths</span></li>
	<li itemscope itemtype="http://schema.org/Person"><span itemprop="name">Daniel Miskovic</span></li>
</ul>
