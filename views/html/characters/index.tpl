<?=$moodpic?>
<ul class="breadcrumbs">
    <li><a href="<?=$linker->link(array('seminaries',$seminary['url']))?>"><?=$seminary['title']?></a></li>
</ul>
<h1><?=_('Characters')?></h1>

<?php if(count(array_intersect(array('admin', 'moderator'), \hhu\z\controllers\SeminaryController::$character['characterroles'])) > 0) : ?>
<nav class="admin">
    <li><a href="<?=$linker->link(array('xplevels','manage',$seminary['url']))?>"><?=_('Manage XP-levels')?></a></li>
    <li><a href="<?=$linker->link(array('charactertypes','index',$seminary['url']))?>"><?=_('Manage Charactertypes')?></a></li>
</nav>
<nav class="admin">
    <li><a href="<?=$linker->link(array('manage',$seminary['url']),1)?>"><?=_('Manage Characters')?></a></li>
</nav>
<?php endif ?>

<form method="get" class="logreg admnqf">
    <fieldset>
        <legend><?=_('Filters')?></legend>
        <small><?=_('Sortorder')?>:</small>
        <select name="sortorder" onchange="this.form.submit();">
            <option value="name" <?php if($sortorder == 'name') : ?>selected="selected"<?php endif ?>><?=_('Character name')?></option>
            <option value="xps" <?php if($sortorder == 'xps') : ?>selected="selected"<?php endif ?>><?=_('XPs')?></option>
            <option value="role" <?php if($sortorder == 'role') : ?>selected="selected"<?php endif ?>><?=_('Role')?></option>
            <option value="created" <?php if($sortorder == 'created') : ?>selected="selected"<?php endif ?>><?=_('Date of registration')?></option>
            <?php foreach($characterfields as &$characterfield) : ?>
            <option value="<?=$characterfield['url']?>" <?php if($sortorder == $characterfield['url']) : ?>selected="selected"<?php endif ?>><?=$characterfield['title']?></option>
            <?php endforeach ?>
        </select>
        <label for="charactername"><?=_('Character name')?>:</label>
        <input id="charactername" type="text" name="charactername" placeholder="<?=_('Character name')?>" value="<?=$charactername?>" />
    </fieldset>
    <input type="submit" value="<?=_('Apply filters')?>" />
</form>

<ul id="characterlist" class="admnql">
    <?php foreach($characters as &$character) : ?>
    <li class="cf">
        <?php if(array_key_exists('avatar', $character) && !is_null($character['avatar']['small_avatarpicture_id'])) : ?>
        <img src="<?=$linker->link(array('media','avatar',$seminary['url'],$character['charactertype_url'],$character['xplevel']['level'],'portrait'))?>">
        <?php endif ?>
        <p><a href="<?=$linker->link(array('characters','character',$seminary['url'],$character['url']))?>"><?=$character['name']?></a><span><?=$character['xps']?> XP</span></p>
        <p><small><a href="<?=$linker->link(array('users','user',$character['user']['url']))?>"><?=$character['user']['username']?></a></small>
        <?php if(in_array('admin', $character['characterroles'])) : ?><small>(<?=_('Admin')?>)</small><?php endif ?>
        <?php if(in_array('moderator', $character['characterroles'])) : ?><small>(<?=_('Moderator')?>)</small><?php endif ?>
        <?php if(in_array('user', $character['characterroles'])) : ?><small>(<?=_('User')?>)</small><?php endif ?>
        </p>
        <?php foreach($character['characterfields'] as &$characterfield) : ?>
        <p class="chrflds"><?=$characterfield['value']?></p>
        <?php endforeach ?>
    </li>
    <?php endforeach ?>
</ul>

<?php if(is_null($all) && ($page*$limit) < $charactersCount) : ?>
<nav class="admin">
    <li><a id="show-more" href="<?=$linker->link(null,3,true,array('page'=>$page+1,'sortorder'=>$sortorder))?>"><?=_('Show more')?></a></li>
    <li><a id="show-all" href="<?=$linker->link('all',3,true,array('sortorder'=>$sortorder))?>"><?=_('Show all')?></a></li>
</nav>
<?php endif ?>

<script>
    var page = 1;
    var request;
    var linkAvatar = "<?=$linker->link(array('media','avatar','SEMINARY','CHARACTERTYPE','XPLEVEL','portrait'))?>";
    var linkCharacter = "<?=$linker->link(array('character','SEMINARY','CHARACTER'),1)?>";
    var linkUser = "<?=$linker->link(array('users','user','USER'))?>";
    var linkPage = "<?=$linker->link(null,3,true,array('page'=>'PAGE','sortorder'=>$sortorder))?>";
    
    $("#show-more").click(function(event) {
        if(request) {
            request.abort();
        }
        
        page++;
        request = $.getJSON(linkPage.replace('PAGE', page), function(data) {
            linkAvatar = linkAvatar.replace('SEMINARY', data['seminary']['url']);
            linkCharacter = linkCharacter.replace('SEMINARY', data['seminary']['url']);
            $.each(data['characters'], function(key, character) {
                var urlAvatar = linkAvatar.replace('CHARACTERTYPE', character['charactertype_url']).replace('XPLEVEL', character['xplevel']['level']);
                var urlCharacter = linkCharacter.replace('CHARACTER', character['url']);
                var urlUser = linkUser.replace('USER', character['user']['url']);
                $("#characterlist").append(
                    "<li class=\"cf\">" +
                    "<img src=\"" + urlAvatar + "\" />" +
                    "<p><a href=\"" + urlCharacter + "\">" + character['name'] + "</a><span>" + character['xps'] + " <?=_('XPs')?></span></p>" +
                    "<p>" + 
                    "<small><a href=\"" + urlUser + "\">" + character['user']['username'] + "</a></small>\n" +
                    (character['characterroles'].length > 0 ? "<small>(" + character['characterroles'].join(', ') + ")</small>" : '') + 
                    "</p>" +
                    "<p class=\"chrflds\">" + $.map(character['characterfields'], function(val, i) {
                        return val['value'];
                    }).join('</p>\n<p class="chrflds">') + "</p>" +
                    "</li>"
                );
            });
            if(data['more']) {
                $("#show-more").attr('href', linkPage.replace('PAGE', page+1));
            }
            else {
                $("#show-more").remove();
                $("#show-all").remove();
            }
        });
        request.fail(function (jqXHR, textStatus, errorThrown) {
            window.location.href = linkPage.replace('PAGE', page);
        });
        
        
        event.preventDefault();
        return false;
    });
</script>
