<div class="moodpic">
    <?php if(!is_null($seminary) && array_key_exists($seminaryMoodpicIndex, $seminary) && !is_null($seminary[$seminaryMoodpicIndex])) : ?>
    <img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url'],$agentName))?>">
    <?php elseif(!is_null($seminary) && !is_null($seminary['seminarymedia_id'])) : ?>
    <img src="<?=$linker->link(array('media','seminarymoodpic',$seminary['url']))?>">
    <?php else : ?>
    <img src="<?=$linker->link(array('grafics','questlab.jpg'))?>" />
    <?php endif ?>
</div>
