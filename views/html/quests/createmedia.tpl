<?php if(!is_null($seminary['seminarymedia_id'])) : ?>
<div class="moodpic">
	<img src="<?=$linker->link(array('media','seminaryheader',$seminary['url']))?>" />
</div>
<?php endif ?>
<h1><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></h1>
<h2>Create Questsmedia</h2>

<?php if(!is_null($mediaid)) :?>
<p>New mediaId: <?=var_dump($mediaid)?></p>
<?php endif ?>
<?php if(!empty($error)) :?>
<p>Error: <?=$error?></p>
<?php endif ?>
<form method="post" enctype="multipart/form-data">
	<input type="text" name="description" placeholder="Description" /><br />
	<input type="file" name="file" required="required" /><br />
	<input type="submit" name="submit" value="create" />
</form>
