<?=$moodpic?>
<?=$questgroupshierarchypath?>
<h1><?=$quest['title']?> (<?=_('Submissions')?>)</h1>

<section>
    <h1><?=_('submitted')?></h1>
    <ol class="cglist">
        <?php foreach($submittedSubmissionCharacters as &$character) : ?>
        <li>
            <a href="<?=$linker->link(array('submission',$seminary['url'],$questgroup['url'],$quest['url'],$character['url']),1)?>"><?=$character['name']?></a>
            <span class="xp"><small><?=sprintf(_('submitted at %s on %s h'), $dateFormatter->format(new \DateTime($character['submission_created'])), $timeFormatter->format(new \DateTime($character['submission_created'])))?></small></span>
        </li>
        <?php endforeach?>
    </ol>
    
    <h1><?=_('unsolved')?></h1>
    <ol class="cglist">
        <?php foreach($unsolvedSubmissionCharacters as &$character) : ?>
        <li>
            <a href="<?=$linker->link(array('submission',$seminary['url'],$questgroup['url'],$quest['url'],$character['url']),1)?>"><?=$character['name']?></a>
            <span class="xp"><small><?=sprintf(_('submitted at %s on %s h'), $dateFormatter->format(new \DateTime($character['submission_created'])), $timeFormatter->format(new \DateTime($character['submission_created'])))?></small></span>
        </li>
        <?php endforeach?>
    </ol>

    <h1><?=_('solved')?></h1>
    <ol class="cglist">
        <?php foreach($solvedSubmissionCharacters as &$character) : ?>
        <li>
            <a href="<?=$linker->link(array('submission',$seminary['url'],$questgroup['url'],$quest['url'],$character['url']),1)?>"><?=$character['name']?></a>
            <span class="xp"><small><?=sprintf(_('submitted at %s on %s h'), $dateFormatter->format(new \DateTime($character['submission_created'])), $timeFormatter->format(new \DateTime($character['submission_created'])))?></small></span>
        </li>
        <?php endforeach?>
    </ol>
</section>
