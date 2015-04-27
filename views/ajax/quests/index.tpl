<?php
	
	foreach($quests as &$quest)
	{
		// Questtype translation
		$questtype = $quest['questtype']['title'];
		switch($quest['questtype']['classname'])
		{
			case null: $questtype = _('Questtype Empty');
			break;
			case 'bossfight': $questtype = _('Questtype bossfight');
			break;
			case 'choiceinput': $questtype = _('Questtype choiceinput');
			break;
			case 'crossword': $questtype = _('Questtype crossword');
			break;
			case 'dragndrop': $questtype = _('Questtype dragndrop');
			break;
			case 'multiplechoice': $questtype = _('Questtype multiplechoice');
			break;
			case 'submit': $questtype = _('Questtype submit');
			break;
			case 'textinput': $questtype = _('Questtype textinput');
			break;
		}
		$quest['questtype']['title'] = $questtype;
	
		// XPs translation
		$quest['xps'] = sprintf(_('%d XPs'), $quest['xps']);
	}
	
?>
<?=json_encode(array(
	'seminary'	=> $seminary,
	'quests'	=> $quests,
	'more'		=> (($page*$limit) < $questsCount)
))?>
