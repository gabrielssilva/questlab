<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8" />
    <title><?=(isset($title)) ? $title : \nre\configs\AppConfig::$app['name']?></title>
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <link href="http://fonts.googleapis.com/css?family=Open+Sans:400,700" rel="stylesheet" type="text/css">
    <link href="//netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css" rel="stylesheet">
    <link rel="stylesheet" type="text/css" href="<?=$linker->link(array('css','desktop.css'))?>" media="all" />
    <link rel="stylesheet" type="text/css" href="<?=$linker->link(array('css','ol.css'))?>" media="all" />
    <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js"></script>
    <script type="text/javascript" src="<?=$linker->link(array('js','jquery-ui.min.js'))?>"></script>
    <script type="text/javascript" src="<?=$linker->link(array('js','jquery.nicescroll.min.js'))?>"></script>
    <script type="text/javascript" src="<?=$linker->link(array('js','ol.js'))?>"></script>
    <script type="text/javascript">
    $(document).ready(
    function() {
        $(".qtextbox").niceScroll({autohidemode:false,cursorcolor:"#c2beb9"});
    }
    );
    </script>
    <script src="/js/imagelightbox.min.js"></script>
    <script type="text/javascript">
    $( function()
    {
        $( 'a' ).imageLightbox();
    });
    </script>
    <script type="text/javascript">
    $(document).ready(function(){
        setTimeout(function() { $(".notify").fadeOut(1500); }, 5000);
        $('body').click(function() { $(".notify").fadeOut(200); });
    });
    </script>
    <!--[if lt IE 9]>
    <script type="text/javascript" src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
    <script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/respond.js/1.4.2/respond.js"></script>
    <![endif]-->
    <script type="text/javascript" src="<?=$linker->link(array('js','misc.js'))?>"></script>
    <script type="text/javascript" src="<?=$linker->link(array('js','notification.js'))?>"></script>
    <script type="text/javascript" src="<?=$linker->link(array('js','dnd.js'))?>"></script>
    <meta name="description" content="">
    <meta name="robots" content="noindex,follow">
    <link rel="icon" href="favicon.ico" type="image/x-icon">
</head>

<body>
    <header>
        <nav class="cf">
            <input type="checkbox" id="toggle">
            <label for="toggle" class="toggle" onclick><i class="fa fa-bars"></i>Menü</label>
            <div id="home">
                <a href="<?=$linker->link(array(), 0, true, array(), true)?>"><?=\nre\configs\AppConfig::$app['name']?></a>
                <?php if(!empty($mailcontact)) : ?>
                <a class="contact" href="mailto:<?=$mailcontact?>"><?=$mailcontact?></a>
                <?php endif ?>
            </div>
            <?php if(!is_null($loggedUser)) : ?>
            <div id="profile" class="cf">
                <?php if(!is_null($loggedCharacter)) : ?>
                <a href="<?=$linker->link(array('characters','character',$loggedSeminary['url'],$loggedCharacter['url']))?>">
                    <?php if(array_key_exists('avatar', $loggedCharacter) && !is_null($loggedCharacter['avatar']['small_avatarpicture_id'])) : ?>
                    <img src="<?=$linker->link(array('media','avatar',$loggedSeminary['url'],$loggedCharacter['charactertype_url'],$loggedCharacter['xplevel']['level'],'portrait'))?>" />
                    <?php endif ?>
                    <span><?=$loggedCharacter['name']?></span><span class="lvlname">Level <?=$loggedCharacter['xplevel']['level']?></span>
                </a>
                <?php else : ?>
                <a href="<?=$linker->link(array('users',$loggedUser['url']))?>"><?=$loggedUser['username']?><span class="lvlname"><?=$loggedUser['prename']?> <?=$loggedUser['surname']?></span></a>
                <?php endif ?>
            </div>
            <?php endif ?>
            <ul id="mainmenu">
                <?=$menu?>
            </ul>
        </nav>
    </header>
    <article class="wrap">
        <?php if(count($notifications) > 0) : ?>
        <ul class="notify">
            <?php foreach($notifications as &$notification) : ?>
            <?php if($notification['type'] == \hhu\z\controllers\components\NotificationComponent::TYPE_ACHIEVEMENT) : ?>
            <li class="cf">
                <?php if(!is_null($notification['image'])) : ?>
                <img src="<?=$notification['image']?>" />
                <?php endif ?>
                <p class="announce"><i class="fa fa-trophy fa-fw"></i><?=_('Achievement')?>:<i class="fa fa-times fa-fw"></i></p>
                <?php if(!is_null($notification['link'])) : ?>
                <p class="fwb"><a href="<?=$notification['link']?>"><?=$notification['message']?></a></p>
                <?php else : ?>
                <p class="fwb"><?=$notification['message']?></p>
                <?php endif ?>
            </li>
            <?php else : ?>
            <li class="cf">
                <img src="<?=$linker->link(array('grafics','lvlup.jpg'))?>">
                <p class="announce"><i class="fa fa-arrow-up fa-fw"></i><?=_('Level-up')?>:<i class="fa fa-times fa-fw"></i></p>
                <?php if(!is_null($notification['link'])) : ?>
                <p class="fwb"><a href="<?=$notification['link']?>"><?=sprintf(_('You have reached level %d'), $notification['message'])?></a></p>
                <?php else : ?>
                <p class="fwb"><?=sprintf(_('You have reached level %d'), $notification['message'])?></p>
                <?php endif ?>
            </li>
            <?php endif ?>
            <?php endforeach ?>
        </ul>
        <audio id="notify-sound" preload="auto" src="<?=$linker->link(array('sounds','notification.mp3'))?>"></audio>
        <?php endif ?>
        <?=$intermediate?>
    </article>
    <aside>
        <?php if(!is_null($loggedCharacter) && count($loggedCharacter['characterroles']) > 0) : ?>
        <?=$seminarybar?>
        <?php endif ?>
    </aside>
    <script type="text/javascript">
        var _paq = _paq || [];
        _paq.push(['trackPageView']);
        _paq.push(['enableLinkTracking']);
        (function() {
            var u=(("https:" == document.location.protocol) ? "https" : "http") + "://" + document.location.hostname + "/analytics/";
            _paq.push(['setTrackerUrl', u+'piwik.php']);
            _paq.push(['setSiteId', 1]);
            var d=document, g=d.createElement('script'), s=d.getElementsByTagName('script')[0]; g.type='text/javascript';
            g.defer=true; g.async=true; g.src=u+'piwik.js'; s.parentNode.insertBefore(g,s);
        })();
    </script>
    <noscript><p><img src="/analytics/piwik.php?idsite=1" style="border:0;" alt="" /></p></noscript>
</body>

</html>
